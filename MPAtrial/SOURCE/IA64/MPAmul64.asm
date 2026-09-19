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
;/*                               ВlВoВ`ВНВХВМ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;det = src1 * src2
;
; Caller responsibility
; pvdstБFZero-initialize entire region
; pvdstБF(nsrc1Size + nsrc2Size)И╚ПуВ╠Ч╠ИцГTГCГY
;
; Ignore error A6004: variable declared but not used (no shadow store)
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
;		LOCAL		tmp:UINT_PTR						; r12

		push		rbx									; ABI standardization
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization
		push		r12									; ABI standardization

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR pvsrc1, rdx
;		mov			UINT_PTR PTR nsrc1Size, r8
;		mov			UINT_PTR PTR pvsrc2, r9

		mov			r10, rcx							; r10 = pvdst;
		mov			r11, rdx							; r11 = pvsrc1

		mov			rcx, UINT_PTR PTR nsrc2Size			; rcx = nLoop = nsrc2Size
		mov			rsi, r9								; rsi = pvsrc2(r9)
;	for(nLoop=0; nLoop<nsrc2Size; nLoop++) {
MUL_100:
		xor			r12, r12							; tmp(r12) = 0

		push		rcx									; nLoop = rcx
		mov			rcx, r8								; rcx = nIndex = nsrc1Size(r8)
		mov			rbx, r11							; rbx = pvsrc1(r11)
		mov			rdi, r10							; rdi = pvdst(r10)
;		for(nIndex=0; nIndex<nsrc1Size; nIndex++) {
MUL_110:
		mov			rax, UINT_PTR PTR [rbx]				; rax = pvsrc1[nIndex]
		mov			rdx, UINT_PTR PTR [rsi]				; rdx = pvsrv2[nLoop]

		push		rbx
		mul			rdx									; pvsrc1[nIndex] * pvsrv2[nLoop]
		mov			rbx, UINT_PTR PTR [rdi]
		add			rax, rbx							; += pvdst[nLoop+nIndex]
		adc			rdx, 0								; += CF
		mov			rbx, r12							; rbx += tmp(r12)
		add			rax, rbx							; += dword[1]
		adc			rdx, 0								; += CF
		mov			UINT_PTR PTR [rdi], rax				; pvdst[nLoop+nIndex]
		mov			r12, rdx							; tmp(r12) = rdx
		pop			rbx

		add			rbx, byteLIMB						; pvsrc1++
		add			rdi, byteLIMB						; pvdst++
		loop		MUL_110								; rcx(nIndex)

		mov			UINT_PTR PTR [rdi], rdx				; pvdst[nLoop+nIndex]

		add			r10, byteLIMB						; pvdst(r10)++
		add			rsi, byteLIMB						; pvsrc2(rsi)++
		pop			rcx									; rcx = nLoop
		loop		MUL_100								; rcx(nLoop)

		pop			r12
		pop			rdi
		pop			rsi
		pop			rbx
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
MPAmulV	PROC	;	pvdst:LPVOID, pvsrc:LPVOID, nsrcSize:UINT_PTR, val:UINT_PTR
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR pvsrc, rdx
;		mov			UINT_PTR PTR nsrcSize, r8
;		mov			UINT_PTR PTR val, r9

		xor			r10, r10							; tmp(r10)=0

		mov			rsi, rdx							; rsi = pvsrc(rdx)
		mov			rdi, rcx							; rdi = pvdst(rcx)
		mov			rcx, r8								; nLoop(rcx) = nsrcSize(r8)

MULV_100:
		mov			rax, UINT_PTR PTR [rsi]				; rax = pvsrc[nLoop]
		mov			rdx, r9								; rdx = val(r9)

		mul			rdx									; pvdst[nLoop] * val
		add			rax, r10							; pvdst[nLoop] += tmp(r10)
		adc			rdx, 0								; += CF

		mov			UINT_PTR PTR [rdi], rax				; pvdst[nLoop] = rax
		mov			r10, rdx							; tmp(r10) = rdx

		add			rsi, byteLIMB						; pvsrc++
		add			rdi, byteLIMB						; pvdst++
		loop		MULV_100

		mov			UINT_PTR PTR [rdi], r10				; pvdst[nLoop+1] = tmp(r10)

		pop			rdi
		pop			rsi
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
MPAmulR PROC	;	pans:LPVOID, pnum:LPVOID, val:UINT_PTR
; Shadow Store
;		mov			UINT_PTR PTR pans, rcx
;		mov			UINT_PTR PTR pnum, rdx
;		mov			UINT_PTR PTR val, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			r10, rdx							; r10 = pnum(rdx)

		mov			rax, UINT_PTR PTR [r10+byteLIMB]	; rax = num.hi(r10)
		mul			r8									; rdx:rax = num.hi(rax) * val(r8)
		mov			r9, rax								; tmp(r9) = rax

		mov			rax, UINT_PTR PTR [r10]				; rax = num.lo(r10)
		mul			r8									; rdx:rax = num.lo(rax) * val(r8)

		add			rdx, r9								; rdx = (num.lo(rax) * val).hi(rdx)
;																+ tmp(r9)

		mov			UINT_PTR PTR [rcx], rax				; pans.lo = ans.lo(rax)
		mov			UINT_PTR PTR [rcx+byteLIMB], rdx	; pans.hi = ans.hi(rdx)

		mov			rax, rcx

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
MPAmulT PROC	;	pans:LPVOID,num:UINT_PTR, val:UINT_PTR
; Shadow Store
;		mov			UINT_PTR PTR pans, rcx
;		mov			UINT_PTR PTR num, rdx
;		mov			UINT_PTR PTR val, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			rax, UINT_PTR PTR r8				; rax = val(r8)

		mul			rdx									; return(val(rax) * num(rdx));

		mov			UINT_PTR PTR [rcx], rax				; pans.lo = ans.lo(rax)
		mov			UINT_PTR PTR [rcx+byteLIMB], rdx	; pans.hi = ans.hi(rdx)

		mov			rax, rcx

        ret
MPAmulT ENDP


END
