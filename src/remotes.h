
typedef struct
{
    int type;
    String btn;
    int value;
    bool repeatable;
} RemoteButton;

#define HDMI_SWITCHER_ADDRESS 0x80
#define NEC_TYPE 0

const RemoteButton HDMISwitcher[]{
    { NEC_TYPE, "1", 0x5, false},   // 1
    { NEC_TYPE, "2", 0x7, false},   // 2
    { NEC_TYPE, "3", 0x8, false},   // 3
    { NEC_TYPE, "4", 0x9, false},   // 4
    { NEC_TYPE, "5", 0x1B, false},  // 5
};

#define SAMSUNG_ADDRESS 0x707
#define SAMSUNG_TYPE 1

const RemoteButton SamsungRemote[] {
    { SAMSUNG_TYPE, "POWER", 0x2, false },
    { SAMSUNG_TYPE, "SOURCE", 0x1, false },
    { SAMSUNG_TYPE, "1", 0x4, false },
    { SAMSUNG_TYPE, "2", 0x5, false },
    { SAMSUNG_TYPE, "3", 0x6, false },
    { SAMSUNG_TYPE, "4", 0x8, false },
    { SAMSUNG_TYPE, "5", 0x9, false },
    { SAMSUNG_TYPE, "6", 0xA, false },
    { SAMSUNG_TYPE, "7", 0xC, false },
    { SAMSUNG_TYPE, "8", 0xD, false },
    { SAMSUNG_TYPE, "9", 0xE, false },
    { SAMSUNG_TYPE, "0", 0x11, false },
    { SAMSUNG_TYPE, "PRE_CH", 0x13, false },
    { SAMSUNG_TYPE, "VOL_UP", 0x7, true },
    { SAMSUNG_TYPE, "VOL_DOWN", 0xB, true },
    { SAMSUNG_TYPE, "MUTE", 0XF, false },
    { SAMSUNG_TYPE, "CH_List", 0x6B, false },
    { SAMSUNG_TYPE, "CH_Up", 0x12, false },
    { SAMSUNG_TYPE, "CH_Down", 0x10, false },
    { SAMSUNG_TYPE, "MEDIA_P", 0x8C, false },
    { SAMSUNG_TYPE, "MENU", 0x1A, false },
    { SAMSUNG_TYPE, "SLEEP", 0x3, false },
    { SAMSUNG_TYPE, "TOOLS", 0x4B, false },
    { SAMSUNG_TYPE, "INFO", 0x1F, false },
    { SAMSUNG_TYPE, "UP", 0x60, false },
    { SAMSUNG_TYPE, "DOWN", 0x61, false },
    { SAMSUNG_TYPE, "LEFT", 0x65, false },
    { SAMSUNG_TYPE, "RIGHT", 0x62, false },
    { SAMSUNG_TYPE, "SELECT", 0x68, false },
    { SAMSUNG_TYPE, "RETURN", 0x58, false },
    { SAMSUNG_TYPE, "EXIT", 0x2D, false },
    { SAMSUNG_TYPE, "A", 0x6c, false },
    { SAMSUNG_TYPE, "B", 0x14, false },
    { SAMSUNG_TYPE, "C", 0x15, false },
    { SAMSUNG_TYPE, "D", 0x16, false },
    { SAMSUNG_TYPE, "P_Size", 0x3e, false },
    { SAMSUNG_TYPE, "MTS", 0x0, false },
    { SAMSUNG_TYPE, "CC", 0x25, false },
    { SAMSUNG_TYPE, "STOP", 0x46, false },
    { SAMSUNG_TYPE, "REWIND", 0x45, false },
    { SAMSUNG_TYPE, "PLAY", 0x47, false },
    { SAMSUNG_TYPE, "PAUSE", 0x4a, false },
    { SAMSUNG_TYPE, "FAST_FORWARD", 0x4, false }
};