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

@call %TOOLROOT%/build/define_variables.bat

@if "x64" == "%TARGET_ARCHITECTURE%" (
	@set BJAM_ADDRESS_MODEL=64
) else (
	@set BJAM_ADDRESS_MODEL=32
)

@set BOOST_ROOT=%DEVROOT%\boost_1_55_0
@set INTERMEDIATE=%DEVROOT%\intermediate\boost\%TARGET_ARCHITECTURE%
@set OUTPUT=%DEVROOT%\output\boost\%TARGET_ARCHITECTURE%
@set BJAM=b2.exe
@set BJAM_WITH=--with-chrono --with-date_time --with-filesystem --with-math --with-program_options --with-random --with-regex --with-serialization --with-system --with-thread
@set BJAM_FLAGS=--build-dir="%INTERMEDIATE%" %BJAM_WITH% toolset=msvc-12.0 address-model=%BJAM_ADDRESS_MODEL% link=static threading=multi runtime-link=static
@set BJAM_CLEAN_FIRST=

set DEVENVCONFIG=Debug
set DEVENVPLATFORM=%TARGET_ARCHITECTURE%

@pushd "%BOOST_ROOT%"

call bootstrap.bat

@if "yes" == "%BJAM_CLEAN_FIRST" (
%BJAM% --stagedir="%OUTPUT%" %BJAM_FLAGS% --clean stage
@if errorlevel 1 @goto error
)

%BJAM% --stagedir="%OUTPUT%" %BJAM_FLAGS% stage
@if errorlevel 1 @goto error

%BJAM% --prefix="%TARGET_PROGRAM_FILES%\Boost" %BJAM_FLAGS% install
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
