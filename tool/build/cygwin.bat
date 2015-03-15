@echo //----------------------------------------------------------------
@echo // brief:
@echo //   open cygwin prompt
@echo // usage:
@echo //   cygwin.bat
@echo // version:
@echo //   $Id: cygwin.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@set SOLUTION=%1
@shift

@call %SETUPMSSDK%
@if errorlevel 1 @goto error

@echo //--------------------------------
@echo // open cygwin
@echo //--------------------------------
@call %CYGWIN%
@if errorlevel 1 @goto error

:success
@echo //----------------------------------------------------------------
@echo // %~f0 succeeded
@echo //----------------------------------------------------------------
@set RETCODE=0
@goto end

:error
@set RETCODE=1
@call %ASSERT% "in %0, failed to open solution %SOLUTION%"
@goto end

:end
@exit /b %RETCODE%
@endlocal
