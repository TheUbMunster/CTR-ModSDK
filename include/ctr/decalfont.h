#pragma once

#include <ctr/macros.h>


/*
 * Types needed for full implementation (not yet in include/ctr/):
 * - Full GameTracker struct (backBuffer, iconGroup[], pushBuffer_UI)
 * - PushBuffer struct (ptrOT member)
 * - BackBuffer/PrimMem structs
 * - sdata struct (gGT, font_icon, font_jfont*IconData for JPN builds)
 * - data.font_* arrays (font_charPixWidth, font_buttonPixWidth, font_puncPixWidth,
 *   font_charPixHeight, font_buttonScale, font_buttonPixHeight, font_IconGroupID,
 *   font_characterIconID, font_indentIconID, font_indentPixDimensions, ptrColor)
 *
 * Already defined in namespace_Decal.h:
 * - struct Icon, struct IconGroup, struct TextureLayout
 * - enum Font, enum FontFlags, enum Colors, enum BlendModeDecal
 * - ICONGROUP_GETICONS macro
 */

enum FontFlags
{
	JUSTIFY_RIGHT = 0x4000,
	JUSTIFY_CENTER = 0x8000
};

enum Colors
{
	ORANGE,
	PERIWINKLE,
	ORANGE_DARKENED,
	RED,
	WHITE,
	CRASH_BLUE,
	CORTEX_RED,
	TINY_GREEN,
	COCO_MAGENTA,
	N_GIN_PURPLE,
	DINGODILE_OLIVE,
	POLAR_CYAN,
	PURA_VIOLET,
	PINSTRIPE_PALE_DARK_BLUE,
	PAPU_YELLOW,
	ROO_ORANGE,
	JOE_COLOR,
	TROPY_LIGHT_BLUE,
	PENTA_WHITE,
	FAKE_CRASH_GRAY,
	OXIDE_LIGHT_GREEN,
	BLACK,
	SILVER,
	GRAY,
	PLAYER_BLUE,
	PLAYER_RED,
	PLAYER_GREEN,
	PLAYER_YELLOW,
	DARK_RED,
	LIGHT_GREEN,
	FOREST_GREEN,
	CREDITS_FADE, // written dynamically while credits are running, makes text fade to black bg
	BLUE,
	LIME_GREEN,
	ORANGE_RED,
	NUM_COLORS
};

enum Font
{
	FONT_DEBUG = 0,
	FONT_BIG = 1,
	FONT_SMALL = 2,
	FONT_CREDITS = 3,
	FONT_NUM = 4,
};

extern s16 fontCharPixelWidth[FONT_NUM]; //0x80082360
extern s16 fontButtonPixelWidth[FONT_NUM]; //0x80082460
extern s16 fontPunctuationPixelWidth[FONT_NUM]; //0x80082370
extern u32* fontColors[NUM_COLORS]; //0x80081d70
extern s16 fontButtonScale[FONT_NUM]; //0x80082458
extern s16 fontButtonPixHeight[FONT_NUM]; //0x80082468
extern u8 fontIndentIconID[FONT_NUM * 2]; //0x80082470
extern s16 fontIndentPixelDimensions[FONT_NUM * 2]; //0x80082478
extern u8 fontCharacterIconID[0xE0]; //0x80082378
extern s16 fontIconGroupID[FONT_NUM]; //0x80082358

s32 DecalFont_GetLineWidthStrlen(char* str, u16 len, s32 fontType);
s32 DecalFont_GetLineWidth(char* str, s32 fontType);
//void DecalFont_DrawLineStrlen(char* str, u16 len, s32 posX, s16 posY, s16 fontType, s32 flags);
//void DecalFont_DrawLine(char* str, s32 posX, s32 posY, s16 fontType, s32 flags);
//void DecalFont_DrawLineOT(char* str, s32 posX, s32 posY, s16 fontType, s32 flags, u32* ot);
//s32 DecalFont_DrawMultiLineStrlen(char* str, u16 len, s16 posX, s16 posY, s16 maxPixLen, s16 fontType, s16 flags);
//s32 DecalFont_DrawMultiLine(char* str, s32 posX, s32 posY, s32 maxPixLen, s16 fontType, s32 flags);