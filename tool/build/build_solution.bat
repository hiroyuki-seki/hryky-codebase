@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build Visual Studio solution
@echo // usage:
@echo //   build_solution.bat
@echo // prerequisite:
@echo //    defines the following variables.
@echo //        DEVENVSLN : The path to the built solution.
@echo //        DEVENVCONFIG : The name of configuration. i.e. Debug.
@echo //        DEVENVPLATFORM : The name of platform. i.e. x64
@echo // version:
@echo //   $Id: build_solution.bat 298 2014-01-02 00:16:32Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@if "%DEVENVSLN%" == "" @(
	@echo variable 'DEVENVSLN' is not defined.
	@goto error
)

@if "%DEVENVCONFIG%" == "" @(
	@echo variable 'DEVENVCONFIG' is not defined.
	@goto error
)

@if "%DEVENVPLATFORM%" == "" @(
	@echo variable 'DEVENVPLATFORM' is not defined.
	@goto error
)

@call %SETUPMSSDK%
@if errorlevel 1 @goto error

@if "%DEVENVTARGET%" == "" @(
	
	@echo //--------------------------------
	@echo // build solution : %DEVENVSLN% : %DEVENVCONFIG% : %DEVENVPLATFORM%
	@echo //--------------------------------
	"%DEVENV%" %DEVENVSLN% /build %DEVENVCONFIG%^|%DEVENVPLATFORM%
	@if errorlevel 1 @goto error
	
	@goto success
)


@if "%DEVENVTARGET%" == "rebuild" @(

	@echo //--------------------------------
	@echo // rebuild solution : %DEVENVSLN% : %DEVENVCONFIG% : %DEVENVPLATFORM%
	@echo //--------------------------------
	"%DEVENV%" %DEVENVSLN% /rebuild %DEVENVCONFIG%^|%DEVENVPLATFORM%
	@if errorlevel 1 @goto error
	
	@goto success

)

@if "%DEVENVTARGET%" == "clean" @(

	@echo //--------------------------------
	@echo // clean solution : %DEVENVSLN% : %DEVENVCONFIG% : %DEVENVPLATFORM%
	@echo //--------------------------------
	"%DEVENV%" %DEVENVSLN% /clean %DEVENVCONFIG%^|%DEVENVPLATFORM%
	@if errorlevel 1 @goto error
	
	@goto success

)

:success
@echo //----------------------------------------------------------------
@echo // %~f0 succeeded
@echo //----------------------------------------------------------------
@set RETCODE=0
@goto end

:error
@set RETCODE=1
@call %ASSERT% "in %0, failed to build solution %SOLUTION%"
@goto end

:end
@exit /b %RETCODE%
@endlocal
