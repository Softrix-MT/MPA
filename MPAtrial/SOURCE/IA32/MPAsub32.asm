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
;/*                               ВlВoВ`ВУВХВВ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;dst -= src
;
; Caller responsibility
; ndstSize >= nsrcSize
; pvdst[...] -= pvsrc[...]
;
;void MPAsub(UINT_PTR* pvdst, size_t ndstSize, const UINT_PTR* pvsrc, size_t nsrcSize)

		PUBLIC		MPAsub
		ALIGN		CALL_ALIGNMENT
MPAsub	PROC		pvdst:LPVOID, ndstSize:UINT_PTR, pvsrc:LPCVOID, nsrcSize:UINT_PTR
		push		ebx									; ABI standardization
		push		esi
		push		edi
;;;		pushfd											; CF operations only (no STD used) - no impact on C code

;;;		mov			eax, E_INVALDARG					; Set error code
		mov			ecx, UINT_PTR PTR nsrcSize
;;;		cmp			ecx, UINT_PTR PTR ndstSize			; Caller responsibility
;;;		ja			ADD_EXIT							; if (nsrcSize > ndstSize) return(E_INVALDARG);

		mov			edi, REGBYTE PTR pvdst
		mov			esi, REGBYTE PTR pvsrc

		clc
;	for(nLoop=0; nLoop<nsrcSize; nLoop++) {
SUB_100:
		mov			eax, UINT_PTR PTR [edi]				; eax = pvdet[nLoop]
		mov			edx, UINT_PTR PTR [esi]				; edx = pvsrc[nLoop]
		sbb			eax, edx							; pvdst[nLoop] -= (pvsrc[nLoop] + CF)
		mov			[edi], UINT_PTR PTR eax

		mov			ebx, 0								; Save CF(1)(XOR is avoided because it alters CF)
		sbb			ebx, ebx							; Save CF(2) ebx = 0 - 0 - CF : (ebx = 0 or -1)
		add			edi, byteLIMB
		add			esi, byteLIMB
		add			ebx, ebx							; Restore CF CF = (-1 + -1) or (0 + 0)
		loop		SUB_100
		jnc			SUB_SUCCEEDED						; Skip further calculations if no CF

		mov			ecx, UINT_PTR PTR ndstSize
		mov			eax, UINT_PTR PTR nsrcSize
		sub			ecx, eax
		jz			SUB_SUCCEEDED

SUB_200:
		stc
		mov			eax, UINT_PTR PTR [edi]				; eax = *pvdet
		sbb			eax, 0								; pvdst -= CF
		mov			[edi], UINT_PTR PTR eax
		jnc			SUB_SUCCEEDED						; Skip further calculations if no CF

		add			edi, byteLIMB
		loop		SUB_200

SUB_SUCCEEDED:
;;;		xor			eax, eax

SUB_EXIT:
;;;		popfd
		pop			edi
		pop			esi
		pop			ebx
		ret
MPAsub	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВХВВВu                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;dst -= val
;
; Caller responsibility
; ndstSize > 0
;
;void MPAsubV(UINT_PTR* pvdst, size_t ndstSize, UINT_PTR val)
;
;	dword[1] = val;
;	for(nLoop=0; nLoop<(ndstSize-1); nLoop++) {
;		qword = MPINTL(pvdst[nLoop]) + MPINTL(dword[1]);
;		pvdst[nLoop] = dword[0];
;		}
;	pvdst[ndstSize-1] = dword[1];
;
		PUBLIC		MPAsubV
		ALIGN		CALL_ALIGNMENT
MPAsubV	PROC		pvdst:LPVOID, ndstSize:UINT_PTR, val:UINT_PTR
		push		edi

		mov			edi, UINT_PTR PTR pvdst
		mov			edx, UINT_PTR PTR val
		mov			ecx, UINT_PTR PTR ndstSize

;	for(nLoop=0; nLoop<ndstSize; nLoop++) {
SUBV_100:
		mov			eax, UINT_PTR PTR [edi]				; eax = *pvdet
		sub			eax, edx							; *pvdst += val
		mov			UINT_PTR PTR [edi], eax				; *pvdet = eax
		jnc			SUBV_SUCCEEDED

		dec			ecx
		jz			SUBV_SUCCEEDED

		add			edi, byteLIMB
SUBV_200:
		mov			eax, UINT_PTR PTR [edi]				; eax = *pvdet
		sub			eax, 1								; *pvdst -= 1
		mov			UINT_PTR PTR [edi], eax				; *pvdet = eax
		jnc			SUBV_SUCCEEDED

		add			edi, byteLIMB
		loop		SUBV_200

SUBV_SUCCEEDED:
;		xor			eax, eax

SUBV_EXIT:
		pop			edi
		ret
MPAsubV	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВУВХВВВq                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; ans = num - den
;
;UDINT_PTR MPAsubR(UDINT_PTR num, UINT_PTR val);

		PUBLIC		MPAsubR
		ALIGN		CALL_ALIGNMENT
MPAsubR	PROC		num_lo:UINT_PTR, num_hi:UINT_PTR, val:UINT_PTR
		mov			eax, UINT_PTR PTR num_lo			; eax = num.lo
		mov			edx, UINT_PTR PTR num_hi			; edx = num.hi
		mov			ecx, UINT_PTR PTR val				; ecx = val

		sub			eax, ecx							; ans.lo(eax) -= val
		sbb			edx, 0								; ans.hi[edx] -= CF

		ret
MPAsubR	ENDP


END
