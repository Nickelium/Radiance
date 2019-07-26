#pragma once

//From => glfw3.h

/* The unknown key */
#define RAD_KEY_UNKNOWN            -1

/* Printable keys */
#define RAD_KEY_SPACE              32
#define RAD_KEY_APOSTROPHE         39  /* ' */
#define RAD_KEY_COMMA              44  /* , */
#define RAD_KEY_MINUS              45  /* - */
#define RAD_KEY_PERIOD             46  /* . */
#define RAD_KEY_SLASH              47  /* / */
#define RAD_KEY_0                  48
#define RAD_KEY_1                  49
#define RAD_KEY_2                  50
#define RAD_KEY_3                  51
#define RAD_KEY_4                  52
#define RAD_KEY_5                  53
#define RAD_KEY_6                  54
#define RAD_KEY_7                  55
#define RAD_KEY_8                  56
#define RAD_KEY_9                  57
#define RAD_KEY_SEMICOLON          59  /* ; */
#define RAD_KEY_EQUAL              61  /* = */
#define RAD_KEY_A                  65
#define RAD_KEY_B                  66
#define RAD_KEY_C                  67
#define RAD_KEY_D                  68
#define RAD_KEY_E                  69
#define RAD_KEY_F                  70
#define RAD_KEY_G                  71
#define RAD_KEY_H                  72
#define RAD_KEY_I                  73
#define RAD_KEY_J                  74
#define RAD_KEY_K                  75
#define RAD_KEY_L                  76
#define RAD_KEY_M                  77
#define RAD_KEY_N                  78
#define RAD_KEY_O                  79
#define RAD_KEY_P                  80
#define RAD_KEY_Q                  81
#define RAD_KEY_R                  82
#define RAD_KEY_S                  83
#define RAD_KEY_T                  84
#define RAD_KEY_U                  85
#define RAD_KEY_V                  86
#define RAD_KEY_W                  87
#define RAD_KEY_X                  88
#define RAD_KEY_Y                  89
#define RAD_KEY_Z                  90
#define RAD_KEY_LEFT_BRACKET       91  /* [ */
#define RAD_KEY_BACKSLASH          92  /* \ */
#define RAD_KEY_RIGHT_BRACKET      93  /* ] */
#define RAD_KEY_GRAVE_ACCENT       96  /* ` */
#define RAD_KEY_WORLD_1            161 /* non-US #1 */
#define RAD_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define RAD_KEY_ESCAPE             256
#define RAD_KEY_ENTER              257
#define RAD_KEY_TAB                258
#define RAD_KEY_BACKSPACE          259
#define RAD_KEY_INSERT             260
#define RAD_KEY_DELETE             261
#define RAD_KEY_RIGHT              262
#define RAD_KEY_LEFT               263
#define RAD_KEY_DOWN               264
#define RAD_KEY_UP                 265
#define RAD_KEY_PAGE_UP            266
#define RAD_KEY_PAGE_DOWN          267
#define RAD_KEY_HOME               268
#define RAD_KEY_END                269
#define RAD_KEY_CAPS_LOCK          280
#define RAD_KEY_SCROLL_LOCK        281
#define RAD_KEY_NUM_LOCK           282
#define RAD_KEY_PRINT_SCREEN       283
#define RAD_KEY_PAUSE              284
#define RAD_KEY_F1                 290
#define RAD_KEY_F2                 291
#define RAD_KEY_F3                 292
#define RAD_KEY_F4                 293
#define RAD_KEY_F5                 294
#define RAD_KEY_F6                 295
#define RAD_KEY_F7                 296
#define RAD_KEY_F8                 297
#define RAD_KEY_F9                 298
#define RAD_KEY_F10                299
#define RAD_KEY_F11                300
#define RAD_KEY_F12                301
#define RAD_KEY_F13                302
#define RAD_KEY_F14                303
#define RAD_KEY_F15                304
#define RAD_KEY_F16                305
#define RAD_KEY_F17                306
#define RAD_KEY_F18                307
#define RAD_KEY_F19                308
#define RAD_KEY_F20                309
#define RAD_KEY_F21                310
#define RAD_KEY_F22                311
#define RAD_KEY_F23                312
#define RAD_KEY_F24                313
#define RAD_KEY_F25                314
#define RAD_KEY_KP_0               320
#define RAD_KEY_KP_1               321
#define RAD_KEY_KP_2               322
#define RAD_KEY_KP_3               323
#define RAD_KEY_KP_4               324
#define RAD_KEY_KP_5               325
#define RAD_KEY_KP_6               326
#define RAD_KEY_KP_7               327
#define RAD_KEY_KP_8               328
#define RAD_KEY_KP_9               329
#define RAD_KEY_KP_DECIMAL         330
#define RAD_KEY_KP_DIVIDE          331
#define RAD_KEY_KP_MULTIPLY        332
#define RAD_KEY_KP_SUBTRACT        333
#define RAD_KEY_KP_ADD             334
#define RAD_KEY_KP_ENTER           335
#define RAD_KEY_KP_EQUAL           336
#define RAD_KEY_LEFT_SHIFT         340
#define RAD_KEY_LEFT_CONTROL       341
#define RAD_KEY_LEFT_ALT           342
#define RAD_KEY_LEFT_SUPER         343
#define RAD_KEY_RIGHT_SHIFT        344
#define RAD_KEY_RIGHT_CONTROL      345
#define RAD_KEY_RIGHT_ALT          346
#define RAD_KEY_RIGHT_SUPER        347
#define RAD_KEY_MENU               348

#define RAD_KEY_LAST               RAD_KEY_MENU