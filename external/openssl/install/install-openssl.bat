@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install OpenSSL
@echo // usage:
@echo //   install_openssl.bat
@echo // version:
@echo //   $Id: install-openssl.bat 346 2014-04-12 02:16:21Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@if "x64" == "%TARGET_ARCHITECTURE%" (
	@set MODULE_CONFIG_ARCHITECTURE=VC-WIN64A
	@set MODULE_CONFIG_BAT=ms\do_win64a.bat
	@set TARGET_PROGRAMFILES=%ProgramW6432%
) else (
	@set MODULE_CONFIG_ARCHITECTURE=VC-WIN32
	@set MODULE_CONFIG_BAT=ms\do_win32.bat
	@set TARGET_PROGRAMFILES=%ProgramFiles%
)

@set MODULE=openssl-1.0.1g
@set SRC_DIR=%DEVROOT%\%MODULE%\

@echo //----------------------------------------------------------------
@echo // ATTENTION :
@echo // The build system of OpenSSL doesn't support the path which includes
@echo // some white spaces. (for example: "Program Files")
@echo //----------------------------------------------------------------
@set OUTPUT=%DEVROOT%\output\openssl

@set CLEAN_FIRST=no
@set XCOPY=xcopy /E /F /Y 

@echo //----------------------------------------------------------------
@echo // ATTENTION :
@echo // to supress error in installation process, define some variables.
@echo //----------------------------------------------------------------
@set LIBPREFIX=%OUTPUT%\lib
@set BINPREFIX=%OUTPUT%\bin
@set SOPREFIX=%OUTPUT%\so

@call %TOOLROOT%/build/setup_mssdk.bat
@if errorlevel 1 @goto :error

@echo //----------------------------------------------------------------
@echo // configure
@echo //----------------------------------------------------------------
@pushd "%SRC_DIR%"
perl Configure --openssldir="%OUTPUT%" %MODULE_CONFIG_ARCHITECTURE% no-asm
@if errorlevel 1 @goto :error

call %MODULE_CONFIG_BAT%
@if errorlevel 1 @goto :error

@if "yes" == "%CLEAN_FIRST%" @(
@echo //----------------------------------------------------------------
@echo // clean
@echo // ATTENTION :
@echo // In the first installation, 'clean' will fails because 'del' 
@echo // command attempts to delete a non-existent directory.
@echo //----------------------------------------------------------------
nmake -f ms\nt.mak clean
@if errorlevel 1 @goto :error
)

@echo //----------------------------------------------------------------
@echo // build
@echo //----------------------------------------------------------------
nmake -f ms\nt.mak
@if errorlevel 1 @goto :error

@echo //----------------------------------------------------------------
@echo // install
@echo //----------------------------------------------------------------
nmake -f ms\nt.mak install
@if errorlevel 1 @goto :error

%XCOPY% %OUTPUT%\* "%TARGET_PROGRAMFILES%"\openssl\
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
