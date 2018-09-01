#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED


#include <system/mouse.h>
#include <system/keyboard.h>


import function Boolean is_hover (Byte *border, function Boolean (*on_border)(Byte *border, N_32 x, N_32 y));
import function Boolean pressed  (Byte *border, function Boolean (*on_border)(Byte *border, N_32 x, N_32 y));
import function Boolean clicked  (Byte *border, function Boolean (*on_border)(Byte *border, N_32 x, N_32 y));

import function Boolean move_if_moved(
    Byte              *border,
	function Boolean (*on_border)(Byte *border, N_32 x, N_32 y),
	function N_32    (*get_border_x)(Byte *border),
	function N_32    (*get_border_y)(Byte *border),
	procedure        (*set_border_x)(Byte *border, N_32 x),
	procedure        (*set_border_y)(Byte *border, N_32 y)
);


#endif // EVENTS_H_INCLUDED