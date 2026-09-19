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
;/*                               ВlВoВ`ВВВУВТ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;int MPAbsr(UINT_PTR val)								// Bit Scan Reverse

		PUBLIC	MPAbsr
		ALIGN	CALL_ALIGNMENT
MPAbsr	PROC	;	val:UINT_PTR
; Shadow Store
;		mov			UINT_PTR PTR val, rcx
;		mov			UINT_PTR PTR xxx, rdx
;		mov			UINT_PTR PTR xxx, r8
;		mov			UINT_PTR PTR xxx, r9

		bsr			rax, rcx
		jnz			BSR_EXIT

BSR_ERROR:
		mov			rax, INT_PTR PTR -1

BSR_EXIT:
		ret
MPAbsr	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВВВУВЖ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;int MPAbsf(UINT_PTR val)								// Bit Scan Forward

		PUBLIC	MPAbsf
		ALIGN	CALL_ALIGNMENT
MPAbsf	PROC	;	val:UINT_PTR
; Shadow Store
;		mov			UINT_PTR PTR val, rcx
;		mov			UINT_PTR PTR xxx, rdx
;		mov			UINT_PTR PTR xxx, r8
;		mov			UINT_PTR PTR xxx, r9

		bsf			rax, rcx
		jnz			BSF_EXIT

BSF_ERROR:
		mov			rax, INT_PTR PTR -1

BSF_EXIT:
		ret
MPAbsf	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВГВФВЪ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;int MPActz(UINT_PTR val)								// Count Trailing Zeros

		PUBLIC	MPActz
		ALIGN	CALL_ALIGNMENT
MPActz	PROC	;	val:UINT_PTR

; Shadow Store
;		mov			UINT_PTR PTR val, rcx
;		mov			UINT_PTR PTR xxx, rdx
;		mov			UINT_PTR PTR xxx, r8
;		mov			UINT_PTR PTR xxx, r9

		test		rcx, rcx
		jz			CTZ_ERROR

		xor			rax, rax
CTZ_100:
		test		rcx, 1
		jnz			CTZ_EXIT

		shr			rcx, 1
		inc			rax
		jmp			CTZ_100

CTZ_ERROR:
		mov			rax, INT_PTR PTR -1

CTZ_EXIT:

		ret
MPActz	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВУВЕВФ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;void MPAset(UINT_PTR* pvdst, UINT_PTR val, size_t nlimbSize)

;		for(nLoop=0; nLoop<nlimbSize); nLoop++) pvdst[nLoop] = val;

		PUBLIC	MPAset
		ALIGN	CALL_ALIGNMENT
MPAset	PROC	;	pvdst:LPVOID, val:UINT_PTR, nlimbSize:UINT_PTR
		push		rdi									; ABI standardization
;;;		pushfq											; CLD only (no STD used) - no impact on C code

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR val, rdx
;		mov			UINT_PTR PTR nlimbSize, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			rdi, rcx							; rdi = pvdst(rcx)
		mov			rax, rdx							; rax = val(rdx)
		mov			rcx, r8								; rcx = nlimbSize(r8)

;;;		cld												; Omitted: MSVC ABI (defaults to CLD)
		rep			stosq

;;;		popfq
		pop			rdi
		ret
MPAset	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВГВРВЩ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;void MPAcpy(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize)

;		for(nLoop=0; nLoop<nlimbSize); nLoop++) pvdst[nLoop] ^= pvsrc[nLoop];

		PUBLIC	MPAcpy
		ALIGN	CALL_ALIGNMENT
MPAcpy	PROC	;	pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR
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

;;;		cld												; Omitted: MSVC ABI (defaults to CLD)
		rep			movsq

;;;		popfq
		pop			rdi
		pop			rsi
		ret
MPAcpy	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВОВПВФ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;void MPAnot(UINT_PTR* pvdst, size_t nlimbSize)
; 1's complement conversion
;		for(nLoop=0; nLoop<nlimbSize); nLoop++) pvdst[nLoop] ^= -1;

		PUBLIC	MPAnot
		ALIGN	CALL_ALIGNMENT
MPAnot	PROC	;	pvdst:LPVOID, nlimbSize:UINT_PTR
		push		rdi									; ABI standardization

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR nlimbSize, rdx
;		mov			UINT_PTR PTR xxx, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			rdi, rcx							; rdi = pvdst(rcx)
		mov			rcx, rdx							; rcx = nlimbSize(rdx)

NOT_100:
		mov			rax, UINT_PTR PTR [rdi]
		xor			rax, -1
		mov			UINT_PTR PTR [rdi], rax

		add			rdi, byteLIMB						; pvdst(rdi)++
		loop		NOT_100

		pop			rdi
		ret
MPAnot	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВОВЕВЗ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;void MPAneg(UINT_PTR* pvdst, size_t nlimbSize)
; 2's complement conversion
;		for(nLoop=0; nLoop<nlimbSize); nLoop++) pvdst[nLoop] ^= -1;
;		add(1)

		PUBLIC	MPAneg
		ALIGN	CALL_ALIGNMENT
MPAneg	PROC	;	pvdst:LPVOID, nlimbSize:UINT_PTR
		push		rdi									; ABI standardization

; Shadow Store
;		mov			UINT_PTR PTR pvdst, rcx
;		mov			UINT_PTR PTR nlimbSize, rdx
;		mov			UINT_PTR PTR xxx, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			rdi, rcx							; edi = pvdst(rcx)
		mov			rcx, rdx							; rcx = nlimbSize(rdx)
		mov			rdx, 1								; rdx=0; DL=1

NEG_100:
		mov			rax, UINT_PTR PTR [rdi]
		xor			rax, -1
		add			rax, rdx
		setc		dl
		mov			UINT_PTR PTR [rdi], rax

		add			rdi, byteLIMB						; pvdst(rdi)++
		loop		NEG_100

		pop			rdi
		ret
MPAneg	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВГВНВРВr                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;int MPAcmpS(UDINT_PTR buf1, UDINT_PTR buf2);
;  0: buh1 == buf2
;  1: buh1 > buf2
; -1: buh1 < buf2

		PUBLIC	MPAcmpS
		ALIGN	CALL_ALIGNMENT
MPAcmpS	PROC	;	pbuf1:LPVOID, pbuf2:LPVOID

; Shadow Store
;		mov			UINT_PTR PTR pbuf1, rcx
;		mov			UINT_PTR PTR pbuf2, rdx
;		mov			UINT_PTR PTR xxx, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			r10, rcx							; r10 = pbuf1(rcx)
		mov			r11, rdx							; r11 = pbuf2(rdx)

		mov			rax, UINT_PTR PTR [r10+byteLIMB]	; rax = buf1.hi(r10)
		mov			rdx, UINT_PTR PTR [r11+byteLIMB]	; rdx = buf2.hi(r11)
		cmp			rax, rdx
		ja			CMPS_PLUS
		jb			CMPS_MINUS

		mov			rax, UINT_PTR PTR [r10]				; rax = buf1.lo(r10)
		mov			rdx, UINT_PTR PTR [r11]				; rdx = buf2.lo(r11)
		cmp			rax, rdx
		ja			CMPS_PLUS
		jb			CMPS_MINUS

CMPS_EXIT:
		xor			rax, rax
		ret

CMPS_PLUS:
		mov			rax, 1
		ret

CMPS_MINUS:
		mov			rax, -1
		ret

MPAcmpS	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                            ВlВoВ`ВЙВУВyВЕВТВП                             */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;bool MPAisZero(const UINT_PTR* pvsrc, size_t nlimbSize)
; Zero check (0: true, else: false)

		PUBLIC	MPAisZero
		ALIGN	CALL_ALIGNMENT
MPAisZero PROC	;	pvsrc:LPVOID, nlimbSize:UINT_PTR
		push		rdi									; ABI standardization

; Shadow Store
;		mov			UINT_PTR PTR pvsrc, rcx
;		mov			UINT_PTR PTR nlimbSize, rdx
;		mov			UINT_PTR PTR xxx, r8
;		mov			UINT_PTR PTR xxx, r9

		mov			rdi, rcx							; rdi = pvsrc(rcx)
		mov			rcx, rdx							; rcx = nlimbSize(rdx)

ZERO_100:
		mov			rax, UINT_PTR PTR [rdi]
		test		rax, rax
		jnz			ZERO_NOT

		add			rdi, byteLIMB						; pvsrc(rdi)++
		loop		ZERO_100

ZERO_EXIT:
		mov			rax, 1
		pop			rdi
		ret

ZERO_NOT:
		xor			rax, rax
		pop			rdi
		ret
MPAisZero	ENDP


END
