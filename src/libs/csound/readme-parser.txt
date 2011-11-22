
To build Csound using the new parser there are three files that need to be
generated using bison and flex ...

csound_orcparse.c
csound_orcparse.h
csound_orclex.c

On Windows:
- Start msys
- cd to <csound-repository>/Engine
- bison -d --report=itemset -pcsound_orc csound_orc.y
- rename csound_orc.tab.h to csound_orcparse.h
- rename csound_orc.tab.c to csound_orcparse.c
- flex -Pcsound_orc csound_orc.l
- rename lex.csound_orc.c to csound_orclex.c
