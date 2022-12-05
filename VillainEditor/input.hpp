namespace villain {

namespace ACTION {
enum {
//The key or mouse button was released.
RELEASE                =0,
//The key or mouse button was pressed.
PRESS                  =1,
//The key was held down until it repeated.
REPEAT                 =2
};
}

//joystick hat
namespace HAT {
enum {
CENTERED           =0,
UP                 =1,
RIGHT              =2,
DOWN               =4,
LEFT               =8,
RIGHT_UP           =(RIGHT | UP   ),
RIGHT_DOWN         =(RIGHT | DOWN ),
LEFT_UP            =(LEFT  | UP   ),
LEFT_DOWN          =(LEFT  | DOWN )
};
}

namespace KEY {
enum {
 /* The unknown key */
UNKNOWN            =-1,

/* Printable keys */
SPACE              =32,
APOSTROPHE         =39,  /* ' */
COMMA              =44,  /* , */
MINUS              =45,  /* - */
PERIOD             =46,  /* . */
SLASH              =47,  /* / */
N_0                  =48,
N_1                  =49,
N_2                  =50,
N_3                  =51,
N_4                  =52,
N_5                  =53,
N_6                  =54,
N_7                  =55,
N_8                  =56,
N_9                  =57,
SEMICOLON          =59,  /* ; */
EQUAL              =61,  /* = */
A                  =65,
B                  =66,
C                  =67,
D                  =68,
E                  =69,
F                  =70,
G                  =71,
H                  =72,
I                  =73,
J                  =74,
K                  =75,
L                  =76,
M                  =77,
N                  =78,
O                  =79,
P                  =80,
Q                  =81,
R                  =82,
S                  =83,
T                  =84,
U                  =85,
V                  =86,
W                  =87,
X                  =88,
Y                  =89,
Z                  =90,
LEFT_BRACKET       =91,  /* [ */
BACKSLASH          =92,  /* \ */
RIGHT_BRACKET      =93,  /* ] */
GRAVE_ACCENT       =96,  /* ` */
WORLD_1            =161, /* non-US #1 */
WORLD_2            =162, /* non-US #2 */

/* Function keys */
ESCAPE             =256,
ENTER              =257,
TAB                =258,
BACKSPACE          =259,
INSERT             =260,
DELETE             =261,
RIGHT              =262,
LEFT               =263,
DOWN               =264,
UP                 =265,
PAGE_UP            =266,
PAGE_DOWN          =267,
HOME               =268,
END                =269,
CAPS_LOCK          =280,
SCROLL_LOCK        =281,
NUM_LOCK           =282,
PRINT_SCREEN       =283,
PAUSE              =284,
F1                 =290,
F2                 =291,
F3                 =292,
F4                 =293,
F5                 =294,
F6                 =295,
F7                 =296,
F8                 =297,
F9                 =298,
F10                =299,
F11                =300,
F12                =301,
F13                =302,
F14                =303,
F15                =304,
F16                =305,
F17                =306,
F18                =307,
F19                =308,
F20                =309,
F21                =310,
F22                =311,
F23                =312,
F24                =313,
F25                =314,
KP_0               =320,
KP_1               =321,
KP_2               =322,
KP_3               =323,
KP_4               =324,
KP_5               =325,
KP_6               =326,
KP_7               =327,
KP_8               =328,
KP_9               =329,
KP_DECIMAL         =330,
KP_DIVIDE          =331,
KP_MULTIPLY        =332,
KP_SUBTRACT        =333,
KP_ADD             =334,
KP_ENTER           =335,
KP_EQUAL           =336,
LEFT_SHIFT         =340,
LEFT_CONTROL       =341,
LEFT_ALT           =342,
LEFT_SUPER         =343,
RIGHT_SHIFT        =344,
RIGHT_CONTROL      =345,
RIGHT_ALT          =346,
RIGHT_SUPER        =347,
MENU               =348,

LAST               =MENU
};
}

namespace MOD {
enum {
//If this bit is set one or more Shift keys were held down.
SHIFT           =0x0001,
//If this bit is set one or more Control keys were held down.
CONTROL         =0x0002,
//If this bit is set one or more Alt keys were held down.
ALT             =0x0004,
//If this bit is set one or more Super keys were held down.
SUPER           =0x0008,
//If this bit is set the Caps Lock key is enabled.
CAPS_LOCK       =0x0010,
//If this bit is set the Num Lock key is enabled.
NUM_LOCK        =0x0020

};
}

namespace MOUSE
{
enum {
BUTTON_1         =0,
BUTTON_2         =1,
BUTTON_3         =2,
BUTTON_4         =3,
BUTTON_5         =4,
BUTTON_6         =5,
BUTTON_7         =6,
BUTTON_8         =7,
LAST             =BUTTON_8,
LEFT             =BUTTON_1,
RIGHT            =BUTTON_2,
MIDDLE           =BUTTON_3
};
}

namespace JOYSTICK
{
enum {
B_1             =0,
B_2             =1,
B_3             =2,
B_4             =3,
B_5             =4,
B_6             =5,
B_7             =6,
B_8             =7,
B_9             =8,
B_10            =9,
B_11            =10,
B_12            =11,
B_13            =12,
B_14            =13,
B_15            =14,
B_16            =15,
B_LAST          =B_16
};
}

namespace GAMEPAD {
enum {
BUTTON_A               =0,
BUTTON_B               =1,
BUTTON_X               =2,
BUTTON_Y               =3,
BUTTON_LEFT_BUMPER     =4,
BUTTON_RIGHT_BUMPER    =5,
BUTTON_BACK            =6,
BUTTON_START           =7,
BUTTON_GUIDE           =8,
BUTTON_LEFT_THUMB      =9,
BUTTON_RIGHT_THUMB     =10,
BUTTON_DPAD_UP         =11,
BUTTON_DPAD_RIGHT      =12,
BUTTON_DPAD_DOWN       =13,
BUTTON_DPAD_LEFT       =14,
BUTTON_LAST            =BUTTON_DPAD_LEFT,

BUTTON_CROSS           =BUTTON_A,
BUTTON_CIRCLE          =BUTTON_B,
BUTTON_SQUARE          =BUTTON_X,
BUTTON_TRIANGLE        =BUTTON_Y,

AXIS_LEFT_X            =0,
AXIS_LEFT_Y            =1,
AXIS_RIGHT_X           =2,
AXIS_RIGHT_Y           =3,
AXIS_LEFT_TRIGGER      =4,
AXIS_RIGHT_TRIGGER     =5,
AXIS_LAST              =AXIS_RIGHT_TRIGGER
};
}

struct Cursor
{
 double prev_xpos;
 double prev_ypos;
 double delta_xpos=0.0;
 double delta_ypos=0.0;
};
}
