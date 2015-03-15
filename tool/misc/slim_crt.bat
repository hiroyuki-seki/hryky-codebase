REM
REM This script takes libcmt.lib for VS2005 and removes the allocation related
REM functions from it.
REM
REM Usage: prep_libcmt.bat <VCInstallDir> <OutputFile>
REM
REM VCInstallDir is the path where VC is installed, typically:
REM    C:\Program Files\Microsoft Visual Studio 8\VC\
REM
REM OutputFile is the directory where the modified libcmt file should be stored.
REM

@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@echo //--------------------------------
@echo // set environment for Microsoft SDK
@echo //--------------------------------
@call %SETUPMSSDK%
@echo

@call %TOOLROOT%/build/define_variables.bat

@cd %~dp0

@set INDIR=%VSINSTALLDIR%\VC\lib\amd64\
@set OUTDIR=%DEVROOT%\output\slimmed_crt\amd64\

@echo //--------------------------------
@echo // Release
@echo //--------------------------------

@set INCMT=%INDIR%\libcmt.lib
@set INCMTPDB=%INDIR%\libcmt.pdb
@set OUTCMT=%OUTDIR%\libcmt.lib
@set OBJDIR=f:\dd\vctools\crt_bld\SELF_64_amd64\crt\src\build\amd64\mt_obj\

MKDIR %OUTDIR%
COPY "%INCMT%" "%OUTDIR%"
COPY "%INCMTPDB%" "%OUTDIR%"

@lib /list "%OUTCMT%"

LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%malloc.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%free.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%realloc.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%calloc.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%new.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%delete.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%new2.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%delete2.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%align.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%msize.obj %OUTCMT%

LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%heapinit.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%expand.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%heapchk.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%heapwalk.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%heapmin.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%sbheap.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%smalheap.obj %OUTCMT% 

@echo //--------------------------------
@echo // Debug
@echo //--------------------------------

@set INCMT=%INDIR%\libcmtd.lib
@set INCMTPDB=%INDIR%\libcmtd.pdb
@set OUTCMT=%OUTDIR%\libcmtd.lib
@set OBJDIR=f:\dd\vctools\crt_bld\SELF_64_amd64\crt\src\build\amd64\xmt_obj\

MKDIR %OUTDIR%
COPY "%INCMT%" "%OUTDIR%"
COPY "%INCMTPDB%" "%OUTDIR%"

@lib /list "%OUTCMT%"

LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%malloc.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%free.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%realloc.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%calloc.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%new.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%delete.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%new2.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%delete2.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%align.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%msize.obj %OUTCMT%

LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%heapinit.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%expand.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%heapchk.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%heapwalk.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%heapmin.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%sbheap.obj %OUTCMT%
LIB /IGNORE:4006,4221 /REMOVE:%OBJDIR%smalheap.obj %OUTCMT% 

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
