#include <common.h>

void DECOMP_CDSYS_SpuCallbackTransfer()
{
	
// PS1
#ifndef USE_PCDRV

	if (sdata->irqAddr == 0)
		sdata->irqAddr = 0x200;
	
	else
		sdata->irqAddr = 0;
	
	SpuSetIRQAddr(sdata->irqAddr);
	
	SpuSetIRQ(1);
	
	sdata->countPass_CdTransferCallback++;
	
	DECOMP_CDSYS_SpuGetMaxSample();

#endif

}