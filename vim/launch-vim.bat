set DEVROOT=V:\develop
set PATH=%PATH%;%DEVROOT%\ctags58;%ProgramFiles(x86)%\GnuWin32\bin
call gvim -g ^
  -S "%USERPROFILE%\vimfiles\Session.vim" ^
  -u "%DEVROOT%\hryky-codebase\vim\vimrc"


