@cls
mkdir "c:\tcc\bin"
@set bin="c:\tcc\bin"
REM @set bin="c:\windows\system32"
@set def="c:\tcc\lib"
@set headers="c:\tcc\include"

@cls
@echo [--------------------------------------------------]

@cd "���⥬�"
@copy system.h "%headers%\"

@mkdir "%headers%\system\"

@cd "������\src"
@tcc -shared memory.c -o system_memory.dll
@copy system_memory.dll "%bin%\"
@del system_memory.dll
@copy system_memory.def "%def%\"
@del system_memory.def
@copy memory.h "%headers%\system\"
@cd ../../

@cd "����\src"
@tcc -shared file.c -o system_file.dll "%def%\memory.def"
@copy system_file.dll "%bin%\"
@del system_file.dll
@copy system_file.def "%def%\"
@del system_file.def
@copy file.h "%headers%\system\"
@cd ../../

@cd "��⮪� �믮������\src"
@tcc -shared thread.c -o system_thread.dll
@copy system_thread.dll "%bin%\"
@del system_thread.dll
@copy system_thread.def "%def%\"
@del system_thread.def
@copy thread.h "%headers%\system\"
@cd ../../

@cd "��ᯫ��\src"
@tcc -shared display.c -o system_display.dll "%def%\user32.def" "%def%\memory.def"
@copy system_display.dll "%bin%\"
@del system_display.dll
@copy system_display.def "%def%\"
@del system_display.def
@copy display.h "%headers%\system\"
@cd ../../

@cd "��䨪�\src"
@tcc -shared graphics.c -o system_graphics.dll "%def%\system_memory.def"
@copy system_graphics.dll "%bin%\"
@del system_graphics.dll
@copy system_graphics.def "%def%\"
@del system_graphics.def
@copy graphics.h "%headers%\system\"
@cd ../../

@cd "����\src"
@tcc -shared mouse.c -o system_mouse.dll
@copy system_mouse.dll "%bin%\"
@del system_mouse.dll
@copy system_mouse.def "%def%\"
@del system_mouse.def
@copy mouse.h "%headers%\system\"
@cd ../../

@cd "���������\src"
@tcc -shared keyboard.c "%def%\user32.def" -o system_keyboard.dll
@copy system_keyboard.dll "%bin%\"
@del system_keyboard.dll
@copy system_keyboard.def "%def%\"
@del system_keyboard.def
@copy keyboard.h "%headers%\system\"
@cd ../../

@cd ../

@cd "������\src"
@tcc -shared memory.c -o memory.dll
@copy memory.dll "%bin%\"
@del memory.dll
@copy memory.def "%def%\"
@del memory.def
@copy memory.h "%headers%\"
@cd ../../

@cd "�������� ������"
@mkdir "%headers%\data-structures"

@cd "����\src"
@tcc -shared buffer.c -o data-structures_buffer.dll "%def%\system_memory.def" "%def%\memory.def"
@copy data-structures_buffer.dll "%bin%\"
@del data-structures_buffer.dll
@copy data-structures_buffer.def "%def%\"
@del data-structures_buffer.def
@copy buffer.h "%headers%\data-structures\"
@cd ../../

@cd ../

@cd "����\src"
@tcc -shared input.c -o input.dll "%def%\data-structures_buffer.def"
@copy input.dll "%bin%\"
@del input.dll
@copy input.def "%def%\"
@del input.def
@copy input.h "%headers%\"
@cd ../../

@cd "��䨪�/2D"
@mkdir "%headers%\graphics\2D"

@cd "��אַ㣮�쭨�\src"
@tcc -shared rectangle.c -o graphics_2D_rectangle.dll "%def%\system_graphics.def"
@copy graphics_2D_rectangle.dll "%bin%\"
@del graphics_2D_rectangle.dll
@copy graphics_2D_rectangle.def "%def%\"
@del graphics_2D_rectangle.def
@copy rectangle.h "%headers%\graphics\2D\"
@cd ../../

@cd "�����\src"
@tcc -shared line.c -o graphics_2D_line.dll "%def%\system_graphics.def"
@copy graphics_2D_line.dll "%bin%\"
@del graphics_2D_line.dll
@copy graphics_2D_line.def "%def%\"
@del graphics_2D_line.def
@copy line.h "%headers%\graphics\2D\"
@cd ../../

@cd "������\src"
@tcc -shared events.c -o graphics_2D_events.dll "%def%\system_mouse.def" "%def%\system_keyboard.def"
@copy graphics_2D_events.dll "%bin%\"
@del graphics_2D_events.dll
@copy graphics_2D_events.def "%def%\"
@del graphics_2D_events.def
@copy events.h "%headers%\graphics\2D\"
@cd ../../

@cd ../../

@echo [##################################################]