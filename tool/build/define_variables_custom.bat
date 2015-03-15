@echo //------------------------------------------------------------------------------
@echo // file:
@echo //   define_variables_custom.bat
@echo // brief:
@echo //   define local variables
@echo // version:
@echo //   $Id: define_variables_custom.template.bat 768 2010-07-17 18:29:40Z hryky $
@echo //------------------------------------------------------------------------------

@echo //------------------------------------------------------------------------------
@echo // TARGET_ARCHITECTURE is [x64^|x86]
@echo // MSSDK_ARCHITECTURE is [x86^|x86_amd64^|amd64]
@echo //------------------------------------------------------------------------------
@set TARGET_ARCHITECTURE=x64
@set MSSDK_ARCHITECTURE=x86_amd64
@set TARGET_PROGRAM_FILES=%ProgramW6432%

@echo //------------------------------------------------------------------------------
@echo // TARGET_ARCHITECTURE:   %TARGET_ARCHITECTURE%
@echo // MSSDK_ARCHITECTURE:    %MSSDK_ARCHITECTURE%
@echo // TARGET_PROGRAM_FILES:  %TARGET_PROGRAM_FILES%
@echo //------------------------------------------------------------------------------

@set SED=%ProgramFiles(x86)%\GnuWin32\bin\sed.exe
@set GREP=%ProgramFiles(x86)%\GnuWin32\bin\grep.exe
@set AWK=%ProgramFiles(x86)%\GnuWin32\bin\awk.exe
@set WGET=%ProgramFiles(x86)%\GnuWin32\bin\wget.exe
@set FIND=%ProgramFiles(x86)%\GnuWin32\bin\find.exe
@set XARGS=%ProgramFiles(x86)%\GnuWin32\bin\xargs.exe
@set RUBY=C:\bin\ruby\bin\ruby.exe

@set CMAKE=%ProgramFiles(x86)%\CMake 2.8\bin\cmake.exe
@set CMAKEGENERATOR=Visual Studio 12 Win64
@set CTEST=%ProgramFiles(x86)%\CMake 2.8\bin\ctest.exe
@set CPACK=%ProgramFiles(x86)%\CMake 2.8\bin\cpack.exe

@set CYGWIN=C:\cygwin\Cygwin.bat

@set DOXYGEN=%ProgramW6432%\doxygen\bin\doxygen.exe
@set GRAPHVIZDIR=%ProgramFiles(x86)%\Graphviz\bin

@set ANDROID_SDK_ROOT=C:\Android\android-sdk
@set JAVA_HOME=%ProgramW6432%\Java\jdk1.6.0_26

@set SVNDIR=%ProgramW6432%\SlikSvn\bin
@set SVN=%SVNDIR%\svn.exe
@set SVN_EDITOR=%ProgramFiles(x86)%\xyzzy\xyzzy.exe

@set HGDIR=%ProgramW6432%\Mercurial
@set HG=%HGDIR%\hg.exe

@set PATH=%PATH%;%GRAPHVIZDIR%;%SVNDIR%
@set PATH=%PATH%;%ANDROID_SDK_ROOT%\platform-tools;%ANDROID_SDK_ROOT%\tools
@set PATH=%PATH%;%JAVA_HOME%\bin

@set VSINSTALLDIR=%ProgramFiles(x86)%\Microsoft Visual Studio 12.0
@set DEVENV=%ProgramFiles(x86)%\Microsoft Visual Studio 12.0\Common7\IDE\WDExpress.exe
@set VSVARS=%VSINSTALLDIR%\VC\vcvarsall.bat

