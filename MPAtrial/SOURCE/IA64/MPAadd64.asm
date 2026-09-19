include ../../Support/x64.inc 
include ../Include/MPA.inc 

;.STACK
; Ignore error A6004: variable declared but not used (no shadow store)

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
		push		rbx									; ABI standardization
		push		rsi									; ABI standardization
		push		rdi									; ABI standardization
;;;		pushfq											; CLD only (no STD used) - no impact on C code
; Shadow Store
		mov			UINT_PTR PTR pvdst, rcx
		mov			UINT_PTR PTR ndstSize, rdx
		mov			UINT_PTR PTR pvsrc, r8
		mov			UINT_PTR PTR nsrcSize, r9

;;;		mov			rax, E_INVALDARG					; Set error code
		mov			rcx, UINT_PTR PTR nsrcSize			; rcx = nsrcSize(r9)
;;;		cmp			rcx, UINT_PTR PTR ndstSize			; Caller responsibility
;;;		ja			ADD_EXIT							; if (nsrcSize > ndstSize) return(E_INVALDARG);

		mov			rdi, UINT_PTR PTR pvdst				; rdi = pvdst
		mov			rsi, UINT_PTR PTR pvsrc				; rsi = pvsrc

		clc
;	for(nLoop=0; nLoop<nsrcSize; nLoop++) {
ADD_100:
		mov			rax, UINT_PTR PTR [rdi]				; rax = pvdet[nLoop]
		mov			rdx, UINT_PTR PTR [rsi]				; rdx = pvsrc[nLoop]
		adc			rax, rdx							; pvdst[nLoop] += pvsrc[nLoop] + CF
		mov			[rdi], UINT_PTR PTR rax

		mov			rbx, 0								; Save CF(1)
		sbb			rbx, rbx							; Save CF(2) rbx = 0 - 0 - CF : (rbx = 0 or -1)
		add			rdi, byteLIMB
		add			rsi, byteLIMB
		add			rbx, rbx							; Restore CF CF = (-1 + -1) or (0 + 0)
		loop		ADD_100
		jnc			ADD_SUCCEEDED						; Skip further calculations if no CF

		mov			rcx, UINT_PTR PTR ndstSize			; rcx = ndstSize
		mov			rax, UINT_PTR PTR nsrcSize			; rax = nsrcSize
		sub			rcx, rax
		jz			ADD_SUCCEEDED

ADD_200:
		stc
		mov			rax, UINT_PTR PTR [rdi]				; rax = pvdet[nLoop]
		adc			rax, 0								; pvdst[nLoop] += CF
		mov			[rdi], UINT_PTR PTR rax
		jnc			ADD_SUCCEEDED

		add			rdi, byteLIMB
		loop		ADD_200

ADD_SUCCEEDED:
;;;		xor			rax, rax

ADD_EXIT:
;;;		popfq
		pop			rdi
		pop			rsi
		pop			rbx
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
MPAaddV	PROC	;	pvdst:LPVOID, ndstSize:UINT_PTR, val:UINT_PTR
		push		rdi									; ABI standardization

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR ndstSize, rdx
;		mov			UINT_PTR PTR val, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			rdi, rcx							; rdi = pvdst(rcx)
		mov			rcx, rdx							; rcx = ndstSize(rdx)
		mov			rdx, r8								; rdx = val(r8)

;	for(nLoop=0; nLoop<ndstSize; nLoop++) {
ADDV_100:
		mov			rax, UINT_PTR PTR [rdi]				; rax = *pvdet
		add			rax, rdx							; *pvdst += val
		mov			UINT_PTR PTR [rdi], rax				; *pvdet = rax
		jnc			ADDV_SUCCEEDED

		dec			rcx
		jz			ADDV_SUCCEEDED

ADDV_200:
		add			rdi, byteLIMB
		mov			rax, UINT_PTR PTR [rdi]				; rax = *pvdet
		add			rax, 1								; *pvdst += 1
		mov			UINT_PTR PTR [rdi], rax				; *pvdet = rax
		jnc			ADDV_SUCCEEDED
		loop		ADDV_200

ADDV_SUCCEEDED:
;		xor			rax, rax

ADDV_EXIT:
		pop			rdi
		ret
MPAaddV	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВБВДВДВq                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; ans = num + val
;UDINT_PTR MPAaddR(UDINT_PTR num, UINT_PTR val);

		PUBLIC		MPAaddR
		ALIGN		CALL_ALIGNMENT
MPAaddR	PROC	;	pans:LPVOID, pnum:LPVOID, val:UINT_PTR
; Shadow Store
;		mov			UINT_PTR PTR pans, rcx
;		mov			UINT_PTR PTR pnum, rdx
;		mov			UINT_PTR PTR val, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			r10, rdx							; r10 = pnum(rdx)
		mov			r11, rcx							; r11 = pans(rcx)

		mov			rax, UINT_PTR PTR [r10]				; rax = num.lo(r10)
		mov			rdx, UINT_PTR PTR [r10+byteLIMB]	; rdx = num.hi(r10)

		add			rax, r8								; ans.lo(rax) += val(r8)
		adc			rdx, 0								; ans.hi[rdx] += CF

		mov			UINT_PTR PTR [r11], rax
		mov			UINT_PTR PTR [r11+byteLIMB], rdx

		mov			rax, r11

		ret
MPAaddR	ENDP


END
