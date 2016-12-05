@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install Boost
@echo // usage:
@echo //   install_boost.bat
@echo // version:
@echo //   $Id: install_boost.bat 352 2014-06-08 08:48:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool
@set DEFINE_VARS=%TOOLROOT%/build/define_variables.bat

@if not exist "%DEFINE_VARS%" @(
	@echo The batch to define variables for development is not found.
	@goto :error
)

@call "%DEFINE_VARS%"

@if "x64" == "%TARGET_ARCHITECTURE%" @(
	@set BJAM_ADDRESS_MODEL=64
) else (
	@set BJAM_ADDRESS_MODEL=32
)

@set BOOST_ROOT=%DEVROOT%\boost_1_61_0
@set BUILDDIR=%DEVROOT%\intermediate\boost\%TARGET_ARCHITECTURE%
@set STAGEDIR=%DEVROOT%\output\boost\%TARGET_ARCHITECTURE%
@set OUTPUTDIR=%DEVROOT%\hryky-codebase\external\boost\%TARGET_ARCHITECTURE%
@set BJAM=b2.exe
@set BJAM_WITH=^
	--with-chrono ^
	--with-date_time ^
	--with-filesystem ^
	--with-math ^
	--with-program_options ^
	--with-random ^
	--with-regex ^
	--with-serialization ^
	--with-system ^
	--with-thread
@set BJAM_FLAGS=^
	--build-dir="%BUILDDIR%" ^
	%BJAM_WITH% ^
	toolset=msvc-14.0 ^
	address-model=%BJAM_ADDRESS_MODEL% ^
	link=static ^
	threading=multi ^
	runtime-link=static ^
	-j 8

@set BJAM_CLEAN_FIRST=no

@set DEVENVCONFIG=Debug
@set DEVENVPLATFORM=%TARGET_ARCHITECTURE%

@call %TOOLROOT%/build/setup_mssdk.bat
@if errorlevel 1 @goto :error

@pushd "%BOOST_ROOT%"

@call bootstrap.bat

@if "yes" == "%BJAM_CLEAN_FIRST%" @(
@echo clean first.
@rmdir /s /q "%BUILDDIR%"
@rmdir /s /q "%STAGEDIR%"
@%BJAM% --stagedir="%STAGEDIR%" ^
	%BJAM_FLAGS% ^
	--clean ^
	stage
@if errorlevel 1 @goto error
)

@%BJAM% --stagedir="%STAGEDIR%" ^
	%BJAM_FLAGS% ^
	stage
@if errorlevel 1 @goto error

@%BJAM% --prefix="%OUTPUTDIR%" ^
	%BJAM_FLAGS% ^
	install
@if errorlevel 1 @goto error

@popd

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
