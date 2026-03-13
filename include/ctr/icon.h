#pragma once

#include <ctr/macros.h>
#include <ctr/lev.h>

typedef struct Icon
{
	char name[16];
	s32 globalIconArrayIndex;
	TextureLayout texLayout;
} Icon;

typedef struct IconGroup
{
	char name[16];
	s16 groupID;
	s16 numIcons;
	Icon* icons[0];
} IconGroup;

#define ICONGROUP_GETICONS(x) (Icon**)((u32)(x) + sizeof(IconGroup))
