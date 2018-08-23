@cls
REM mkdir "c:\tcc\bin"
REM @set bin="c:\tcc\bin"
@set bin="c:\windows\system32"
@set def="c:\tcc\lib"
@set headers="c:\tcc\include"

@cls
@echo [--------------------------------------------------]

@cd "���⥬�"
@copy system.h "%headers%\"

@mkdir "%headers%\system\"

@cd "������\src"
@tcc -shared memory.c -o memory.dll
@copy memory.dll "%bin%\"
@del memory.dll
@copy memory.def "%def%\"
@del memory.def
@copy memory.h "%headers%\system\"
@cd ../../

@cd "��⮪� �믮������\src"
@tcc -shared thread.c -o thread.dll
@copy thread.dll "%bin%\"
@del thread.dll
@copy thread.def "%def%\"
@del thread.def
@copy thread.h "%headers%\system\"
@cd ../../

@cd "��䨪�\src"
@tcc -shared graphics.c -o graphics.dll "%def%\memory.def"
@copy graphics.dll "%bin%\"
@del graphics.dll
@copy graphics.def "%def%\"
@del graphics.def
@copy graphics.h "%headers%\system\"
@cd ../../

@cd "����\src"
@tcc -shared mouse.c -o mouse.dll
@copy mouse.dll "%bin%\"
@del mouse.dll
@copy mouse.def "%def%\"
@del mouse.def
@copy mouse.h "%headers%\system\"
@cd ../../

@cd "���������\src"
@tcc -shared keyboard.c -o keyboard.dll
@copy keyboard.dll "%bin%\"
@del keyboard.dll
@copy keyboard.def "%def%\"
@del keyboard.def
@copy keyboard.h "%headers%\system\"
@cd ../../

@cd ../

@cd "��䨪�/2D"

@mkdir "%headers%\graphics\2D"

@cd "��אַ㣮�쭨�\src"
@tcc -shared rectangle.c -o rectangle.dll "%def%\graphics.def"
@copy rectangle.dll "%bin%\"
@del rectangle.dll
@copy rectangle.def "%def%\"
@del rectangle.def
@copy rectangle.h "%headers%\graphics\2D\"
@cd ../../

@mkdir "%headers%\graphics\2D\manipulators"
@cd "����������"

@cd "������\src"
@tcc -shared events.c -o events.dll "%def%\mouse.def" "%def%\keyboard.def"
@copy events.dll "%bin%\"
@del events.dll
@copy events.def "%def%\"
@del events.def
@copy events.h "%headers%\graphics\2D\manipulators\"
@cd ../../

@cd ../../

@echo [##################################################]