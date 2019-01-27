#include "base.h"


export void initialize_address (Address* address, char* value)
{
    Bit32   i;

    address->bit_address = 0;
    address->byte_address = 0;

    for(i = 0; *value && i < 3; ++i, ++value)
        if(*value == '1')
            address->bit_address |= 1 << i;

    for(i = 0; *value && i < 32; ++i, ++value)
        if(*value == '1')
            address->byte_address |= 1 << i;
}


export void print_address (Address* address)
{
    Bit32 i;

    for(i = 0; i < 3; ++i)
        if(address->bit_address & (1 << i))
            printf("1");
        else
            printf("0");

    for(i = 0; i < 32; ++i)
        if(address->byte_address & (1 << i))
            printf("1");
        else
            printf("0");
}


export Bit read_bit_from_memory (Address address)
{
    return (*((Bit8*)address.byte_address) >> address.bit_address) & 1;
}


export void write_bit_in_memory (Address address, Bit bit)
{
    *((Bit8*)address.byte_address) = bit << address.bit_address;
}


export void next_address (Address* address)
{
    ++address->bit_address;

    if((address->bit_address & 0b111) == 0b000)
    {
        ++address->byte_address;
        address->bit_address = 0;
    }
}


export void previouse_address (Address* address)
{
    --address->bit_address;

    if((address->bit_address & 0b111) == 0b111)
    {
        --address->byte_address;
        address->bit_address = 0b111;
    }
}


export void add_address_to_address (Address* a, Address* b)
{
    a->bit_address += b->bit_address;

    a->byte_address += a->bit_address >> 3;
    a->bit_address = a->bit_address & 0b111;

    a->byte_address += b->byte_address;

    //не проверено переполнение
}


export void sub_address_from_address (Address* a, Address* b)
{
    a->bit_address -= b->bit_address;

    a->byte_address -= a->bit_address >> 3;
    a->bit_address = a->bit_address & 0b111;

    a->byte_address -= b->byte_address;

    //не работает переполнение
}


Bit32 main()
{
    /*
    Address a;
    a.byte_address = 1;
    a.bit_address = 0;
    printf("%d", *((Bit8*)&a));
    */

    //Bit8 a = 0b10;

    /*
    Address a;
    Bit32 i;

    initialize_address(&a, "0");

    for(i = 0; i < 20; ++i)
    {
        print_address(&a);
        next_address(&a);
        printf("\n");
    }
    */

    /*
    Address a;
    Bit32 i;

    initialize_address(&a, "11111");

    for(i = 0; i < 40; ++i)
    {
        print_address(&a);
        previouse_address(&a);
        printf("\n");
    }
    */

    /*
    Address a;
    Address b;

    initialize_address(&a, "11101101");
    initialize_address(&b, "10110101");

    add_address_to_address(&a, &b);
    print_address(&a);
    */

    /*
    Address a;
    Address b;

    initialize_address(&a, "10110101");
    initialize_address(&b, "11101101");

    sub_address_from_address(&a, &b);
    print_address(&a);
    */

    Address memory;

    memory.byte_address = malloc(1024);
    memory.bit_address = 0;

    write_bit_in_memory(memory, 0);
    printf("%d", read_bit_from_memory(memory));

    next_address(&memory);
    write_bit_in_memory(memory, 1);
    printf("%d", read_bit_from_memory(memory));

    return 0;
}
