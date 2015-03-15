@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install xiph
@echo // usage:
@echo //   install_xiph.bat
@echo // version:
@echo //   $Id: install_xiph.bat 109 2012-12-08 21:45:38Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

set MODULE=xiph.org
set SRC_DIR=%DEVROOT%\%MODULE%
set BIN_DIR=%DEVROOT%\output\%MODULE%

@call %TOOLROOT%/build/setup_mssdk.bat

set SRCROOT=%SRC_DIR%
set MSDEVDIR=%MSSDK%

pushd "%SRCROOT%\win32sdk"

call mkmak.bat
call makesdk.bat

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
