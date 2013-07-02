<CsoundSynthesizer>
<CsOptions>
-d
-odac
--env:INCDIR=full_path_to_audiocarver_instruments_directory
-+max_str_len=10000
-+skip_seconds=0
</CsOptions>
<CsInstruments>
#include "<.orc file>"
</CsInstruments>
<CsScore>
#include "<full path to .sco file>"
</CsScore>
</CsoundSynthesizer>
