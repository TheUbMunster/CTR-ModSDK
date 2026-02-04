#pragma once

#include <ctr/macros.h>

extern short fontCharPixelWidth[4]; //0x80082360
extern short fontButtonPixelWidth[4]; //0x80082460
extern short fontPunctuationPixelWidth[4]; //0x80082370

s32 DecalFont_GetLineWidthStrlen(char* str, s16 len, s32 fontType);
s32 DecalFont_GetLineWidth(char* str, s16 fontType);
void DecalFont_DrawLineStrlen(u8* str, s16 len, s32 posX, s16 posY, s16 fontType, s32 flags);
void DecalFont_DrawLine(char* str, s32 posX, s32 posY, s16 fontType, s32 flags);
void DecalFont_DrawLineOT(char* str, s32 posX, s32 posY, s16 fontType, s32 flags, u32* ot);
s32 DecalFont_DrawMultiLineStrlen(char* str, s16 len, s16 posX, s16 posY, s16 maxPixLen, s16 fontType, s16 flags);
s32 DecalFont_DrawMultiLine(char* str, s32 posX, s32 posY, s32 maxPixLen, s16 fontType, s32 flags);