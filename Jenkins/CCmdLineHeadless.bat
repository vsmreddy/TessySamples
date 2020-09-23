@echo off
set TESSYBIN=C:\Razorcat42\TESSY_4.2\bin

set TESSYCMD="%TESSYBIN%\tessycmd.exe"
set TESSYD="%TESSYBIN%\tessyd.exe"

set TESSYPROJECTFILE="%TESSYPRJPATH%\tessy\tessy.pdbx"
set TESSYPRJPATH=%~dp0\CCmdLine
set TBSFILE="%~dp0\CCmdLine.tbs"

set TESTPROJECTNAME="CCmdLine"
set TESTCOLLECTION="CCmdLine"

rem Starting TESSY headless if not already running
rem -----------------------------------------------
cmd /c %TESSYD% shutdown
%TESSYD%
 
rem Connect to running TESSY instance
rem ----------------------------------
echo 1. Connecting to TESSY
%TESSYCMD% connect
if %ERRORLEVEL%==0 goto next1
	rem try disconnect
	%TESSYCMD% disconnect
	if NOT %ERRORLEVEL%==0 goto exit
	%TESSYCMD% connect
	if %ERRORLEVEL%==0 goto next1
	echo *** Error connecting to TESSY application! ***
	exit /b
:next1

echo 2. List of all TESSY projects in your workspace:
%TESSYCMD% list-projects
echo. 

rem Select current project and test collection
rem ------------------------------------------------------
REM echo 4. Selecting current project
REM for /f "tokens=*" %%a in ('%TESSYCMD% list-projects') do set PROJECT="%%a"
%TESSYCMD% select-project %TESTPROJECTNAME%
TITLE TESSY - Selected Project: %TESTPROJECTNAME%
if NOT %ERRORLEVEL%==0 goto exit

echo 3. List of all test collections in current project:
%TESSYCMD% list-test-collections
echo.

echo 4. Selecting test collection %TESTCOLLECTION%
%TESSYCMD% select-test-collection %TESTCOLLECTION%
if NOT %ERRORLEVEL%==0 goto exit
	
rem Run the tests
rem --------------
echo 5. Running the tests...
%TESSYCMD% -animate exec-test %TBSFILE%

rem Disconnect from TESSY
rem ----------------------
%TESSYCMD% disconnect

rem Shutdown TESSY headless
cmd /c %TESSYD% shutdown

rem Normal completion
rem ------------------
	echo   *** Successful completion! ***
REM pause
	exit /b
