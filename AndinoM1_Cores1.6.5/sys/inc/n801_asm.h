/*
 * n801_asm.h
 *
 *  Created on: 2013/12/3
 *      Author: joe.hsu
 */

#ifndef N801_ASM_H_
#define N801_ASM_H_



#ifndef NDS32_INTR_DEF
/*
 * NDS32_REG_SET_BITS(addr, mask)
 * Do set bits to 1 at specified location
 * Operation: *addr = (*addr | mask)
 * */
#define NDS32_SET_BITS(addr, mask) \
__asm__ __volatile__(\
"	sethi 	$r1, hi20(%1)		\n\t"	\
"	ori   	$r1, $r1, lo12(%1)	\n\t"	\
"	sethi 	$r2, hi20(%0)		\n\t"	\
"	ori   	$r2, $r2, lo12(%0)	\n\t"	\
"	lwi   	$r0, [$r2]		\n\t"	\
"	or    	$r0, $r0, $r1		\n\t"	\
"	sw      $r0, [$r2]		\n\t"	\
	::"i"(addr),"i"(mask):"$r0", "$r1", "$r2")
/*
 * NDS32_REG_WAIT4_BIT_ON(addr, mask)
 * Read the contents at addr and use mask to
 * mask off unused bits then wait until all of
 * the remaining bits are on
 *
 * Operation: while(!(*addr & mask));
 * */
#define NDS32_REG_WAIT4_BIT_ON(addr, mask) \
__asm__ __volatile__(\
"	sethi  $r1, hi20(%1)		\n\t"	\
"	ori    $r1, $r1, lo12(%1)	\n\t"	\
"	sethi  $r2, hi20(%0)		\n\t"	\
"	ori    $r2, $r2, lo12(%0)	\n\t"	\
"1:	lwi    $r0, [$r2]		\n\t"	\
"	and    $r0, $r0, $r1		\n\t"	\
"	beqz   $r0, 1b			\n\t"	\
        ::"i"(addr),"i"(mask):"$r0", "$r1", "$r2")

/*
 * NDS32_REG_WAIT4_BIT_OFF(addr, mask)
 * Read the contents at addr and use mask to
 * mask off unused bits then wait until all of
 * the remaining bits are off
 *
 * Operation: while((*addr & mask));
 * */
#define NDS32_REG_WAIT4_BIT_OFF(addr, mask) \
__asm__ __volatile__(\
"	sethi  $r1, hi20(%1)		\n\t"	\
"	ori    $r1, $r1, lo12(%1)	\n\t"	\
"	sethi  $r2, hi20(%0)		\n\t"	\
"	ori    $r2, $r2, lo12(%0)	\n\t"	\
"1:	lwi    $r0, [$r2]		\n\t"	\
"	and    $r0, $r0, $r1		\n\t"	\
"	bnez   $r0, 1b			\n\t"	\
        ::"i"(addr),"i"(mask):"$r0", "$r1", "$r2")

/*
 * NDS32_REG_WRITE(addr, data)
 * Write data to specified location at addr
 *
 * Operation: *addr = data
 * */
#define NDS32_REG_WRITE(addr, data) \
__asm__ __volatile__(\
"	sethi 	$r1, hi20(%1)		\n\t"	\
"	ori   	$r1, $r1, lo12(%1)	\n\t"	\
"	sethi 	$r0, hi20(%0)		\n\t"	\
"	swi   	$r1, [$r0 + lo12(%0)]	\n\t"	\
	::"i"(addr),"i"(data):"$r0", "$r1")

/*
 * NDS32_FMEMCPY_BYTE(dst, src, size)
 * Do forward (low address to high address) memory copy in byte
 * */
#define NDS32_FMEMCPY_BYTE(dst, src, size) \
__asm__ __volatile__(\
"	sethi	$r3, hi20(%2)		\n\t"	\
"	ori	$r3, $r3, lo12(%2)	\n\t"	\
"	sethi	$r1, hi20(%0)		\n\t"	\
"	ori	$r1, $r1, lo12(%0)	\n\t"	\
"	sethi	$r2, hi20(%1)		\n\t"	\
"	ori	$r2, $r2, lo12(%1)	\n\t"	\
"1:	lbi.bi	$r0, [$r2], 1		\n\t"	\
"	sbi.bi	$r0, [$r1], 1		\n\t"	\
"	addi	$r3, $r3, -1		\n\t"	\
"	bnez	$r3, 1b			\n\t"	\
	::"i"(dst),"i"(src),"i"(size):"$r0", "$r1","$r2","$r3")

#define NDS32_FMEMCPY(dst, src, size) \
__asm__ __volatile__(\
"	sethi	$r3, hi20(%2)		\n\t"	\
"	ori	$r3, $r3, lo12(%2)	\n\t"	\
"	sethi	$r1, hi20(%0)		\n\t"	\
"	ori	$r1, $r1, lo12(%0)	\n\t"	\
"	sethi	$r2, hi20(%1)		\n\t"	\
"	ori	$r2, $r2, lo12(%1)	\n\t"	\
"1:	lwi.bi	$r0, [$r2], 4 		\n\t"	\
"	swi.bi	$r0, [$r1], 4		\n\t"	\
"	addi	$r3, $r3, -4		\n\t"	\
"	bgtz	$r3, 1b			\n\t"	\
	::"i"(dst),"i"(src),"i"(size):"$r0", "$r1","$r2","$r3")

#endif

#endif /* N801_ASM_H_ */
