@echo //----------------------------------------------------------------
@echo // file:
@echo //   setup_mssdk.bat
@echo // brief:
@echo //   create environment of Microsoft SDK
@echo // usage:
@echo //   setup_mssdk.bat
@echo // optional environment variables:
@echo //   MSSDK_ARCHITECTURE : target architecture for VS(x86^|x86_amd64^|amd64)
@echo // version:
@echo //   $Id: setup_mssdk.bat 146 2013-02-02 12:17:38Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@rem //--------------------------------
@rem // check prerequisites
@rem //--------------------------------
@if "%vsvars%" == "" @goto error_no_mssdk

@echo //--------------------------------
@echo // set environment variables for Windows SDK
@echo //--------------------------------
call "%vsvars%" %MSSDK_ARCHITECTURE%

:success
@set RETCODE=0
@goto end

:error_no_mssdk
@set RETCODE=1
@call %ASSERT% "in %0, environment variable mssdk is not defined"
@goto end

:error_no_mssdk
@set RETCODE=1
@call %ASSERT% "in %0, environment variable mssdk is not defined"
@goto end

:end
@echo on
@exit /b %RETCODE%
