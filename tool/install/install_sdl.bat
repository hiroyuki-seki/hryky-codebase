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

@set MODULE=SDL
@set MODULE_ROOT=%DEVROOT%\%MODULE%\
@set MODULE_PROJDIR=%DEVROOT%\%MODULE%\VisualC
@set INSTALL_ROOT=%DEVROOT%\hryky-codebase\external\SDL
@set XCOPY=xcopy /E /F /Y 
@set DEVENVSLN=%MODULE_PROJDIR%\SDL_VS2010.sln
@set DEVENVTARGET=

@set DEVENVCONFIG=Debug
@set DEVENVPLATFORM=%TARGET_ARCHITECTURE%

@echo //--------------------------------
@echo // build %MODULE% : %DEVENVCONFIG% : %DEVENVPLATFORM%
@echo //--------------------------------

call "%BUILDSOLUTION%"
@if errorlevel 1 @goto error

@REM @echo //--------------------------------
@REM @echo // test %MODULE% : %DEVENVCONFIG% : %DEVENVPLATFORM%
@REM @echo //--------------------------------
@REM 
@REM call "%MODULE_PROJDIR%\%DEVENVCONFIG%\tests.exe"
@REM @if errorlevel 1 @goto error
@REM call "%MODULE_PROJDIR%\%DEVENVCONFIG%\lite-test.exe"
@REM @if errorlevel 1 @goto error

@echo //--------------------------------
@echo // install %MODULE% : %DEVENVCONFIG% : %DEVENVPLATFORM%
@echo //--------------------------------

%XCOPY% "%MODULE_PROJDIR%\SDL\%DEVENVPLATFORM%\%DEVENVCONFIG%\*.lib" "%INSTALL_ROOT%\lib\win\%DEVENVPLATFORM%\%DEVENVCONFIG%\"
%XCOPY% "%MODULE_PROJDIR%\SDLmain\%DEVENVPLATFORM%\%DEVENVCONFIG%\*.lib" "%INSTALL_ROOT%\lib\win\%DEVENVPLATFORM%\%DEVENVCONFIG%\"


set DEVENVCONFIG=Release
set DEVENVPLATFORM=%TARGET_ARCHITECTURE%
@echo //--------------------------------
@echo // build %MODULE% : %DEVENVCONFIG% : %DEVENVPLATFORM%
@echo //--------------------------------

call "%BUILDSOLUTION%"
@if errorlevel 1 @goto error

@REM @echo //--------------------------------
@REM @echo // test %MODULE% : %DEVENVCONFIG% : %DEVENVPLATFORM%
@REM @echo //--------------------------------
@REM 
@REM call "%MODULE_PROJDIR%\%DEVENVCONFIG%\tests.exe"
@REM @if errorlevel 1 @goto error
@REM call "%MODULE_PROJDIR%\%DEVENVCONFIG%\lite-test.exe"
@REM @if errorlevel 1 @goto error

@echo //--------------------------------
@echo // install %MODULE% : %DEVENVCONFIG% : %DEVENVPLATFORM%
@echo //--------------------------------

%XCOPY% "%MODULE_PROJDIR%\SDL\%DEVENVPLATFORM%\%DEVENVCONFIG%\*.lib" "%INSTALL_ROOT%\lib\win\%DEVENVPLATFORM%\%DEVENVCONFIG%\"
%XCOPY% "%MODULE_PROJDIR%\SDLmain\%DEVENVPLATFORM%\%DEVENVCONFIG%\*.lib" "%INSTALL_ROOT%\lib\win\%DEVENVPLATFORM%\%DEVENVCONFIG%\"

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
