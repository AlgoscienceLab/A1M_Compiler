# Change Log

All notable changes to the "Algo Language Support" extension will be documented in this file.

## [1.5.0] - 2025-11-16

### Added
- **#[nomain] directive support**: Add `#[nomain]` at the top of your file to suppress "no main found" warnings
- Syntax highlighting for `#[nomain]` directive
- Directive validation in first 10 lines of file

### Features
- Files with `#[nomain]` can be used for libraries or modules without a main() function
- Diagnostic validation now respects the directive and won't show main-related warnings

## [1.4.0] - 2025-11-16

### Fixed
- **Git Bash Detection**: Extension now properly detects Git Bash terminals on Windows and generates Bash commands instead of PowerShell commands
- **Path Conversion**: Automatically converts Windows paths (C:\path) to Git Bash format (/c/path) when needed
- **MSYS2 Integration**: Uses full paths to MSYS2-installed executables for better compatibility

### Changed
- Shell detection based on VS Code terminal profile settings
- Enhanced terminal output with shell type information

## [1.3.0] - 2025-11-16

### Added
- **Cross-Platform Support**
  - Full Windows support via MSYS2/MinGW64
  - Full macOS support (Intel & Apple Silicon)
  - Enhanced Linux support
  - Auto-detection of platform and executable extensions (.exe on Windows)
  - Platform-specific terminal commands (PowerShell for Windows, bash/zsh for Unix)
  - Smart executable path resolution (workspace-local or global)
  
### Improved
- **Executable Detection**
  - Auto-detects `.exe` extension on Windows
  - Searches workspace-local builds first, then global PATH
  - Falls back gracefully if tools not found
  - Configuration settings now optional (auto-detection preferred)
  
- **Terminal Integration**
  - Windows: PowerShell-compatible commands with proper error handling
  - macOS/Linux: Unix shell commands with proper quoting
  - Cross-platform output formatting
  - Platform information in output channel

### Changed
- Default configuration paths now empty (uses auto-detection)
- Extension description mentions cross-platform support
- Terminal commands use platform-appropriate syntax

### Documentation
- Added README-CROSSPLATFORM.md with platform-specific instructions
- Updated package.json with clearer configuration descriptions

## [1.2.0] - 2025-11-13

### Added
- **Float and Double Type Support - Complete**
  - Added `float` and `double` to autocomplete suggestions
  - Added `short` and `long` to type suggestions
  - Full IntelliSense support for floating-point types
  - Type hints show "Algo type" for all data types

### Fixed
- Autocomplete now properly suggests `float` and `double` keywords
- Type parameter completion includes all numeric types

## [1.1.0] - 2025-11-13

### Added
- **Float and Double Type Support**
  - Added `float` and `double` keywords to syntax highlighting
  - Support for floating-point literals: `3.14f`, `2.718`
  - Support for scientific notation: `1.23e10f`, `4.56e-5`
  - Float suffix recognition: `f`, `F`
  - Double suffix recognition: `d`, `D`
  - Updated number patterns to recognize decimal points and exponents

### Improved
- Enhanced syntax highlighting for numeric literals
- Better type keyword recognition
- Updated language grammar for floating-point numbers

### Compiler Updates
- Full lexer support for float/double literals
- Parser support for float/double types in:
  - Variable declarations: `let x: float = 3.14f;`
  - Function parameters: `func foo(x: float) -> double`
  - Function return types
  - sizeof operator
- Code generation for IEEE 754 float (32-bit) and double (64-bit)

## [1.0.3] - 2025-11-10

### Added
- All 36 C keywords support
- Compound assignment operators (+=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=)
- Increment/Decrement operators (++, --)
- Ternary operator (?:)
- sizeof operator
- do-while loops
- switch-case statements
- goto and labels
- Enum support

### Improved
- Complete operator precedence handling
- Enhanced control flow structures
- Better error messages

## [1.0.2] - 2025-11-01

### Added
- Basic syntax highlighting
- Code diagnostics
- Run command integration

### Fixed
- Keyword recognition issues
- Comment highlighting

## [1.0.1] - 2025-10-15

### Added
- Initial release
- Basic Algo language support
- Syntax highlighting for keywords, strings, comments
- File association for .algo files

## [1.0.0] - 2025-10-01

### Added
- Initial release of Algo Language Support extension
