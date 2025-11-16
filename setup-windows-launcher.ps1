# PowerShell Launcher for MSYS2 Setup
# This script opens MSYS2 MinGW64 and runs the setup

$ErrorActionPreference = "Stop"

Write-Host "========================================" -ForegroundColor Blue
Write-Host "A1M Compiler Setup Launcher" -ForegroundColor Blue
Write-Host "========================================" -ForegroundColor Blue
Write-Host ""

# Find MSYS2 installation
$msys2Paths = @(
    "C:\msys64\msys2_shell.cmd",
    "$env:USERPROFILE\msys64\msys2_shell.cmd"
)

$msys2Shell = $null
foreach ($path in $msys2Paths) {
    if (Test-Path $path) {
        $msys2Shell = $path
        break
    }
}

if (-not $msys2Shell) {
    Write-Host "ERROR: MSYS2 not found" -ForegroundColor Red
    Write-Host ""
    Write-Host "Please install MSYS2 from: https://www.msys2.org/" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Alternative: Open MSYS2 MinGW 64-bit manually and run:" -ForegroundColor Yellow
    Write-Host "  cd /c/Users/shahrear/Downloads/A1M_Compiler" -ForegroundColor White
    Write-Host "  bash setup-windows.sh" -ForegroundColor White
    Write-Host ""
    pause
    exit 1
}

Write-Host "Found MSYS2 at: $msys2Shell" -ForegroundColor Green
Write-Host ""
Write-Host "Opening MSYS2 MinGW 64-bit terminal..." -ForegroundColor Cyan
Write-Host ""
Write-Host "The setup script will:" -ForegroundColor Yellow
Write-Host "  1. Install make (if needed)" -ForegroundColor White
Write-Host "  2. Build all components" -ForegroundColor White
Write-Host "  3. Optionally install globally" -ForegroundColor White
Write-Host "  4. Test the installation" -ForegroundColor White
Write-Host "  5. Optionally build VS Code extension" -ForegroundColor White
Write-Host ""
Write-Host "Press any key to continue..." -ForegroundColor Cyan
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")

# Get current directory in MSYS2 format
$currentDir = (Get-Location).Path
$msys2Dir = $currentDir -replace '^([A-Z]):', '/$1' -replace '\\', '/'
$msys2Dir = $msys2Dir.ToLower()

# Launch MSYS2 MinGW64 with the setup script
$msys2Root = Split-Path $msys2Shell
& $msys2Shell -mingw64 -defterm -no-start -c "cd '$msys2Dir' && bash setup-windows.sh"
