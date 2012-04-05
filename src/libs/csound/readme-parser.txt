
To build Csound using the new parser there are three files that need to be
generated using bison and flex ...

csound_orcparse.c
csound_orcparse.h
csound_orclex.c
csound_prelex.c

On Windows:
- Start msys
- cd to <csound-repository-directory>/Engine
- bison -d --report=itemset -pcsound_orc csound_orc.y
- rename csound_orc.tab.h to csound_orcparse.h
- rename csound_orc.tab.c to csound_orcparse.c
- flex -Pcsound_orc csound_orc.l > csound_orclex.c
- flex -Pcsound_orc csound_pre.lex > csound_prelex.c
- put csound_orcparse.h in <audiocarver-repository-directory>/src/libs/csound/src/H
- put csound_orcparse.c in <audiocarver-repository-directory>/src/libs/csound/src/Engine
- put csound_orclex.c in   <audiocarver-repository-directory>/src/libs/csound/src/Engine
- put csound_prelex.c in   <audiocarver-repository-directory>/src/libs/csound/src/Engine
