@ File generated by m4a2s Song-Module
	.include "MPlayDef.s"

	.equ	seq_468_grp, bank_027
	.equ	seq_468_pri, 127
	.equ	seq_468_rev, 0
	.equ	seq_468_mvl, 127
	.equ	seq_468_key, 0

	.section .rodata
	.global	seq_468
	.align	2

@*********************** Track 01 ***********************@

seq_468_0:
	.byte	KEYSH , seq_468_key+0
	.byte	TEMPO , 240/2
	.byte		VOICE , 79
	.byte		VOL   , 90*seq_468_mvl/mxv
	.byte		PAN   , c_v+0
	.byte	W01
	.byte		BENDR , 2
	.byte		BEND  , c_v-60
	.byte	W02
	.byte		        c_v-50
	.byte		N09   , Cs5 , v127
	.byte	W01
	.byte		BEND  , c_v-46
	.byte	W01
	.byte		        c_v-39
	.byte	W01
	.byte		        c_v-24
	.byte	W01
	.byte		        c_v-13
	.byte	W01
	.byte		        c_v+2
	.byte	W01
	.byte		        c_v+28
	.byte	W01
	.byte		        c_v+63
	.byte	W02
	.byte	FINE

@******************************************************@

	.align	2

seq_468:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	seq_468_pri	@ Priority
	.byte	seq_468_rev	@ Reverb

	.word	seq_468_grp

	.word	seq_468_0

	.end