#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED


#define __WIN32__


#define import   __attribute__((dllimport)) __attribute__((__stdcall__))
#define export   __attribute__((dllexport)) __attribute__((__stdcall__))


typedef unsigned char          Bit;
typedef unsigned char          Bit8;
typedef unsigned short int     Bit16;
typedef unsigned long int      Bit32;
typedef unsigned long long int Bit64;

typedef struct
{
    Bit8  bit_address;  //должно быть 3 бита
    Bit32 byte_address;
}
Address;

import void initialize_address (Address* address, char* value);

import void print_address (Address* address);

import Bit read_bit_from_memory (Address address);
import void write_bit_in_memory (Address address, Bit bit);

import void next_address (Address* address);
import void previouse_address (Address* address);

import void add_address_to_address (Address* a, Address* b);
import void sub_address_from_address (Address* a, Address* b);


//#define ADDRESS(context, address)\
//    initialize_address((#address))

//#define procedure  void


#define end }

#define loop\
    for(;;)\
        {

#define cycle(from, to, step)\
    N_32 i;\
    for(i = (from); i < (to); i += (step))\
        {

#endif // BASE_H_INCLUDED
