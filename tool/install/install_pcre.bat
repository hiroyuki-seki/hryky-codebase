@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install pcre
@echo // usage:
@echo //   install_pcre.bat
@echo // version:
@echo //   $Id: install_pcre.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

set MODULE=pcre
set ZLIB_INCLUDE_DIR=%TARGET_PROGRAM_FILES%\zlib\include
set ZLIB_LIBRARY=%TARGET_PROGRAM_FILES%\zlib\lib
set CMAKE_SRC_DIR=%DEVROOT%\%MODULE%\
set CMAKE_BIN_DIR=%DEVROOT%\output\%MODULE%
set CMAKE_CONFIGURE_FLAGS=-D BUILD_STATIC_LIBS=true -D BUILD_SHARED_LIBS=false
set CMAKE_BUILD_FLAGS=
set CMAKE_CLEAN_FIRST=

@call %TOOLROOT%\install\install_by_cmake.bat
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
