import * as vscode from 'vscode';
import * as path from 'path';
import * as fs from 'fs';
import * as os from 'os';
import { spawn } from 'child_process';

let diagnosticCollection: vscode.DiagnosticCollection;
let outputChannel: vscode.OutputChannel;

export function activate(context: vscode.ExtensionContext) {
    console.log('Algo language extension is now active');

    // Create diagnostic collection for error reporting
    diagnosticCollection = vscode.languages.createDiagnosticCollection('algo');
    context.subscriptions.push(diagnosticCollection);

    // Create output channel
    outputChannel = vscode.window.createOutputChannel('Algo');
    context.subscriptions.push(outputChannel);

    // Register commands
    context.subscriptions.push(
        vscode.commands.registerCommand('algo.run', () => runAlgoProgram())
    );

    context.subscriptions.push(
        vscode.commands.registerCommand('algo.compile', () => compileAlgoProgram())
    );

    // Register code lens provider for run buttons
    context.subscriptions.push(
        vscode.languages.registerCodeLensProvider('algo', new AlgoCodeLensProvider())
    );

    // Register completion provider for code suggestions
    context.subscriptions.push(
        vscode.languages.registerCompletionItemProvider('algo', new AlgoCompletionProvider(), '.', ':')
    );

    // Watch for document changes to update diagnostics
    context.subscriptions.push(
        vscode.workspace.onDidChangeTextDocument(event => {
            if (event.document.languageId === 'algo') {
                validateDocument(event.document);
            }
        })
    );

    context.subscriptions.push(
        vscode.workspace.onDidOpenTextDocument(document => {
            if (document.languageId === 'algo') {
                validateDocument(document);
            }
        })
    );

    context.subscriptions.push(
        vscode.workspace.onDidSaveTextDocument(document => {
            if (document.languageId === 'algo') {
                validateDocument(document);
            }
        })
    );

    // Validate all open algo documents
    vscode.workspace.textDocuments.forEach(document => {
        if (document.languageId === 'algo') {
            validateDocument(document);
        }
    });
}

export function deactivate() {
    if (diagnosticCollection) {
        diagnosticCollection.dispose();
    }
    if (outputChannel) {
        outputChannel.dispose();
    }
}

// Code Lens Provider - adds run button above main()
class AlgoCodeLensProvider implements vscode.CodeLensProvider {
    provideCodeLenses(document: vscode.TextDocument): vscode.CodeLens[] {
        const codeLenses: vscode.CodeLens[] = [];
        const text = document.getText();
        const lines = text.split('\n');

        for (let i = 0; i < lines.length; i++) {
            const line = lines[i].trim();
            // Look for main function definition
            if (line.match(/func\s+main\s*\(\s*\)\s*->\s*void/)) {
                const range = new vscode.Range(i, 0, i, line.length);
                
                // Run button
                const runLens = new vscode.CodeLens(range, {
                    title: "▶ Run",
                    command: 'algo.run',
                    tooltip: 'Compile and run this Algo program'
                });
                
                codeLenses.push(runLens);
            }
        }

        return codeLenses;
    }
}

// Completion Provider - code suggestions
class AlgoCompletionProvider implements vscode.CompletionItemProvider {
    provideCompletionItems(document: vscode.TextDocument, position: vscode.Position): vscode.CompletionItem[] {
        const items: vscode.CompletionItem[] = [];

        // Keywords
        const keywords = ['func', 'let', 'if', 'else', 'while', 'for', 'return', 'break', 'continue', 
                         'switch', 'case', 'default', 'goto', 'enum', 'struct', 'typedef', 'sizeof'];
        keywords.forEach(kw => {
            const item = new vscode.CompletionItem(kw, vscode.CompletionItemKind.Keyword);
            item.detail = 'Algo keyword';
            items.push(item);
        });

        // Types
        const types = ['void', 'int', 'char', 'bool', 'float', 'double', 'i64', 'u64', 'short', 'long'];
        types.forEach(type => {
            const item = new vscode.CompletionItem(type, vscode.CompletionItemKind.TypeParameter);
            item.detail = 'Algo type';
            items.push(item);
        });

        // Built-in functions
        const builtins = [
            { name: 'print', detail: 'print(value) - Print value to output', snippet: 'print($1)' },
            { name: 'exit', detail: 'exit(code) - Exit program', snippet: 'exit($1)' }
        ];
        builtins.forEach(fn => {
            const item = new vscode.CompletionItem(fn.name, vscode.CompletionItemKind.Function);
            item.detail = fn.detail;
            item.insertText = new vscode.SnippetString(fn.snippet);
            items.push(item);
        });

        // Function template
        const funcSnippet = new vscode.CompletionItem('func', vscode.CompletionItemKind.Snippet);
        funcSnippet.insertText = new vscode.SnippetString('func ${1:name}(${2:param}: ${3:int}) -> ${4:void} {\n\t$0\n}');
        funcSnippet.detail = 'Function template';
        funcSnippet.documentation = 'Create a new function';
        items.push(funcSnippet);

        // Main function template
        const mainSnippet = new vscode.CompletionItem('main', vscode.CompletionItemKind.Snippet);
        mainSnippet.insertText = new vscode.SnippetString('func main() -> void {\n\t$0\n}');
        mainSnippet.detail = 'Main function template';
        mainSnippet.documentation = 'Create main entry point';
        items.push(mainSnippet);

        return items;
    }
}

// Helper function to get executable extension based on platform
function getExeExtension(): string {
    return os.platform() === 'win32' ? '.exe' : '';
}

// Helper function to find compiler path (global or local)
function getCompilerPath(workspacePath?: string): string {
    const exeExt = getExeExtension();
    const baseName = 'algo-compiler';
    
    // If workspace path provided, check for local build
    if (workspacePath) {
        const localPath = path.join(workspacePath, 'compiler', baseName + exeExt);
        if (fs.existsSync(localPath)) {
            return localPath;
        }
        // Try without extension (for backward compatibility)
        const localPathNoExt = path.join(workspacePath, 'compiler', baseName);
        if (fs.existsSync(localPathNoExt)) {
            return localPathNoExt;
        }
    }
    
    // If the user has specified a path in settings, use it
    const config = vscode.workspace.getConfiguration('algo');
    const configured = config.get<string>('compilerPath');
    if (configured && configured.trim().length > 0) {
        return configured.trim();
    }

    // Check MSYS2 installation on Windows
    if (os.platform() === 'win32') {
        const msys2Path = 'C:\\msys64\\usr\\local\\bin\\' + baseName + exeExt;
        if (fs.existsSync(msys2Path)) {
            return msys2Path;
        }
        // Check Program Files installation
        const programFiles = process.env['ProgramFiles'] || 'C:\\Program Files';
        const programPath = path.join(programFiles, 'A1M_Compiler', 'bin', baseName + exeExt);
        if (fs.existsSync(programPath)) {
            return programPath;
        }
        // Check user-local bin (WSL/Git Bash style or custom path)
        const userLocal = path.join(os.homedir(), '.local', 'bin', baseName + exeExt);
        if (fs.existsSync(userLocal)) {
            return userLocal;
        }
        // Also check APPDATA/.local/bin which some install scripts may use
        const appdataLocal = process.env['APPDATA'] ? path.join(process.env['APPDATA'] || '', '.local', 'bin', baseName + exeExt) : '';
        if (appdataLocal && fs.existsSync(appdataLocal)) {
            return appdataLocal;
        }
    }
    
    // Default to global (assumes it's in PATH)
    // On Windows, shell will find .exe automatically
    return baseName + exeExt;
}

function getAssemblerPath(workspacePath?: string): string {
    const exeExt = getExeExtension();
    const baseName = 'a1m-asm';
    
    if (workspacePath) {
        const localPath = path.join(workspacePath, 'assembler', baseName + exeExt);
        if (fs.existsSync(localPath)) {
            return localPath;
        }
        // Try without extension (for backward compatibility)
        const localPathNoExt = path.join(workspacePath, 'assembler', baseName);
        if (fs.existsSync(localPathNoExt)) {
            return localPathNoExt;
        }
    }
    
    const config = vscode.workspace.getConfiguration('algo');
    const configured = config.get<string>('assemblerPath');
    if (configured && configured.trim().length > 0) {
        return configured.trim();
    }

    // Check MSYS2 installation on Windows
    if (os.platform() === 'win32') {
        const msys2Path = 'C:\\msys64\\usr\\local\\bin\\' + baseName + exeExt;
        if (fs.existsSync(msys2Path)) {
            return msys2Path;
        }
        // Program Files
        const programFiles = process.env['ProgramFiles'] || 'C:\\Program Files';
        const programPath = path.join(programFiles, 'A1M_Compiler', 'bin', baseName + exeExt);
        if (fs.existsSync(programPath)) {
            return programPath;
        }
        // user-local
        const userLocal = path.join(os.homedir(), '.local', 'bin', baseName + exeExt);
        if (fs.existsSync(userLocal)) {
            return userLocal;
        }
    }
    
    return baseName + exeExt;
}

function getEmulatorPath(workspacePath?: string): string {
    const exeExt = getExeExtension();
    const baseName = 'a1m-emu';
    
    if (workspacePath) {
        const localPath = path.join(workspacePath, 'emulator', baseName + exeExt);
        if (fs.existsSync(localPath)) {
            return localPath;
        }
        // Try without extension (for backward compatibility)
        const localPathNoExt = path.join(workspacePath, 'emulator', baseName);
        if (fs.existsSync(localPathNoExt)) {
            return localPathNoExt;
        }
    }
    
    const config = vscode.workspace.getConfiguration('algo');
    const configured = config.get<string>('emulatorPath');
    if (configured && configured.trim().length > 0) {
        return configured.trim();
    }

    // Check MSYS2 installation on Windows
    if (os.platform() === 'win32') {
        const msys2Path = 'C:\\msys64\\usr\\local\\bin\\' + baseName + exeExt;
        if (fs.existsSync(msys2Path)) {
            return msys2Path;
        }
        const programFiles = process.env['ProgramFiles'] || 'C:\\Program Files';
        const programPath = path.join(programFiles, 'A1M_Compiler', 'bin', baseName + exeExt);
        if (fs.existsSync(programPath)) {
            return programPath;
        }
        const userLocal = path.join(os.homedir(), '.local', 'bin', baseName + exeExt);
        if (fs.existsSync(userLocal)) {
            return userLocal;
        }
    }
    
    return baseName + exeExt;
}

// Check if document has #[nomain] directive
function hasNoMainDirective(document: vscode.TextDocument): boolean {
    const text = document.getText();
    const lines = text.split('\n');
    
    // Check first 10 lines for #[nomain] directive
    for (let i = 0; i < Math.min(10, lines.length); i++) {
        const line = lines[i].trim();
        if (line === '#[nomain]') {
            return true;
        }
    }
    
    return false;
}

// Validate document and show diagnostics
async function validateDocument(document: vscode.TextDocument) {
    const workspaceFolder = vscode.workspace.getWorkspaceFolder(document.uri);
    
    const workspacePath = workspaceFolder?.uri.fsPath;
    const compilerPath = getCompilerPath(workspacePath);

    const filePath = document.uri.fsPath;
    const diagnostics: vscode.Diagnostic[] = [];
    
    // Check for #[nomain] directive
    const hasNomain = hasNoMainDirective(document);
    
    // Use temp directory in user's home or system temp
    const tempDir = workspacePath ? path.join(workspacePath, '.vscode') : path.join(os.tmpdir(), 'algo-vscode');
    const tempOutput = path.join(tempDir, 'temp.asm');

    // Ensure temp directory exists
    if (!fs.existsSync(tempDir)) {
        fs.mkdirSync(tempDir, { recursive: true });
    }

    const compiler = spawn(compilerPath, [filePath, '-o', tempOutput]);
    let stderr = '';

    compiler.stderr.on('data', (data) => {
        stderr += data.toString();
    });

    compiler.on('close', (code) => {
        if (code !== 0 && stderr.trim()) {
            // Parse error messages - improved regex patterns
            const lines = stderr.split('\n');
            
            for (const errorLine of lines) {
                // Skip empty lines and compilation status messages
                if (!errorLine.trim() || errorLine.includes('Compiling')) {
                    continue;
                }
                
                // Skip "no main found" warning if #[nomain] directive is present
                if (hasNomain && (
                    errorLine.toLowerCase().includes('no main') || 
                    errorLine.toLowerCase().includes('main not found') ||
                    errorLine.toLowerCase().includes('missing main')
                )) {
                    continue;
                }

                // Match different error formats
                // Format 1: [Line X] Error at 'token': message
                let match = errorLine.match(/\[Line\s+(\d+)\]\s+Error\s+at\s+'([^']+)':\s*(.+)/i);
                if (match) {
                    const lineNum = parseInt(match[1]) - 1;
                    const token = match[2];
                    const message = match[3];
                    
                    // Find the token position in the line
                    const lineText = document.lineAt(Math.min(lineNum, document.lineCount - 1)).text;
                    const tokenIndex = lineText.indexOf(token);
                    const startCol = tokenIndex >= 0 ? tokenIndex : 0;
                    const endCol = tokenIndex >= 0 ? tokenIndex + token.length : lineText.length;

                    const diagnostic = new vscode.Diagnostic(
                        new vscode.Range(lineNum, startCol, lineNum, endCol),
                        message,
                        vscode.DiagnosticSeverity.Error
                    );
                    diagnostic.source = 'algo-compiler';
                    diagnostics.push(diagnostic);
                    continue;
                }

                // Format 2: Error: message (line X)
                match = errorLine.match(/Error:\s*(.+?)\s*\(line\s+(\d+)\)/i);
                if (match) {
                    const message = match[1];
                    const lineNum = parseInt(match[2]) - 1;

                    const diagnostic = new vscode.Diagnostic(
                        new vscode.Range(lineNum, 0, lineNum, 1000),
                        message,
                        vscode.DiagnosticSeverity.Error
                    );
                    diagnostic.source = 'algo-compiler';
                    diagnostics.push(diagnostic);
                    continue;
                }

                // Format 3: Generic Error: message
                match = errorLine.match(/Error:\s*(.+)/i);
                if (match) {
                    const message = match[1];
                    
                    // Try to extract line number from message
                    const lineMatch = message.match(/line\s+(\d+)/i);
                    const lineNum = lineMatch ? parseInt(lineMatch[1]) - 1 : 0;

                    const diagnostic = new vscode.Diagnostic(
                        new vscode.Range(lineNum, 0, lineNum, 1000),
                        message,
                        vscode.DiagnosticSeverity.Error
                    );
                    diagnostic.source = 'algo-compiler';
                    diagnostics.push(diagnostic);
                }
            }
        }

        diagnosticCollection.set(document.uri, diagnostics);

        // Clean up temp file
        if (fs.existsSync(tempOutput)) {
            fs.unlinkSync(tempOutput);
        }
    });

    compiler.on('error', (err) => {
        console.error('Failed to run compiler:', err);
    });
}

// Run the Algo program
async function runAlgoProgram() {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== 'algo') {
        vscode.window.showErrorMessage('No Algo file is currently active');
        return;
    }

    const document = editor.document;
    const workspaceFolder = vscode.workspace.getWorkspaceFolder(document.uri);

    // Save the document first
    if (document.isDirty) {
        await document.save();
    }

    const filePath = document.uri.fsPath;
    const workspacePath = workspaceFolder?.uri.fsPath;
    const fileName = path.basename(filePath, '.algo');
    
    // Use global or local tools
    const compilerPath = getCompilerPath(workspacePath);
    const assemblerPath = getAssemblerPath(workspacePath);
    const emulatorPath = getEmulatorPath(workspacePath);
    
    // Output files in same directory as source or in build folder
    const fileDir = path.dirname(filePath);
    const asmFile = path.join(fileDir, `${fileName}.asm`);
    const binFile = path.join(fileDir, `${fileName}.bin`);

    outputChannel.clear();
    outputChannel.show(true);

    // Detect the default shell (Git Bash vs PowerShell on Windows)
    const defaultShell = vscode.workspace.getConfiguration('terminal.integrated.defaultProfile').get<string>('windows') || '';
    const isGitBash = defaultShell.toLowerCase().includes('bash') || defaultShell.toLowerCase().includes('git');
    const isBashTerminal = os.platform() !== 'win32' || isGitBash;

    // Create and show terminal with appropriate shell
    const terminal = vscode.window.createTerminal({
        name: 'Algo Run',
        cwd: workspacePath || path.dirname(filePath)
    });
    terminal.show();

    // Convert paths for Git Bash on Windows (C:\path -> /c/path)
    const convertPath = (p: string): string => {
        if (isBashTerminal && os.platform() === 'win32') {
            // Convert Windows path to Git Bash path: C:\path -> /c/path
            return p.replace(/^([A-Z]):\\/i, '/$1/').replace(/\\/g, '/').toLowerCase();
        }
        return p;
    };

    // Build the command based on shell type
    let command: string;
    
    if (isBashTerminal) {
        // Bash command (Git Bash, Linux, macOS)
        const bashCompiler = convertPath(compilerPath);
        const bashAssembler = convertPath(assemblerPath);
        const bashEmulator = convertPath(emulatorPath);
        const bashFilePath = convertPath(filePath);
        const bashAsmFile = convertPath(asmFile);
        const bashBinFile = convertPath(binFile);
        
        command = `echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" && ` +
                 `echo "▶ Running: ${fileName}.algo" && ` +
                 `echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" && ` +
                 `"${bashCompiler}" "${bashFilePath}" -o "${bashAsmFile}" && ` +
                 `"${bashAssembler}" "${bashAsmFile}" -o "${bashBinFile}" && ` +
                 `echo "" && ` +
                 `echo "📤 Program Output:" && ` +
                 `echo "────────────────────────────────────────────────────────────────────" && ` +
                 `"${bashEmulator}" "${bashBinFile}" && ` +
                 `echo "────────────────────────────────────────────────────────────────────" && ` +
                 `echo "✓ Execution completed"`;
    } else {
        // PowerShell command (Windows)
        command = `Write-Host "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" ; ` +
                 `Write-Host "▶ Running: ${fileName}.algo" ; ` +
                 `Write-Host "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" ; ` +
                 `& "${compilerPath}" "${filePath}" -o "${asmFile}" ; ` +
                 `if ($?) { & "${assemblerPath}" "${asmFile}" -o "${binFile}" } ; ` +
                 `if ($?) { Write-Host "" ; Write-Host "📤 Program Output:" ; ` +
                 `Write-Host "────────────────────────────────────────────────────────────────────" ; ` +
                 `& "${emulatorPath}" "${binFile}" ; ` +
                 `Write-Host "────────────────────────────────────────────────────────────────────" ; ` +
                 `Write-Host "✓ Execution completed" }`;
    }
    
    outputChannel.appendLine(`Running: ${fileName}.algo`);
    outputChannel.appendLine(`Platform: ${os.platform()}`);
    outputChannel.appendLine(`Shell: ${isBashTerminal ? 'Bash' : 'PowerShell'}`);
    outputChannel.appendLine(`Working directory: ${workspacePath || path.dirname(filePath)}`);
    outputChannel.appendLine('');
    
    terminal.sendText(command);
}

// Compile only (no run)
async function compileAlgoProgram() {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== 'algo') {
        vscode.window.showErrorMessage('No Algo file is currently active');
        return;
    }

    const document = editor.document;
    const workspaceFolder = vscode.workspace.getWorkspaceFolder(document.uri);

    // Save the document first
    if (document.isDirty) {
        await document.save();
    }

    const filePath = document.uri.fsPath;
    const workspacePath = workspaceFolder?.uri.fsPath;
    const fileName = path.basename(filePath, '.algo');
    
    const compilerPath = getCompilerPath(workspacePath);
    
    // Output file in same directory as source
    const fileDir = path.dirname(filePath);
    const asmFile = path.join(fileDir, `${fileName}.asm`);

    outputChannel.clear();
    outputChannel.show(true);
    outputChannel.appendLine(`Compiling: ${fileName}.algo`);

    const compiler = spawn(compilerPath, [filePath, '-o', asmFile]);

    compiler.stdout.on('data', (data) => {
        outputChannel.append(data.toString());
    });

    compiler.stderr.on('data', (data) => {
        outputChannel.append(data.toString());
    });

    compiler.on('close', (code) => {
        if (code === 0) {
            outputChannel.appendLine('\n✓ Compilation successful!');
            vscode.window.showInformationMessage(`${fileName}.algo compiled successfully`);
        } else {
            outputChannel.appendLine('\n✗ Compilation failed');
            vscode.window.showErrorMessage(`Failed to compile ${fileName}.algo`);
        }
    });
}
