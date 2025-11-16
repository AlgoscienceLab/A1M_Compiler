@echo off
REM Build script for A1M Compiler on Windows (MSYS2/MinGW64)
REM This script builds all components of the A1M toolchain
REM Must be run from MSYS2 MinGW 64-bit terminal

echo ========================================
echo Building A1M Compiler Toolchain
echo Platform: Windows (MSYS2/MinGW64)
echo ========================================
echo.

REM Check if we're in MSYS2/MinGW64 environment
where gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: GCC not found in PATH
    echo.
    echo This script must be run from MSYS2 MinGW 64-bit terminal.
    echo.
    echo If you're in PowerShell/CMD, use: build-windows.ps1
    echo.
    echo To install MSYS2:
    echo   1. Download from: https://www.msys2.org/
    echo   2. Install to C:\msys64
    echo   3. Open "MSYS2 MinGW 64-bit" terminal
    echo   4. Run: pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make make
    echo   5. Run this script again
    echo.
    pause
    exit /b 1
)

echo Compiler found: 
gcc --version | findstr /C:"gcc"
echo.

where make >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Make not found in PATH
    echo Please install: pacman -S mingw-w64-x86_64-make make
    echo.
    pause
    exit /b 1
)

echo Make found:
make --version | findstr /C:"GNU Make"
echo.

REM Build Compiler
echo [1/4] Building Algo Compiler...
cd compiler
if exist obj rmdir /S /Q obj >nul 2>&1
make clean >nul 2>&1
make
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to build compiler
    cd ..
    pause
    exit /b 1
)
if not exist algo-compiler.exe (
    echo ERROR: algo-compiler.exe not created
    cd ..
    pause
    exit /b 1
)
echo [OK] Built: algo-compiler.exe
cd ..
echo.

REM Build Assembler
echo [2/4] Building A1M Assembler...
cd assembler
if exist obj rmdir /S /Q obj >nul 2>&1
make clean >nul 2>&1
make
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to build assembler
    cd ..
    pause
    exit /b 1
)
if not exist a1m-asm.exe (
    echo ERROR: a1m-asm.exe not created
    cd ..
    pause
    exit /b 1
)
echo [OK] Built: a1m-asm.exe
cd ..
echo.

REM Build Emulator
echo [3/4] Building A1M Emulator...
cd emulator
if exist obj rmdir /S /Q obj >nul 2>&1
make clean >nul 2>&1
make
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to build emulator
    cd ..
    pause
    exit /b 1
)
if not exist a1m-emu.exe (
    echo ERROR: a1m-emu.exe not created
    cd ..
    pause
    exit /b 1
)
echo [OK] Built: a1m-emu.exe
cd ..
echo.

REM Build GUI Console
echo [4/4] Building A1M Console...
cd gui-console
make clean >nul 2>&1
make
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to build console
    cd ..
    pause
    exit /b 1
)
if not exist a1m-console.exe (
    echo ERROR: a1m-console.exe not created
    cd ..
    pause
    exit /b 1
)
echo [OK] Built: a1m-console.exe
cd ..
echo.

echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Built executables:
echo   - compiler\algo-compiler.exe
echo   - assembler\a1m-asm.exe
echo   - emulator\a1m-emu.exe
echo   - gui-console\a1m-console.exe
echo.
echo To test the installation:
echo   .\compiler\algo-compiler.exe examples\algo\01_hello_world.algo -o test.asm
echo   .\assembler\a1m-asm.exe test.asm -o test.bin
echo   .\emulator\a1m-emu.exe test.bin
echo.
echo To install globally:
echo   Run: ./install.sh
echo.
pause
