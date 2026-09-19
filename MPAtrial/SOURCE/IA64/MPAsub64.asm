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
		push		rbx									; ABI standardization
		push		rsi
		push		rdi
;;;		pushfq											; CF operations only (no STD used) - no impact on C code
; Shadow Store
		mov			UINT_PTR PTR pvdst, rcx
		mov			UINT_PTR PTR ndstSize, rdx
		mov			UINT_PTR PTR pvsrc, r8
		mov			UINT_PTR PTR nsrcSize, r9

;;;		mov			rax, E_INVALDARG					; Set error code
		mov			rcx, UINT_PTR PTR nsrcSize
;;;		cmp			rcx, UINT_PTR PTR ndstSize			; Caller responsibility
;;;		ja			ADD_EXIT							; if (nsrcSize > ndstSize) return(E_INVALDARG);

		mov			rdi, REGBYTE PTR pvdst
		mov			rsi, REGBYTE PTR pvsrc

		clc
;	for(nLoop=0; nLoop<nsrcSize; nLoop++) {
SUB_100:
		mov			rax, UINT_PTR PTR [rdi]				; rax = pvdet[nLoop]
		mov			rdx, UINT_PTR PTR [rsi]				; rdx = pvsrc[nLoop]
		sbb			rax, rdx							; pvdst[nLoop] -= (pvsrc[nLoop] + CF)
		mov			[rdi], UINT_PTR PTR rax

		mov			rbx, 0								; Save CF(1)(XOR is avoided because it alters CF)
		sbb			rbx, rbx							; Save CF(2) rbx = 0 - 0 - CF : (rbx = 0 or -1)
		add			rdi, byteLIMB
		add			rsi, byteLIMB
		add			rbx, rbx							; Restore CF CF = (-1 + -1) or (0 + 0)
		loop		SUB_100
		jnc			SUB_SUCCEEDED						; Skip further calculations if no CF

		mov			rcx, UINT_PTR PTR ndstSize
		mov			rax, UINT_PTR PTR nsrcSize
		sub			rcx, rax
		jz			SUB_SUCCEEDED

SUB_200:
		stc
		mov			rax, UINT_PTR PTR [rdi]				; rax = *pvdet
		sbb			rax, 0								; pvdst -= CF
		mov			[rdi], UINT_PTR PTR rax
		jnc			SUB_SUCCEEDED						; Skip further calculations if no CF

		add			rdi, byteLIMB
		loop		SUB_200

SUB_SUCCEEDED:
;;;		xor			rax, rax

SUB_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
		pop			rbx
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
		push		rdi

; Shadow Store
		mov			UINT_PTR PTR pvdst, rcx
		mov			UINT_PTR PTR ndstSize, rdx
		mov			UINT_PTR PTR val, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			rdi, UINT_PTR PTR pvdst
		mov			rdx, UINT_PTR PTR val
		mov			rcx, UINT_PTR PTR ndstSize

;	for(nLoop=0; nLoop<ndstSize; nLoop++) {
SUBV_100:
		mov			rax, UINT_PTR PTR [rdi]				; rax = *pvdet
		sub			rax, rdx							; *pvdst += val
		mov			UINT_PTR PTR [rdi], rax				; *pvdet = rax
		jnc			SUBV_SUCCEEDED

		dec			rcx
		jz			SUBV_SUCCEEDED

		add			rdi, byteLIMB
SUBV_200:
		mov			rax, UINT_PTR PTR [rdi]				; rax = *pvdet
		sub			rax, 1								; *pvdst -= 1
		mov			UINT_PTR PTR [rdi], rax				; *pvdet = rax
		jnc			SUBV_SUCCEEDED

		add			rdi, byteLIMB
		loop		SUBV_200

SUBV_SUCCEEDED:
;		xor			rax, rax

SUBV_EXIT:
		pop			rdi
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
MPAsubR	PROC	;	pans:LPVOID, pnum:LPVOID, val:UINT_PTR
; Shadow Store
;		mov			UINT_PTR PTR pans, rcx
;		mov			UINT_PTR PTR pnum, rdx
;		mov			UINT_PTR PTR val, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			r10, rdx							; r10 = pnum(rdx)
		mov			r11, rcx							; r11 = pans(rcx)

		mov			rax, UINT_PTR PTR [r10]				; rax = num.lo(r10)
		mov			rdx, UINT_PTR PTR [r10+byteLIMB]	; rdx = num.hi(r10)

		sub			rax, r8								; ans.lo(rax) -= val(r8)
		sbb			rdx, 0								; ans.hi[rdx] -= CF

		mov			UINT_PTR PTR [r11], rax
		mov			UINT_PTR PTR [r11+byteLIMB], rdx

		mov			rax, r11

		ret
MPAsubR	ENDP


END
