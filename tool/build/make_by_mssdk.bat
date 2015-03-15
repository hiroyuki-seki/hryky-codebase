@echo //----------------------------------------------------------------
@echo // file:
@echo //   make_by_mssdk.bat
@echo // brief:
@echo //   build environment to make project
@echo // usage:
@echo //   make_by_mssdk.bat MAKEFILE MAKETARGET MAKECONFIGURATION
@echo //     MAKEFILE            : file path passed to gnu-make
@echo //     MAKETARGET          : target for makefile
@echo //     MAKECONFIGURATION   : configuration of the build process
@echo //
@echo // version : $Id: make_by_mssdk.bat 146 2013-02-02 12:17:38Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@echo //--------------------------------
@echo // start counter
@echo //--------------------------------
@for /f "usebackq" %%i in (`call %RUBY% %TIMESTAMP%`) do @set STARTTIMESTAMP=%%i

@set MAKEFILE=%1
@shift

@if "%MAKEFILE%" == "" goto error_no_makefile

@echo //--------------------------------
@echo // Makefile is %MAKEFILE%
@echo //--------------------------------

@set MAKETARGET=%1
@shift

@if "%MAKETARGET%" == "" goto error_no_maketarget

@echo //--------------------------------
@echo // target is %MAKETARGET%
@echo //--------------------------------

@set MAKECONFIGURATION=%1
@shift 

@if "%MAKECONFIGURATION%" == "" @(
    @set MAKECONFIGURATION=debug
)

@echo //--------------------------------
@echo // configuration is %MAKECONFIGURATION%
@echo //--------------------------------

@if "%MAKECONFIGURATION%" == "debug" @(
    @set DEBUG=debug
) else @(
    @if "%MAKECONFIGURATION%" == "release" @(
        @set RELEASE=release
    ) else @(
        @echo ERROR : invalid MAKECONFIGURATION : %MAKECONFIGURATION%
        @goto error
    )
)

@call %SETUPMSSDK%

%MAKE% -f %MAKEFILE% %MAKETARGET%
@if errorlevel 1 @goto error_make

@echo //--------------------------------
@echo // stop counter
@echo //--------------------------------
@for /f "usebackq" %%i in (`call %RUBY% %TIMESTAMP%`) do @set ENDTIMESTAMP=%%i

@set /a ELAPSETIME=%ENDTIMESTAMP% - %STARTTIMESTAMP%

@echo //--------------------------------
@echo // elapse time : %ELAPSETIME% sec
@echo //--------------------------------

:success
@set RETCODE=0
goto end

@echo //--------------------------------
@echo // Error
@echo //--------------------------------

:error_no_makefile
@set RETCODE=1
@call %ASSERT% "Makefile is not specified."
@goto end

:error_no_maketarget
@set RETCODE=1
@call %ASSERT% "target to make is not specified."
@goto end

:error_no_mssdk
@set RETCODE=1
@call %ASSERT% "environment variable mssdk is not defined"
@goto end

:error_make
@set RETCODE=1
@call %ASSERT% "failed to make project "%MAKEFILE%""
@goto end

:error_timestamp_exist
@set RETCODE=1
@call %ASSERT% "temporary file for timestamp already exists"
@goto end

:error 
@set RETCODE=1
@goto end

:end

@exit /b %RETCODE%

@endlocal
