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
;/*---------------------------------------------------------------------------*/
;/*                              ВbВkВ`ВrВr  ВO                               */
;/*                           ВrВtВaВqВnВtВsВhВmВd                            */
;/*---------------------------------------------------------------------------*/
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВДВЙВЦВq                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; ans = fllor(num / den)
;
; Caller responsibility
; den > 0
;
;UDINT_PTR MPAdivR(UDINT_PTR num, UINT_PTR den);

		PUBLIC		MPAdivR
		ALIGN		CALL_ALIGNMENT
MPAdivR	PROC	;	pans:LPVOID, pnum:LPVOID, den:UINT_PTR
		push		rbx									; ABI standardization

; Shadow Store
;		mov			UINT_PTR PTR pans, rcx
;		mov			UINT_PTR PTR pnum, rdx
;		mov			UINT_PTR PTR den, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			r10, rdx							; r10 = pnum(rdx)
		mov			rax, UINT_PTR PTR [r10+byteLIMB]	; rax = num.hi(r10)
		xor			rdx, rdx
		div			r8									; rax...rdx <- 0(rdx):num.hi / den(r8)

		mov			r11, rax							; ans.hi(r11) = rax
		mov			rax, UINT_PTR PTR [r10]				; rax = num.lo(r10)
		div			r8									; rax...rdx <- rem(rdx):num.lo / den(r8)

		mov			UINT_PTR PTR [rcx], rax				; pans.lo = ans.lo(rax)
		mov			UINT_PTR PTR [rcx+byteLIMB], r11	; pans.hi = ans.hi(r11)

		mov			rax, rcx							; return(pans(eax))

		pop			rbx
		ret
MPAdivR ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВДВЙВЦВd                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; ans = floor(num / den)
; prem = num % den
;
; Caller responsibility
; den > 0
; prem != NULL
;
;UDINT_PTR MPAdivE(UDINT_PTR num, UINT_PTR den, UINT_PTR* prem);

		PUBLIC		MPAdivE
		ALIGN		CALL_ALIGNMENT
MPAdivE	PROC	;	pans:LPVOID, pnum:LPVOID, den:UINT_PTR, prem:LPVOID

; Shadow Store
;		mov			UINT_PTR PTR pans, rcx
;		mov			UINT_PTR PTR pnum, rdx
;		mov			UINT_PTR PTR den, r8
;		mov			UINT_PTR PTR prem, r9

		mov			r10, rdx							; r10 = pnum(rdx)
		mov			rax, UINT_PTR PTR [r10+byteLIMB]	; rax = num.hi(r10)
		xor			rdx, rdx
		div			r8									; rax...rdx <- 0(rdx):num.hi(rax) / den(r8)

		mov			r11, rax							; r11 = ans.hi(rax)
		mov			rax, UINT_PTR PTR [r10]				; rax = num.lo(r10)
		div			r8									; rax...rdx <- rem(rdx):num.lo(rax) / den(r8)

		mov			UINT_PTR PTR [r9], rdx				; *prem = rem(rdx);

		mov			UINT_PTR PTR [rcx], rax				; pans.lo = ans.lo(rax)
		mov			UINT_PTR PTR [rcx+byteLIMB], r11	; pans.hi = ans.hi(r11)

		mov			rax, rcx							; return(pans(eax))

		ret
MPAdivE ENDP


END
