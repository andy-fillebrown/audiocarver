
@if "%BLENDER_DIR%."=="." goto blender_dir_not_set

"%BLENDER_DIR%\blender.exe" ..\..\..\testing\audiosculpture-rig.blend
@exit

:blender_dir_not_set
@echo.
@echo error: BLENDER_DIR not set.
@echo.
@pause
@exit
