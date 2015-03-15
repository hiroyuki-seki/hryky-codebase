@echo //----------------------------------------------------------------
@echo // brief:
@echo //   build and install libxml2
@echo // usage:
@echo //   install_libxml2.bat
@echo // version:
@echo //   $Id: install_libxml2.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@set MODULE=libxml2
@set SRC_DIR=%DEVROOT%\%MODULE%\
@set OUTPUT=%TARGET_PROGRAM_FILES%\%MODULE%
@set CLEAN_FIRST=yes
@set XCOPY=xcopy /E /F /Y 

@echo //----------------------------------------------------------------
@echo // build libxml2 : Debug
@echo //----------------------------------------------------------------

@set INTERMEDIATE=%DEVROOT%\intermediate\%MODULE%\%TARGET_ARCHITECTURE%\Debug

@echo //----------------------------------------------------------------
@echo // ATTENTION :
@echo // to supress error in installation process, define some variables.
@echo //----------------------------------------------------------------
@set LIBPREFIX=%OUTPUT%\lib\Debug
@set BINPREFIX=%OUTPUT%\bin\Debug
@set SOPREFIX=%OUTPUT%\so\Debug

@echo //----------------------------------------------------------------
@echo // configure
@echo //----------------------------------------------------------------
@pushd "%SRC_DIR%"
@pushd win32
cscript configure.js iconv=no compiler=msvc cruntime=/MTd debug=yes static=yes prefix="%INTERMEDIATE%" bindir="%BINPREFIX%" incdir="%OUTPUT%\include" libdir="%LIBPREFIX%" sodir="%SOPREFIX%"
@if errorlevel 1 @goto :error

@call %TOOLROOT%/build/setup_mssdk.bat
@if errorlevel 1 @goto :error

@if "yes" == "%CLEAN_FIRST%" @(
@echo //----------------------------------------------------------------
@echo // clean
@echo //----------------------------------------------------------------
nmake /f Makefile clean
@if errorlevel 1 @goto :error
)

@echo //----------------------------------------------------------------
@echo // build
@echo //----------------------------------------------------------------
nmake /f Makefile all
@if errorlevel 1 @goto :error

@echo //----------------------------------------------------------------
@echo // install
@echo // ATTENTION :
@echo //   Makefile.msvc doesn't quote some path. : e.g. $(INCPREFIX)
@echo //   Make sure to modify Makefile.msvc
@echo //----------------------------------------------------------------
nmake /f Makefile install
@if errorlevel 1 @goto :error

@echo //----------------------------------------------------------------
@echo // build libxml2 : Release
@echo //----------------------------------------------------------------

@set INTERMEDIATE=%DEVROOT%\intermediate\%MODULE%\%TARGET_ARCHITECTURE%\Release

@echo //----------------------------------------------------------------
@echo // ATTENTION :
@echo // to supress error in installation process, define some variables.
@echo //----------------------------------------------------------------
@set LIBPREFIX=%OUTPUT%\lib\Release
@set BINPREFIX=%OUTPUT%\bin\Release
@set SOPREFIX=%OUTPUT%\so\Release

@echo //----------------------------------------------------------------
@echo // configure
@echo //----------------------------------------------------------------
@pushd "%SRC_DIR%"
@pushd win32
cscript configure.js iconv=no compiler=msvc cruntime=/MT debug=no static=yes prefix="%INTERMEDIATE%" bindir="%BINPREFIX%" incdir="%OUTPUT%\include" libdir="%LIBPREFIX%" sodir="%SOPREFIX%"
@if errorlevel 1 @goto :error

@call %TOOLROOT%/build/setup_mssdk.bat
@if errorlevel 1 @goto :error

@if "yes" == "%CLEAN_FIRST%" @(
@echo //----------------------------------------------------------------
@echo // clean
@echo //----------------------------------------------------------------
nmake /f Makefile clean
@if errorlevel 1 @goto :error
)

@echo //----------------------------------------------------------------
@echo // build
@echo //----------------------------------------------------------------
nmake /f Makefile all
@if errorlevel 1 @goto :error

@echo //----------------------------------------------------------------
@echo // install
@echo // ATTENTION :
@echo //   Makefile.msvc doesn't quote some path. : e.g. $(INCPREFIX)
@echo //   Make sure to modify Makefile.msvc
@echo //----------------------------------------------------------------
nmake /f Makefile install
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
