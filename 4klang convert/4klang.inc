%macro export_func 1
   global _%1
   _%1:
%endmacro
%define USE_SECTIONS
%define SAMPLE_RATE	44100
%define MAX_INSTRUMENTS	13
%define MAX_VOICES 2
%define HLD 1
%define BPM 130.011795
%define MAX_PATTERNS 83
%define PATTERN_SIZE_SHIFT 4
%define PATTERN_SIZE (1 << PATTERN_SIZE_SHIFT)
%define	MAX_TICKS (MAX_PATTERNS*PATTERN_SIZE)
%define	SAMPLES_PER_TICK 5087
%define DEF_LFO_NORMALIZE 0.0000491352
%define	MAX_SAMPLES	(SAMPLES_PER_TICK*MAX_TICKS)
;%define 	GO4K_USE_16BIT_OUTPUT
;%define 	GO4K_USE_GROOVE_PATTERN
;%define 	GO4K_USE_ENVELOPE_RECORDINGS
;%define 	GO4K_USE_NOTE_RECORDINGS
%define 	GO4K_CLIP_OUTPUT
%define 	GO4K_USE_DST
%define 	GO4K_USE_DLL
%define 	GO4K_USE_PAN
%define 	GO4K_USE_GLOBAL_DLL
%define 	GO4K_USE_ENV_CHECK
%define 	GO4K_USE_ENV_MOD_GM
%define 	GO4K_USE_VCO_CHECK
%define 	GO4K_USE_VCO_PHASE_OFFSET
%define 	GO4K_USE_VCO_SHAPE
%define		GO4K_USE_VCO_GATE
%define 	GO4K_USE_VCO_MOD_TM
%define 	GO4K_USE_VCO_MOD_DM
%define 	GO4K_USE_VCO_MOD_CM
%define 	GO4K_USE_VCF_CHECK
%define 	GO4K_USE_VCF_MOD_FM
%define 	GO4K_USE_VCF_MOD_RM
%define 	GO4K_USE_VCF_HIGH
%define 	GO4K_USE_VCF_BAND
%define 	GO4K_USE_VCF_PEAK
%define 	GO4K_USE_DST_CHECK
%define 	GO4K_USE_DST_SH
%define		GO4K_USE_DLL_NOTE_SYNC
%define		GO4K_USE_DLL_CHORUS_CLAMP
%define 	GO4K_USE_DLL_DAMP
%define 	GO4K_USE_DLL_DC_FILTER
%define 	GO4K_USE_FSTG_CHECK
%define		GO4K_USE_WAVESHAPER_CLIP
%define	MAX_DELAY			65536
%define MAX_WORKSPACE_SLOTS	8
%define GO4K_BEGIN_CMDDEF(def_name)
%define GO4K_END_CMDDEF db 0
%define GO4K_BEGIN_PARAMDEF(def_name)
%define GO4K_END_PARAMDEF
GO4K_ENV_ID		equ		1
%macro	GO4K_ENV 5
	db	%1
	db	%2
	db	%3
	db	%4
	db	%5
%endmacro
%define	ATTAC(val)		val	
%define	DECAY(val)		val	
%define	SUSTAIN(val)	val	
%define	RELEASE(val)	val	
%define	GAIN(val)		val	
struc	go4kENV_val
	.attac		resd	1
	.decay		resd	1
	.sustain	resd	1
	.release	resd	1
	.gain		resd	1
	.size
endstruc
struc	go4kENV_wrk
	.state		resd	1
	.level		resd	1
	.gm			resd	1
	.am			resd	1
	.dm			resd	1
	.sm			resd	1
	.rm			resd	1
	.size
endstruc
%define ENV_STATE_ATTAC		0
%define ENV_STATE_DECAY		1
%define ENV_STATE_SUSTAIN	2
%define ENV_STATE_RELEASE	3
%define ENV_STATE_OFF		4
GO4K_VCO_ID		equ		2
%macro	GO4K_VCO 8
	db	%1
	db	%2
%ifdef GO4K_USE_VCO_PHASE_OFFSET	
	db	%3
%endif	
%ifdef GO4K_USE_VCO_GATE	
	db	%4
%endif	
	db	%5
%ifdef GO4K_USE_VCO_SHAPE	
	db	%6
%endif	
	db	%7
	db	%8
%endmacro
%define	TRANSPOSE(val)	val	
%define	DETUNE(val)		val	
%define	PHASE(val)		val	
%define	GATES(val)		val	
%define	COLOR(val)		val	
%define	SHAPE(val)		val 
%define	FLAGS(val)		val	
%define SINE		0x01
%define TRISAW		0x02
%define PULSE		0x04
%define NOISE		0x08
%define LFO			0x10
%define GATE		0x20
struc	go4kVCO_val
	.transpose	resd	1
	.detune		resd	1
%ifdef GO4K_USE_VCO_PHASE_OFFSET	
	.phaseofs	resd	1
%endif	
%ifdef GO4K_USE_VCO_GATE	
	.gate		resd	1
%endif	
	.color		resd	1
%ifdef GO4K_USE_VCO_SHAPE	
	.shape		resd	1
%endif	
	.gain		resd	1
	.flags		resd	1	
	.size
endstruc
struc	go4kVCO_wrk
	.phase		resd	1
	.tm			resd	1
	.dm			resd	1
	.fm			resd	1
	.pm			resd	1
	.cm			resd	1
	.sm			resd	1
	.gm			resd	1
	.size
endstruc
GO4K_VCF_ID		equ		3
%macro	GO4K_VCF 3
	db	%1
	db	%2
	db	%3
%endmacro
%define LOWPASS		0x1
%define HIGHPASS	0x2
%define BANDPASS	0x4
%define	BANDSTOP	0x3
%define ALLPASS		0x7
%define	PEAK		0x8
%define	FREQUENCY(val)	val
%define	RESONANCE(val)	val
%define	VCFTYPE(val)	val
struc	go4kVCF_val
	.freq		resd	1
	.res		resd	1
	.type		resd	1
	.size
endstruc
struc	go4kVCF_wrk
	.low		resd	1
	.high		resd	1
	.band		resd	1
	.freq		resd	1
	.fm			resd	1
	.rm			resd	1	
	.size
endstruc
GO4K_DST_ID		equ		4
%macro	GO4K_DST 2
	db	%1
%ifdef GO4K_USE_DST_SH	
	db	%2
%endif	
%endmacro
%define	DRIVE(val)		val
%define	SNHFREQ(val)	val
struc	go4kDST_val
	.drive		resd	1
%ifdef GO4K_USE_DST_SH	
	.snhfreq	resd	1
%endif	
	.size
endstruc
struc	go4kDST_wrk
%ifdef GO4K_USE_DST_SH	
	.out		resd	1
	.snhphase	resd	1
%endif	
	.dm			resd	1
	.sm			resd	1
	.size
endstruc
GO4K_DLL_ID		equ		5
%macro	GO4K_DLL 8
	db	%1
	db	%2
	db	%3
%ifdef GO4K_USE_DLL_DAMP	
	db	%4
%endif		
%ifdef GO4K_USE_DLL_CHORUS	
	db	%5
	db	%6
%endif
	db	%7
	db	%8
%endmacro
%define PREGAIN(val)	val
%define	DRY(val)		val
%define	FEEDBACK(val)	val
%define	DEPTH(val)		val
%define DAMP(val)		val
%define	DELAY(val)		val
%define	COUNT(val)		val
struc	go4kDLL_val
	.pregain	resd	1
	.dry		resd	1
	.feedback	resd	1
%ifdef GO4K_USE_DLL_DAMP	
	.damp		resd	1	
%endif
%ifdef GO4K_USE_DLL_CHORUS
	.freq		resd	1
	.depth
%endif
	.delay		resd	1
	.count		resd	1
	.size
endstruc
struc	go4kDLL_wrk
	.index		resd	1
	.store		resd	1
	.dcin		resd	1
	.dcout		resd	1
%ifdef GO4K_USE_DLL_CHORUS
	.phase		resd	1
%endif
	.buffer		resd	MAX_DELAY
	.size
endstruc
struc	go4kDLL_wrk2
 .pm			resd	1
 .fm			resd	1
 .im			resd	1
 .dm			resd	1
 .sm			resd	1
 .am			resd	1
 .size
endstruc
GO4K_FOP_ID	equ			6
%macro	GO4K_FOP 1
	db	%1
%endmacro
%define	OP(val)			val
%define FOP_POP			0x1
%define FOP_ADDP		0x2
%define FOP_MULP		0x3
%define FOP_PUSH		0x4
%define FOP_XCH			0x5
%define FOP_ADD			0x6
%define FOP_MUL			0x7
%define FOP_ADDP2		0x8
%define FOP_LOADNOTE	0x9
struc	go4kFOP_val
	.flags		resd	1
	.size
endstruc
struc	go4kFOP_wrk
	.size
endstruc
GO4K_FST_ID		equ		7
%macro	GO4K_FST 2
	db	%1
	db	%2
%endmacro
%define	AMOUNT(val)		val
%define	DEST(val)		val
struc	go4kFST_val
	.amount		resd	1
	.op1		resd	1
	.size
endstruc
struc	go4kFST_wrk
	.size
endstruc
GO4K_PAN_ID		equ		8
%macro	GO4K_PAN 1
%ifdef GO4K_USE_PAN
	db	%1
%endif
%endmacro
%define	PANNING(val)	val
struc	go4kPAN_val
%ifdef GO4K_USE_PAN
	.panning	resd	1
%endif
	.size
endstruc
struc	go4kPAN_wrk
	.pm			resd	1
	.size
endstruc
GO4K_OUT_ID		equ		9
%macro	GO4K_OUT 2
	db	%1
%ifdef GO4K_USE_GLOBAL_DLL	
	db	%2
%endif	
%endmacro
%define	AUXSEND(val)	val
struc	go4kOUT_val
	.gain		resd	1
%ifdef GO4K_USE_GLOBAL_DLL	
	.auxsend	resd	1
%endif
	.size
endstruc
struc	go4kOUT_wrk
	.am			resd	1
	.gm			resd	1
	.size
endstruc
GO4K_ACC_ID		equ		10
%macro	GO4K_ACC 1
	db	%1
%endmacro
%define OUTPUT			0
%define	AUX				8
%define ACCTYPE(val)	val
struc	go4kACC_val
	.acctype	resd	1
	.size
endstruc
struc	go4kACC_wrk
	.size
endstruc
%ifdef GO4K_USE_FLD
GO4K_FLD_ID	equ		11
%macro	GO4K_FLD 1
	db	
%endmacro
%define	VALUE(val)	val
struc	go4kFLD_val
	.value		resd	1
	.size
endstruc
struc	go4kFLD_wrk
	.vm			resd	1
	.size
endstruc
%endif
%ifdef GO4K_USE_FSTG
GO4K_FSTG_ID	equ		12
%macro	GO4K_FSTG 2
	db	%1
	dd	%2
%endmacro
struc	go4kFSTG_val
	.amount		resd	1
	.op1		resd	1
	.size
endstruc
struc	go4kFSTG_wrk
	.size
endstruc
%endif
struc	go4k_instrument
	.release	resd	1
	.note		resd	1
	.workspace	resd	256
	.dlloutl	resd	1
	.dlloutr	resd	1
	.outl		resd	1
	.outr		resd	1
	.size
endstruc
struc	go4k_synth
	.instruments	resb	go4k_instrument.size * MAX_INSTRUMENTS * MAX_VOICES
	.global			resb	go4k_instrument.size * MAX_VOICES
	.size
endstruc
%ifdef USE_SECTIONS
section .g4kmuc1 data align=1
%else
section .data align=1
%endif
go4k_patterns
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 67, HLD, 0, 65, 0, 0, 64, HLD, 
	db	62, HLD, HLD, HLD, 0, 0, 59, HLD, HLD, HLD, HLD, HLD, 0, 0, 0, 0, 
	db	55, HLD, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	55, HLD, HLD, HLD, 0, 0, 67, 0, 69, 0, 64, 0, 65, 0, 62, 0, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 67, HLD, HLD, 65, HLD, HLD, 64, HLD, 
	db	69, 0, 0, 0, 67, 0, 0, 0, 67, 0, 0, 0, 0, 0, 64, 0, 
	db	69, 0, 67, 0, 67, 0, 69, 67, 0, 0, 0, 0, 0, 0, 64, 0, 
	db	67, 0, 64, 0, 64, 0, 62, 64, 0, 64, 0, 62, 64, 0, 62, 0, 
	db	76, 74, 71, 67, 64, HLD, 76, HLD, 78, 79, 78, 76, 74, HLD, 71, HLD, 
	db	64, HLD, 71, 69, 71, HLD, 71, 69, 71, HLD, 74, 76, 78, 79, 78, 74, 
	db	69, HLD, 71, 69, 71, HLD, 71, 69, 71, HLD, 71, 69, 64, 62, 69, 62, 
	db	64, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	0, 0, 0, 0, 0, 0, 83, 81, 83, HLD, 83, 81, 83, 85, 86, 85, 
	db	76, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	88, 86, 83, 79, 76, HLD, 88, HLD, 86, 81, 76, 74, 71, HLD, 83, HLD, 
	db	64, HLD, 71, 69, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	40, HLD, HLD, HLD, 55, HLD, 54, HLD, 55, HLD, 0, 0, 59, HLD, 60, HLD, 
	db	59, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, HLD, HLD, HLD, 
	db	38, HLD, HLD, HLD, 54, HLD, 55, HLD, 54, HLD, 0, 0, 54, HLD, 55, HLD, 
	db	50, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 43, HLD, HLD, HLD, 
	db	42, HLD, HLD, HLD, 55, HLD, 54, HLD, 55, HLD, 0, 0, 59, HLD, 60, HLD, 
	db	59, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, HLD, HLD, HLD, 
	db	47, HLD, HLD, HLD, 54, HLD, 55, HLD, 54, HLD, 0, 0, 50, HLD, HLD, HLD, 
	db	54, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 55, HLD, HLD, HLD, 42, HLD, HLD, HLD, 
	db	64, HLD, 71, 69, 54, HLD, 55, 69, 54, HLD, 74, 76, 54, 79, 55, 74, 
	db	64, HLD, 71, 69, 71, HLD, HLD, HLD, HLD, HLD, 74, 76, 78, 79, 78, 74, 
	db	0, 0, 0, 0, 0, 0, 64, 66, 67, 66, 64, 62, 71, HLD, 74, HLD, 
	db	69, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 64, 62, 64, HLD, 67, HLD, 
	db	76, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 79, 78, 76, 86, 83, HLD, 79, HLD, 
	db	81, HLD, HLD, HLD, HLD, HLD, 81, 79, 81, HLD, 79, HLD, 76, HLD, 74, HLD, 
	db	64, HLD, 71, 69, 71, HLD, 71, 69, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	71, 0, 0, 69, 67, 0, 69, 0, 71, HLD, 69, 0, 71, 0, 67, HLD, 
	db	69, 0, 69, 0, 69, 0, 64, HLD, 0, 0, 0, 0, 0, 0, 66, HLD, 
	db	65, HLD, 66, HLD, 69, HLD, HLD, HLD, HLD, HLD, 74, HLD, HLD, HLD, 67, HLD, 
	db	48, 0, 0, 0, 48, 0, 0, 0, 48, 0, 0, 0, 48, 0, 0, 0, 
	db	48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	48, 0, 0, 0, 48, 0, 0, 0, 48, 0, 0, 0, 48, 0, 48, 0, 
	db	48, 0, 0, 0, 48, 0, 0, 0, 48, 0, 0, 0, 0, 0, 0, 0, 
	db	48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 0, 
	db	48, 0, 0, 0, 0, 0, 48, 0, 48, 0, 0, 0, 0, 0, 48, 0, 
	db	48, 0, 0, 0, 48, 0, 0, 0, 72, 60, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 72, HLD, 84, 0, 0, 0, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 72, 0, 0, 0, 96, HLD, 
	db	28, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 38, HLD, HLD, HLD, 
	db	28, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 35, HLD, HLD, HLD, 
	db	36, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 38, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	28, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 26, HLD, HLD, HLD, 
	db	15, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	36, HLD, HLD, HLD, 0, 0, 36, HLD, 38, HLD, HLD, HLD, 0, 0, 38, HLD, 
	db	24, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 31, HLD, HLD, HLD, 
	db	33, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 26, HLD, HLD, HLD, 
	db	26, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 23, HLD, HLD, HLD, 
	db	28, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 52, 40, 28, 16, 0, 0, 0, 0, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 67, HLD, HLD, 64, HLD, HLD, 50, HLD, 
	db	HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, HLD, HLD, HLD, HLD, 0, 96, 93, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, 48, HLD, HLD, 60, HLD, HLD, HLD, 60, HLD, 48, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, 48, HLD, HLD, 60, HLD, HLD, HLD, 60, HLD, HLD, HLD, HLD, HLD, 
	db	0, 0, 0, 48, HLD, HLD, 60, HLD, HLD, HLD, 60, HLD, 48, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, 48, HLD, HLD, 60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	36, HLD, HLD, 0, 0, 0, 36, HLD, 0, 0, 36, HLD, 0, 36, HLD, HLD, 
	db	40, HLD, HLD, 0, 0, 0, 40, HLD, 0, 0, 40, HLD, 0, 40, HLD, HLD, 
	db	41, HLD, HLD, 0, 0, 0, 41, HLD, 0, 0, 41, HLD, 0, 41, 0, 0, 
	db	43, HLD, HLD, 0, 0, 0, 43, HLD, 0, 0, 43, HLD, 0, 43, HLD, HLD, 
	db	36, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	40, 0, 40, HLD, HLD, HLD, 0, 0, 0, 0, 50, HLD, 52, HLD, 0, 0, 
	db	40, HLD, HLD, HLD, 0, 0, 40, HLD, 0, 0, 0, 0, 47, HLD, HLD, HLD, 
	db	38, 0, 38, HLD, HLD, HLD, 0, 0, 0, 0, 47, 0, 50, HLD, 47, 0, 
	db	38, HLD, HLD, 0, 0, 0, 38, HLD, HLD, HLD, HLD, 0, 43, HLD, HLD, HLD, 
	db	47, 0, 47, HLD, HLD, HLD, 0, 0, 0, 0, 45, HLD, 47, HLD, 0, 0, 
	db	35, HLD, HLD, 0, 0, 0, 35, HLD, 0, 0, 0, 0, 45, HLD, HLD, HLD, 
	db	40, 0, 40, HLD, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	38, 0, 38, HLD, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	0, 0, 0, 0, 64, HLD, HLD, HLD, HLD, HLD, 64, HLD, HLD, HLD, 64, HLD, 
	db	HLD, HLD, HLD, HLD, 62, HLD, HLD, HLD, HLD, HLD, 62, HLD, HLD, HLD, 62, HLD, 
	db	HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, 60, HLD, 
	db	HLD, HLD, HLD, HLD, 64, HLD, HLD, HLD, HLD, HLD, 64, HLD, HLD, HLD, 64, HLD, 
	db	64, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	64, HLD, HLD, HLD, HLD, HLD, 62, HLD, 64, HLD, HLD, HLD, 71, HLD, HLD, HLD, 
	db	69, HLD, HLD, HLD, HLD, HLD, 67, HLD, 69, HLD, HLD, HLD, 66, HLD, HLD, HLD, 
	db	67, HLD, HLD, HLD, HLD, HLD, 66, HLD, 67, HLD, HLD, HLD, 74, HLD, HLD, HLD, 
	db	69, HLD, HLD, HLD, HLD, HLD, 67, HLD, 64, HLD, HLD, HLD, 62, HLD, HLD, HLD, 
	db	81, HLD, HLD, HLD, 79, HLD, HLD, HLD, 79, HLD, HLD, HLD, HLD, HLD, 76, HLD, 
	db	81, HLD, 79, HLD, 79, HLD, 81, 79, 0, 0, 0, 0, 0, 0, 76, HLD, 
	db	79, HLD, 76, HLD, 76, HLD, 74, 76, HLD, 76, HLD, 74, 76, HLD, 74, HLD, 
	db	HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	0, 0, 0, 0, 0, 0, 0, 72, 76, 79, 84, 88, 91, 96, 100, 103, 
	db	76, HLD, 83, 81, 83, HLD, 83, 81, 83, HLD, 83, 81, 83, 85, 86, 85, 
	db	76, HLD, 83, 81, 83, HLD, 83, 81, 83, HLD, 83, 81, 76, 74, 69, 74, 
	db	76, HLD, 83, 81, 82, 0, 69, HLD, 56, 0, 0, 0, 0, 0, 0, 0, 
	db	76, HLD, 83, 81, 83, HLD, 83, 81, 83, HLD, 0, 0, 0, 0, 0, 0, 
	db	88, HLD, 88, HLD, 88, HLD, 88, 90, 91, 90, 88, 86, 83, HLD, 79, HLD, 
	db	81, HLD, 81, HLD, 81, HLD, 81, 83, 81, 79, 76, 74, 76, HLD, 79, HLD, 
	db	81, HLD, 81, 83, 81, HLD, 81, 83, 81, HLD, 79, HLD, 76, HLD, 74, HLD, 
	db	76, HLD, 83, 81, 83, HLD, 83, 81, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 88, 89, 90, 91, 102, HLD, 
	db	101, HLD, 102, HLD, 105, HLD, HLD, HLD, 107, 108, 110, HLD, HLD, HLD, 91, 90, 
	db	89, 88, 87, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, HLD, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	60, HLD, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	48, 0, 55, 0, 60, 0, 67, 0, 72, 0, 0, 0, 0, 0, 0, 0, 
	db	55, 0, 62, 0, 67, 0, 74, 0, 79, 0, 0, 0, 0, 0, 0, 0, 
	db	53, 0, 57, 0, 65, 0, 69, 0, 77, 0, 0, 0, 0, 0, 0, 0, 
	db	55, 0, 62, 0, 67, 0, 74, 0, 67, 0, 0, 0, 0, 0, 0, 0, 
	db	48, 0, 55, 0, 60, 0, 67, 0, 72, 0, 72, 0, 0, 0, 72, 0, 
	db	55, 0, 62, 0, 67, 0, 74, 0, 79, 0, 71, 0, 0, 0, 71, 0, 
	db	53, 0, 57, 0, 65, 0, 69, 0, 77, 0, 69, 0, 0, 0, 69, 0, 
	db	55, 0, 62, 0, 67, 0, 74, 0, 67, 0, 67, 0, 0, 0, 67, 0, 
	db	81, 0, 79, 0, 79, 0, 81, 0, 79, 0, 71, 0, 0, 0, 71, 0, 
	db	79, 0, 76, 0, 76, 0, 74, 0, 76, 0, 67, 74, 76, 0, 74, 0, 
	db	79, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	76, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	78, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	74, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	71, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	76, HLD, 0, 0, 0, 0, 74, 0, 76, 0, 0, 0, 83, HLD, HLD, HLD, 
	db	69, HLD, 0, 0, 0, 0, 79, 0, 81, 0, 0, 0, 78, HLD, HLD, HLD, 
	db	76, HLD, 0, 0, 0, 0, 74, 0, 76, 0, 0, 0, 86, HLD, HLD, HLD, 
	db	81, HLD, 0, 0, 0, 0, 79, HLD, 76, HLD, 0, 0, 74, HLD, HLD, HLD, 
	db	86, 88, 90, 91, 90, HLD, 88, HLD, 86, 83, 81, 79, 81, HLD, 79, HLD, 
	db	88, HLD, 95, 93, 94, HLD, 0, 0, 92, 91, HLD, HLD, 91, 90, HLD, HLD, 
	db	HLD, 90, 89, HLD, HLD, HLD, HLD, 88, 87, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	88, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	0, 0, 83, HLD, 88, HLD, 90, HLD, 93, HLD, 91, HLD, 90, HLD, 91, HLD, 
	db	HLD, HLD, 90, 91, 86, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 93, HLD, 95, HLD, 
	db	86, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	HLD, HLD, 83, HLD, 86, HLD, 83, HLD, 86, HLD, 88, HLD, HLD, HLD, 90, HLD, 
	db	HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 86, HLD, 
	db	90, HLD, HLD, HLD, 86, HLD, 90, HLD, HLD, HLD, HLD, HLD, 91, HLD, HLD, HLD, 
	db	0, 0, 0, 0, 0, 0, 95, 93, 88, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 79, 80, 81, 82, 
	db	83, 0, 0, 81, 79, 0, 81, HLD, 83, 0, 81, 0, 83, 0, 79, 0, 
	db	81, 0, 81, HLD, 81, 0, 88, HLD, 0, 0, 0, 0, 0, 0, 90, 0, 
	db	89, 0, 90, 0, 93, 0, 0, 0, 0, 0, 98, 0, 0, 0, 79, 0, 
	db	0, 0, 75, 74, 0, 0, 43, HLD, HLD, HLD, HLD, HLD, 0, 0, 0, 0, 
	db	0, 0, 0, 0, 60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, HLD, 60, HLD, HLD, 60, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, HLD, 60, HLD, HLD, 60, HLD, 60, HLD, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 60, HLD, HLD, HLD, 0, 0, 0, 0, 
	db	0, 0, 0, 0, 0, 0, 60, HLD, 60, HLD, HLD, HLD, HLD, HLD, 60, HLD, 
	db	HLD, HLD, HLD, HLD, 60, HLD, HLD, HLD, 60, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	36, HLD, 36, HLD, 36, HLD, 36, HLD, 36, HLD, 36, HLD, 36, HLD, 36, HLD, 
	db	0, 0, 60, HLD, 0, 0, 60, 60, 0, 0, 60, HLD, 0, 0, 60, 60, 
	db	0, 0, 60, HLD, 0, 0, 60, 60, 0, 0, 60, HLD, 0, 0, 0, 60, 
	db	0, 0, 60, HLD, 0, 0, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	0, 0, 60, HLD, HLD, HLD, 0, 60, 0, 0, 60, HLD, HLD, HLD, 0, 60, 
	db	40, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	76, HLD, 83, 81, 83, HLD, 0, 0, 0, 0, 83, 81, 83, 85, 86, 85, 
	db	76, HLD, 0, 0, 0, 0, 0, 0, 50, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	76, 0, 83, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 76, 0, 83, 0, 86, 0, 
	db	88, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 83, HLD, 81, HLD, 76, 0, 81, 0, 
	db	76, 0, 83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	88, HLD, HLD, HLD, 81, HLD, HLD, HLD, 78, HLD, HLD, HLD, 74, HLD, HLD, HLD, 
	db	40, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 50, HLD, HLD, HLD, 
	db	52, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	48, HLD, HLD, HLD, 0, 0, 48, 0, 50, HLD, HLD, HLD, 0, 0, 50, 0, 
	db	72, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	69, HLD, HLD, HLD, HLD, HLD, 81, 83, 81, HLD, 79, HLD, 76, HLD, 74, HLD, 
	db	52, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 
go4k_patterns_end
%ifdef USE_SECTIONS
section .g4kmuc2 data align=1
%else
section .data
%endif
go4k_pattern_lists
Instrument0List		db	1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 5, 3, 1, 2, 5, 4, 6, 7, 6, 8, 6, 7, 6, 8, 1, 2, 5, 3, 0, 0, 0, 0, 0, 9, 10, 11, 12, 9, 13, 14, 13, 15, 16, 0, 17, 18, 19, 20, 21, 22, 23, 24, 17, 18, 19, 20, 21, 22, 23, 24, 17, 18, 25, 20, 26, 9, 10, 11, 12, 9, 27, 28, 29, 30, 31, 0, 0, 0, 32, 33, 34, 0, 0, 
Instrument1List		db	0, 0, 0, 0, 0, 0, 0, 0, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 0, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 37, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 36, 39, 36, 39, 36, 39, 36, 37, 36, 37, 36, 35, 40, 35, 35, 35, 35, 35, 35, 35, 35, 41, 0, 0, 0, 0, 42, 43, 0, 0,
Instrument2List		db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 45, 44, 46, 44, 45, 44, 46, 47, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 0, 44, 49, 44, 45, 44, 46, 50, 51, 50, 52, 53, 0, 0, 0, 0, 0, 0, 0, 0, 
Instrument3List		db	0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 55, 55, 55, 55, 56, 55, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 59, 55, 57, 57, 59, 57, 57, 57, 57, 57, 57, 57, 57, 57, 60, 55, 55, 55, 55, 55, 55, 55, 55, 
Instrument5List		db	0, 0, 0, 0, 0, 0, 0, 0, 61, 62, 63, 64, 61, 62, 63, 64, 61, 62, 63, 64, 61, 62, 63, 64, 61, 62, 63, 64, 65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 66, 67, 68, 69, 70, 71, 68, 69, 72, 67, 73, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
Instrument6List		db	0, 0, 0, 0, 0, 0, 0, 0, 74, 75, 76, 75, 77, 75, 76, 75, 77, 75, 76, 75, 77, 75, 76, 75, 77, 75, 76, 75, 78, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 79, 80, 81, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0,
Instrument7List		db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 84, 83, 85, 83, 84, 83, 85, 86, 0, 0, 0, 87, 0, 88, 89, 88, 15, 88, 89, 88, 15, 88, 89, 88, 15, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 91, 0, 91, 0, 88, 15, 88, 89, 88, 15, 92, 93, 92, 94, 95, 0, 0, 0, 0, 96, 97, 98, 0, 
Instrument8List		db	0, 0, 0, 0, 0, 0, 0, 0, 99, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 86, 0, 0, 99, 86, 99, 86, 0, 0, 99, 86, 0, 0, 0, 0, 0, 100, 99, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 101, 0, 101, 0, 101, 0, 101, 99, 102, 0, 101, 99, 103, 99, 86, 0, 0, 99, 86, 0, 0, 104, 86, 0, 0, 0, 0, 100, 55, 55, 
Instrument9List		db	105, 106, 107, 108, 105, 106, 107, 108, 109, 110, 111, 112, 109, 110, 111, 112, 109, 113, 111, 114, 109, 113, 111, 114, 109, 110, 111, 112, 105, 106, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 115, 116, 117, 118, 117, 118, 119, 118, 115, 116, 117, 118, 117, 118, 119, 118, 115, 116, 0, 118, 0, 0, 0, 0, 0, 0, 120, 121, 122, 123, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
Instrument11List		db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 125, 126, 55, 55, 55, 55, 55, 55, 55, 55, 127, 128, 129, 130, 131, 132, 133, 134, 0, 128, 0, 134, 135, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 136, 137, 138, 139, 140, 0, 
Instrument12List		db	0, 0, 0, 0, 0, 0, 0, 0, 141, 142, 143, 142, 143, 142, 143, 142, 143, 142, 143, 142, 143, 142, 143, 142, 143, 142, 143, 142, 144, 55, 55, 55, 55, 55, 141, 143, 143, 145, 143, 143, 143, 145, 144, 55, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 141, 146, 141, 147, 143, 143, 143, 145, 143, 143, 143, 145, 148, 55, 55, 55, 55, 55, 55, 55, 55, 
Instrument13List		db	0, 0, 0, 0, 0, 0, 0, 0, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 86, 0, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 151, 152, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 150, 86, 150, 86, 150, 153, 150, 150, 150, 150, 150, 150, 150, 150, 152, 0, 0, 0, 0, 0, 0, 0, 0, 
Instrument15List		db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 154, 55, 155, 156, 157, 158, 159, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 161, 0, 162, 163, 154, 55, 155, 156, 99, 78, 164, 165, 166, 0, 0, 0, 0, 0, 0, 0, 0, 
go4k_pattern_lists_end
%ifdef USE_SECTIONS
section .g4kmuc3 data align=1
%else
section .data
%endif
go4k_synth_instructions
GO4K_BEGIN_CMDDEF(Instrument0)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_DST_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_VCF_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument1)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_ENV_ID
	db GO4K_DST_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument2)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_VCF_ID
	db GO4K_DST_ID
	db GO4K_PAN_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument3)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_VCF_ID
	db GO4K_ENV_ID
	db GO4K_DST_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument5)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_VCF_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument6)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument7)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_DST_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_VCF_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument8)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_VCF_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_DST_ID
	db GO4K_DLL_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument9)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument11)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_DLL_ID
	db GO4K_VCF_ID
	db GO4K_FOP_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument12)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_DST_ID
	db GO4K_VCF_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument13)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_PAN_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument15)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_PAN_ID
	db GO4K_DLL_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Global)
	db GO4K_ACC_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_ACC_ID
	db GO4K_FOP_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
go4k_synth_instructions_end
%ifdef USE_SECTIONS
section .g4kmuc4 data align=1
%else
section .data
%endif
go4k_synth_parameter_values
GO4K_BEGIN_PARAMDEF(Instrument0)
	GO4K_ENV	ATTAC(48),DECAY(80),SUSTAIN(64),RELEASE(64),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(63),FLAGS(NOISE)
	GO4K_DST	DRIVE(64), SNHFREQ(0)
	GO4K_VCO	TRANSPOSE(16),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(TRISAW|LFO)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FST	AMOUNT(40),DEST(10*MAX_WORKSPACE_SLOTS+4)
	GO4K_FST	AMOUNT(58),DEST(10*MAX_WORKSPACE_SLOTS+5)
	GO4K_FOP	OP(FOP_POP)
	GO4K_VCO	TRANSPOSE(88),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(SINE)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(64),GAIN(5),FLAGS(NOISE)
	GO4K_VCF	FREQUENCY(77),RESONANCE(24),VCFTYPE(BANDPASS)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FOP	OP(FOP_PUSH)
	GO4K_VCF	FREQUENCY(32),RESONANCE(128),VCFTYPE(BANDPASS)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_VCF	FREQUENCY(96),RESONANCE(128),VCFTYPE(BANDPASS)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_DLL	PREGAIN(64),DRY(128),FEEDBACK(64),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(17),COUNT(1)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(64)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument1)
	GO4K_ENV	ATTAC(0),DECAY(64),SUSTAIN(96),RELEASE(64),GAIN(87)
	GO4K_FST	AMOUNT(128),DEST(0*MAX_WORKSPACE_SLOTS+2)
	GO4K_ENV	ATTAC(0),DECAY(70),SUSTAIN(0),RELEASE(0),GAIN(128)
	GO4K_DST	DRIVE(57), SNHFREQ(128)
	GO4K_FST	AMOUNT(84),DEST(6*MAX_WORKSPACE_SLOTS+1)
	GO4K_FOP	OP(FOP_POP)
	GO4K_VCO	TRANSPOSE(34),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(112),FLAGS(TRISAW)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(128), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument2)
	GO4K_ENV	ATTAC(60),DECAY(66),SUSTAIN(26),RELEASE(65),GAIN(128)
	GO4K_FST	AMOUNT(94),DEST(0*MAX_WORKSPACE_SLOTS+2)
	GO4K_VCO	TRANSPOSE(88),DETUNE(64),PHASE(12),GATES(85),COLOR(12),SHAPE(114),GAIN(67),FLAGS(TRISAW)
	GO4K_VCO	TRANSPOSE(128),DETUNE(72),PHASE(32),GATES(85),COLOR(118),SHAPE(107),GAIN(110),FLAGS(GATE|LFO)
	GO4K_VCO	TRANSPOSE(16),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(90),GAIN(110),FLAGS(SINE|LFO)
	GO4K_FST	AMOUNT(68),DEST(2*MAX_WORKSPACE_SLOTS+2)
	GO4K_FST	AMOUNT(60),DEST(3*MAX_WORKSPACE_SLOTS+2)
	GO4K_FOP	OP(FOP_POP)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(14),RESONANCE(30),VCFTYPE(PEAK)
	GO4K_VCF	FREQUENCY(40),RESONANCE(45),VCFTYPE(LOWPASS)
	GO4K_DST	DRIVE(114), SNHFREQ(100)
	GO4K_PAN	PANNING(99)
	GO4K_DLL	PREGAIN(45),DRY(95),FEEDBACK(0),DAMP(67),FREQUENCY(0),DEPTH(45),DELAY(18),COUNT(1)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_DLL	PREGAIN(30),DRY(23),FEEDBACK(0),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(19),COUNT(1)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_OUT	GAIN(128), AUXSEND(82)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument3)
	GO4K_ENV	ATTAC(0),DECAY(75),SUSTAIN(0),RELEASE(0),GAIN(27)
	GO4K_FST	AMOUNT(128),DEST(0*MAX_WORKSPACE_SLOTS+2)
	GO4K_VCF	FREQUENCY(28),RESONANCE(99),VCFTYPE(LOWPASS)
	GO4K_ENV	ATTAC(0),DECAY(70),SUSTAIN(0),RELEASE(0),GAIN(128)
	GO4K_DST	DRIVE(8), SNHFREQ(128)
	GO4K_FST	AMOUNT(76),DEST(8*MAX_WORKSPACE_SLOTS+1)
	GO4K_FOP	OP(FOP_POP)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(SINE)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_DLL	PREGAIN(27),DRY(128),FEEDBACK(14),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(20),COUNT(1)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(7), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument5)
	GO4K_ENV	ATTAC(0),DECAY(64),SUSTAIN(64),RELEASE(76),GAIN(80)
	GO4K_FST	AMOUNT(112),DEST(0*MAX_WORKSPACE_SLOTS+2)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(85),COLOR(114),SHAPE(64),GAIN(128),FLAGS(PULSE)
	GO4K_VCO	TRANSPOSE(76),DETUNE(64),PHASE(0),GATES(85),COLOR(0),SHAPE(64),GAIN(88),FLAGS(SINE)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_ENV	ATTAC(0),DECAY(66),SUSTAIN(16),RELEASE(64),GAIN(128)
	GO4K_FST	AMOUNT(94),DEST(9*MAX_WORKSPACE_SLOTS+4)
	GO4K_FST	AMOUNT(81),DEST(10*MAX_WORKSPACE_SLOTS+4)
	GO4K_FOP	OP(FOP_POP)
	GO4K_VCF	FREQUENCY(30),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_VCF	FREQUENCY(12),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_DLL	PREGAIN(22),DRY(128),FEEDBACK(12),DAMP(39),FREQUENCY(0),DEPTH(0),DELAY(17),COUNT(1)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(128), AUXSEND(4)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument6)
	GO4K_ENV	ATTAC(0),DECAY(74),SUSTAIN(0),RELEASE(74),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(43),GATES(85),COLOR(64),SHAPE(88),GAIN(128),FLAGS(SINE)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(96),GAIN(128),FLAGS(SINE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(100)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument7)
	GO4K_ENV	ATTAC(0),DECAY(74),SUSTAIN(0),RELEASE(74),GAIN(74)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(96),GAIN(128),FLAGS(PULSE)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(96),GAIN(56),FLAGS(GATE)
	GO4K_DST	DRIVE(98), SNHFREQ(95)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(17),RESONANCE(23),VCFTYPE(PEAK)
	GO4K_VCF	FREQUENCY(74),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(80)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument8)
	GO4K_ENV	ATTAC(0),DECAY(80),SUSTAIN(0),RELEASE(78),GAIN(39)
	GO4K_FST	AMOUNT(128),DEST(0*MAX_WORKSPACE_SLOTS+2)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(86),GATES(85),COLOR(64),SHAPE(127),GAIN(128),FLAGS(NOISE)
	GO4K_VCF	FREQUENCY(86),RESONANCE(64),VCFTYPE(BANDSTOP)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(80),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_DST	DRIVE(99), SNHFREQ(128)
	GO4K_DLL	PREGAIN(64),DRY(128),FEEDBACK(64),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(17),COUNT(1)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(20), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument9)
	GO4K_ENV	ATTAC(64),DECAY(64),SUSTAIN(64),RELEASE(64),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(72),GAIN(128),FLAGS(SINE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_DLL	PREGAIN(64),DRY(128),FEEDBACK(64),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(17),COUNT(1)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument11)
	GO4K_ENV	ATTAC(0),DECAY(48),SUSTAIN(128),RELEASE(64),GAIN(69)
	GO4K_FST	AMOUNT(116),DEST(0*MAX_WORKSPACE_SLOTS+2)
	GO4K_ENV	ATTAC(0),DECAY(56),SUSTAIN(0),RELEASE(0),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(48),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_DLL	PREGAIN(128),DRY(128),FEEDBACK(127),DAMP(8),FREQUENCY(0),DEPTH(0),DELAY(0),COUNT(1)
	GO4K_VCF	FREQUENCY(48),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(16)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument12)
	GO4K_ENV	ATTAC(0),DECAY(70),SUSTAIN(0),RELEASE(13),GAIN(20)
	GO4K_FST	AMOUNT(128),DEST(0*MAX_WORKSPACE_SLOTS+2)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(35),GAIN(128),FLAGS(NOISE|LFO)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_DST	DRIVE(109), SNHFREQ(60)
	GO4K_VCF	FREQUENCY(20),RESONANCE(99),VCFTYPE(PEAK)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument13)
	GO4K_ENV	ATTAC(0),DECAY(64),SUSTAIN(0),RELEASE(0),GAIN(45)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(128),RESONANCE(128),VCFTYPE(BANDPASS)
	GO4K_PAN	PANNING(64)
	GO4K_DLL	PREGAIN(64),DRY(128),FEEDBACK(96),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(18),COUNT(1)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_DLL	PREGAIN(64),DRY(128),FEEDBACK(64),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(17),COUNT(1)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_OUT	GAIN(45), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument15)
	GO4K_ENV	ATTAC(54),DECAY(78),SUSTAIN(38),RELEASE(25),GAIN(103)
	GO4K_VCO	TRANSPOSE(69),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(SINE|LFO)
	GO4K_FST	AMOUNT(72),DEST(11*MAX_WORKSPACE_SLOTS+2)
	GO4K_FOP	OP(FOP_POP)
	GO4K_VCO	TRANSPOSE(73),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(SINE|LFO)
	GO4K_FST	AMOUNT(56),DEST(12*MAX_WORKSPACE_SLOTS+2)
	GO4K_FST	AMOUNT(56),DEST(12*MAX_WORKSPACE_SLOTS+5)
	GO4K_FOP	OP(FOP_POP)
	GO4K_VCO	TRANSPOSE(77),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(SINE|LFO)
	GO4K_FST	AMOUNT(72),DEST(13*MAX_WORKSPACE_SLOTS+2)
	GO4K_FOP	OP(FOP_POP)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(85),COLOR(0),SHAPE(64),GAIN(128),FLAGS(TRISAW)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(85),COLOR(0),SHAPE(64),GAIN(128),FLAGS(TRISAW)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(85),COLOR(0),SHAPE(64),GAIN(128),FLAGS(TRISAW)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_VCF	FREQUENCY(104),RESONANCE(96),VCFTYPE(LOWPASS)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_DLL	PREGAIN(64),DRY(64),FEEDBACK(64),DAMP(0),FREQUENCY(0),DEPTH(0),DELAY(21),COUNT(1)
	GO4K_PAN	PANNING(64)
	GO4K_DLL	PREGAIN(128),DRY(0),FEEDBACK(0),DAMP(0),FREQUENCY(0),DEPTH(0),DELAY(22),COUNT(1)
	GO4K_OUT	GAIN(16), AUXSEND(64)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Global)
	GO4K_ACC	ACCTYPE(AUX)
	GO4K_DLL	PREGAIN(40),DRY(128),FEEDBACK(125),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(1),COUNT(8)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_DLL	PREGAIN(40),DRY(128),FEEDBACK(125),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(9),COUNT(8)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_ACC	ACCTYPE(OUTPUT)
	GO4K_FOP	OP(FOP_ADDP2)
	GO4K_OUT	GAIN(88), AUXSEND(0)
GO4K_END_PARAMDEF
go4k_synth_parameter_values_end
%ifdef USE_SECTIONS
section .g4kmuc5 data align=1
%else
section .data
%endif
%ifdef GO4K_USE_DLL
global _go4k_delay_times
_go4k_delay_times
	dw 0
	dw 1116
	dw 1188
	dw 1276
	dw 1356
	dw 1422
	dw 1492
	dw 1556
	dw 1618
	dw 1140
	dw 1212
	dw 1300
	dw 1380
	dw 1446
	dw 1516
	dw 1580
	dw 1642
	dw 20351
	dw 10175
	dw 65535
	dw 27135
	dw 30527
	dw 512
%endif
