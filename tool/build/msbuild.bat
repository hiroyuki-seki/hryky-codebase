@echo //-----------------------------------------------------------------------
@echo // brief:
@echo //    builds Visual Studio Project by MSBuild
@echo // usage:
@echo //    msbuild.bat
@echo // prerequisite:
@echo //    defines the following variables
@echo //        MSBUILD_SLN : The path to the built solution.
@echo //        MSBUILD_CONFIG : The name of configuration. i.e. Debug.
@echo //        MSBUILD_PLATFORM : The name of platform. i.e. x64
@echo // version:
@echo //   $Id: msbuild.bat 300 2014-01-02 07:58:43Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@if "%MSBUILD_SLN%" == "" @(
	@echo variable 'MSBUILD_SLN' is not defined.
	@goto error
)

@if "%MSBUILD_CONFIG%" == "" @(
	@echo variable 'MSBUILD_CONFIG' is not defined.
	@goto error
)

@if "%MSBUILD_PLATFORM%" == "" @(
	@echo variable 'MSBUILD_PLATFORM' is not defined.
	@goto error
)

@call %SETUPMSSDK%
@if errorlevel 1 @goto error

@set MSBUILD_EXE=MSBuild.exe
@set MSBUILD_FLAGS=%MSBUILD_FLAGS% /p:Configuration=%MSBUILD_CONFIG% /p:Platform=%MSBUILD_PLATFORM% /v:d /m

@if "%MSBUILD_TARGET%" == "" @(
	
	@echo //--------------------------------
	@echo // build solution : %MSBUILD_SLN% : %MSBUILD_CONFIG% : %MSBUILD_PLATFORM%
	@echo //--------------------------------
	"%MSBUILD_EXE%" %MSBUILD_SLN% /t:build %MSBUILD_FLAGS%
	@if errorlevel 1 @goto error
	
	@goto success
)


@if "%MSBUILD_TARGET%" == "rebuild" @(

	@echo //--------------------------------
	@echo // rebuild solution : %MSBUILD_SLN% : %MSBUILD_CONFIG% : %MSBUILD_PLATFORM%
	@echo //--------------------------------
	"%MSBUILD_EXE%" %MSBUILD_SLN% /t:rebuild %MSBUILD_FLAGS%
	@if errorlevel 1 @goto error
	
	@goto success

)

@if "%MSBUILD_TARGET%" == "clean" @(

	@echo //--------------------------------
	@echo // clean solution : %MSBUILD_SLN% : %MSBUILD_CONFIG% : %MSBUILD_PLATFORM%
	@echo //--------------------------------
	"%MSBUILD_EXE%" %MSBUILD_SLN% /t:clean %MSBUILD_FLAGS%
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
