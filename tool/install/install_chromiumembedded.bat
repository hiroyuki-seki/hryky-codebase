@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install chromiumembedded
@echo // usage:
@echo //   install_chromiumembedded.bat
@echo // version:
@echo //   $Id: install_chromiumembedded.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@call %TOOLROOT%/build/setup_mssdk.bat

@set PATH=%DEVROOT%\depot_tools;%PATH%
@set GYP_DEFINES="OS=win target_arch=%TARGET_ARCHITECTURE% v8_target_arch=%TARGET_ARCHITECTURE%"

@cd %DEVROOT%\chromium\src\cef

@call cef_create_projects.bat
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
