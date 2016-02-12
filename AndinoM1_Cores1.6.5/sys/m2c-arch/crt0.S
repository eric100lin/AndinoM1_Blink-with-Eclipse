##==============================================================================
##
##  crt0.S
##
##  nds32 startup code
##
##==============================================================================

#include <nds32_init.inc>
#include "config.h"
#include "interrupt.h"
##------------------------------------------------------------------------------

	.section .nds32_init, "ax"
!========================================================================
! Vector table
!========================================================================
	.align 3
exception_vector:
	j _start                    !  (0) Trap Reset		
	j OS_Trap_TLB_Fill          !  (1) Trap TLB fill
	j OS_Trap_PTE_Not_Present   !  (2) Trap PTE not present
	j OS_Trap_TLB_Misc          !  (3) Trap TLB misc
	j OS_Trap_TLB_VLPT_Miss     !  (4) Trap TLB VLPT miss
	j OS_Trap_Machine_Error     !  (5) Trap Machine error
	j OS_Trap_Debug_Related     !  (6) Trap Debug related
	j OS_Trap_General_Exception !  (7) Trap General exception
	j OS_Trap_Syscall           !  (8) Syscall	
	j OS_Trap_Interrupt_HW0     !  (9) Interrupt HW0 (for IVB.IVIC_VER = 0)
	j OS_Trap_Interrupt_HW1     ! (10) Interrupt HW1 (for IVB.IVIC_VER = 0)
	j OS_Trap_Interrupt_HW2     ! (10) Interrupt HW2 (for IVB.IVIC_VER = 0)
	j OS_Trap_SWI               ! (15) Interrupt HW6 (for IVB.IVIC_VER = 0)	
	.align  2
exception_vector_end:
exception_handler:
	.long tlb_exception_handler
	.long error_exception_handler
	.long syscall_handler
#ifndef BOOTLOADER	
ISR_TABLE:
	.long HW0_ISR
	.long HW1_ISR
	.long HW2_ISR
#endif	
/*
 * exception handlers
 */

/*----------------------------------------------------------------------
   Since N903 doesn't have MMU, make them share the common error handler.
----------------------------------------------------------------------*/
#ifndef BOOTLOADER
OS_Trap_TLB_Fill:
/*
	SAVE_ALL
	li  $r0, #0x1
	b   tlb_exception_handler
*/

OS_Trap_PTE_Not_Present:
/*
	SAVE_ALL
	li  $r0, #0x2
	b   tlb_exception_handler
*/

OS_Trap_TLB_Misc:
/*
	SAVE_ALL
	li  $r0, #0x3
	b   tlb_exception_handler
*/

OS_Trap_TLB_VLPT_Miss:
1:  b   1b
	SAVE_ALL
//	li  $r0, #0x4
	b   tlb_exception_handler

OS_Trap_Machine_Error:
1:  b   1b
	SAVE_ALL
	li  $r0, #0x5
	b   error_exception_handler

OS_Trap_Debug_Related:
1:  b   1b
	SAVE_ALL
	li  $r0, #0x6
	b   error_exception_handler
#endif
OS_Trap_General_Exception:
!1:  b   1b
	SAVE_ALL
	li  $r0, #0x7
	b   error_exception_handler
OS_Trap_Syscall:
	SYSCALL_SAVE_ALL
	bal syscall_handler
	SYSCALL_RESTORE_ALL
	iret

OS_Trap_Interrupt_HW0:
	SAVE_ALL_HW0
	li  $r0, 0x0
	la  $r1, HW0_ISR
	jral $r1
	RESTORE_ALL_HW0
	iret

common_ISR_wrapper:
	SAVE_ALL_HW
	la  $r1, ISR_TABLE
	lw  $r1, [$r1+$r0<<2]
	jral $r1
	RESTORE_ALL_HW
	iret

OS_Trap_Interrupt_UNDEF:
	push $r0
	li  $r0, 0xff
	b   common_ISR_wrapper

OS_Trap_Interrupt_HW1:
	push $r0
	li   $r0, 0x01
	b    common_ISR_wrapper


OS_Trap_Interrupt_HW2:
	push $r0
	li   $r0, 0x02
	b    common_ISR_wrapper

OS_Trap_SWI:
	SAVE_ALL
	li  $r0, 0x0f
	la  $r1, SW0_ISR
	jral $r1
	RESTORE_ALL
	iret
##------------------------------------------------------------------------------
## Startup code

#include "config.h"
#include "n801_asm.h"


#define LED_VALUE (0x23)


	.section .text
	.global _start
	.weak _call_exit
	.weak _SDA_BASE_
	.weak _FP_BASE_
	.func _start
	.type _start, @function

	.align 2
_start:
	!************************** Begin of do-not-modify **************************
	! Please don't modify this code
	! Initialize the registers used by the compiler
#ifndef CONFIG_NO_NDS32_EXT_EX9
	! make sure the instruction before setting ITB
	! will not be optimized with ex9
	.no_ex9_begin           ! disable ex9 generation
#endif

	! Support Relax, Set $gp to _SDA_BASE_
	la  $gp, _SDA_BASE_     ! init GP for small data access

#ifdef CFG_DEBUG
	mfsr $r0, $MSC_CFG

#ifndef CONFIG_NO_NDS32_EXT_EX9
	li  $r1, (1 << 24)      ! EIT
	and $r2, $r0, $r1
1:  beqz $r2, 1b
#endif

#ifdef NDS32_EXT_IFC
	li  $r1, (1 << 19)      ! IFC
	and $r2, $r0, $r1
1:  beqz $r2, 1b
#endif

#endif //#ifdef CFG_DEBUG

#ifndef CONFIG_NO_NDS32_EXT_EX9
	! Initialize the table base of EX9 instruction
	la      $r0, _ITB_BASE_ ! init ITB
	mtusr   $r0, $ITB
	.no_ex9_end
#endif
	!*************************** End of do-not-modify ***************************

	la  $fp, _FP_BASE_      ! init FP
	la  $sp, _stack         ! init SP

//#ifndef CFG_SIMU
#ifdef FPGA_VER
	li  $r0, LED_VALUE
	bal set_led
#endif

	bal _nds32_init_mem
	bal __init
	bal __do_global_ctors
	bal main

1:  b   1b

//#ifndef CFG_SIMU
#ifdef FPGA_VER
	.global set_led
set_led:
	! light LED
	li  $r1, LED_BASE
	sw  $r0, [$r1]
	ret
#endif

	.size _start, .-_start

	.end
