#include <common.h>

int DECOMP_LOAD_HowlSectorChainEnd()
{
	int* howlChainParams;
	int howlChainState = sdata->howlChainState;
	howlChainParams = sdata->howlChainParams;
	
	if(howlChainState == -1)
	{
		DECOMP_LOAD_HowlSectorChainStart(
			(CdlFILE*)howlChainParams[0], (void*)howlChainParams[1],
			howlChainParams[2], howlChainParams[3]
		);
	
		return 0;
	}
	
	return (howlChainState == 0);
}