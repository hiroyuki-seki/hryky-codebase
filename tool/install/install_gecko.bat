@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install Gecko
@echo // usage:
@echo //   install_gecko.bat
@echo // version:
@echo //   $Id: install_gecko.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@set MODULE=mozilla-central
@set SRC_DIR=%DEVROOT%\%MODULE%

@pushd %SRC_DIR%

@popd

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
