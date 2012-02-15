
@rem ---------------------------------------------------------------------------
@set INSTRUMENT_DIR=..\src\plugins\ac_synthesizer\instruments
@set INSTRUMENT=sine--smooth-envelope
@set AC=test11.ac
@set TRACK=track
@rem ---------------------------------------------------------------------------

@set ORC=%INSTRUMENT_DIR%\%INSTRUMENT%.orc
@set SCO=%AC%-output\csound\%TRACK%.sco

@if not exist %SCO% ^
echo. && ^
echo Error: %SCO% does not exist. && ^
echo Build test11.ac before running this script. && ^
echo. && ^
goto end

@set INCDIR=%INSTRUMENT_DIR%

csound -odac %ORC% %SCO%

@echo.

:end
@pause
