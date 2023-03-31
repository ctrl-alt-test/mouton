.\nasmw.exe -fwin32 -o"4klang.obj" 4klang.asm
copy 4klang.obj ..\intro /Y
copy 4klang.h ..\intro\src /Y
copy 4klang.obj .\WavExport /Y
copy 4klang.h .\WavExport /Y
pause