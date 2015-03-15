@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install Bjam
@echo // usage:
@echo //   install_bjam.bat
@echo // version:
@echo //   $Id: install_bjam.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@set TOOLSET=msvc
@set SRCROOT=%EXTERNALROOT%/boost-jam-3.1.17
@set BINDIRECTORY=%SRCROOT%/bin.ntx86
@set DESTROOT=%EXTERNALROOT%/boost_1_43_0
@set BJAMFLAGS=%TOOLSET%

@echo //--------------------------------
@echo // set environment for Microsoft SDK
@echo //--------------------------------
@call %SETUPMSSDK%

@cd %SRCROOT:/=\%

@echo //--------------------------------
@echo // build Boost-jam
@echo //--------------------------------
call %SRCROOT%/build.bat %BJAMFLAGS%
@if errorlevel 1 @goto error

@echo //--------------------------------
@echo // copy bjam.exe
@echo //--------------------------------
call %RUBY% %COPY% -v %BINDIRECTORY%/bjam.exe %DESTROOT%/
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
