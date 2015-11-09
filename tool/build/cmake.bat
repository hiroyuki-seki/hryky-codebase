@echo //------------------------------------------------------------------------------
@echo // file:
@echo //    cmake.bat
@echo // brief:
@echo //    builds project by cmake
@echo // version:
@echo //    $Id: cmake.bat 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
@echo //
@echo // usage:
@echo //    cmake_build.bat
@echo //
@echo // prerequisite variables:
@echo //    CMAKE_SRC_DIR   is the root directory containing source files.
@echo //    CMAKE_BIN_DIR   is the destination of CMake.
@echo //    CMAKE_COMMAND   is the built-in target of the building project.
@echo //                    [build or clean or test or rebuild or document or
@echo //                    install or pack]
@echo //    CMAKE_TARGET    is the individual target of the building project.
@echo //                    If the CMAKE_COMMAND is build, this argument 
@echo //                    specifies an indivisual project. If the CMAKE_COMMAND
@echo //                    is test, this argument specifies an individual test.
@echo //   CMAKE_CONFIG     is the configuration of the building project.
@echo //                    [Debug or Release or RelWithDebInfo or MinSizeRel]
@echo //------------------------------------------------------------------------------

@setlocal enableextensions enabledelayedexpansion

@if not defined CMAKE_SRC_DIR @(
	@echo %~f0 : error : CMAKE_SRC_DIR is not defined.
	@exit /b 1
)

@if not defined CMAKE_BIN_DIR @(
	@echo %~f0 : error : CMAKE_BIN_DIR is not defined.
	@exit /b 1
)

@if "" == "%CMAKE_CONFIG%" @(
	@set CMAKE_CONFIG=Debug
)

@REM // The verbosity of output
@REM //  q[uiet]
@REM //  m[inimal]
@REM //  n[ormal]
@REM //  d[etailed]
@REM //  diag[nostic]
@set MSBUILD_VERBOSITY=m

@set CMAKE_BUILD_FLAGS=^
    --build "%CMAKE_BIN_DIR%" ^
    --config %CMAKE_CONFIG%

@set CMAKE_BUILD_FLAGS_NATIVE=^
    /m ^
    /nologo ^
    /verbosity:%MSBUILD_VERBOSITY% ^
    /clp:DisableMPLogging

@set CPACK_FLAGS=^
    --config "%CMAKE_BIN_DIR%/CPackConfig.cmake" ^
    -C "%CMAKE_CONFIG%"

@set CTEST_FLAGS=^
    --parallel 8 ^
    --output-on-failure ^
    -vv ^
    -C "%CMAKE_CONFIG%"

call %DEVROOT%/hryky-codebase/tool/build/define_variables.bat

REM call %SETUPMSSDK%
REM @if errorlevel 1 @goto error

@if not defined CMAKEGENERATOR @(
	@echo %~f0 : error : CMAKEGENERATOR is not defined.
	@exit /b 1
)

"%CMAKE%" -E make_directory %CMAKE_BIN_DIR%

@set CMAKE_CONFIGURE_FLAGS=^
    -G "%CMAKEGENERATOR%" ^
    -DHRYKY_CMAKE_VERBOSITY:STRING=1

@echo change directory to %CMAKE_BIN_DIR% for out-of-source build.
@pushd %CMAKE_BIN_DIR:/=\%

@if not "" == "%CMAKE_TARGET%" @(
	@if "%CMAKE_COMMAND%" == "test" @(
		@set CTEST_REGEX=-R %CMAKE_TARGET%
	) else @(
		@set CMAKE_BUILD_TARGET=--target %CMAKE_TARGET%
	)
)

:main

@if "%CMAKE_COMMAND%" == "configure" @(
	call :configure
	@if errorlevel 1 @exit /b 1

	goto :success
)

@if "%CMAKE_COMMAND%" == "build" @(
	call :build
	@if errorlevel 1 @exit /b 1

	goto :success
)

@if "%CMAKE_COMMAND%" == "clean" @(
	call :clean
	@if errorlevel 1 @exit /b 1

	goto :success
)

@if "%CMAKE_COMMAND%" == "test" @(
	call :build
	@if errorlevel 1 @exit /b 1

	call :test
	@if errorlevel 1 @exit /b 1

	goto :success
)

@if "%CMAKE_COMMAND%" == "rebuild" @(
	call :rebuild
	@if errorlevel 1 @exit /b 1

	goto :success
)

@if "%CMAKE_COMMAND%" == "document" @(
	call :document
	@if errorlevel 1 @exit /b 1

	goto :success
)

@if "%CMAKE_COMMAND%" == "install" @(
	call :install
	@if errorlevel 1 @exit /b 1

	call :pack
	@if errorlevel 1 @exit /b 1
	
	goto :success
)

@if "%CMAKE_COMMAND%" == "pack" @(
	call :pack
	@if errorlevel 1 @exit /b 1
	
	goto :success
)

@echo //----------------------------------------------------------------
@echo // default process.
@echo //----------------------------------------------------------------
call :configure
@if errorlevel 1 @exit /b 1

call :build
@if errorlevel 1 @exit /b 1

call :test
@if errorlevel 1 @exit /b 1

goto :success

:configure
@echo //------------------------------------------------------------------------------
@echo // configuration
@echo //------------------------------------------------------------------------------
"%CMAKE%" ^
	%CMAKE_CONFIGURE_FLAGS% ^
	%CMAKE_SRC_DIR%
@if errorlevel 1 @(
	@echo %~f0 : error : configuration process failed.
	@exit /b 1
)
@exit /b 0

:build
@echo //------------------------------------------------------------------------------
@echo // build
@echo //------------------------------------------------------------------------------
"%CMAKE%" ^
	%CMAKE_BUILD_FLAGS% ^
	%CMAKE_BUILD_TARGET% ^
	-- %CMAKE_BUILD_FLAGS_NATIVE%
	@rem | "%SED%" "s/ \+[0-9]\+>//g"
@if errorlevel 1 @(
	@echo %~f0 : error : build process failed.
	@exit /b 1
)
@exit /b 0

:clean
@echo //------------------------------------------------------------------------------
@echo // clean
@echo //------------------------------------------------------------------------------
"%CMAKE%" ^
	%CMAKE_BUILD_FLAGS% ^
	--target clean ^
	-- %CMAKE_BUILD_FLAGS_NATIVE%
@if errorlevel 1 @(
	@echo %~f0 : error : clean process failed.
	@exit /b 1
)
@exit /b 0

:rebuild
@echo //------------------------------------------------------------------------------
@echo // rebuild
@echo //------------------------------------------------------------------------------
"%CMAKE%" ^
	%CMAKE_BUILD_FLAGS% ^
	--clean-first ^
	%CMAKE_BUILD_TARGET% ^
	-- %CMAKE_BUILD_FLAGS_NATIVE% 
	@rem | "%SED%" "s/ \+[0-9]\+>//g"
@if errorlevel 1 @(
	@echo %~f0 : error : rebuild process failed.
	@exit /b 1
)
@exit /b 0


:test
@echo //------------------------------------------------------------------------------
@echo // testing
@echo //------------------------------------------------------------------------------
"%CTEST%" ^
	%CTEST_FLAGS% ^
	%CTEST_REGEX%
@if errorlevel 1 @(
	@echo %~f0 : error : test process failed.
	@exit /b 1
)
@exit /b 0


:document
@echo //------------------------------------------------------------------------------
@echo // generates document
@echo //------------------------------------------------------------------------------
"%CMAKE%" ^
	%CMAKE_BUILD_FLAGS% ^
	--target doc_hryky_codebase
@if errorlevel 1 @(
	@echo %~f0 : error : running doxygen failed.
	@exit /b 1
)
@exit /b 0


:install
@echo //------------------------------------------------------------------------------
@echo // installation
@echo //------------------------------------------------------------------------------
"%CMAKE%" ^
	%CMAKE_BUILD_FLAGS% ^
	--target INSTALL
@if errorlevel 1 @(
	@echo %~f0 : error : test process failed.
	@exit /b 1
)
@exit /b 0

:pack
@echo //------------------------------------------------------------------------------
@echo // packing
@echo //------------------------------------------------------------------------------
"%CPACK%" ^
	-G "NSIS" ^
	%CPACK_FLAGS%
@if errorlevel 1 @(
	@echo %~f0 : error : pack process failed.
	@exit /b 1
)
@exit /b 0

:success

@echo //------------------------------------------------------------------------------
@echo // cmake for '%CMAKE_SRC_DIR%' succeeded
@echo //------------------------------------------------------------------------------
@popd
@exit /b 0

@endlocal 
