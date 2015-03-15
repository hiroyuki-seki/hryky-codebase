@echo //----------------------------------------------------------------
@echo // file:
@echo //   open_solution.bat
@echo // brief:
@echo //   opens Visual Studio solution
@echo // usage:
@echo //   open_solution.bat SOLUTION CONFIG ENVCONFIG ENVARC ENVOS
@echo //     SOLUTION  : visual studio solution file
@echo //     CONFIG    : solution configuration
@echo // version:
@echo //   $Id: open_solution.bat 81 2012-07-01 07:50:14Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@set SOLUTION=%~1
@shift

@call %SETUPMSSDK%
@if errorlevel 1 @goto error

@echo //--------------------------------
@echo // open solution : %SOLUTION%
@echo //--------------------------------
"%DEVENV%" "%SOLUTION%"
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
