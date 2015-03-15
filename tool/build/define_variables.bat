@echo //----------------------------------------------------------------
@echo // file:
@echo //   define_variables.bat
@echo // brief:
@echo //   define local variables for Windows OS
@echo // version:
@echo //   $Id: define_variables.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@echo //----------------------------------------------------------------

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool
@set EXTERNALROOT=%DEVROOT%/external
@set MODULEROOT=%DEVROOT%/module
@set ASSERT=%TOOLROOT%/build/assert.bat
@set MAKE=%TOOLROOT%/mingw/gnumake.exe
@set TIMESTAMP=%TOOLROOT%/timestamp/timestamp.rb
@set BUILDSOLUTION=%TOOLROOT%/build/build_solution.bat
@set SETUPMSSDK=%TOOLROOT%/build/setup_mssdk.bat
@set CMD=%TOOLROOT%/build/cmd.bat
@set COPY=%TOOLROOT%/fileutil/copy.rb
@set MKDIR=%TOOLROOT%/fileutil/mkdir.rb
@set REMOVE=%TOOLROOT%/fileutil/remove.rb


call %TOOLROOT%/build/define_variables_custom.bat

@set CALLEDDEFINEVARIABLESBAT=yes
