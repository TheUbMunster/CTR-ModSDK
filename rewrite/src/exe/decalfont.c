#include <ctr/decalfont.h>
#include <ctr/game_tracker.h>
#include <ctr/icon.h>
#include <ctr/test.h>
#include <ctr/redux.h>

#define GT_OFFSET_BACKBUFFER 0x10
#define GT_OFFSET_ICONGROUPS 0x2114
#define DB_OFFSET_PRIMMEM 0x74

static force_inline void* DecalFont_GetPrimMem(void)
{
	void* backBuffer = *(void**)((u8*)e_gameTracker + GT_OFFSET_BACKBUFFER);
	if (backBuffer == nullptr) { return nullptr; }
	return (void*)((u8*)backBuffer + DB_OFFSET_PRIMMEM);
}

static force_inline IconGroup** DecalFont_GetIconGroups(void)
{
	return (IconGroup**)((u8*)e_gameTracker + GT_OFFSET_ICONGROUPS);
}

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
				break;
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
void DecalFont_DrawLineStrlen(char* str, u16 len, s32 posX, s16 posY, s16 fontType, s32 flags)
{
	if ((flags & (JUSTIFY_CENTER | JUSTIFY_RIGHT)) != 0)
	{
		s32 alignX = DecalFont_GetLineWidthStrlen(str, len, fontType);
		if ((flags & JUSTIFY_CENTER) != 0) { alignX >>= 1; }
		posX -= alignX;
	}

	for (u16 i = 0; i < len && str[i] != '\0'; i++)
	{
		u8 c = (u8)str[i];
		u32* color = fontColors[flags & 0xFFF];
		s16 pixelWidth = fontCharPixelWidth[fontType];
		s16 scale = FP(1);
		s16 pixWidthExtra = 0;
		s16 pixHeightExtra = 0;
		u8 iconID = 0xFF;

		if (c == ':' || c == '.')
		{
			pixelWidth = fontPunctuationPixelWidth[fontType];
		}
		else if (c == '@' || c == '[' || c == '^' || c == '*')
		{
			scale = fontButtonScale[fontType];
			pixHeightExtra = fontButtonPixHeight[fontType];
			pixelWidth = fontCharPixelWidth[fontType] + fontButtonPixelWidth[fontType];
			color = fontColors[GRAY];
		}

		if (c < 3)
		{
			pixelWidth = 0;
			iconID = fontIndentIconID[fontType * 2 + c - 1];
			pixWidthExtra = fontIndentPixelDimensions[fontType * 2];
			pixHeightExtra = fontIndentPixelDimensions[fontType * 2 + 1];
		}
		else if ((u32)(c - 0x21) < 0xDF)
		{
			iconID = fontCharacterIconID[c - 0x21];
		}

		if (iconID != 0xFF)
		{
			s16 iconGroupID = fontIconGroupID[fontType];
			if (iconID > 0x7F)
			{
				iconID -= 0x80;
				iconGroupID = (iconGroupID == 4) ? 14 : 15;
			}

			IconGroup* iconGroup = DecalFont_GetIconGroups()[iconGroupID];
			if (iconGroup != nullptr)
			{
				if ((u16)iconID < (u16)iconGroup->numIcons)
				{
					Icon* icon = iconGroup->icons[iconID];
					ND_DecalHUD_DrawPolyGT4(
						icon,
						(s16)posX + pixWidthExtra,
						posY + pixHeightExtra,
						DecalFont_GetPrimMem(),
						e_gameTracker->ptrOT,
						color[0], color[1], color[2], color[3],
						0,
						scale);
				}
			}
		}

		posX += pixelWidth;
	}
}

/* Address: 0x80022878 */
void DecalFont_DrawLine(char* str, s32 posX, s32 posY, s16 fontType, s32 flags)
{
	DecalFont_DrawLineStrlen(str, 0xFFFF, posX, posY, fontType, flags);
}

/* Address: 0x800228c4 */
void DecalFont_DrawLineOT(char* str, s32 posX, s32 posY, s16 fontType, s32 flags, u32* ot)
{
	u32* ptrOTBackup = e_gameTracker->ptrOT;
	e_gameTracker->ptrOT = ot;
	DecalFont_DrawLine(str, posX, posY, fontType, flags);
	e_gameTracker->ptrOT = ptrOTBackup;
}

/* Address: 0x80022930 */
s32 DecalFont_DrawMultiLineStrlen(char* str, s16 len, s16 posX, s16 posY, s16 maxPixLen, s16 fontType, s16 flags)
{
	char* const inputStr = str;
	const s16 inputLen = len;
	const s16 inputPosX = posX;
	const s16 inputPosY = posY;
	const s16 inputMaxPixLen = maxPixLen;
	const s16 inputFontType = fontType;
	const s16 inputFlags = flags;

	char strCharacter;
	s16 lineLen;
	char* currPointer;
	s16 lettersRemaining;
	char* strPointer;
	s32 totalPassageHeight = 0;

	while (1)
	{
		strPointer = str;

		if (*str != '\r')
		{
			strCharacter = *str;
			while (1)
			{
				currPointer = strPointer;
				lettersRemaining = len;

				if ((strCharacter == ' ') && (len != 0))
				{
					currPointer = strPointer + 1;
					lettersRemaining = len - 1;
				}

				strCharacter = *currPointer;
				if ((strCharacter == '\0') || (lettersRemaining == 0)) { break; }

				if ((strCharacter != ' ') && (strCharacter != '\r'))
				{
					while (lettersRemaining != 0)
					{
						currPointer++;
						strCharacter = *currPointer;
						lettersRemaining--;
						if ((strCharacter == '\0') || (strCharacter == ' ') || (strCharacter == '\r')) { break; }
					}
				}

				lineLen = DecalFont_GetLineWidthStrlen(str, (u16)(currPointer - str), fontType);
				if (maxPixLen <= lineLen)
				{
					break;
				}

				strCharacter = *currPointer;
				strPointer = currPointer;
				len = lettersRemaining;
				if (strCharacter == '\r') { break; }
			}
		}

		DecalFont_DrawLineStrlen(str, (u16)(strPointer - str), posX, posY + totalPassageHeight, fontType, flags);
		totalPassageHeight += fontCharPixelHeight[fontType];

		if (*strPointer == '\0')
		{
			TEST_DecalFont_DrawMultiLineStrlen(inputStr, inputLen, inputPosX, inputPosY, inputMaxPixLen, inputFontType, inputFlags, totalPassageHeight);
			return totalPassageHeight;
		}

		if (len != 0)
		{
			strPointer++;
			len--;
		}

		if ((*strPointer == '\0') || (len == 0))
		{
			TEST_DecalFont_DrawMultiLineStrlen(inputStr, inputLen, inputPosX, inputPosY, inputMaxPixLen, inputFontType, inputFlags, totalPassageHeight);
			return totalPassageHeight;
		}
		str = strPointer;
	}
}

/* Address: 0x80022b34 */
s32 DecalFont_DrawMultiLine(char* str, s32 posX, s32 posY, s32 maxPixLen, s16 fontType, s32 flags)
{
	s32 result = DecalFont_DrawMultiLineStrlen(str, -1, posX, posY, maxPixLen, fontType, flags);
	TEST_DecalFont_DrawMultiLine(str, posX, posY, maxPixLen, fontType, flags, result);
	return result;
}
