#include <ctr/decalfont.h>
#include <ctr/game_tracker.h>
#include <ctr/test.h>
#include <ctr/redux.h>

/* Address: 0x800223f4 */
s32 DecalFont_GetLineWidthStrlen(char* str, u16 len, s32 fontType)
{
	s32 result = 0;
	for (u16 i = 0; i < len && str[i] != '\0'; i++) //go until reach len or nullterm.
	{
		char c = str[i];
		switch (c)
		{
			case '@': // Circle button
			case '[': // Square button
			case '^': // Triangle button
			case '*': // Cross button
				result += fontButtonPixelWidth[fontType] + fontCharPixelWidth[fontType];
				break;
			case ':': // Colon punctuation
			case '.': // Period punctuation
				result += fontPunctuationPixelWidth[fontType];
				break;
			case '\x1':
			case '\x2':
				; //ignore a couple control characters.
			default: // Regular character
				result += fontCharPixelWidth[fontType];
				break;
		}
	}

	TEST_DecalFont_GetLineWidthStrlen(str, len, fontType, result);
	return result;
}

/* Address: 0x800224d0 */
s32 DecalFont_GetLineWidth(char* str, s32 fontType)
{
	s32 result = DecalFont_GetLineWidthStrlen(str, 0xFFFF, fontType);
	TEST_DecalFont_GetLineWidth(str, fontType, result);
	return result;
}

/* Address: 0x800224fc */
//void DecalFont_DrawLineStrlen(char* str, u16 len, s32 posX, s16 posY, s16 fontType, s32 flags)
//{
//	s32 strWidth = DecalFont_GetLineWidthStrlen(str, len, fontType);
//	if (flags & JUSTIFY_CENTER)
//	{
//		posX -= strWidth / 2;
//	}
//	else if (flags & JUSTIFY_RIGHT)
//	{
//		posX -= strWidth;
//	}
//
//	for (u16 i = 0; i < len && str[i] != '\0'; i++)
//	{
//		u32* color = fontColors[flags & 0xfff];
//		s16 pixelWidth = fontCharPixelWidth[fontType];
//		char c = str[i];
//		s16 scale = FP(1);
//		s16 pixWidthExtra = 0;
//		s16 pixHeightExtra = 0;
//		u8 iconID = 0xff;
//
//		if (c == ':' || c == '.')
//		{
//			pixelWidth = fontPunctuationPixelWidth[fontType];
//		}
//		else if (c == '@' || c == '[' || c == '^' || c == '*')
//		{
//			scale = fontButtonScale[fontType];
//			pixHeightExtra = fontButtonPixHeight[fontType];
//			pixelWidth = fontCharPixelWidth[fontType] + fontButtonPixelWidth[fontType];
//			color = fontColors[GRAY];
//		}
//
//		if (c < '\x3')
//		{
//			pixelWidth = 0;
//			iconID = fontIndentIconID[fontType * 2 + c - 1];
//			pixWidthExtra = fontIndentPixelDimensions[fontType * 2];
//			pixHeightExtra = fontIndentPixelDimensions[fontType * 2 + 1];
//		}
//		else if ((u32)(c - 0x21) < 0xdf)
//		{
//			iconID = fontCharacterIconID[c - 0x21];
//		}
//
//		if (iconID != 0xff)
//		{
//			s16 iconGroupID = fontIconGroupID[fontType];
//
//			if (iconID > 0x7f)
//			{
//				iconID -= 0x80;
//				s16 kanaIconGroupID = 15;
//				if (iconGroupID == 4)
//				{
//					kanaIconGroupID = 14;
//				}
//				iconGroupID = kanaIconGroupID;
//			}
//
//			struct Icon** iconPtrArray = ICONGROUP_GETICONS(gGT->iconGroup[iconGroupID]);
//
//			DecalHUD_DrawPolyGT4(
//				iconPtrArray[iconID],
//				posX + pixWidthExtra,
//				posY + pixHeightExtra,
//				NULL,
//				NULL,
//				color[0], color[1], color[2], color[3],
//				0, scale);
//		}
//
//		posX += pixelWidth;
//	}
//}

/* Address: 0x80022878 */
//void DecalFont_DrawLine(char* str, s32 posX, s32 posY, s16 fontType, s32 flags)
//{
//	DecalFont_DrawLineStrlen(str, 0xFFFF, posX, posY, fontType, flags);
//}

/* Address: 0x800228c4 */
//void DecalFont_DrawLineOT(char* str, s32 posX, s32 posY, s16 fontType, s32 flags, u32* ot)
//{
//	u32* ptrOTBackup = e_gameTracker->ptrOT;
//	e_gameTracker->ptrOT = ot;
//	DecalFont_DrawLine(str, posX, posY, fontType, flags);
//	e_gameTracker->ptrOT = ptrOTBackup;
//}

/* Address: 0x80022930 */
//s32 DecalFont_DrawMultiLineStrlen(char* str, u16 len, s16 posX, s16 posY, s16 maxPixLen, s16 fontType, s16 flags)
//{
//
//}

/* Address: 0x80022b34 */
//s32 DecalFont_DrawMultiLine(char* str, s32 posX, s32 posY, s32 maxPixLen, s16 fontType, s32 flags)
//{
//	s32 result = DecalFont_DrawMultiLineStrlen(str, 0xFFFF, posX, posY, maxPixLen, fontType, flags);
//	//TEST_DecalFont_DrawMultiLine(str, posX, posY, maxPixLen, fontType, flags, result);
//	return result;
//}