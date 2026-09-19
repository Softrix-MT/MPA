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
;/*                              ВlВoВ`ВУВИВТВk                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; pvdst[...] = pvsrc[...] >> (bitsLIMB*nlimbShift + nbitsShift)
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
;void MPAshrL(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR nbitsShift/*, UINT_PTR padding*/)

		PUBLIC		MPAshrL
		ALIGN		CALL_ALIGNMENT
MPAshrL	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nlimbShift:UINT_PTR, nbitsShift:UINT_PTR;;;, padding:UINT_PTR
		push		ebx									; ABI standardization
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; CLD only (no STD used) - no impact on C code

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize
		mov			eax, UINT_PTR PTR nlimbShift		; eax = nlimbShift
		mov			ebx, UINT_PTR PTR nbitsShift		; ebx = nbitsShift
;		test		ecx, ecx							; Caller responsibility
;		jz			SHRL_SUCCEEDED
;		test		eax, eax							; Caller responsibility
;		jz			SHRL_SUCCEEDED
;		and			ebx, bitREM_LIMB					; Caller responsibility
;		jz			SHRL_SUCCEEDED

SHRL_100:
;		cmp			ecx, eax							; Caller responsibility
;		je			SHRL_310							; if (nlimbSize == nlimbShift) goto SHRL_310
;		jb			SHRL_SUCCEEDED

		mov			edx, eax
		shl			edx, shlLIMBtoBYTE					; limb order -> BYTE order
		add			esi, edx							; esi = &pvsrc[nlimbShift]

		sub			ecx, eax							; ecx = nlimbSize - nlimbShift
		dec			ecx									; For the final shift(ecx = (nlimbSize - nlimbShift) - 1)

		mov			eax, UINT_PTR PTR [esi]				; eax = pvsrc[nlimbShift]
		test		ecx, ecx
		jz			SHRL_200

SHRL_110:
		push		ecx									; nLoop = ecx (PUSH/POP is faster than MOV for LOCAL definition)
		mov			ecx, ebx							; ecx = nshiftBits(ebx);
		mov			edx, eax
		mov			eax, UINT_PTR PTR [esi+byteLIMB]
		shrd		edx, eax, cl						; edx = pvsrc[nlimbShift+1]:pvsrc[nlimbShift] >> nshiftBits
		mov			UINT_PTR PTR [edi], edx				; pvdst[...] = edx

		add			esi, byteLIMB
		add			edi, byteLIMB
		pop			ecx									; ecx = nLoop;
		loop		SHRL_110

SHRL_200:
		mov			ecx, ebx							; ecx = nshiftBits(ebx);

; Padding calculation
;;;		mov			edx, UINT_PTR PTR -1
;;;		shr			edx, cl
;;;		not			edx									; edx = ~(1 >> nbitsShift))
;;;		and			edx, UINT_PTR PTR padding

; Final shift
		shr			eax, cl								; pvdst[nlimbSize-1] >>= nshiftBits
;;;		or			eax, edx							; pvdst[nlimbSize-1] |= (padding & ~(-1 >> nbitsShift))
		mov			UINT_PTR PTR [edi], eax

		add			edi, byteLIMB

; Fill with zero
SHRL_300:
		mov			ecx, UINT_PTR PTR nlimbShift

SHRL_310:
		xor			eax, eax
;;;		mov			eax, UINT_PTR PTR padding

;;;		cld												; Omitted: MSVC ABI (defaults to CLD)
		rep			stosd								; rep			stosq		; 64bit

SHRL_SUCCEEDED:
;		xor			eax, eax

SHRL_EXIT:
;;;		popfd
		pop			edi
		pop			esi
		pop			ebx
		ret
MPAshrL	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВИВТВl                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; pvdst[...] = pvsrc[...+nlimbShift]
; n-place operation allowed (pvdst == pvsrc)
;
; Caller responsibility
; nlimbSize > 0
; nlimbShift > 0
; nlimbSize > nlimbShift
;
;void MPAshrM(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, UINT_PTR nlimbShift, UINT_PTR padding)

		PUBLIC		MPAshrM
		ALIGN		CALL_ALIGNMENT
MPAshrM	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nlimbShift:UINT_PTR, padding:UINT_PTR
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; CLD only (no STD used) - no impact on C code

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize
		mov			eax, UINT_PTR PTR nlimbShift		; eax = nlimbShift
;		test		ecx, ecx							; Caller responsibility
;		jz			SHR_SUCCEEDED
;		test		eax, eax							; Caller responsibility
;		jz			SHL_SUCCEEDED

SHRM_100:
;		cmp			ecx, eax							; Caller responsibility
;		je			SHRM_210							; if (nlimbSize == nlimbShift) goto SHRM_210
;		jb			SHR_SUCCEEDED

		mov			edx, eax							; edx = nlimbShift
		shl			edx, shlLIMBtoBYTE					; limb order -> BYTE order
		add			esi, edx							; esi = &pvsrc[nlimbShift]

		sub			ecx, eax							; ecx = nlimbSize(ecx) - nlimbShift(eax)

SHRM_110:
		mov			eax, UINT_PTR PTR [esi]
		mov			UINT_PTR PTR [edi], eax

		add			esi, byteLIMB
		add			edi, byteLIMB
		loop		SHRM_110

SHRM_200:
		mov			ecx, UINT_PTR PTR nlimbShift

; Fill with padding
SHRM_210:
		mov			eax, UINT_PTR PTR padding

;;;		cld												; Omitted: MSVC ABI (defaults to CLD)
		rep			stosd								; rep			stosq		; 64bit

SHR_SUCCEEDED:
;		xor			eax, eax

SHR_EXIT:
;;;		popfd
		pop			edi
		pop			esi
		ret
MPAshrM	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВИВТВr                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; pvdst[...] = pvsrc[...] >> nbitsShift(1...(bitsLIMB-1))
; n-place operation allowed (pvdst == pvsrc)
;
; Caller responsibility
; nlimbSize > 0
; nbitsShift Б╕ 1...(bitsLIMB-1)
;
;void MPAshrS(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, UINT_PTR nbitsShift/*, UINT_PTR padding*/)

		PUBLIC		MPAshrS
		ALIGN		CALL_ALIGNMENT
MPAshrS	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nbitsShift:UINT_PTR;;;, padding:UINT_PTR
		push		ebx									; ABI standardization
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; CLD only (no STD used) - no impact on C code

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize
		mov			ebx, UINT_PTR PTR nbitsShift		; ebx = nbitsShift
;		test		ecx, ecx							; Caller responsibility
;		jz			SHR_SUCCEEDED
;		and			ebx, bitREM_LIMB					; Caller responsibility
;		jz			SHR_SUCCEEDED

SHRS_100:
		mov			eax, UINT_PTR PTR [esi]

		dec			ecx									; For the final shift(ecx = nlimbSize - 1)
		jz			SHRS_200

SHRS_110:
		push		ecx									; nLoop = ecx	; (PUSH/POP is faster than MOV for LOCAL definition)
		mov			ecx, ebx							; ecx = nbitsShift(ebx);
		mov			edx, eax
		mov			eax, UINT_PTR PTR [esi+byteLIMB]
		shrd		edx, eax, cl						; pvdst[1]:pvdst[0] >>= nbitsShift
		mov			UINT_PTR PTR [edi], edx

		add			esi, byteLIMB
		add			edi, byteLIMB
		pop			ecx									; ecx = nLoop
		loop		SHRS_110

SHRS_200:
		mov			ecx, ebx							; ecx = nbitsShift(ebx);

; Padding calculation
;;;		mov			edx, UINT_PTR PTR -1
;;;		shr			edx, cl
;;;		not			edx									; edx = ~(-1 >> nbitsShift))
;;;		and			edx, UINT_PTR PTR padding

; Final shift
		shr			eax, cl								; pvdst[nlimbSize-1] >>= nbitsShift
;;;		or			eax, edx							; pvdst[nlimbSize-1] |= (padding & ~(-1 >> nbitsShift))
		mov			UINT_PTR PTR [edi], eax

SHR_SUCCEEDED:
;		xor			eax, eax

SHR_EXIT:
;;;		popfd
		pop			edi
		pop			esi
		pop			ebx
		ret
MPAshrS	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВИВТВP                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; pvdst[...] = pvsrc[...] >> 1
; n-place operation allowed (pvdst == pvsrc)
;
; Caller responsibility
; nlimbSize > 0
;void MPAshr1(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize)

		PUBLIC		MPAshr1
		ALIGN		CALL_ALIGNMENT
MPAshr1	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; CLD only (no STD used) - no impact on C code

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize
;		test		ecx, ecx							; Caller responsibility
;		jz			SHR1_SUCCEEDED

SHR1_100:
		mov			eax, ecx
		dec			eax									; nlimbSize - 1
		shl			eax, shlLIMBtoBYTE					; limb order -> BYTE order
		add			esi, eax							; esi = &pvsrc[nlimbSize-1]
		add			edi, eax							; edi = &pvdst[nlimbSize-1]

SHR1_110:
		mov			eax, UINT_PTR PTR [esi]
		rcr			eax, 1
		mov			UINT_PTR PTR [edi], eax

		mov			edx, 0								; Save CF(1)
		sbb			edx, edx							; Save CF(2) edx = 0 - 0 - CF : (edx = 0 or -1)
		sub			esi, byteLIMB
		sub			edi, byteLIMB
		add			edx, edx							; Restore CF CF = (-1 + -1) or (0 + 0)
		loop		SHR1_110

SHR1_SUCCEEDED:
;		xor			eax, eax

SHR1_EXIT:
;;;		popfd
		pop			edi
		pop			esi
		ret
MPAshr1	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВИВТВq                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; return(val >>= shift)
;
;UDINT_PTR MPAshrR(UDINT_PTR val, UINT_PTR shift)

		PUBLIC		MPAshrR
		ALIGN		CALL_ALIGNMENT
MPAshrR	PROC		val_lo:UINT_PTR, val_hi:UINT_PTR, shift:UINT_PTR

		mov			ecx, UINT_PTR PTR shift				; ecx = shift
		mov			eax, UINT_PTR PTR val_lo			; eax = val_lo
		mov			edx, UINT_PTR PTR val_hi			; eax = val_hi

		shrd		eax, edx, cl						; edx = val_hi:val_lo >> shift
		shr			edx, cl								; eax >>= shift

		ret
MPAshrR	ENDP



END
