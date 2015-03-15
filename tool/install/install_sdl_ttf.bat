@rem //----------------------------------------------------------------
@rem // build & install SDL_ttf
@rem // $Id: install_sdl_ttf.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@rem //----------------------------------------------------------------

@setlocal

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@set SRCROOT=%EXTERNALROOT%/SDL_ttf-2.0.9
@set DESTROOT=%MODULEROOT%/SDL_ttf
@set INCDIR=%DESTROOT%/include
@set LIBDIR=%DESTROOT%/lib
@set SOLUTION=%SRCROOT%/VisualC/SDL_ttf.sln
@set OUTPUTROOT=%SRCROOT%/VisualC

@echo //--------------------------------
@echo // copy include files
@echo //--------------------------------
@call %RUBY% %COPY% %SRCROOT%/SDL_ttf.h %INCDIR%/SDL_ttf.h

@echo //--------------------------------
@echo // build SDL_ttf as Debug configuration for 32bit XP
@echo //--------------------------------
@call %BUILDSOLUTION% %SOLUTION% Debug Debug x86 xp

@call %RUBY% %COPY% %OUTPUTROOT%/Debug/SDL_ttf.dll %LIBDIR%/debug/SDL_ttf.dll
@call %RUBY% %COPY% %OUTPUTROOT%/Debug/SDL_ttf.lib %LIBDIR%/debug/SDL_ttf.lib

@echo //--------------------------------
@echo // build SDL_ttf as Release configuration for 32bit XP
@echo //--------------------------------
@call %BUILDSOLUTION% %SOLUTION% Release Release x86 xp

@call %RUBY% %COPY% %OUTPUTROOT%/Release/SDL_ttf.dll %LIBDIR%/release/SDL_ttf.dll
@call %RUBY% %COPY% %OUTPUTROOT%/Release/SDL_ttf.lib %LIBDIR%/release/SDL_ttf.lib

@endlocal
