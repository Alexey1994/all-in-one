//https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-_display_devicea
typedef struct
{
    N_32 structure_size;
    Byte device_name[32];
    Byte device_context_name[128];
    N_32 state;
    Byte device_id[128];
    Byte device_key[128];
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
    Byte device_name[32];
    N_32 version;
    N_16 structure_size;
    N_16 private_structure_size;
    N_32 fields;

    union {
        struct
        {
            N_16 orientaion;
            N_16 paper_size;
            N_16 paper_length;
            N_16 paper_width;
            N_16 scale;
            N_16 copies;
            N_16 default_score;
            N_16 quality;
        }
        printer;

        struct
        {
            N_32 x;
            N_32 y;
        }
        position;

        struct
        {
            struct
            {
                N_32 x;
                N_32 y;
            }
            position;

            N_32 orientaion;
            N_32 output;
        }
        display;
    };

    N_16 color;
    N_16 duplex;
    N_16 y_resolution;
    N_16 option;
    N_16 collate;
    Byte form_name[32];
    N_16 pixels_per_inch;
    N_32 bits_per_pixel;
    N_32 width;
    N_32 height;

    union
    {
        N_32 display_flags;
        N_32 NUP;
    };

    N_32 frequency;
    N_32 ICM_method;
    N_32 ICM_intent;
    N_32 media_type;
    N_32 dither_type;
    N_32 reserved1;
    N_32 reserved2;
    N_32 panning_width;
    N_32 panning_height;
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