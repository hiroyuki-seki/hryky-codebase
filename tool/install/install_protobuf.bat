@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install protocol buffer
@echo // usage:
@echo //   install_protobuf.bat
@echo // version:
@echo //   $Id: install_protobuf.bat 300 2014-01-02 07:58:43Z hryky.private@gmail.com $
@echo //
@echo // Protocol Buffer is built by MSVC2009.
@echo // MSVC can't use std::tuple and so on.
@echo // The following projects have to be ignored.
@echo // - gtest
@echo // - gtest_main
@echo // - lite-test
@echo // - test_plugin
@echo // - tests
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call "%TOOLROOT%/build/define_variables.bat"

set MODULE=protobuf
set MODULE_ROOT=%DEVROOT%\%MODULE%\
set MODULE_PROJDIR=%DEVROOT%\%MODULE%\vsprojects
set INSTALL_ROOT=%DEVROOT%\hryky-codebase\external\protobuf
set INSTALL_LIBDIR=%INSTALL_ROOT%\lib\win\%TARGET_ARCHITECTURE%\
set INSTALL_TOOLDIR=%INSTALL_ROOT%\tool\win\%TARGET_ARCHITECTURE%\
set XCOPY=xcopy /E /F /Y 

@if "x64" == "%TARGET_ARCHITECTURE%" @(
	@set MSBUILD_PLATFORM=x64
) else @(
	@set MSBUILD_PLATFORM=Win32
)

set MSBUILD_SLN=%MODULE_PROJDIR%\%MODULE%.sln
set MSBUILD_TARGET=
set MSBUILD_FLAGS=/p:DefineConstants=GTEST_HAS_TR1_TUPLE=0

set MSBUILD_CONFIG=Debug
@echo //--------------------------------
@echo // build %MODULE% : %MSBUILD_CONFIG% : %MSBUILD_PLATFORM%
@echo //--------------------------------

REM call "%TOOLROOT%\build\msbuild.bat"
REM @if errorlevel 1 @goto error

@echo //--------------------------------
@echo // test %MODULE% : %MSBUILD_CONFIG% : %MSBUILD_PLATFORM%
@echo //--------------------------------

REM call "%MODULE_PROJDIR%\%MSBUILD_CONFIG%\tests.exe"
REM @if errorlevel 1 @goto error
REM call "%MODULE_PROJDIR%\%MSBUILD_CONFIG%\lite-test.exe"
REM @if errorlevel 1 @goto error

@echo //--------------------------------
@echo // install %MODULE% : %MSBUILD_CONFIG% : %MSBUILD_PLATFORM%
@echo //--------------------------------

%XCOPY% "%MODULE_PROJDIR%\%MSBUILD_CONFIG%\*.lib" "%INSTALL_LIBDIR%\"
%XCOPY% "%MODULE_PROJDIR%\Debug\*.exe" "%INSTALL_TOOLDIR%\"

set MSBUILD_CONFIG=Release
@echo //--------------------------------
@echo // build %MODULE% : %MSBUILD_CONFIG% : %MSBUILD_PLATFORM%
@echo //--------------------------------

REM call "%TOOLROOT%\build\msbuild.bat"
REM @if errorlevel 1 @goto error

@echo //--------------------------------
@echo // test %MODULE% : %MSBUILD_CONFIG% : %MSBUILD_PLATFORM%
@echo //--------------------------------

REM call "%MODULE_PROJDIR%\%MSBUILD_CONFIG%\tests.exe"
REM @if errorlevel 1 @goto error
REM call "%MODULE_PROJDIR%\%MSBUILD_CONFIG%\lite-test.exe"
REM @if errorlevel 1 @goto error

@echo //--------------------------------
@echo // install %MODULE% : %MSBUILD_CONFIG% : %MSBUILD_PLATFORM%
@echo //--------------------------------

%XCOPY% "%MODULE_PROJDIR%\%MSBUILD_CONFIG%\*.lib" "%INSTALL_LIBDIR%\"
%XCOPY% "%MODULE_PROJDIR%\%MSBUILD_CONFIG%\*.exe" "%INSTALL_TOOLDIR%\"

@echo //--------------------------------
@echo // extract %MODULE% include files
@echo //--------------------------------

cd "%MODULE_PROJDIR%"
call "%MODULE_PROJDIR%\extract_includes.bat"

@echo //--------------------------------
@echo // install %MODULE% include files
@echo //--------------------------------

@mkdir "%INSTALL_ROOT%\include"
%XCOPY% "%MODULE_PROJDIR%\include" "%INSTALL_ROOT%\include\"


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
