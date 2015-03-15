@setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS
%BJAM% --prefix="%TARGET_PROGRAM_FILES%\Boost" %BJAM_FLAGS% install
@endlocal

pause

exit /B 0
