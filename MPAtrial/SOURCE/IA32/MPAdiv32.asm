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
MPAdivR	PROC		num_lo:UINT_PTR, num_hi:UINT_PTR, den:UINT_PTR
		push		ebx									; ABI standardization

		mov			ecx, UINT_PTR PTR den				; ecx = den

		mov			eax, UINT_PTR PTR num_hi			; eax = num.hi
		xor			edx, edx
		div			ecx									; eax...edx <- 0(edx):num.hi / den(ecx)

		mov			ebx, eax							; ans.hi(ebx) = eax
		mov			eax, UINT_PTR PTR num_lo
		div			ecx									; eax...edx <- rem(edx):num.lo / den(ecx)

		mov			edx, ebx							; retrun(ans.hi(ebx);ans.lo(eax))

		pop			ebx
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
MPAdivE	PROC		num_lo:UINT_PTR, num_hi:UINT_PTR, den:UINT_PTR, prem:LPVOID
		push		ebx									; ABI standardization
		push		edi

		mov			edi, UINT_PTR PTR prem				; edi = prem
		mov			ecx, UINT_PTR PTR den				; ecx = den
		mov			eax, UINT_PTR PTR num_hi			; eax = num.hi
		xor			edx, edx
		div			ecx									; eax...edx <- 0(edx):num.hi(eax) / den(ecx)

		mov			ebx, eax							; ebx = ans.hi(eax)
		mov			eax, UINT_PTR PTR num_lo
		div			ecx									; eax...edx <- rem(edx):num.lo(eax) / den(ecx)

		mov			UINT_PTR PTR [edi], edx				; *prem = rem(edx);
		mov			edx, ebx							; retrun(ans.hi(edx):ans.lo(eax))

		pop			edi
		pop			ebx
		ret
MPAdivE ENDP


END
