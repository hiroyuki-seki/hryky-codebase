@echo //----------------------------------------------------------------
@echo // brief:
@echo //   call system's cmd.exe with specified options
@echo // usage:
@echo //   cmd.bat PATH
@echo //     PATH is name which is invoked by system's cmd.exe.
@echo // version:
@echo //   $Id: cmd.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@setlocal

@rem //--------------------------------
@rem // define common variables
@rem //--------------------------------
@if not defined "%CALLEDDEFINEVARIABLESBAT%" @(
  @call %DEVROOT%/hryky-codebase/tool/build/define_variables.bat
)

@rem //--------------------------------
@rem // evaluate arguments
@rem //--------------------------------
@set TARGETBAT=%*
@shift

@rem //--------------------------------
@rem // check prerequisites
@rem //--------------------------------
@if "%COMSPEC%" == "" @(
  @echo "COMSPEC" which indicate system's cmd.exe is not defined.
  @set COMSPEC=cmd
)
@if not "%TARGETBAT%" == "" @(
  @set CMDOPTS=%CMDOPTS% /C
)

@rem //--------------------------------
@rem // set environment variables
@rem //--------------------------------
@set CMDOPTS=%CMDOPTS% /E:ON /V:ON

@rem //--------------------------------
@rem // call system's cmd.exe
@rem //--------------------------------
%COMSPEC% %CMDOPTS% %TARGETBAT%

@if ERRORLEVEL 1 @goto error

:success
@set RETCODE=0
@goto end

:error
@set RETCODE=1
@call %ASSERT% "failed to call cmd.exe"
@goto end

:end
@exit /b %RETCODE%
@endlocal
