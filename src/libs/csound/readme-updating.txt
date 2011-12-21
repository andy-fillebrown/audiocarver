
Use the following command to update the Csound source on Windows:

xcopy /d /s /u /y <csound-repository-directory> <audiocarver-repository-directory>\src\libs\csound\src

The use of the /d switch makes is such that only files in the csound repository
that are more recent than the files in the audiocarver repository are copied
over.

The use of the /s switch makes files in subdirectories get copied over.

The use of the /u switch makes it such that only the files already existing in
the audiocarver repository are copied over.

The use of the /y switch makes it such that the user is not prompted to
for Yes/No/All when overwriting existing files.
