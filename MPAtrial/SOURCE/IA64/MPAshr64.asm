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
; Ignore error A6004: variable declared but not used (no shadow store)
;
;void MPAshrL(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR nbitsShift/*, UINT_PTR padding*/)

		PUBLIC		MPAshrL
		ALIGN		CALL_ALIGNMENT
MPAshrL	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nlimbShift:UINT_PTR, nbitsShift:UINT_PTR;;;, padding:UINT_PTR
		push		rbx									; ABI standardization
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization
;;;		pushfq											; CLD only (no STD used) - no impact on C code

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
;		jz			SHRL_SUCCEEDED
;		test		rax, rax							; Caller responsibility
;		jz			SHRL_SUCCEEDED
;		and			rbx, bitREM_LIMB					; Caller responsibility
;		jz			SHRL_SUCCEEDED

SHRL_100:
;		cmp			rcx, rax							; Caller responsibility
;		je			SHRL_310							; if (nlimbSize == nlimbShift) goto SHRL_310
;		jb			SHRL_SUCCEEDED

		mov			rdx, rax
		shl			rdx, shlLIMBtoBYTE					; limb order -> BYTE order
		add			rsi, rdx							; rsi = &pvsrc[nlimbShift]

		sub			rcx, rax							; rcx = nlimbSize - nlimbShift
		dec			rcx									; For the final shift(rcx = (nlimbSize - nlimbShift) - 1)

		mov			rax, UINT_PTR PTR [rsi]				; rax = pvsrc[nlimbShift]
		test		rcx, rcx
		jz			SHRL_200

SHRL_110:
		push		rcx									; nLoop = rcx	; (PUSH/POP is faster than MOV for LOCAL definition)
		mov			rcx, rbx							; rcx = nshiftBits(rbx);
		mov			rdx, rax
		mov			rax, UINT_PTR PTR [rsi+byteLIMB]
		shrd		rdx, rax, cl						; rdx = pvsrc[nlimbShift+1]:pvsrc[nlimbShift] >> nshiftBits
		mov			UINT_PTR PTR [rdi], rdx				; pvdst[...] = rdx

		add			rsi, byteLIMB
		add			rdi, byteLIMB
		pop			rcx									; rcx = nLoop;
		loop		SHRL_110

SHRL_200:
		mov			rcx, rbx							; rcx = nshiftBits(rbx);

; Padding calculation
;;;		mov			rdx, UINT_PTR PTR -1
;;;		shr			rdx, cl
;;;		not			rdx									; rdx = ~(1 >> nbitsShift))
;;;		and			rdx, UINT_PTR PTR padding

; Final shift
		shr			rax, cl								; pvdst[nlimbSize-1] >>= nshiftBits
;;;		or			rax, rdx							; pvdst[nlimbSize-1] |= (padding & ~(-1 >> nbitsShift))
		mov			UINT_PTR PTR [rdi], rax

		add			rdi, byteLIMB

; Fill with zero
SHRL_300:
		mov			rcx, r9								; rcx = nlimbShift(r9)

SHRL_310:
		xor			rax, rax
;;;		mov			rax, UINT_PTR PTR padding

;;;		cld												; Omitted: MSVC ABI (defaults to CLD)
		rep			stosq

SHRL_SUCCEEDED:
;		xor			rax, rax

SHRL_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
		pop			rbx
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
; Ignore error A6004: variable declared but not used (no shadow store)
;
;void MPAshrM(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, UINT_PTR nlimbShift, UINT_PTR padding)

		PUBLIC		MPAshrM
		ALIGN		CALL_ALIGNMENT
MPAshrM	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nlimbShift:UINT_PTR, padding:UINT_PTR
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization
;;;		pushfq											; CLD only (no STD used) - no impact on C code

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
;		jz			SHR_SUCCEEDED
;		test		rax, rax							; Caller responsibility
;		jz			SHL_SUCCEEDED

SHRM_100:
;		cmp			rcx, rax							; Caller responsibility
;		je			SHRM_210							; if (nlimbSize == nlimbShift) goto SHRM_210
;		jb			SHR_SUCCEEDED

		mov			rdx, rax							; rdx = nlimbShift
		shl			rdx, shlLIMBtoBYTE					; limb order -> BYTE order
		add			rsi, rdx							; rsi = &pvsrc[nlimbShift]

		sub			rcx, rax							; rcx = nlimbSize(rcx) - nlimbShift(rax)

SHRM_110:
		mov			rax, UINT_PTR PTR [rsi]
		mov			UINT_PTR PTR [rdi], rax

		add			rsi, byteLIMB
		add			rdi, byteLIMB
		loop		SHRM_110

SHRM_200:
		mov			rcx, r9								; rcx = nlimbShift(r9)

; Fill with padding
SHRM_210:
		mov			rax, UINT_PTR PTR padding

;;;		cld												; Omitted: MSVC ABI (defaults to CLD)
		rep			stosq

SHR_SUCCEEDED:
;		xor			rax, rax

SHR_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
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
; Ignore error A6004: variable declared but not used (no shadow store)
;
;void MPAshrS(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, UINT_PTR nbitsShift/*, UINT_PTR padding*/)

		PUBLIC		MPAshrS
		ALIGN		CALL_ALIGNMENT
MPAshrS	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR, nbitsShift:UINT_PTR;;;, padding:UINT_PTR
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization
;;;		pushfq											; CLD only (no STD used) - no impact on C code

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR pvsrc, rdx
;		mov			UINT_PTR PTR nlimbSize, r8
;		mov			UINT_PTR PTR nbitsShift, r9

		mov			rdi, rcx							; rdi = pvdst(rcx)
		mov			rsi, rdx							; rsi = pvsrc(rdx)
		mov			rcx, r8								; rcx = nlimbSize(r8)
;		test		rcx, rcx							; Caller responsibility
;		jz			SHR_SUCCEEDED
;		and			r9, bitREM_LIMB						; Caller responsibility
;		jz			SHR_SUCCEEDED

SHRS_100:
		mov			rax, UINT_PTR PTR [rsi]

		dec			rcx									; For the final shift(rcx = nlimbSize - 1)
		jz			SHRS_200

SHRS_110:
		push		rcx									; nLoop = rcx // PUSH/POP is faster than MOV for LOCAL definition
		mov			rcx, r9								; rcx = nbitsShift(r9);
		mov			rdx, rax
		mov			rax, UINT_PTR PTR [rsi+byteLIMB]
		shrd		rdx, rax, cl						; pvdst[1]:pvdst[0] >>= nbitsShift
		mov			UINT_PTR PTR [rdi], rdx

		add			rsi, byteLIMB
		add			rdi, byteLIMB
		pop			rcx									; rcx = nLoop
		loop		SHRS_110

SHRS_200:
		mov			rcx, r9								; rcx = nbitsShift(r9);

; Padding calculation
;;;		mov			rdx, UINT_PTR PTR -1
;;;		shr			rdx, cl
;;;		not			rdx									; rdx = ~(-1 >> nbitsShift))
;;;		and			rdx, UINT_PTR PTR padding

; Final shift
		shr			rax, cl								; pvdst[nlimbSize-1] >>= nbitsShift
;;;		or			rax, rdx							; pvdst[nlimbSize-1] |= (padding & ~(-1 >> nbitsShift))
		mov			UINT_PTR PTR [rdi], rax

SHR_SUCCEEDED:
;		xor			rax, rax

SHR_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
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
MPAshr1	PROC	;	pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR
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
;		jz			SHR1_SUCCEEDED

SHR1_100:
		mov			rax, rcx
		dec			rax									; nlimbSize - 1
		shl			rax, shlLIMBtoBYTE					; limb order -> BYTE order
		add			rsi, rax							; rsi = &pvsrc[nlimbSize-1]
		add			rdi, rax							; rdi = &pvdst[nlimbSize-1]

SHR1_110:
		mov			rax, UINT_PTR PTR [rsi]
		rcr			rax, 1
		mov			UINT_PTR PTR [rdi], rax

		mov			rdx, 0								; Save CF(1)
		sbb			rdx, rdx							; Save CF(2) rdx = 0 - 0 - CF : (rdx = 0 or -1)
		sub			rsi, byteLIMB
		sub			rdi, byteLIMB
		add			rdx, rdx							; Restore CF CF = (-1 + -1) or (0 + 0)
		loop		SHR1_110

SHR1_SUCCEEDED:
;		xor			rax, rax

SHR1_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
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
MPAshrR	PROC	;	pans:LPVOID, pval:LPVOID, shift:UINT_PTR

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

		shrd		rax, rdx, cl						; rdx = val.hi:val.lo >> shift
		shr			rdx, cl								; rax >>= shift

		mov			UINT_PTR PTR [r11], rax				; pans.lo(r11) = ans.lo(rax)
		mov			UINT_PTR PTR [r11+byteLIMB], rdx	; pans.hi(r11) = ans.hi(rdx)

		mov			rax, r11

		ret
MPAshrR	ENDP



END
