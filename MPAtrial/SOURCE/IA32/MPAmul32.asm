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
;/*                               ВlВoВ`ВНВХВМ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;det = src1 * src2
;
; Caller responsibility
; pvdstБFZero-initialize entire region
; pvdstБFBuffer size >= (nsrc1Size + nsrc2Size)
;
;void MPAmul(UINT_PTR* pvdst, const UINT_PTR* pvsrc1, size_t nsrc1Size, const UINT_PTR* pvsrc2, size_t nsrc2Size);

;	for(nLoop=0; nLoop<nsrc2Size; nLoop++) {
;		dword[1] = 0;
;		for(nIndex=0; nIndex<nsrc1Size; nIndex++) {
;			qword = (pvsrc1[nIndex] * pvsrv2[nLoop]) + pvdst[nLoop+nIndex] + dword[1];
;			pvdst[nLoop+nIndex] = dword[0];
;			}
;		pvdst[nLoop+nIndex] = dword[1];
;		}
;
		PUBLIC		MPAmul
		ALIGN		CALL_ALIGNMENT
MPAmul	PROC		pvdst:LPVOID, pvsrc1:LPCVOID, nsrc1Size:UINT_PTR, pvsrc2:LPCVOID, nsrc2Size:UINT_PTR
		LOCAL		tmp:UINT_PTR

		push		ebx									; ABI standardization
		push		esi									; ABI standardization
		push		edi									; ABI standardization

		mov			ecx, UINT_PTR PTR nsrc2Size			; ecx = nLoop = nsrc2Size
		mov			esi, UINT_PTR PTR pvsrc2			; esi = pvsrc2
;	for(nLoop=0; nLoop<nsrc2Size; nLoop++) {
MUL_100:
		xor			eax, eax
		mov			UINT_PTR PTR tmp, eax				; tmp = 0

		push		ecx									; nLoop = ecx
		mov			ecx, UINT_PTR PTR nsrc1Size			; ecx = nIndex = nsrc1Size
		mov			ebx, UINT_PTR PTR pvsrc1			; ebx = pvsrc1
		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
;		for(nIndex=0; nIndex<nsrc1Size; nIndex++) {
MUL_110:
		mov			eax, UINT_PTR PTR [ebx]				; eax = pvsrc1[nIndex]
		mov			edx, UINT_PTR PTR [esi]				; edx = pvsrv2[nLoop]

		push		ebx
		mul			edx									; pvsrc1[nIndex] * pvsrv2[nLoop]
		mov			ebx, UINT_PTR PTR [edi]
		add			eax, ebx							; += pvdst[nLoop+nIndex]
		adc			edx, 0								; += CF
		mov			ebx, UINT_PTR PTR tmp
		add			eax, ebx							; += dword[1]
		adc			edx, 0								; += CF
		mov			UINT_PTR PTR [edi], eax				; pvdst[nLoop+nIndex]
		mov			UINT_PTR PTR tmp, edx				; tmp = edx
		pop			ebx

		add			ebx, byteLIMB						; pvsrc1++
		add			edi, byteLIMB						; pvdst++
		loop		MUL_110								; ecx(nIndex)

		mov			UINT_PTR PTR [edi], edx				; pvdst[nLoop+nIndex]

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		add			edi, byteLIMB						; pvdst++
		mov			UINT_PTR PTR pvdst, edi				; pvdst = edi

		add			esi, byteLIMB						; pvsrc2++
		pop			ecx									; ecx = nLoop
		loop		MUL_100								; ecx(nLoop)

MUL_SUCCEEDED:
;		xor			eax, eax

MUL_EXIT:
		pop			edi
		pop			esi
		pop			ebx
		ret
MPAmul	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВНВХВМВu                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;dst = src * val
; n-place operation allowed (pvdst == pvsrc)
;
; Caller responsibility
; pvdst: Buffer larger than pvsrc
; nsrcSize > 0
;
;void MPAmulV(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nsrcSize, UINT_PTR val);
;
		PUBLIC		MPAmulV
		ALIGN		CALL_ALIGNMENT
MPAmulV	PROC		pvdst:LPVOID, pvsrc:LPVOID, nsrcSize:UINT_PTR, val:UINT_PTR
		push		ebx									; ABI standardization
		push		esi									; ABI standardization
		push		edi									; ABI standardization

		xor			ebx, ebx							; tmp(ebx)=0

		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			ecx, UINT_PTR PTR nsrcSize			; nLoop(ecx) = nsrcSize

MULV_100:
		mov			eax, UINT_PTR PTR [esi]				; eax = pvsrc[nLoop]
		mov			edx, UINT_PTR PTR val				; edx = val

		mul			edx									; pvdst[nLoop] * val
		add			eax, ebx							; pvdst[nLoop] += tmp(ebx)
		adc			edx, 0								; += CF

		mov			UINT_PTR PTR [edi], eax				; pvdst[nLoop] = eax
		mov			ebx, edx							; tmp(ebx) = edx

		add			esi, byteLIMB						; pvsrc++
		add			edi, byteLIMB						; pvdst++
		loop		MULV_100

		mov			UINT_PTR PTR [edi], ebx				; pvdst[nLoop+1] = tmp(ebx)
MULV_SUCCEEDED:
;		xor			eax, eax

MULV_EXIT:
		pop			edi
		pop			esi
		pop			ebx
		ret
MPAmulV	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВНВХВМВq                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;ans = num * val
;
;       num.hi * val
; +              num.lo * val
; ---------------------
;
;UDINT_PTR MPAmulR(UDINT_PTR num, UINT_PTR val);

		PUBLIC		MPAmulR
		ALIGN		CALL_ALIGNMENT
MPAmulR PROC		num_lo:UINT_PTR, num_hi:UINT_PTR, val:UINT_PTR
		push		ebx

		mov			eax, UINT_PTR PTR num_hi			; eax = num.hi
		mov			ecx, UINT_PTR PTR val				; ecx = val
		mul			ecx									; edx:eax = num.hi(eax) * val(ecx)
		mov			ebx, eax							; tmp(ebx) = eax

		mov			eax, UINT_PTR PTR num_lo			; eax = num.lo
		mul			ecx									; edx:eax = num.lo(eax) * val(ecx)

		add			edx, ebx							; edx = (num.lo(eax) * val).hi(edx)
;																+ tmp(ebx)
		pop			ebx
        ret
MPAmulR ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВНВХВМВs                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;ans = num * val
;
;UDINT_PTR MPAmulT(UINT_PTR num, UINT_PTR val);

		PUBLIC		MPAmulT
		ALIGN		CALL_ALIGNMENT
MPAmulT PROC		num:UINT_PTR, val:UINT_PTR
		mov			eax, UINT_PTR PTR num				; eax = num
		mov			edx, UINT_PTR PTR val				; edx = val

		mul			edx									; return(num(eax) * val(edx));
        ret
MPAmulT ENDP


END
