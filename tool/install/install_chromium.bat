@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install chromium(embedded)
@echo // usage:
@echo //   install_chromium.bat
@echo // version:
@echo //   $Id: install_chromium.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@set MODULE=chromium

cd %DEVROOT%\%MODULE%

%DEVROOT%\depot_tools\gclient.bat sync
@if errorlevel 1 @goto :error

:success
@echo //----------------------------------------------------------------
@echo // %~f0 succeeded
@echo //----------------------------------------------------------------
@set RETCODE=0
@goto end

:error
@set RETCODE=1
@call %ASSERT% "%~f0 failed"
@goto end

:end

@exit /b %RETCODE%

@endlocal
