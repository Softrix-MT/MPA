IFNDEF __x86_inc__
__x86_inc__				EQU			1

.686

.MODEL FLAT, C

;/*****************************************************************************/
;/*                                ГIГvГVГЗГУ                                 */
;/*****************************************************************************/
;/*****************************************************************************/
;/*                                 ТшРФТшЛ`                                  */
;/*****************************************************************************/
E_INVALDARG				EQU			80070057h

;/*****************************************************************************/
;/*                             ГvГНГgГ^ГCГvТшЛ`                              */
;/*****************************************************************************/
CALL_ALIGNMENT			EQU			16								; ▒╫▓╥▌─

IF @Version LT 800													; MASM8.0(Visual Studio 2005)
	XMMWORD				TYPEDEF		OWORD
ENDIF

__int32					TYPEDEF		SDWORD
long					TYPEDEF		SDWORD
ULONG					TYPEDEF		DWORD
float					TYPEDEF		REAL4
double					TYPEDEF		REAL8
LONGLONG				TYPEDEF		QWORD

INT_PTR					TYPEDEF		SDWORD							; sign double word
UINT_PTR				TYPEDEF		DWORD							; register size word
REGBYTE					TYPEDEF		DWORD							; register size word

LPVOID					TYPEDEF		PTR
LPCVOID					TYPEDEF		PTR
LPBYTE					TYPEDEF		PTR BYTE

;/*****************************************************************************/
;/*                                Г}ГNГНЧ╠Иц                                 */
;/*****************************************************************************/
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                            В`ВkВФВПВWВaВxВsВd                             */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; КЎФнРл(eax, ecx)
ALto8BYTE		MACRO	dst:=<edi>
; AL - > EAX
		mov			ah, al
		mov			cx, ax
		shl			eax, 16
		mov			ax, cx
;
		mov			DWORD PTR [dst], eax;
		mov			DWORD PTR [dst+4], eax;
ENDM

;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                            В`ВwВФВПВWВvВnВqВc                             */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
; КЎФнРл(eax, ecx)
AXto8WORD		MACRO	dst:=<edi>
; AX - > EAX
		mov			ecx, eax
		shl			eax, 16
		mov			ax, cx
;
		mov			DWORD PTR [dst], eax;
		mov			DWORD PTR [dst+4], eax;
		mov			DWORD PTR [dst+8], eax;
		mov			DWORD PTR [dst+12], eax;
ENDM

; Proc call
; PPROTO TYPEDEF   PROTO NEAR C arg1:byte, arg2:word ; Define proc prototype
ENDIF	; __x86_inc__



