@echo //----------------------------------------------------------------
@echo // brief:
@echo //    build and install SDL
@echo // usage:
@echo //    install_sdl.bat
@echo // version:
@echo //    $Id: install_sdl.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //
@echo // attention:
@echo //    before building SDL, we must modify some properties in .vscproj
@echo //        1. replace from 'DynamicLibrary' to 'StaticLibrary'
@echo //        2. replace from 'MultiThreadedDebugDLL' to 'MultiThreadedDebug'
@echo //        3. replace from 'MultiThreadedDLL' to 'MultiThreaded'
@echo //        4. add macro 'HAVE_LIBC'
@echo //        5. add macro '_USE_MATH_DEFINES'
@echo //    to build tests,
@echo //        1. add libraries winmm.lib, imm32.lib and version.lib
@echo //        2. remove PostBuildEvent
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call "%TOOLROOT%/build/define_variables.bat"

@if "x64" == "%TARGET_ARCHITECTURE%" @(
	set MSBUILD_PLATFORM=x64
)
@if "x86" == "%TARGET_ARCHITECTURE%" @(
	set MSBUILD_PLATFORM=Win32
)

@set MODULE=SDL
@set MODULE_ROOT=%DEVROOT%\%MODULE%\
@set MODULE_PROJDIR=%DEVROOT%\%MODULE%\VisualC
@set INSTALL_ROOT=%DEVROOT%\hryky-codebase\external\SDL
@set XCOPY=xcopy /E /F /Y 
@set MSVS_VERSION=2015

@call %TOOLROOT%/build/setup_mssdk.bat
@if errorlevel 1 @goto :error

@pushd "%MODULE_PROJDIR%"
@if errorlevel 1 @goto :error

:build
@echo //--------------------------------
@echo // build %MODULE% : Debug : %TARGET_ARCHITECTURE%
@echo //--------------------------------

msbuild ^
	/property:Configuration=Debug ^
	/property:Platform=%MSBUILD_PLATFORM% ^
	/verbosity:n ^
	/target:build ^
	SDL\SDL_VS%MSVS_VERSION%.vcxproj
@if errorlevel 1 @goto error

msbuild ^
	/property:Configuration=Debug ^
	/property:Platform=%MSBUILD_PLATFORM% ^
	/verbosity:n ^
	/target:build ^
	SDLmain\SDLmain_VS%MSVS_VERSION%.vcxproj
@if errorlevel 1 @goto error

@echo //--------------------------------
@echo // build %MODULE% : Release : %TARGET_ARCHITECTURE%
@echo //--------------------------------

msbuild ^
	/property:Configuration=Release ^
	/property:Platform=%MSBUILD_PLATFORM% ^
	/verbosity:n ^
	/target:build ^
	SDL\SDL_VS%MSVS_VERSION%.vcxproj
@if errorlevel 1 @goto error

msbuild ^
	/property:Configuration=Release ^
	/property:Platform=%MSBUILD_PLATFORM% ^
	/verbosity:n ^
	/target:build ^
	SDLmain\SDLmain_VS%MSVS_VERSION%.vcxproj
@if errorlevel 1 @goto error

:install
@echo //--------------------------------
@echo // install %MODULE% : Debug : %TARGET_ARCHITECTURE%
@echo //--------------------------------

%XCOPY% "%MODULE_PROJDIR%\SDL\%MSBUILD_PLATFORM%\Debug\*.lib" "%INSTALL_ROOT%\lib\win\%MSBUILD_PLATFORM%\Debug%\"
%XCOPY% "%MODULE_PROJDIR%\SDLmain\%MSBUILD_PLATFORM%\Debug\*.lib" "%INSTALL_ROOT%\lib\win\%MSBUILD_PLATFORM%\Debug\"

@echo //--------------------------------
@echo // install %MODULE% : Release : %TARGET_ARCHITECTURE%
@echo //--------------------------------

%XCOPY% "%MODULE_PROJDIR%\SDL\%MSBUILD_PLATFORM%\Release\*.lib" "%INSTALL_ROOT%\lib\win\%MSBUILD_PLATFORM%\Release%\"
%XCOPY% "%MODULE_PROJDIR%\SDLmain\%MSBUILD_PLATFORM%\Release\*.lib" "%INSTALL_ROOT%\lib\win\%MSBUILD_PLATFORM%\Release\"

@echo //--------------------------------
@echo // install %MODULE% include files
@echo //--------------------------------

@mkdir "%INSTALL_ROOT%\include\SDL"
%XCOPY% "%MODULE_ROOT%\include" "%INSTALL_ROOT%\include\SDL\"

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
