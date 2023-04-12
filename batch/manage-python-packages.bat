:: This script uninstalls, installs, or upgrades Python packages based on the
:: provided command.

@echo off

:: Initializes variables
set command=%1
set python=%2

:: Process the command
call :processCommand

:: End
goto :eof

:: Functions

:processCommand
if /i "%command%"=="Uninstall" (
    call :uninstallPackages
) else if /i "%command%"=="Install" (
    call :installPackages
) else if /i "%command%"=="Upgrade" (
    call :upgradePackages
) else (
    echo Invalid command provided. Use "Uninstall", "Install", or "Upgrade".
)
goto :eof

:uninstallPackages
echo Uninstall...
cmd /c "%python%" -m pip uninstall setuptools pip -y    
goto :eof

:installPackages
echo Install...
cmd /c "%python%" -m ensurepip --default-pip
goto :eof

:upgradePackages
echo Upgrade...
cmd /c "%python%" -m pip install --upgrade pip
goto :eof
