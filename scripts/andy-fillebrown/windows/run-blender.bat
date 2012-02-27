
set BLENDER_DIR=C:\Program Files\Blender Foundation\Blender
set BLENDER_VER=2.62
rem ---------------------------------------------------------------------------

xcopy /q /s /y "%CD%\repo\scripts\blender\addons" "%BLENDER_DIR%\%BLENDER_VER%\scripts\addons"

pushd "%BLENDER_DIR%"
blender
popd
