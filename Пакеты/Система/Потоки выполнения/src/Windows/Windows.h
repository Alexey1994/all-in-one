typedef struct
{
	Bit32 length;
	Bit8* security_descriptor;
	Bit8  is_inherit_handle;
}
Windows_Sequrity_Attributes;


import void  Sleep        (Bit32 milliseconds);
import Bit32 CreateThread (
	Windows_Sequrity_Attributes* security_attributes,
	Bit32                        stack_size,
	void                       (*thread_function)(Bit8* arguments),
	Bit8*                        attributes,
	Bit32                        creation_flags,
	Bit32*                       thread_id
);

#include "Windows.c"