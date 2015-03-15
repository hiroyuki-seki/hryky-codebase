@echo //-----------------------------------------------------------------------
@echo // applies 'svn rename' to multiple files.
@echo // usage:
@echo //    svn_rename.bat SRCDIR SRCMODULE DESTMODULE
@echo //        SRCDIR is the path to the directory containing the renamed 
@echo //            files.
@echo //        SRCMODULE is the word to be replaced.
@echo //        DESTMODULE is the word after the substitution.
@echo // version: 
@echo //    $Id: svn-rename.bat 253 2013-10-27 05:06:41Z hryky.private@gmail.com $
@echo //-----------------------------------------------------------------------
@setlocal ENABLEDELAYEDEXPANSION

@set SRCDIR=%1
@set SRCMODULE=%2
@set DESTMODULE=%3

@pushd %SRCDIR%

@for %%F in (%SRCMODULE%*) do @(
	@set TEST=%%F
	@echo rename from !TEST! to !TEST:%SRCMODULE%_=%DESTMODULE%_!
	svn rename !TEST! !TEST:%SRCMODULE%=%DESTMODULE%!
)

@popd

@endlocal

exit /b 0
