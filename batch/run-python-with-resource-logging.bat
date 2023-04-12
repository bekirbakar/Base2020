:: This script sets up and runs a Python script, logs start and end times, and
:: continuously logs CPU usage and available memory.

@echo off

:: Initializes Variables
set pythonExe="python.exe"
set pipExe="pip.exe"

set sampleFile=%1
set pythonScript=run.py

set logFile="log.log"
set cpuLogs="cpu-logs.txt"
set memoryLogs="memory-logs.txt"

:: Clears log files.
call :clearLogFiles

:: Set up Python environment.
call :setupPython

:: Run the Python script.
call :runPythonScript

:: Continuously log CPU and memory usage while the Python script is running.
call :logCpuMemoryUsage

:: Log end time.
call :logEndTime

:: End
goto :eof

:: Functions

:clearLogFiles
break> %logFile%
break> %cpuLogs%
break> %memoryLogs%
goto :eof

:setupPython
echo Uninstall in Process
%pythonExe% -m pip uninstall setuptools pip -y    
echo Install in Process
%pythonExe% -m ensurepip --default-pip
echo Upgrade in Process
%pythonExe% -m pip install --upgrade pip
%pipExe% install --no-index --find-links "packages" -r "requirements.txt"
goto :eof

:runPythonScript
set startTime=%time%
echo Start Time: %startTime% >> %logFile%
start /wait %pythonExe% %pythonScript% %sampleFile% >output.json
goto :eof

:logCpuMemoryUsage
set startTimeLoop=%time%
:LOOP
for /f "skip=1" %%p in ('wmic cpu get loadpercentage') do (
    echo %%p >> %cpuLogs%,
)

for /f "skip=1" %%p in ('wmic OS get FreePhysicalMemory') do (
    echo %%p >> %memoryLogs%,
)

if not exist output.json goto :LOOP
goto :eof

:logEndTime
set endTime=%time%
echo End Time: %endTime% >> %logFile%
goto :eof
