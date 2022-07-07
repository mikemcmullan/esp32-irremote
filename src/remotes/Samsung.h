
#define SAMSUNG_ADDRESS 0x707
#define SAMSUNG_NUM_BUTTONS 43

typedef struct
{
    String btn;
    int value;
    bool repeatable;
} SamsungRemoteButton;

const SamsungRemoteButton SamsungRemote[] {
    { "POWER", 0x2, false },
    { "SOURCE", 0x1, false },
    { "1", 0x4, false },
    { "2", 0x5, false },
    { "3", 0x6, false },
    { "4", 0x8, false },
    { "5", 0x9, false },
    { "6", 0xA, false },
    { "7", 0xC, false },
    { "8", 0xD, false },
    { "9", 0xE, false },
    { "0", 0x11, false },
    { "PRE_CH", 0x13, false },
    { "VOL_UP", 0x7, true },
    { "VOL_DOWN", 0xB, true },
    { "MUTE", 0XF, false },
    { "CH_List", 0x6B, false },
    { "CH_Up", 0x12, false },
    { "CH_Down", 0x10, false },
    { "MEDIA_P", 0x8C, false },
    { "MENU", 0x1A, false },
    { "SLEEP", 0x3, false },
    { "TOOLS", 0x4B, false },
    { "INFO", 0x1F, false },
    { "UP", 0x60, false },
    { "DOWN", 0x61, false },
    { "LEFT", 0x65, false },
    { "RIGHT", 0x62, false },
    { "SELECT", 0x68, false },
    { "RETURN", 0x58, false },
    { "EXIT", 0x2D, false },
    { "A", 0x6c, false },
    { "B", 0x14, false },
    { "C", 0x15, false },
    { "D", 0x16, false },
    { "P_Size", 0x3e, false },
    { "MTS", 0x0, false },
    { "CC", 0x25, false },
    { "STOP", 0x46, false },
    { "REWIND", 0x45, false },
    { "PLAY", 0x47, false },
    { "PAUSE", 0x4a, false },
    { "FAST_FORWARD", 0x4, false }
};