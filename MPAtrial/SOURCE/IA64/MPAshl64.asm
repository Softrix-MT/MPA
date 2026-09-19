include ../../Support/x64.inc 
include ../Include/MPA.inc 

;.STACK

;/*****************************************************************************/
;/*                             ГvГНГgГ^ГCГvТшЛ`                              */
;/*****************************************************************************/
;/*****************************************************************************/
;/*                                ГfБ[Г^Ч╠Иц                                 */
;/*****************************************************************************/
.DATA
.CONST

;/*****************************************************************************/
;/*                                Г}ГNГНЧ╠Иц                                 */
;/*****************************************************************************/
;/*****************************************************************************/
;/*                                ГRБ[ГhЧ╠Иц                                 */
;/*****************************************************************************/
.CODE
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВИВМВk                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; pvdst[...] = pvsrc[...] << (bitsLIMB*nlimbShift + nbitsShift)
; n-place operation allowed (pvdst == pvsrc)
; nlimbShift = floor(shift_bits / bitsLIMB)
; nbitsShift = shift_bits % bitsLIMB 
;
; Caller responsibility
; nlimbSize > 0
; nlimbShift > 0
; nlimbSize > nlimbShift
; nbitsShift Б╕ 1...(bitsLIMB-1)
;
; Ignore error A6004: variable declared but not used (no shadow store)
;
;void MPAshlL(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR nbitsShift/*, UINT_PTR padding*/)

		PUBLIC		MPAshlL
		ALIGN		CALL_ALIGNMENT
MPAshlL	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nlimbShift:UINT_PTR, nbitsShift:UINT_PTR;;;, padding:UINT_PTR
		push		rbx									; ABI standardization
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization
;;;		pushfq											; Support STD (C ABI compliant): Executing CLD before ret to restore DF

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR pvsrc, rdx
;		mov			UINT_PTR PTR nlimbSize, r8
;		mov			UINT_PTR PTR nlimbShift, r9

		mov			rdi, rcx							; rdi = pvdst(rcx)
		mov			rsi, rdx							; rsi = pvsrc(rdx)
		mov			rcx, r8								; rcx = nlimbSize(r8)
		mov			rax, r9								; rax = nlimbShift(r9)
		mov			rbx, UINT_PTR PTR nbitsShift		; rbx = nbitsShift
;		test		rcx, rcx							; Caller responsibility
;		jz			SHLL_SUCCEEDED
;		test		rax, rax							; Caller responsibility
;		jz			SHLL_SUCCEEDED
;		and			rbx, bitREM_LIMB					; Caller responsibility
;		jz			SHLL_SUCCEEDED

SHLL_100:
		mov			rdx, rcx
		dec			rdx									; nlimbSize - 1
		shl			rdx, shlLIMBtoBYTE					; limb order -> BYTE order
		add			rdi, rdx							; rdi = &pvdst[nlimbSize-1]
		add			rsi, rdx							; rsi = &pvsrc[nlimbSize-1]

;		cmp			rcx, rax							; Caller responsibility
;		je			SHLL_310							; if (nlimbSize == nlimbShift) goto SHLL_310
;		jb			SHLL_SUCCEEDED

		mov			rdx, rax
		shl			rdx, shlLIMBtoBYTE					; limb order -> BYTE order
		sub			rsi, rdx							; rsi = &pvsrc[(nlimbSize-1)-nlimbShift]

		sub			rcx, rax							; rcx = nlimbSize - nlimbShift
		dec			rcx									; For the final shift(rcx = (nlimbSize - nlimbShift) - 1)

		mov			rax, UINT_PTR PTR [rsi]				; rax = pvsrc[nlimbSize-1]

SHLL_110:
		push		rcx									; nLoop = rcx	; (PUSH/POP is faster than MOV for LOCAL definition)
		mov			rcx, rbx							; rcx = nbitsShift(rbx);
		mov			rdx, rax
		mov			rax, UINT_PTR PTR [rsi-byteLIMB]
		shld		rdx, rax, cl						; rdx = pvsrc[nlimbSize-1]:pvsrc[(nlimbSize-1)-1] << nbitsShift
		mov			UINT_PTR PTR [rdi], rdx				; pvdst[(nlimbSize-1)-nlimbShift] = rdx

		sub			rsi, byteLIMB
		sub			rdi, byteLIMB
		pop			rcx									; rcx = nLoop
		loop		SHLL_110

SHLL_200:
		mov			rcx, rbx							; rcx = nbitsShift(rbx);

; Padding calculation
;;;		mov			rdx, UINT_PTR PTR -1
;;;		shl			rdx, cl
;;;		not			rdx									; rdx = ~(1 << nbitsShift))
;;;		and			rdx, UINT_PTR PTR padding

; Final shift
		shl			rax, cl								; pvdst[(nlimbSize-1)-nlimbShift] <<= nbitsShift
;;;		or			rax, rdx							; pvdst[(nlimbSize-1)-nlimbShift] |= (padding & ~(1 << nbitsShift))
		mov			UINT_PTR PTR [rdi], rax

		sub			rdi, byteLIMB

; Fill with zero
SHLL_300:
		mov			rcx, r9								; rcx = nlimbShift(r9)

SHLL_310:
		xor			rax, rax
;;;		mov			rax, UINT_PTR PTR padding

		std
		rep			stosq
		cld												; Handles STD (C ABI compliant) - replaces pushfq/popfq

SHLL_SUCCEEDED:
;		xor			rax, rax

SHLL_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
		pop			rbx
		ret
MPAshlL	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВИВМВl                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; pvdst[...+nlimbShift] = pvsrc[...]
; n-place operation allowed (pvdst == pvsrc)
;
; Caller responsibility
; nlimbSize > 0
; nlimbShift > 0
; nlimbSize > nlimbShift
;
; Ignore error A6004: variable declared but not used (no shadow store)
;
;void MPAshlM(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR padding)

		PUBLIC		MPAshlM
		ALIGN		CALL_ALIGNMENT
MPAshlM	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nlimbShift:UINT_PTR, padding:UINT_PTR
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization
;;;		pushfq											; Handles STD (C ABI compliant) - CLD right after REP to protect CF

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR pvsrc, rdx
;		mov			UINT_PTR PTR nlimbSize, r8
;		mov			UINT_PTR PTR nlimbShift, r9

		mov			rdi, rcx							; rdi = pvdst(rcx)
		mov			rsi, rdx							; rsi = pvsrc(rdx)
		mov			rcx, r8								; rcx = nlimbSize(r8)
		mov			rax, r9								; rax = nlimbShift(r9)
;		test		rcx, rcx							; Caller responsibility
;		jz			SHL_SUCCEEDED
;		test		rax, rax							; Caller responsibility
;		jz			SHL_SUCCEEDED

SHLM_100:
		mov			rdx, rcx
		dec			rdx									; nlimbSize - 1
		shl			rdx, shlLIMBtoBYTE					; limb order -> BYTE order
		add			rsi, rdx							; rsi = &pvsrc[nlimbSize-1]
		add			rdi, rdx							; rdi = &pvdst[nlimbSize-1]

;		cmp			rcx, rax							; Caller responsibility
;		je			SHLM_210
;		jb			SHL_SUCCEEDED

		mov			rdx, rax
		shl			rdx, shlLIMBtoBYTE					; limb order -> BYTE order
		sub			rsi, rdx							; rsi = &pvsrc[nlimbSize-nlimbShift-1]

		sub			rcx, rax

SHLM_110:
		mov			rax, UINT_PTR PTR [rsi]
		mov			UINT_PTR PTR [rdi], rax

		sub			rsi, byteLIMB
		sub			rdi, byteLIMB
		loop		SHLM_110

SHLM_200:
		mov			rcx, r9								; rcx = nlimbShift(r9)

; Fill with padding
SHLM_210:
		mov			rax, UINT_PTR PTR padding

		std
		rep			stosq
		cld												; Handles STD (C ABI compliant) - replaces pushfq/popfq

SHL_SUCCEEDED:
;;;		xor			rax, rax

SHL_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
		ret
MPAshlM	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВИВМВr                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; pvdst[...] = pvsrc[...] << nbitsShift(1...(bitsLIMB-1))
; n-place operation allowed (pvdst == pvsrc)
;
; Caller responsibility
; nlimbSize > 0
; nbitsShift Б╕ 1...(bitsLIMB-1)
;
; Ignore error A6004: variable declared but not used (no shadow store)
;
;void MPAshlS(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, UINT_PTR nbitsShift/*, UINT_PTR padding*/)

		PUBLIC		MPAshlS
		ALIGN		CALL_ALIGNMENT
MPAshlS	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nbitsShift:UINT_PTR;;;, padding:UINT_PTR
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization
;;;		pushfq											; Support STD (C ABI compliant): Executing CLD before ret to restore DF

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR pvsrc, rdx
;		mov			UINT_PTR PTR nlimbSize, r8
;		mov			UINT_PTR PTR nbitsShift, r9

		mov			rdi, rcx							; rdi = pvdst(rcx)
		mov			rsi, rdx							; rsi = pvsrc(rdx)
		mov			rcx, r8								; rcx = nlimbSize(r8)
;		test		rcx, rcx							; Caller responsibility
;		jz			SHLS_SUCCEEDED
;		and			r9, bitREM_LIMB						; Caller responsibility
;		jz			SHLS_SUCCEEDED

SHLS_100:
		dec			rcx									; For the final shift(rcx = nlimbSize - 1)
		mov			rax, rcx
		shl			rax, shlLIMBtoBYTE					; limb order -> BYTE order
		add			rsi, rax							; rsi = &pvsrc[nlimbSize-1]
		add			rdi, rax							; rdi = &pvdst[nlimbSize-1]

		mov			rax, UINT_PTR PTR [rsi]				; rax = pvsrc[nlimbSize-1]

		test		rcx, rcx
		jz			SHLS_200

SHLS_110:
		push		rcx									; nLoop = rcx	; (PUSH/POP is faster than MOV for LOCAL definition)
		mov			rcx, r9								; rcx = nbitsShift(r9);
		mov			rdx, rax
		mov			rax, UINT_PTR PTR [rsi-byteLIMB]
		shld		rdx, rax, cl						; rdx = pvsrc[nlimbSize-1]:pvsrc[nlimbSize-1-1] << nbitsShift
		mov			UINT_PTR PTR [rdi], rdx				; pvdst[nlimbSize-1] = pvsrc[nlimbSize-1]

		sub			rsi, byteLIMB
		sub			rdi, byteLIMB
		pop			rcx									; rcx = nLoop
		loop		SHLS_110

SHLS_200:
		mov			rcx, r9								; rcx = nbitsShift(r9);

; Padding calculation
;;;		mov			rdx, UINT_PTR PTR -1
;;;		shl			rdx, cl
;;;		not			rdx									; rdx = ~(-1 << nbitsShift))
;;;		and			rdx, UINT_PTR PTR padding

; Final shift
		shl			rax, cl								; pvdst[0] <<= nbitsShift(cl)
;;;		or			rax, rdx							; pvdst[0] |= (padding & ~(-1 << nbitsShift))
		mov			UINT_PTR PTR [rdi], rax

SHLS_SUCCEEDED:
;		xor			rax, rax

SHLS_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
		ret
MPAshlS	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВИВМВP                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; pvdst[...] = pvsrc[...] << 1
; n-place operation allowed (pvdst == pvsrc)
;
; Caller responsibility
; nlimbSize > 0
;
;void MPAshl1(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize)

		PUBLIC		MPAshl1
		ALIGN		CALL_ALIGNMENT
MPAshl1	PROC	;	pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization
;;;		pushfq											; CLD only (no STD used) - no impact on C code

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR pvsrc, rdx
;		mov			UINT_PTR PTR nlimbSize, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			rdi, rcx							; rdi = pvdst(rcx)
		mov			rsi, rdx							; rsi = pvsrc(rdx)
		mov			rcx, r8								; rcx = nlimbSize(r8)
;		test		rcx, rcx							; Caller responsibility
;		jz			SHL1_SUCCEEDED

SHL1_100:

SHL1_110:
		mov			rax, UINT_PTR PTR [rsi]
		adc			rax, rax							; rcl			rax, 1		; (ADC is faster than RCL)
		mov			UINT_PTR PTR [rdi], rax

		mov			rdx, 0								; Save CF(1)
		sbb			rdx, rdx							; Save CF(2) rdx = 0 - 0 - CF : (rdx = 0 or -1)
		add			rsi, byteLIMB
		add			rdi, byteLIMB
		add			rdx, rdx							; Restore CF CF = (-1 + -1) or (0 + 0)
		loop		SHL1_110

SHL1_SUCCEEDED:
;;;		xor			rax, rax

SHL1_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
		ret
MPAshl1	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВИВМВq                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; return(val <<= shift)
;
;UDINT_PTR MPAshlR(UDINT_PTR val, UINT_PTR shift)

		PUBLIC		MPAshlR
		ALIGN		CALL_ALIGNMENT
MPAshlR	PROC	;	pans:LPVOID, pval:LPVOID, shift:UINT_PTR

; Shadow Store
;		mov			UINT_PTR PTR pans, rcx
;		mov			UINT_PTR PTR pval, rdx
;		mov			UINT_PTR PTR shift, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			r10 ,rdx							; r10 = pval(rdx)
		mov			r11 ,rcx							; r11 = pans(rcx)

		mov			rcx, r8								; rcx = shift(r8)
		mov			rax, UINT_PTR PTR [r10]				; rax = val.lo(r10)
		mov			rdx, UINT_PTR PTR [r10+byteLIMB]	; rax = val.hi(r10)

		shld		rdx, rax, cl						; rdx = val.hi:val.lo << shift
		shl			rax, cl								; rax <<= shift

		mov			UINT_PTR PTR [r11], rax				; pans.lo(r11) = ans.lo(rax)
		mov			UINT_PTR PTR [r11+byteLIMB], rdx	; pans.hi(r11) = ans.hi(rdx)

		mov			rax, r11

		ret
MPAshlR	ENDP


END
