IFNDEF __x64_inc__
__x64_inc__				EQU			1

;.686

;.MODEL FLAT, C

;/*****************************************************************************/
;/*                                ГIГvГVГЗГУ                                 */
;/*****************************************************************************/
; Сц 1 И°РФ	RCX	ПэВ╔Н┼ПЙВ╠И°РФВ╔ОgЧpВ│ВъВ▄В╖БB
; Сц 2 И°РФ	RDX	
; Сц 3 И°РФ	R8	
; Сц 4 И°РФ	R9

IFNDEF @WordSize
	@WordSize			EQU			8
ENDIF

;/*****************************************************************************/
;/*                             ГvГНГgГ^ГCГvТшЛ`                              */
;/*****************************************************************************/
_WIN64					EQU			1
CALL_ALIGNMENT			EQU			16								; ▒╫▓╥▌─

__int32					TYPEDEF		SDWORD
long					TYPEDEF		SDWORD
ULONG					TYPEDEF		DWORD
float					TYPEDEF		REAL4
double					TYPEDEF		REAL8
LONGLONG				TYPEDEF		SQWORD

INT_PTR					TYPEDEF		SQWORD							; sign quad word
UINT_PTR				TYPEDEF		QWORD							; register size word
REGBYTE					TYPEDEF		QWORD							; register size word

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
ALto8BYTE		MACRO	dst:=<rdi>
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
AXto8WORD		MACRO	dst:=<rdi>
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


ENDIF	; __x64_inc__
