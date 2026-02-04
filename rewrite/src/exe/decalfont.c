#include <ctr/decalfont.h>
#include <ctr/test.h>

/* Address: 0x800223f4 */
s32 DecalFont_GetLineWidthStrlen(char* str, s16 len, s32 fontType)
{
	s32 result = 0;
	for (s16 i = 0; i < len && str[i] != '\0'; i++) //go until reach len or nullterm.
	{
		char c = str[i];
		switch (c)
		{
			case '@': // Circle button
			case '[': // Square button
			case '^': // Triangle button
			case '*': // Cross button
				result += fontButtonPixelWidth[fontType];
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