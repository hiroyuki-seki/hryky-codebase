@echo //-------------------------------------------------------------------------
@echo // invokes a MSYS Terminal.
@echo // prerequisites
@echo //    define a DEVROOT environment variable.
@echo //    install MinGW under the DEVROOT directory.
@echo // $Id: msys.bat 259 2013-11-08 17:07:14Z hryky.private@gmail.com $
@echo //-------------------------------------------------------------------------

%DEVROOT%\MinGW\msys\1.0\bin\bash --login -i
