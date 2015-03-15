@rem //----------------------------------------------------------------
@rem // build & install SDL_image
@rem // $Id: install_sdl_image.bat 80 2012-07-01 07:35:59Z hryky.private@gmail.com $
@rem //----------------------------------------------------------------

@setlocal

@set TOOLROOT=%DEVROOT%/hryky-codebase/tool

@call %TOOLROOT%/build/define_variables.bat

@set SRCROOT=%EXTERNALROOT%/SDL_image-1.2.6
@set DESTROOT=%MODULEROOT%/SDL_image
@set INCDIR=%DESTROOT%/include
@set LIBDIR=%DESTROOT%/lib
@set SOLUTION=%SRCROOT%/VisualC/SDL_image.sln
@set OUTPUTROOT=%SRCROOT%/VisualC

@echo //--------------------------------
@echo // copy include files
@echo //--------------------------------
@call %RUBY% %COPY% %SRCROOT%/SDL_image.h %INCDIR%/SDL_image.h

@echo //--------------------------------
@echo // build SDL_image as Debug configuration for 32bit XP
@echo //--------------------------------
@call %BUILDSOLUTION% %SOLUTION% Debug Debug x86 xp

@call %RUBY% %COPY% %OUTPUTROOT%/Debug/SDL_image.dll %LIBDIR%/debug/SDL_image.dll
@call %RUBY% %COPY% %OUTPUTROOT%/Debug/SDL_image.lib %LIBDIR%/debug/SDL_image.lib

@echo //--------------------------------
@echo // build SDL_image as Release configuration for 32bit XP
@echo //--------------------------------
@call %BUILDSOLUTION% %SOLUTION% Release Release x86 xp

@call %RUBY% %COPY% %OUTPUTROOT%/Release/SDL_image.dll %LIBDIR%/release/SDL_image.dll
@call %RUBY% %COPY% %OUTPUTROOT%/Release/SDL_image.lib %LIBDIR%/release/SDL_image.lib

@endlocal
