@echo off
setlocal EnableExtensions
REM ============================================================================
REM Clean Project.bat - clean MDK / IAR / Eclipse build artifacts for this example
REM Platform: G32R502 (SDK-wide **/g32r502/** examples; not for other MCU families)
REM Version : 1.4.0
REM Date    : 2026-08-24
REM ============================================================================
REM Usage:
REM   Clean Project.bat              clean MDK + IAR + Eclipse
REM   Clean Project.bat -mdk         clean MDK only
REM   Clean Project.bat -iar -eclipse clean IAR and Eclipse (max 2 flags)
REM Keep: MDK (*.uvprojx, *.sct, *.ini); IAR (*.ewp, *.eww, *.icf);
REM       Eclipse (.project, .cproject, *.ld, pyocd*).
REM Output/ layout: rd Output (+ IDE caches); Eclipse also rd <Config> roots.
REM Only named tool output folders are removed; user-added subdirs are kept.

set "SCRIPT_VER=1.4.0"
set "SCRIPT_DATE=2026-08-24"

cd /d "%~dp0"

set "DO_MDK=0"
set "DO_IAR=0"
set "DO_ECLIPSE=0"

if "%~1"=="" (
  set "DO_MDK=1"
  set "DO_IAR=1"
  set "DO_ECLIPSE=1"
  goto :run
)

if not "%~3"=="" (
  echo ERROR: At most 2 options. Use: -mdk -iar -eclipse
  echo Example: Clean Project.bat -mdk -iar
  exit /b 1
)

call :parse_flag "%~1"
if errorlevel 1 exit /b 1
if not "%~2"=="" (
  call :parse_flag "%~2"
  if errorlevel 1 exit /b 1
)

if "%DO_MDK%"=="0" if "%DO_IAR%"=="0" if "%DO_ECLIPSE%"=="0" (
  echo ERROR: Unknown option. Use: -mdk -iar -eclipse
  exit /b 1
)

:run
echo Clean Project.bat v%SCRIPT_VER% (%SCRIPT_DATE%) [G32R502]

if "%DO_MDK%"=="1" if exist "MDK\" (
  echo Cleaning MDK ...
  call :clean_mdk
)
if "%DO_IAR%"=="1" if exist "IAR\" (
  echo Cleaning IAR ...
  call :clean_iar
)
if "%DO_ECLIPSE%"=="1" if exist "Eclipse\" (
  echo Cleaning Eclipse ...
  call :clean_eclipse
)

echo Done.
exit /b 0

:parse_flag
set "ARG=%~1"
if "%ARG%"=="" exit /b 0
if /i "%ARG%"=="-mdk" (
  set "DO_MDK=1"
  exit /b 0
)
if /i "%ARG%"=="-iar" (
  set "DO_IAR=1"
  exit /b 0
)
if /i "%ARG%"=="-eclipse" (
  set "DO_ECLIPSE=1"
  exit /b 0
)
echo ERROR: Invalid option "%ARG%". Use: -mdk -iar -eclipse
exit /b 1

:clean_mdk
rd /Q /S "MDK\DebugConfig" 2>nul
rd /Q /S "MDK\Output" 2>nul
rd /Q /S "MDK\RTE" 2>nul
del /Q /F "MDK\*.bak" 2>nul
del /Q /F "MDK\*.dep" 2>nul
del /Q /F "MDK\JLink*" 2>nul
del /Q /F "MDK\*.uvguix.*" 2>nul
del /Q /F "MDK\*.uvoptx" 2>nul
del /Q /F "MDK\*.axf" 2>nul
del /Q /F "MDK\*.hex" 2>nul
del /Q /F "MDK\*.bin" 2>nul
del /Q /F "MDK\*.map" 2>nul
del /Q /F "MDK\*.lnp" 2>nul
del /Q /F "MDK\*.htm" 2>nul
del /Q /F "MDK\*.crf" 2>nul
del /Q /F "MDK\*.o" 2>nul
del /Q /F "MDK\*.d" 2>nul
del /Q /F "MDK\*.lst" 2>nul
exit /b 0

:clean_iar
del /Q /F "IAR\*.dep" 2>nul
del /Q /F "IAR\*.ewd" 2>nul
del /Q /F "IAR\*.ewt" 2>nul
del /Q /F "IAR\*.out" 2>nul
del /Q /F "IAR\*.hex" 2>nul
del /Q /F "IAR\*.bin" 2>nul
del /Q /F "IAR\*.map" 2>nul
del /Q /F "IAR\*.o" 2>nul
del /Q /F "IAR\*.pbi" 2>nul
del /Q /F "IAR\*.xcl" 2>nul
del /Q /F "IAR\*.lst" 2>nul
del /Q /F "IAR\*.sim" 2>nul
del /Q /F "IAR\*.htm" 2>nul
rd /Q /S "IAR\Debug" 2>nul
rd /Q /S "IAR\Flash" 2>nul
rd /Q /S "IAR\Output" 2>nul
rd /Q /S "IAR\Release" 2>nul
rd /Q /S "IAR\settings" 2>nul
exit /b 0

:clean_eclipse
del /Q /F "Eclipse\*.gitignore" 2>nul
del /Q /F "Eclipse\*.elf" 2>nul
del /Q /F "Eclipse\*.hex" 2>nul
del /Q /F "Eclipse\*.bin" 2>nul
del /Q /F "Eclipse\*.map" 2>nul
del /Q /F "Eclipse\*.o" 2>nul
del /Q /F "Eclipse\*.d" 2>nul
del /Q /F "Eclipse\*.lst" 2>nul
del /Q /F "Eclipse\*.htm" 2>nul
del /Q /F "Eclipse\*.lnp" 2>nul
rd /Q /S "Eclipse\.settings" 2>nul
rd /Q /S "Eclipse\Debug" 2>nul
rd /Q /S "Eclipse\FAPI_R502" 2>nul
rd /Q /S "Eclipse\Output" 2>nul
rd /Q /S "Eclipse\Release" 2>nul
exit /b 0
