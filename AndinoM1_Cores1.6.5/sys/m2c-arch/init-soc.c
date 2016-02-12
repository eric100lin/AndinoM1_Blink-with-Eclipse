/*
	This file includes weak (i.e. optional) functions to perform SoC related
	initialization. They are:
	1). _nds32_init_mem():
		Executed before C language initialization to make memory
		ready so that program data can be initialized. An example
		is to initialize DRAM.
		Since this is called before C initialization, please
		use provided macros to avoid problems.
	2). __soc_init():
		Further SoC intialization. Called after C language
		initialization, so it is a typical C function.
*/
#include <stdio.h>
#include "nds32_intrinsic.h"
#include "config.h"
#include "n801_asm.h"
#include "m2c8001.h"


/* This must be a leave function, no child funcion. */
void _nds32_init_mem(void) __attribute__((no_prologue, optimize("Os")));
void _nds32_init_mem(void) //The function is weak (optional)
{

	/* System without SDRAM. Use data local memory as system memory. */
    extern char __data_start;
    register unsigned int dlmsize;

	dlmsize = DLM_SIZE;//0x1000 << ((__nds32__mfsr(NDS32_SR_DLMB) >> 1) & 0xf);

#ifndef DLM_8K
	__nds32__mtsr(ILM_BASE|1, NDS32_SR_ILMB);
	__nds32__isb();
#endif
	/* Set DLM base to .data start address and enable it */
	__nds32__mtsr(DLM_BASE|1, NDS32_SR_DLMB);//__nds32__mtsr((unsigned)&__data_start|1, NDS32_SR_DLMB);
	__nds32__dsb();

	/* Update stack pointer to end of DLM
	 * We suppose the .data + .bss + stack less then DLM size */
	__nds32__set_current_sp((unsigned)&__data_start + dlmsize);

}



void __soc_init() //The function is weak (optional)
{


}
