
set MINGW_DIR=C:\-\usr\bin\mingw
set QT_DIR=C:\-\usr\bin\qt\4.8.0\gnu-x86
rem ---------------------------------------------------------------------------

set PATH=%PATH%;%MINGW_DIR%\bin;%QT_DIR%\lib

pushd build-gnu-x86-r\bin
start audiocarver.exe
popd
