#pragma once

#include <ctr/macros.h>
#include <ctr/rng.h>

typedef union GameTracker
{
	struct
	{
		u8 fill[0x252c];
		RNGSeed seed;
	};
	struct
	{
		u8 fill2[0x147c];
		u32* ptrOT;
	};
} GameTracker;

extern GameTracker* e_gameTracker;