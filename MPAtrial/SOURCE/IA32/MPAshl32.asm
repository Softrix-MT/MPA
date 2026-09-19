include ../../Support/x86.inc 
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
;void MPAshlL(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR nbitsShift/*, UINT_PTR padding*/)

		PUBLIC		MPAshlL
		ALIGN		CALL_ALIGNMENT
MPAshlL	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nlimbShift:UINT_PTR, nbitsShift:UINT_PTR;;;, padding:UINT_PTR
		push		ebx									; ABI standardization
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; Support STD (C ABI compliant): Executing CLD before ret to restore DF

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize
		mov			eax, UINT_PTR PTR nlimbShift		; eax = nlimbShift
		mov			ebx, UINT_PTR PTR nbitsShift		; ecx = nbitsShift
;		test		ecx, ecx							; Caller responsibility
;		jz			SHLL_SUCCEEDED
;		test		eax, eax							; Caller responsibility
;		jz			SHLL_SUCCEEDED
;		and			ebx, bitREM_LIMB					; Caller responsibility
;		jz			SHLL_SUCCEEDED

SHLL_100:
		mov			edx, ecx
		dec			edx									; nlimbSize - 1
		shl			edx, shlLIMBtoBYTE					; limb order -> BYTE order
		add			edi, edx							; edi = &pvdst[nlimbSize-1]
		add			esi, edx							; esi = &pvsrc[nlimbSize-1]

;		cmp			ecx, eax							; Caller responsibility
;		je			SHLL_310							; if (nlimbSize == nlimbShift) goto SHLL_310
;		jb			SHLL_SUCCEEDED

		mov			edx, eax
		shl			edx, shlLIMBtoBYTE					; limb order -> BYTE order
		sub			esi, edx							; esi = &pvsrc[(nlimbSize-1)-nlimbShift]

		sub			ecx, eax							; ecx = nlimbSize - nlimbShift
		dec			ecx									; For the final shift(ecx = (nlimbSize - nlimbShift) - 1)

		mov			eax, UINT_PTR PTR [esi]				; eax = pvsrc[nlimbSize-1]

SHLL_110:
		push		ecx									; nLoop = ecx ; (PUSH/POP is faster than MOV for LOCAL definition)
		mov			ecx, ebx							; ecx = nbitsShift(ebx);
		mov			edx, eax
		mov			eax, UINT_PTR PTR [esi-byteLIMB]
		shld		edx, eax, cl						; edx = pvsrc[nlimbSize-1]:pvsrc[(nlimbSize-1)-1] << nbitsShift
		mov			UINT_PTR PTR [edi], edx				; pvdst[(nlimbSize-1)-nlimbShift] = edx

		sub			esi, byteLIMB
		sub			edi, byteLIMB
		pop			ecx									; ecx = nLoop
		loop		SHLL_110

SHLL_200:
		mov			ecx, ebx							; ecx = nbitsShift(ebx);

; Padding calculation
;;;		mov			edx, UINT_PTR PTR -1
;;;		shl			edx, cl
;;;		not			edx									; edx = ~(1 << nbitsShift))
;;;		and			edx, UINT_PTR PTR padding

; Final shift
		shl			eax, cl								; pvdst[(nlimbSize-1)-nlimbShift] <<= nbitsShift
;;;		or			eax, edx							; pvdst[(nlimbSize-1)-nlimbShift] |= (padding & ~(1 << nbitsShift))
		mov			UINT_PTR PTR [edi], eax

		sub			edi, byteLIMB

; Fill with zero
SHLL_300:
		mov			ecx, UINT_PTR PTR nlimbShift		; ecx = nlimbShift

SHLL_310:
		xor			eax, eax
;;;		mov			eax, UINT_PTR PTR padding

		std
		rep			stosd								; rep			stosq		// 64bit
		cld												; Handles STD (C ABI compliant) - replaces pushfd/popfd

SHLL_SUCCEEDED:
;		xor			eax, eax

SHLL_EXIT:
;;;		popfd
		pop			edi
		pop			esi
		pop			ebx
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
;void MPAshlM(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR padding)

		PUBLIC		MPAshlM
		ALIGN		CALL_ALIGNMENT
MPAshlM	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nlimbShift:UINT_PTR, padding:UINT_PTR
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; Handles STD (C ABI compliant) - CLD right after REP to protect CF

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize
		mov			eax, UINT_PTR PTR nlimbShift		; eax = nlimbShift
;		test		ecx, ecx							; Caller responsibility
;		jz			SHL_SUCCEEDED
;		test		eax, eax							; Caller responsibility
;		jz			SHL_SUCCEEDED

SHLM_100:
		mov			edx, ecx
		dec			edx									; nlimbSize - 1
		shl			edx, shlLIMBtoBYTE					; limb order -> BYTE order
		add			esi, edx							; esi = &pvsrc[nlimbSize-1]
		add			edi, edx							; edi = &pvdst[nlimbSize-1]

;		cmp			ecx, eax							; Caller responsibility
;		je			SHLM_210
;		jb			SHL_SUCCEEDED

		mov			edx, eax
		shl			edx, shlLIMBtoBYTE					; limb order -> BYTE order
		sub			esi, edx							; esi = &pvsrc[nlimbSize-nlimbShift-1]

		sub			ecx, eax

SHLM_110:
		mov			eax, UINT_PTR PTR [esi]
		mov			UINT_PTR PTR [edi], eax

		sub			esi, byteLIMB
		sub			edi, byteLIMB
		loop		SHLM_110

SHLM_200:
		mov			ecx, UINT_PTR PTR nlimbShift		; ecx = nlimbShift

; Fill with padding
SHLM_210:
		mov			eax, UINT_PTR PTR padding

		std
		rep			stosd								; rep			stosq		// 64bit
		cld												; Handles STD (C ABI compliant) - replaces pushfd/popfd

SHL_SUCCEEDED:
;;;		xor			eax, eax

SHL_EXIT:
;;;		popfd
		pop			edi
		pop			esi
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
;void MPAshlS(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, UINT_PTR nbitsShift/*, UINT_PTR padding*/)

		PUBLIC		MPAshlS
		ALIGN		CALL_ALIGNMENT
MPAshlS	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nbitsShift:UINT_PTR;;;, padding:UINT_PTR
		push		ebx									; ABI standardization
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; Support STD (C ABI compliant): Executing CLD before ret to restore DF

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize
		mov			ebx, UINT_PTR PTR nbitsShift		; ebx = nbitsShift
;		test		ecx, ecx							; Caller responsibility
;		jz			SHLS_SUCCEEDED
;		and			ebx, bitREM_LIMB					; Caller responsibility
;		jz			SHLS_SUCCEEDED

SHLS_100:
		dec			ecx									; For the final shift(ecx = nlimbSize - 1)
		mov			eax, ecx
		shl			eax, shlLIMBtoBYTE					; limb order -> BYTE order
		add			esi, eax							; esi = &pvsrc[nlimbSize-1]
		add			edi, eax							; edi = &pvdst[nlimbSize-1]

		mov			eax, UINT_PTR PTR [esi]				; eax = pvsrc[nlimbSize-1]

		test		ecx, ecx
		jz			SHLS_200

SHLS_110:
		push		ecx									; nLoop = ecx	; (PUSH/POP is faster than MOV for LOCAL definition)
		mov			ecx, ebx							; ecx = nbitsShift(ebx);
		mov			edx, eax
		mov			eax, UINT_PTR PTR [esi-byteLIMB]
		shld		edx, eax, cl						; edx = pvsrc[nlimbSize-1]:pvsrc[nlimbSize-1-1] << nbitsShift
		mov			UINT_PTR PTR [edi], edx				; pvdst[nlimbSize-1] = pvsrc[nlimbSize-1]

		sub			esi, byteLIMB
		sub			edi, byteLIMB
		pop			ecx									; ecx = nLoop
		loop		SHLS_110

SHLS_200:
		mov			ecx, ebx							; ecx = nbitsShift(ebx);

; Padding calculation
;;;		mov			edx, UINT_PTR PTR -1
;;;		shl			edx, cl
;;;		not			edx									; edx = ~(-1 << nbitsShift))
;;;		and			edx, UINT_PTR PTR padding

; Final shift
		shl			eax, cl								; pvdst[0] <<= nbitsShift(cl)
;;;		or			eax, edx							; pvdst[0] |= (padding & ~(-1 << nbitsShift))
		mov			UINT_PTR PTR [edi], eax

SHLS_SUCCEEDED:
;		xor			eax, eax

SHLS_EXIT:
;;;		popfd
		pop			edi
		pop			esi
		pop			ebx
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
MPAshl1	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; CLD only (no STD used) - no impact on C code

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize
;		test		ecx, ecx							; Caller responsibility
;		jz			SHL1_SUCCEEDED

SHL1_100:

SHL1_110:
		mov			eax, UINT_PTR PTR [esi]
		adc			eax, eax							; rcl			eax, 1		; (ADC is faster than RCL)
		mov			UINT_PTR PTR [edi], eax

		mov			edx, 0								; Save CF(1)
		sbb			edx, edx							; Save CF(2) edx = 0 - 0 - CF : (edx = 0 or -1)
		add			esi, byteLIMB
		add			edi, byteLIMB
		add			edx, edx							; Restore CF CF = (-1 + -1) or (0 + 0)
		loop		SHL1_110

SHL1_SUCCEEDED:
;;;		xor			eax, eax

SHL1_EXIT:
;;;		popfd
		pop			edi
		pop			esi
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
MPAshlR	PROC		val_lo:UINT_PTR, val_hi:UINT_PTR, shift:UINT_PTR

		mov			ecx, UINT_PTR PTR shift				; ecx ~ shift
		mov			eax, UINT_PTR PTR val_lo			; eax = val_lo
		mov			edx, UINT_PTR PTR val_hi			; eax = val_hi

		shld		edx, eax, cl						; edx = val_hi:val_lo << shift
		shl			eax, cl								; eax <<= shift

		ret
MPAshlR	ENDP


END
