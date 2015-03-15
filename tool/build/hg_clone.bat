@echo //----------------------------------------------------------------
@echo // brief:
@echo //    clone Mercurial project
@echo // usage:
@echo //    clone_hg url working_directory
@echo //        url is the URL of the repository
@echo //        working_diretory is the local path for working directory
@echo // version:
@echo //    $Id: hg_clone.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call "%TOOLROOT%/build/define_variables.bat"

@set URL=%1
@if "" == "%URL%" @(
    @echo invalid argument : URL is not specified.
    @goto error
)
@shift

@set WD=%1
@if "" == "%WD%" @(
    @echo invalid argument : Working Directory is not specified.
    @goto error
)
@shift

@if not exist "%HG%" @(
    @echo pre-condition error : %HG% is not exist.
    @goto error
)

@if not exist "%WD%" @(
    @mkdir "%WD%"
)

"%HG%" clone "%URL%" "%WD%"
@if errorlevel 1 @(
    @echo hg failed.
    @goto error
)


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
