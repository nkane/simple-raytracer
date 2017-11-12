@ECHO OFF
IF NOT EXIST ..\\build MKDIR ..\build
PUSHD ..\build

cl /Od /MTd /Zi /nologo ..\code\main.c

POPD
