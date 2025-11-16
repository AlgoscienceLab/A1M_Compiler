# A1M Compiler Build Script for Windows PowerShell
# This script builds all components using MSYS2/MinGW64

$ErrorActionPreference = "Stop"

Write-Host "========================================" -ForegroundColor Blue
Write-Host "A1M Compiler Toolchain Build (Windows)" -ForegroundColor Blue
Write-Host "========================================" -ForegroundColor Blue
Write-Host ""

# Check if MSYS2 is installed
$msys2Paths = @(
    "C:\msys64\mingw64\bin",
    "C:\msys64\usr\bin",
    "$env:USERPROFILE\msys64\mingw64\bin",
    "$env:USERPROFILE\msys64\usr\bin"
)

$msys2Found = $false
$msys2Path = ""

foreach ($path in $msys2Paths) {
    if (Test-Path "$path\gcc.exe") {
        $msys2Path = $path
        $msys2Found = $true
        break
    }
}

if (-not $msys2Found) {
    Write-Host "ERROR: MSYS2/MinGW64 not found" -ForegroundColor Red
    Write-Host ""
    Write-Host "Please install MSYS2 from: https://www.msys2.org/" -ForegroundColor Yellow
    Write-Host "Then install MinGW-w64 toolchain:" -ForegroundColor Yellow
    Write-Host "  pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make make" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Or use the build-windows.bat script from MSYS2 MinGW64 terminal" -ForegroundColor Yellow
    exit 1
}

Write-Host "[OK] MSYS2 found at: $msys2Path" -ForegroundColor Green

# Temporarily add MSYS2 to PATH
$env:PATH = "$msys2Path;$env:PATH"

# Verify tools
$makeFound = $false
$makePaths = @("$msys2Path\make.exe", "C:\msys64\usr\bin\make.exe", "$env:USERPROFILE\msys64\usr\bin\make.exe")

foreach ($makePath in $makePaths) {
    if (Test-Path $makePath) {
        $makeFound = $true
        # Add to PATH if not already there
        $makeDir = Split-Path $makePath
        if ($env:PATH -notlike "*$makeDir*") {
            $env:PATH = "$makeDir;$env:PATH"
        }
        break
    }
}

if (-not $makeFound) {
    Write-Host "ERROR: Make not found in MSYS2" -ForegroundColor Red
    Write-Host ""
    Write-Host "Please install make in MSYS2:" -ForegroundColor Yellow
    Write-Host "  1. Open MSYS2 MinGW 64-bit terminal" -ForegroundColor Yellow
    Write-Host "  2. Run: pacman -S make mingw-w64-x86_64-make" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Or use build-windows.bat from MSYS2 terminal" -ForegroundColor Yellow
    exit 1
}

try {
    $gccVersion = & gcc --version 2>&1 | Select-Object -First 1
    Write-Host "[OK] GCC: $gccVersion" -ForegroundColor Green
} catch {
    Write-Host "ERROR: GCC not found in MSYS2" -ForegroundColor Red
    exit 1
}

try {
    $makeVersion = & make --version 2>&1 | Select-Object -First 1
    Write-Host "[OK] Make: $makeVersion" -ForegroundColor Green
} catch {
    Write-Host "ERROR: Make not accessible" -ForegroundColor Red
    Write-Host "Please install: pacman -S make mingw-w64-x86_64-make" -ForegroundColor Yellow
    exit 1
}

Write-Host ""

# Build components
$components = @(
    @{Name="Compiler"; Dir="compiler"; Target="algo-compiler.exe"},
    @{Name="Assembler"; Dir="assembler"; Target="a1m-asm.exe"},
    @{Name="Emulator"; Dir="emulator"; Target="a1m-emu.exe"},
    @{Name="Console"; Dir="gui-console"; Target="a1m-console.exe"}
)

$buildCount = 0
foreach ($component in $components) {
    $buildCount++
    Write-Host "[$buildCount/4] Building $($component.Name)..." -ForegroundColor Cyan
    
    Push-Location $component.Dir
    
    # Clean previous build
    & make clean 2>&1 | Out-Null
    
    # Build
    & make
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "ERROR: Failed to build $($component.Name)" -ForegroundColor Red
        Pop-Location
        exit 1
    }
    
    # Verify executable was created
    if (Test-Path $component.Target) {
        Write-Host "[OK] Built: $($component.Target)" -ForegroundColor Green
    } else {
        Write-Host "ERROR: $($component.Target) not created" -ForegroundColor Red
        Pop-Location
        exit 1
    }
    
    Pop-Location
    Write-Host ""
}

Write-Host "========================================" -ForegroundColor Blue
Write-Host "Build completed successfully!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Blue
Write-Host ""
Write-Host "Built executables:" -ForegroundColor Cyan
Write-Host "  - compiler\algo-compiler.exe" -ForegroundColor White
Write-Host "  - assembler\a1m-asm.exe" -ForegroundColor White
Write-Host "  - emulator\a1m-emu.exe" -ForegroundColor White
Write-Host "  - gui-console\a1m-console.exe" -ForegroundColor White
Write-Host ""
Write-Host "To test the toolchain:" -ForegroundColor Cyan
Write-Host "  .\compiler\algo-compiler.exe examples\algo\01_hello_world.algo -o test.asm" -ForegroundColor White
Write-Host "  .\assembler\a1m-asm.exe test.asm -o test.bin" -ForegroundColor White
Write-Host "  .\emulator\a1m-emu.exe test.bin" -ForegroundColor White
Write-Host ""
Write-Host "To install globally (in MSYS2):" -ForegroundColor Cyan
Write-Host "  Open MSYS2 MinGW64 terminal and run: ./install.sh" -ForegroundColor White
Write-Host ""
