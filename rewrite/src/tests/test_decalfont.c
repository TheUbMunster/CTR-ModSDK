#include <ctr/test.h>

#ifdef TEST_DECALFONT_IMPL

void TEST_DecalFont_GetLineWidthStrlen(char* str, u16 len, s32 fontType, s32 ret)
{
	const u32 index = PatchFunction_Beg((u32*)(&ND_DecalFont_GetLineWidthStrlen), "DecalFont_GetLineWidthStrlen");
	const s32 expected = ND_DecalFont_GetLineWidthStrlen(str, len, fontType);
	if (expected != ret) { ND_printf("[%s] Test Failed:\nInput: \"%s\" %d %d\nExpected: %d\nResult: %d\n", s_nameTestedFunc, str, len, fontType, expected, ret); }
	PatchFunction_End(index);
}

void TEST_DecalFont_GetLineWidth(char* str, s32 fontType, s32 ret)
{
	const u32 index = PatchFunction_Beg((u32*)(&ND_DecalFont_GetLineWidth), "DecalFont_GetLineWidth");
	const s32 expected = ND_DecalFont_GetLineWidth(str, fontType);
	if (expected != ret) { ND_printf("[%s] Test Failed:\nInput: \"%s\" %d\nExpected: %d\nResult: %d\n", s_nameTestedFunc, str, fontType, expected, ret); }
	PatchFunction_End(index);
}

#endif // TEST_DECALFONT_IMPL