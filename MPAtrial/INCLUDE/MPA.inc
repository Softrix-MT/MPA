
;/*****************************************************************************/
;/*                                ГIГvГVГЗГУ                                 */
;/*****************************************************************************/
;/*****************************************************************************/
;/*                             ГvГНГgГ^ГCГvТшЛ`                              */
;/*****************************************************************************/

byteLIMB					EQU				SIZEOF UINT_PTR
;bitsLIMB					EQU				byteLIMB * 8

IFDEF _WIN64
;;;	byteLIMB				EQU				8				; Byte SIZE
	bitSHR_LIMB				EQU				6				; floor(n / bitsLIMB(64))
	bitREM_LIMB				EQU				3Fh				; n %= bitsLIMB
	shlLIMBtoBYTE			EQU				3				; n *= byteLIMB(limb order -> BYTE order)
ELSE
;;;	byteLIMB				EQU				4				; Byte SIZE
	bitSHR_LIMB				EQU				5				; floor(n / bitsLIMB(32))
	bitREM_LIMB				EQU				1Fh				; n %= bitsLIMB
	shlLIMBtoBYTE			EQU				2				; n *= byteLIMB(limb order -> BYTE order)
ENDIF

	bitsLIMB				EQU				(byteLIMB * 8)	; Bit SIZE

;/*****************************************************************************/
;/*                                Н\СвС╠ТшЛ`                                 */
;/*****************************************************************************/
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                            ВlВoВ`ВtВcВhВmВs                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
MPAUDINT32 STRUCT 1
		DWORD						lo;
		DWORD						hi;
MPAUDINT32 ENDS

MPAUDINT64 STRUCT 1
		QWORD						lo;
		QWORD						hi;
MPAUDINT64 ENDS

IF @WordSize NE 8										; not 64bit(32bit)
	MPAUDINT		TYPEDEF			MPAUDINT32
ELSE													; 64bit
	MPAUDINT		TYPEDEF			MPAUDINT64
ENDIF

LPMPAUDINT			TYPEDEF			PTR MPAUDINT

;/*****************************************************************************/
;/*                             ГvГНГgГ^ГCГvТшЛ`                              */
;/*****************************************************************************/
IF @WordSize NE 8										; not 64bit(32bit)
	UDINT_PTR		TYPEDEF			QWORD
ELSE													; 64bit
	UDINT_PTR		TYPEDEF			MPAUDINT
ENDIF

LPUDINTPTR			TYPEDEF			PTR UDINT_PTR

;/*****************************************************************************/
;/*                                Г}ГNГНЧ╠Иц                                 */
;/*****************************************************************************/
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;/*                              ВoВЕВТВaВЙВФВУ                               */
;/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
;RegPerBitsLIBM	MACRO	reg
;		shr			reg, bitSHR_LIMB						; reg = floor(reg / bitsLIMB)
;ENDM

