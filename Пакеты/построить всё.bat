@cls
@mkdir "c:\tcc\bin"
@mkdir "c:\tcc\def"
@set bin="c:\tcc\bin"
@set def="c:\tcc\def"
@set headers="c:\tcc\include"

@cls
@echo [--------------------------------------------------]

@cd "Система"
@copy system.h "%headers%\"

@mkdir "%headers%\system\"

@cd "Память\src"
@tcc -shared memory.c -o memory.dll
@copy memory.dll "%bin%\"
@del memory.dll
@copy memory.def "%def%\"
@del memory.def
@copy memory.h "%headers%\system\"
@cd ../../

@cd "Потоки выполнения\src"
@tcc -shared thread.c -o thread.dll
@copy thread.dll "%bin%\"
@del thread.dll
@copy thread.def "%def%\"
@del thread.def
@copy thread.h "%headers%\system\"
@cd ../../

@REM @tcc tests.c "%def%\memory.def"

@cd ../

@echo [##################################################]