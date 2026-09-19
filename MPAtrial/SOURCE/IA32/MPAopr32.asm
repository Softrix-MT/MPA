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
;/*                               ВlВoВ`ВВВУВТ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;int MPAbsr(UINT_PTR val)								// Bit Scan Reverse

		PUBLIC		MPAbsr
		ALIGN		CALL_ALIGNMENT
MPAbsr	PROC		val:UINT_PTR
		bsr			eax, UINT_PTR PTR val
		jnz			BSR_EXIT

BSR_ERROR:
		mov			eax, INT_PTR PTR -1

BSR_EXIT:
		ret
MPAbsr	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВВВУВЖ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;int MPAbsf(UINT_PTR val)								// Bit Scan Forward

		PUBLIC		MPAbsf
		ALIGN		CALL_ALIGNMENT
MPAbsf	PROC		val:UINT_PTR
		bsf			eax, UINT_PTR PTR val
		jnz			BSF_EXIT

BSF_ERROR:
		mov			eax, INT_PTR PTR -1

BSF_EXIT:
		ret
MPAbsf	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВГВФВЪ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;int MPActz(UINT_PTR val)								// Count Trailing Zeros

		PUBLIC		MPActz
		ALIGN		CALL_ALIGNMENT
MPActz	PROC		val:UINT_PTR

		mov			ecx, UINT_PTR PTR val				; Use ECX to comply with Microsoft x64 calling convention
		test		ecx, ecx
		jz			CTZ_ERROR

		xor			eax, eax
CTZ_100:
		test		ecx, 1
		jnz			CTZ_EXIT

		shr			ecx, 1
		inc			eax
		jmp			CTZ_100

CTZ_ERROR:
		mov			eax, INT_PTR PTR -1

CTZ_EXIT:

		ret
MPActz	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВУВЕВФ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;void MPAset(UINT_PTR* pvdst, UINT_PTR val, size_t nlimbSize)

;		for(nLoop=0; nLoop<nlimbSize); nLoop++) pvdst[nLoop] = val;

		PUBLIC		MPAset
		ALIGN		CALL_ALIGNMENT
MPAset	PROC		pvdst:LPVOID, val:UINT_PTR, nlimbSize:UINT_PTR
		push		edi									; ABI standardization
;;;		pushfd											; CLD only (no STD used) - no impact on C code

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			eax, UINT_PTR PTR val				; eax = val
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize

;;;		cld												; Omitted: MSVC ABI (defaults to CLD)
		rep			stosd								; rep			stosq		; 64bit

;;;		popfd
		pop			edi
		ret
MPAset	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВГВРВЩ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;void MPAcpy(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize)

;		for(nLoop=0; nLoop<nlimbSize); nLoop++) pvdst[nLoop] = pvsrc[nLoop];

		PUBLIC		MPAcpy
		ALIGN		CALL_ALIGNMENT
MPAcpy	PROC		pvdst:LPVOID, pvsrc:LPVOID, nlimbSize:UINT_PTR
		push		esi									; ABI standardization
		push		edi									; ABI standardization
;;;		pushfd											; CLD only (no STD used) - no impact on C code

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			esi, UINT_PTR PTR pvsrc				; esi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize

;;;		cld												; Omitted: MSVC ABI (defaults to CLD)
		rep			movsd								; rep			movsq		; 64bit

;;;		popfd
		pop			edi
		pop			esi
		ret
MPAcpy	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВОВПВФ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;void MPAnot(UINT_PTR* pvdst, size_t nlimbSize)
; 1В╠ХтРФХ╧К╖
;		for(nLoop=0; nLoop<nlimbSize); nLoop++) pvdst[nLoop] ^= -1;

		PUBLIC		MPAnot
		ALIGN		CALL_ALIGNMENT
MPAnot	PROC		pvdst:LPVOID, nlimbSize:UINT_PTR
		push		edi									; ABI standardization

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize

NOT_100:
		mov			eax, UINT_PTR PTR [edi]
		xor			eax, -1
		mov			UINT_PTR PTR [edi], eax

		add			edi, byteLIMB						; pvdst(edi)++
		loop		NOT_100

		pop			edi
		ret
MPAnot	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                               ВlВoВ`ВОВЕВЗ                                */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;void MPAneg(UINT_PTR* pvdst, size_t nlimbSize)
; 2В╠ХтРФХ╧К╖
;		for(nLoop=0; nLoop<nlimbSize); nLoop++) pvdst[nLoop] ^= -1;
;		add(1)

		PUBLIC		MPAneg
		ALIGN		CALL_ALIGNMENT
MPAneg	PROC		pvdst:LPVOID, nlimbSize:UINT_PTR
		push		edi									; ABI standardization

		mov			edi, UINT_PTR PTR pvdst				; edi = pvdst
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize
		mov			edx, 1								; EDX=0; DL=1

NEG_100:
		mov			eax, UINT_PTR PTR [edi]
		xor			eax, -1
		add			eax, edx
		setc		dl
		mov			UINT_PTR PTR [edi], eax

		add			edi, byteLIMB						; pvdst(edi)++
		loop		NEG_100

		pop			edi
		ret
MPAneg	ENDP

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВlВoВ`ВГВНВРВr                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;int MPAcmpS(UDINT_PTR buf1, UDINT_PTR buf2);

		PUBLIC		MPAcmpS
		ALIGN		CALL_ALIGNMENT
MPAcmpS	PROC		buf1_lo:UINT_PTR, buf1_hi:UINT_PTR, buf2_lo:UINT_PTR, buf2_hi:UINT_PTR

		mov			eax, UINT_PTR PTR buf1_hi			; eax = buf1.hi
		mov			edx, UINT_PTR PTR buf2_hi			; edx = buf2.hi
		cmp			eax, edx
		ja			CMPS_PLUS
		jb			CMPS_MINUS

		mov			eax, UINT_PTR PTR buf1_lo			; eax = buf1.lo
		mov			edx, UINT_PTR PTR buf2_lo			; edx = buf2.lo
		cmp			eax, edx
		ja			CMPS_PLUS
		jb			CMPS_MINUS

CMPS_EXIT:
		xor			eax, eax
		ret

CMPS_PLUS:
		mov			eax, 1
		ret

CMPS_MINUS:
		mov			eax, -1
		ret

MPAcmpS	ENDP


;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                            ВlВoВ`ВЙВУВyВЕВТВП                             */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;bool MPAisZero(const UINT_PTR* pvsrc, size_t nlimbSize)
; Zero check (0: true, else: false)

		PUBLIC		MPAisZero
		ALIGN		CALL_ALIGNMENT
MPAisZero PROC		pvsrc:LPVOID, nlimbSize:UINT_PTR
		push		edi									; ABI standardization

		mov			edi, UINT_PTR PTR pvsrc				; edi = pvsrc
		mov			ecx, UINT_PTR PTR nlimbSize			; ecx = nlimbSize

ZERO_100:
		mov			eax, UINT_PTR PTR [edi]
		test		eax, eax
		jnz			ZERO_NOT

		add			edi, byteLIMB						; pvsrc(edi)++
		loop		ZERO_100

ZERO_EXIT:
		mov			eax, 1
		pop			edi
		ret

ZERO_NOT:
		xor			eax, eax
		pop			edi
		ret
MPAisZero	ENDP

END
