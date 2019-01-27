#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED


#define __WIN32__


#define import   __attribute__((dllimport)) __attribute__((__stdcall__))
#define export   __attribute__((dllexport)) __attribute__((__stdcall__))


typedef unsigned char          Bit;
typedef unsigned char          Byte;
typedef unsigned char          Boolean;

typedef char                   Z_8;
typedef short int              Z_16;
typedef long int               Z_32;
typedef long long int          Z_64;

typedef unsigned char          N_8;
typedef unsigned short int     N_16;
typedef unsigned long int      N_32;
typedef unsigned long long int N_64;

typedef float                  R_32;
typedef double                 R_64;

/////////////////////////////////////

typedef unsigned char          Bit8;
typedef unsigned short int     Bit16;
typedef unsigned long int      Bit32;
typedef unsigned long long int Bit64;

typedef struct
{
    Bit32 byte_address;
    Bit8  bit_address;
}
Address;

//#define read_bit(address, out)\
//    out = (*((Bit8*)address.)

/////////////////////////////////////

#define private    static
#define procedure  void
#define function
#define in
#define out

#define end }

#define loop\
    for(;;)\
        {

#define cycle(from, to, step)\
    N_32 i;\
    for(i = (from); i < (to); i += (step))\
        {


#endif // SYSTEM_H_INCLUDED
