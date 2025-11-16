@echo off
REM VS Code Extension Installation Script for Windows
REM Builds and packages the Algo Language extension

echo ========================================
echo Algo Language VS Code Extension Setup
echo Platform: Windows
echo ========================================
echo.

REM Check if Node.js is installed
where node >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Node.js is not installed
    echo.
    echo Please install Node.js from: https://nodejs.org/
    echo Or in MSYS2 MinGW64: pacman -S mingw-w64-x86_64-nodejs
    exit /b 1
)

REM Check if npm is installed
where npm >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: npm is not installed
    echo npm is usually installed with Node.js. Please reinstall Node.js.
    exit /b 1
)

echo [OK] Node.js found
node --version
echo [OK] npm found
npm --version
echo.

REM Navigate to extension directory
cd /d "%~dp0"

REM Install dependencies
echo [1/3] Installing dependencies...
call npm install
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to install dependencies
    exit /b 1
)
echo.

REM Compile TypeScript
echo [2/3] Compiling TypeScript...
call npm run compile
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to compile TypeScript
    exit /b 1
)
echo.

REM Check if vsce is installed
where vsce >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo vsce not found. Installing @vscode/vsce...
    call npm install -g @vscode/vsce
    echo.
)

REM Package extension
echo [3/3] Packaging extension...
call vsce package
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to package extension
    exit /b 1
)
echo.

REM Find the .vsix file
for /f "delims=" %%i in ('dir /b /od *.vsix 2^>nul') do set VSIX_FILE=%%i

if "%VSIX_FILE%"=="" (
    echo ERROR: Failed to create .vsix package
    exit /b 1
)

echo ========================================
echo Extension built successfully!
echo ========================================
echo.
echo Package: %VSIX_FILE%
echo.
echo To install in VS Code:
echo.
echo   Method 1: Using VS Code GUI
echo     1. Open VS Code
echo     2. Press Ctrl+Shift+P
echo     3. Type "Extensions: Install from VSIX"
echo     4. Select: %CD%\%VSIX_FILE%
echo.
echo   Method 2: Using command line
echo     code --install-extension "%CD%\%VSIX_FILE%"
echo.

REM Offer to install automatically if code command is available
where code >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo.
    set /p INSTALL="Would you like to install the extension now? (y/n): "
    if /i "%INSTALL%"=="y" (
        echo Installing extension...
        code --install-extension "%VSIX_FILE%"
        echo.
        echo [OK] Extension installed!
        echo Please reload VS Code to activate the extension
    )
)

echo.
echo Done!
echo.
pause
