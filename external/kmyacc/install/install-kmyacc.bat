@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install kmyacc
@echo // usage:
@echo //   install_kmyacc.bat
@echo // version:
@echo //   $Id: install-kmyacc.bat 339 2014-03-25 06:00:27Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

set CMAKE_SRC_DIR=%DEVROOT%\hryky-codebase\external\kmyacc\install
set CMAKE_BIN_DIR=%DEVROOT%\output\hryky-codebase\external\kmyacc\install
set CMAKE_CONFIGURE_FLAGS=
set CMAKE_BUILD_FLAGS=
set CMAKE_CLEAN_FIRST=yes

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
