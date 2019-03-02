//https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-_display_devicea
typedef struct
{
    Bit32 structure_size;
    Bit8  device_name[32];
    Bit8  device_context_name[128];
    Bit32 state;
    Bit8  device_id[128];
    Bit8  device_key[128];
}
Dispaly;

//https://vxlab.info/wasm/article.php-article=Multimon.htm
typedef enum
{
    DISPLAY_IS_ATTACHED_TO_DESKTOP  = 0x00000001,
    DISPLAY_IS_MULTI_DRIVER         = 0x00000002,
    DISPLAY_IS_PRIMARY_DEVICE       = 0x00000004,
    DISPLAY_IS_MIRRORING_DRIVER     = 0x00000008,
    DISPLAY_IS_VGA_COMPATIBLE       = 0x00000010,
}
Display_States;

//https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-_devicemodea
typedef struct
{
    Bit8 device_name[32];
    Bit32 version;
    Bit16 structure_size;
    Bit16 private_structure_size;
    Bit32 fields;

    union {
        struct
        {
            Bit16 orientaion;
            Bit16 paper_size;
            Bit16 paper_length;
            Bit16 paper_width;
            Bit16 scale;
            Bit16 copies;
            Bit16 default_score;
            Bit16 quality;
        }
        printer;

        struct
        {
            Bit32 x;
            Bit32 y;
        }
        position;

        struct
        {
            struct
            {
                Bit32 x;
                Bit32 y;
            }
            position;

            Bit32 orientaion;
            Bit32 output;
        }
        display;
    };

    Bit16 color;
    Bit16 duplex;
    Bit16 y_resolution;
    Bit16 option;
    Bit16 collate;
    Bit8  form_name[32];
    Bit16 pixels_per_inch;
    Bit32 bits_per_pixel;
    Bit32 width;
    Bit32 height;

    union
    {
        Bit32 display_flags;
        Bit32 NUP;
    };

    Bit32 frequency;
    Bit32 ICM_method;
    Bit32 ICM_intent;
    Bit32 media_type;
    Bit32 dither_type;
    Bit32 reserved1;
    Bit32 reserved2;
    Bit32 panning_width;
    Bit32 panning_height;
}
Dispaly_Mode;

//http://www.asmcommunity.net/forums/topic/?id=2281
typedef enum
{
    DM_PELSWIDTH        = 0x00080000,
    DM_PELSHEIGHT       = 0x00100000,
    DM_DISPLAYFREQUENCY = 0x00400000
}
Display_Mode_Flags;

//https://gist.github.com/curzona/92cdeb66e850846c1e69f29b63f34691
typedef enum
{
    CDS_UPDATEREGISTRY       = 0x00000001,
    CDS_RESET                = 0x40000000
}
Change_Display_Settings_Flags;