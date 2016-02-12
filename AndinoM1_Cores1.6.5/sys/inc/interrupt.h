#ifndef INTERRUPT_H
#define INTERRUPT_H

	.macro gie_disable
		setgie.d
		dsb
	.endm

	.macro gie_enable
		setgie.e
		dsb
	.endm

	/* align $sp to 8B boundary */
	.macro align_sp_8 R0="$r2", R1="$r3"
		move    \R0, $sp        !keep original $sp to be pushed
#if !defined(NDS32_BASELINE_V3M) || 1 //could be optimized out
 #ifndef NDS32_EXT_PERF
		andi    \R1, $sp, #4    ! R1 = $sp.bit2 // 0 or 4
		subri   \R1, \R1, #4    ! R1 = 4 - R1   // 4 or 0
		sub     $sp, $sp, \R1   ! $sp -= R1     //-4 or 0
		push    \R0
 #else
		addi    $sp, $sp, #-4   ! $sp -= 4
		bclr    $sp, $sp, #2    ! $sp.bit2 = 0
		sw      \R0, [$sp]
 #endif
#endif
	.endm

	.macro push_d0d1 R0="$r2", R1="$r3", R2="$r4", R3="$r5"
#ifdef NDS32_DX_REGS
		mfusr   \R0, $d1.lo
		mfusr   \R1, $d1.hi
		mfusr   \R2, $d0.lo
		mfusr   \R3, $d0.hi
		pushm   \R0, \R3
#endif
	.endm

	.macro pop_d0d1 R0="$r2", R1="$r3", R2="$r4", R3="$r5"
#ifdef NDS32_DX_REGS
		popm    \R0, \R3
		mtusr   \R0, $d1.lo
		mtusr   \R1, $d1.hi
		mtusr   \R2, $d0.lo
		mtusr   \R3, $d0.hi
#endif
	.endm

	.macro push_ifc_lp R0="$r2"
#ifdef NDS32_EXT_IFC
		mfusr   \R0, $IFC_LP
		push    \R0
#endif
	.endm

	.macro pop_ifc_lp R0="$r2"
#ifdef NDS32_EXT_IFC
	pop     \R0
	mtusr   \R0, $IFC_LP
#endif
	.endm

	.macro SAVE_FPU_REGS_00
		addi    $sp, $sp, -8
		fsdi.bi $fd2, [$sp], -8
		fsdi.bi $fd1, [$sp], -8
		fsdi    $fd0, [$sp+0]
	.endm

	.macro SAVE_FPU_REGS_01
		addi    $sp, $sp, -8
		fsdi.bi $fd6, [$sp], -8
		fsdi.bi $fd4, [$sp], -8
		fsdi.bi $fd2, [$sp], -8
		fsdi.bi $fd1, [$sp], -8
		fsdi    $fd0, [$sp+0]
	.endm

	.macro SAVE_FPU_REGS_02
		addi    $sp, $sp, -8
		fsdi.bi $fd14, [$sp], -8
		fsdi.bi $fd12, [$sp], -8
		fsdi.bi $fd10, [$sp], -8
		fsdi.bi $fd8, [$sp], -8
		fsdi.bi $fd6, [$sp], -8
		fsdi.bi $fd4, [$sp], -8
		fsdi.bi $fd2, [$sp], -8
		fsdi.bi $fd1, [$sp], -8
		fsdi    $fd0, [$sp+0]
	.endm

	.macro SAVE_FPU_REGS_03
		addi    $sp, $sp, -8
		fsdi.bi $fd30, [$sp], -8
		fsdi.bi $fd28, [$sp], -8
		fsdi.bi $fd26, [$sp], -8
		fsdi.bi $fd24, [$sp], -8
		fsdi.bi $fd22, [$sp], -8
		fsdi.bi $fd20, [$sp], -8
		fsdi.bi $fd18, [$sp], -8
		fsdi.bi $fd16, [$sp], -8
		fsdi.bi $fd14, [$sp], -8
		fsdi.bi $fd12, [$sp], -8
		fsdi.bi $fd10, [$sp], -8
		fsdi.bi $fd8, [$sp], -8
		fsdi.bi $fd6, [$sp], -8
		fsdi.bi $fd4, [$sp], -8
		fsdi.bi $fd2, [$sp], -8
		fsdi.bi $fd1, [$sp], -8
		fsdi    $fd0, [$sp+0]
	.endm

	.macro push_fpu
#if defined(NDS32_EXT_FPU_CONFIG_0)
		SAVE_FPU_REGS_00
#elif defined(NDS32_EXT_FPU_CONFIG_1)
		SAVE_FPU_REGS_01
#elif defined(NDS32_EXT_FPU_CONFIG_2)
		SAVE_FPU_REGS_02
#elif defined(NDS32_EXT_FPU_CONFIG_3)
		SAVE_FPU_REGS_03
#else
#endif
	.endm

	.macro RESTORE_FPU_REGS_00
		fldi.bi $fd0, [$sp], 8
		fldi.bi $fd1, [$sp], 8
		fldi.bi $fd2, [$sp], 8
	.endm

	.macro RESTORE_FPU_REGS_01
		fldi.bi $fd0, [$sp], 8
		fldi.bi $fd1, [$sp], 8
		fldi.bi $fd2, [$sp], 8
		fldi.bi $fd4, [$sp], 8
		fldi.bi $fd6, [$sp], 8
	.endm

	.macro RESTORE_FPU_REGS_02
		fldi.bi $fd0, [$sp], 8
		fldi.bi $fd1, [$sp], 8
		fldi.bi $fd2, [$sp], 8
		fldi.bi $fd4, [$sp], 8
		fldi.bi $fd6, [$sp], 8
		fldi.bi $fd8, [$sp], 8
		fldi.bi $fd10, [$sp], 8
		fldi.bi $fd12, [$sp], 8
		fldi.bi $fd14, [$sp], 8
	.endm

	.macro RESTORE_FPU_REGS_03
		fldi.bi $fd0, [$sp], 8
		fldi.bi $fd1, [$sp], 8
		fldi.bi $fd2, [$sp], 8
		fldi.bi $fd4, [$sp], 8
		fldi.bi $fd6, [$sp], 8
		fldi.bi $fd8, [$sp], 8
		fldi.bi $fd10, [$sp], 8
		fldi.bi $fd12, [$sp], 8
		fldi.bi $fd14, [$sp], 8
		fldi.bi $fd16, [$sp], 8
		fldi.bi $fd18, [$sp], 8
		fldi.bi $fd20, [$sp], 8
		fldi.bi $fd22, [$sp], 8
		fldi.bi $fd24, [$sp], 8
		fldi.bi $fd26, [$sp], 8
		fldi.bi $fd28, [$sp], 8
		fldi.bi $fd30, [$sp], 8
	.endm

	.macro pop_fpu
#if defined(NDS32_EXT_FPU_CONFIG_0)
		RESTORE_FPU_REGS_00
#elif defined(NDS32_EXT_FPU_CONFIG_1)
		RESTORE_FPU_REGS_01
#elif defined(NDS32_EXT_FPU_CONFIG_2)
		RESTORE_FPU_REGS_02
#elif defined(NDS32_EXT_FPU_CONFIG_3)
		RESTORE_FPU_REGS_03
#else
#endif
	.endm


	.macro SAVE_ALL
		pushm   $r0, $r5
		pushm   $r15,$r30
		push_d0d1
		push_ifc_lp
		mfsr    $r0, $PSW
		mfsr    $r1, $IPC
		mfsr    $r2, $IPSW
		pushm   $r0, $r2

		/* Descend interrupt level */
		addi    $r0, $r0, #-2
		mtsr    $r0, $PSW
		dsb

		align_sp_8
		push_fpu
	.endm

	.macro RESTORE_ALL
		pop_fpu
		lwi     $sp, [$sp]
		popm    $r0, $r2
		mtsr    $r0, $PSW
		dsb
		mtsr    $r1, $IPC
		mtsr    $r2, $IPSW
		pop_ifc_lp
		pop_d0d1
		popm    $r15,$r30
		popm    $r0, $r5
	.endm

	.macro SYSCALL_SAVE_ALL
		pushm   $r1, $r9                    ! $r0 for return value,
		pushm   $r15,$r30                   ! $r0 ~ $r5 are arguments, and
		push_d0d1   "$r6","$r7","$r8","$r9" ! saved them in case ABI are not followed
		push_ifc_lp "$r6"                   ! $r6 ~ $r9 are clobber-list
		mfsr    $r6, $PSW
		mfsr    $r7, $IPC
		addi    $r7, $r7, 4
		mfsr    $r8, $IPSW
		pushm   $r6, $r8                    ! save $psw, $ipc, $ipsw

		/* Descend interrupt level */
		addi    $r6, $r6, #-2
		mtsr    $r6, $PSW
		dsb

		align_sp_8 "$r6","$r7"
		push_fpu
	.endm

	.macro SYSCALL_RESTORE_ALL
		pop_fpu
		lwi     $sp, [$sp]      ! restore align_sp_8
		popm    $r6, $r8        ! restore $psw, $ipc, $ipsw
		mtsr    $r6, $PSW
		dsb
		mtsr    $r7, $IPC
		mtsr    $r8, $IPSW
		pop_ifc_lp "$r6"
		pop_d0d1   "$r6","$r7","$r8","$r9"
		popm    $r15,$r30
		popm    $r1, $r9
	.endm

	.macro SAVE_ALL_HW0
		pushm   $r0, $r5
		pushm   $r15,$r30
		push_d0d1
		push_ifc_lp

		align_sp_8
		push_fpu
	.endm

	.macro RESTORE_ALL_HW0
		pop_fpu
		lwi     $sp, [$sp]
		pop_ifc_lp
		pop_d0d1
		popm    $r15,$r30
		popm    $r0, $r5
	.endm

	.macro SAVE_ALL_HW      !should not touch $r0
		/* push caller-saved gpr */
		pushm	$r1, $r5
		pushm	$r15, $r30
		push_d0d1
		push_ifc_lp

#if !(defined(NDS32_BASELINE_V3M) || defined(NDS32_BASELINE_V3))
		/* push $INT_MASK */
		mfsr    $r1, $INT_MASK
		push    $r1             ! push $INT_MASK

		/* disable low priority and
		 * enable high priority interrupt */
		ori $r1, $r1, 0x3f  ! r1= {mask[31:6],000000}
		li  $r2, 1
		sll $r2, $r2, $r0   ! 1<<r0
		subri $r2, $r2, 64  ! 64 - (1 << r0)
		sub $r1, $r1, $r2   ! {mask[31:6],000000} - (64- (1<<r0))

		mtsr $r1, $INT_MASK
#endif

		/* push $PSW, $IPC, $IPSW */
		mfsr    $r1, $PSW
		mfsr    $r2, $IPC
		mfsr    $r3, $IPSW
		pushm   $r1, $r3

		/* You can use -1 if you want to
		 * descend interrupt level and enable gie or
		 * you can enable gie when you finish your top
		 * half isr. */
		/* Descend interrupt level */
		addi    $r1, $r1, #-2
		mtsr    $r1, $PSW

		align_sp_8
		push_fpu
	.endm

	.macro RESTORE_ALL_HW
		/* pop fpu*/
		pop_fpu
		lwi $sp, [$sp]

		/* pop $PSW, $IPC, $IPSW*/
		popm    $r0, $r2
		gie_disable
		mtsr    $r0, $PSW
		mtsr    $r1, $IPC
		mtsr    $r2, $IPSW

#if !(defined(NDS32_BASELINE_V3M) || defined(NDS32_BASELINE_V3))
		/* pop $INT_MASK */
		pop     $r0             ! get $INT_MASK
		mtsr    $r0, $INT_MASK  ! restore $INT_MASK
#endif
		pop_ifc_lp
		/* pop d0d1 */
		pop_d0d1

		/* pop gpr */
		popm    $r15,$r30
		popm    $r1, $r5
		pop     $r0
	.endm

#endif //#ifndef INTERRUPT_H
