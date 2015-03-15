@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install modules by CMake
@echo // usage:
@echo //   install_by_cmake.bat
@echo // precondition :
@echo //   following variables must be defined.
@echo //     CMAKE_SRC_DIR : input source root directory
@echo //     CMAKE_BIN_DIR : output binary root directory
@echo //     CMAKE_CONFIGURE_FLAGS : flags to configure settings
@echo //     CMAKE_BUILD_FLAGS : flags to build module
@echo // version:
@echo //   $Id: install_by_cmake.bat 339 2014-03-25 06:00:27Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

"%CMAKE%" -E make_directory "%CMAKE_BIN_DIR%"
@if errorlevel 1 @goto error

@echo //----------------------------------------------------------------
@echo // change directory for out-of-source build
@echo //----------------------------------------------------------------
@cd "%CMAKE_BIN_DIR%"

@echo //----------------------------------------------------------------
@echo // configure build setting 
@echo //----------------------------------------------------------------
"%CMAKE%" %CMAKE_CONFIGURE_FLAGS%  -G "%CMAKEGENERATOR%" "%CMAKE_SRC_DIR%"
@if errorlevel 1 @goto error

@if "yes" == "%CMAKE_CLEAN_FIRST%" (
@echo //----------------------------------------------------------------
@echo // clean old output
@echo //----------------------------------------------------------------
"%CMAKE%" %CMAKE_BUILD_FLAGS% --build %CMAKE_BIN_DIR% --target clean --config Debug
@if errorlevel 1 @goto error
"%CMAKE%" %CMAKE_BUILD_FLAGS% --build %CMAKE_BIN_DIR% --target clean --config Release
@if errorlevel 1 @goto error
)

@echo //----------------------------------------------------------------
@echo // build
@echo //----------------------------------------------------------------
"%CMAKE%" %CMAKE_BUILD_FLAGS% --build %CMAKE_BIN_DIR% --target ALL_BUILD --config Debug
@if errorlevel 1 @goto error
"%CMAKE%" %CMAKE_BUILD_FLAGS% --build %CMAKE_BIN_DIR% --target ALL_BUILD --config Release
@if errorlevel 1 @goto error

@echo //----------------------------------------------------------------
@echo // install
@echo //----------------------------------------------------------------
"%CMAKE%" --build "%CMAKE_BIN_DIR%" --target INSTALL --config Debug
"%CMAKE%" --build "%CMAKE_BIN_DIR%" --target INSTALL --config Release
@if errorlevel 1 @goto error

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
