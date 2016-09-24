@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install v8
@echo // usage:
@echo //   install_v8.bat [command]
@echo // version:
@echo //   $Id: install_v8.bat 352 2014-06-08 08:48:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set COMMAND=%1
shift

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@if "x64" == "%TARGET_ARCHITECTURE%" @(
	@set V8_ARCHITECTURE=x64
) else @(
	@set V8_ARCHITECTURE=ia32
)

@set MODULE=v8
@set MODULE_ROOT=%DEVROOT%\google\%MODULE%
@set MODULE_PROJDIR=%MODULE_ROOT%\build
@set INSTALL_ROOT=%DEVROOT%\hryky-codebase\external\v8
@set INSTALL_LIBDIR=%INSTALL_ROOT%\lib\win\%TARGET_ARCHITECTURE%\
@set INSTALL_INCDIR=%INSTALL_ROOT%\include\v8\
@set XCOPY=xcopy /F /Y 

@set DEPOT_TOOLS_WIN_TOOLCHAIN=0
@set GYP_MSVS_VERSION=2015

@set PATH=%DEVROOT%\depot_tools;%PATH%

@if not exist "%MODULE_ROOT%" @(
	@echo "%MODULE_ROOT%" is not found.
	@goto :error
)
@pushd "%MODULE_ROOT%"

@chcp 437

@if "build" == "%COMMAND%" @(
	@goto :build
)
@if "install" == "%COMMAND%" @(
	@goto :install
)

:configure
@echo //--------------------------------
@echo // configure V8 : %TARGET_ARCHITECTURE%
@echo //--------------------------------

@call "tools\dev\v8gen.py" x64.debug ^
	-- is_component_build=true
@if errorlevel 1 @goto :error
@call "tools\dev\v8gen.py" x64.optdebug ^
	-- is_component_build=true
@if errorlevel 1 @goto :error
@call "tools\dev\v8gen.py" x64.release ^
	-- is_component_build=true
@if errorlevel 1 @goto :error

:build
@echo //--------------------------------
@echo // build V8
@echo //--------------------------------

@call ninja -v -C out.gn/x64.debug v8
@if errorlevel 1 @goto :error
@call ninja -v -C out.gn/x64.optdebug v8
@if errorlevel 1 @goto :error
@call ninja -v -C out.gn/x64.release v8
@if errorlevel 1 @goto :error

:install
@echo //--------------------------------
@echo // install V8 : %TARGET_ARCHITECTURE%
@echo //--------------------------------

@if not exist "%INSTALL_LIBDIR%\Debug" @mkdir "%INSTALL_LIBDIR%\Debug"
%XCOPY% "%MODULE_ROOT%"\out.gn\x64.debug\v8.dll "%INSTALL_LIBDIR%\Debug"
%XCOPY% "%MODULE_ROOT%"\out.gn\x64.debug\v8.dll.lib "%INSTALL_LIBDIR%\Debug"
%XCOPY% "%MODULE_ROOT%"\out.gn\x64.debug\v8.dll.exp "%INSTALL_LIBDIR%\Debug"
%XCOPY% "%MODULE_ROOT%"\out.gn\x64.debug\v8.dll.pdb "%INSTALL_LIBDIR%\Debug"

@if not exist "%INSTALL_LIBDIR%\Release" @mkdir "%INSTALL_LIBDIR%\Release"
%XCOPY% "%MODULE_ROOT%"\out.gn\x64.release\v8.dll "%INSTALL_LIBDIR%\Release"
%XCOPY% "%MODULE_ROOT%"\out.gn\x64.release\v8.dll.lib "%INSTALL_LIBDIR%\Release"
%XCOPY% "%MODULE_ROOT%"\out.gn\x64.release\v8.dll.exp "%INSTALL_LIBDIR%\Release"
%XCOPY% "%MODULE_ROOT%"\out.gn\x64.release\v8.dll.pdb "%INSTALL_LIBDIR%\Release"

@if not exist "%INSTALL_INCDIR%" @mkdir "%INSTALL_INCDIR%"
%XCOPY% "%MODULE_ROOT%"\include "%INSTALL_INCDIR%\"


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
