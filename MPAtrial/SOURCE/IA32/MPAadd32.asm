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
;/*                               ВlВoВ`ВБВДВД                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;det += src
;
; Caller responsibility
; ndstSize >= (nsrcSize+1)
;
;void MPAadd(UINT_PTR* pvdst, size_t ndstSize, const UINT_PTR* pvsrc, size_t nsrcSize)
;
;	dword[1] = 0;
;	for(nLoop=0; nLoop<nsrcSize; nLoop++) {
;		qword = pvdst[nLoop] + pvsrc[nLoop] + dword[1];
;		pvdst[nLoop] = dword[0];
;		}
;	for( ; nLoop<(ndstSize-1); nLoop++) {
;		qword = MPINTL(pnBuffer[nLoop]) + MPINTL(dword[1]);
;		pvdst[nLoop] = dword[0];
;		}
;	pvdst[ndstSize] = dword[1];
;
;void MPAadd(UINT_PTR* pvdst, size_t ndstSize, const UINT_PTR* pvsrc, size_t nsrcSize)

		PUBLIC		MPAadd
		ALIGN		CALL_ALIGNMENT
MPAadd	PROC		pvdst:LPVOID, ndstSize:UINT_PTR, pvsrc:LPCVOID, nsrcSize:UINT_PTR
		push		ebx									; ABI standardization
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; CLD only (no STD used) - no impact on C code

;;;		mov			eax, E_INVALDARG					; Set error code
		mov			ecx, UINT_PTR PTR nsrcSize			; rcx = nsrcSize
;;;		cmp			ecx, UINT_PTR PTR ndstSize			; Caller responsibility
;;;		ja			ADD_EXIT							; if (nsrcSize > ndstSize) return(E_INVALDARG);

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc

		clc
;	for(nLoop=0; nLoop<nsrcSize; nLoop++) {
ADD_100:
		mov			eax, UINT_PTR PTR [edi]				; eax = pvdet[nLoop]
		mov			edx, UINT_PTR PTR [esi]				; edx = pvsrc[nLoop]
		adc			eax, edx							; pvdst[nLoop] += pvsrc[nLoop] + CF
		mov			[edi], UINT_PTR PTR eax

		mov			ebx, 0								; Save CF(1)
		sbb			ebx, ebx							; Save CF(2) ebx = 0 - 0 - CF : (ebx = 0 or -1)
		add			edi, byteLIMB
		add			esi, byteLIMB
		add			ebx, ebx							; Restore CF CF = (-1 + -1) or (0 + 0)
		loop		ADD_100
		jnc			ADD_SUCCEEDED						; Skip further calculations if no CF

		mov			ecx, UINT_PTR PTR ndstSize			; ecx = ndstSize
		mov			eax, UINT_PTR PTR nsrcSize			; eax = nsrcSize
		sub			ecx, eax
		jz			ADD_SUCCEEDED

ADD_200:
		stc
		mov			eax, UINT_PTR PTR [edi]				; eax = pvdet[nLoop]
		adc			eax, 0								; pvdst[nLoop] += CF
		mov			[edi], UINT_PTR PTR eax
		jnc			ADD_SUCCEEDED

		add			edi, byteLIMB
		loop		ADD_200

ADD_SUCCEEDED:
;;;		xor			eax, eax

ADD_EXIT:
;;;		popfd
		pop			edi
		pop			esi
		pop			ebx
		ret
MPAadd	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВБВДВДВu                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;det += src
;
; Caller responsibility
; ndstSize > 0
;
;void MPAaddV(UINT_PTR* pvdst, size_t ndstSize, UINT_PTR val)
;
;	dword[1] = val;
;	for(nLoop=0; nLoop<(ndstSize-1); nLoop++) {
;		qword = MPINTL(pvdst[nLoop]) + MPINTL(dword[1]);
;		pvdst[nLoop] = dword[0];
;		}
;	pvdst[m_nSize] = dword[1];
;
		PUBLIC		MPAaddV
		ALIGN		CALL_ALIGNMENT
MPAaddV	PROC		pvdst:LPVOID, ndstSize:UINT_PTR, val:UINT_PTR
		push		edi									; ABI standardization
;;;		pushfd											; CLD only (no STD used) - no impact on C code

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			edx, UINT_PTR PTR val				; edx = val
		mov			ecx, UINT_PTR PTR ndstSize			; ecx = ndstSize

;	for(nLoop=0; nLoop<ndstSize; nLoop++) {
ADDV_100:
		mov			eax, UINT_PTR PTR [edi]				; eax = *pvdet
		add			eax, edx							; *pvdst += val
		mov			UINT_PTR PTR [edi], eax				; *pvdet = eax
		jnc			ADDV_SUCCEEDED

		dec			ecx
		jz			ADDV_SUCCEEDED

ADDV_200:
		add			edi, byteLIMB
		mov			eax, UINT_PTR PTR [edi]				; eax = *pvdet
		add			eax, 1								; *pvdst += 1
		mov			UINT_PTR PTR [edi], eax				; *pvdet = eax
		jnc			ADDV_SUCCEEDED
		loop		ADDV_200

ADDV_SUCCEEDED:
;		xor			eax, eax

ADDV_EXIT:
;;;		popfd
		pop			edi
		ret
MPAaddV	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВБВДВДВq                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; ans = num + val
;UDINT_PTR MPAaddR(UDINT_PTR num, UINT_PTR val);

		PUBLIC		MPAaddR
		ALIGN		CALL_ALIGNMENT
MPAaddR	PROC		num_lo:UINT_PTR, num_hi:UINT_PTR, val:UINT_PTR
		mov			eax, UINT_PTR PTR num_lo			; eax = num.lo
		mov			edx, UINT_PTR PTR num_hi			; edx = num.hi
		mov			ecx, UINT_PTR PTR val				; ecx = val

		add			eax, ecx							; ans.lo(eax) += val
		adc			edx, 0								; ans.hi[edx] += CF

		ret
MPAaddR	ENDP


END
