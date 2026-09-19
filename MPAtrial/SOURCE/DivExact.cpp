#include "../INCLUDE/StdHead.h"

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
#pragma pack(push, 1)

typedef struct tagDEVBUFF {
		union {
			struct {
				UINT_PTR			lo;
				UINT_PTR			hi;
				};
			UDINT_PTR				val;
			};
		} DEVBUFF, *LPDEVBUFF;

#pragma pack(pop)

/*****************************************************************************/
/*                                ГfБ[Г^Ч╠Иц                                 */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГRБ[ГhЧ╠Иц                                 */
/*****************************************************************************/
// Exact Division by a Constant proposed by Jebelean et al.
// Modular Multiplicative Inverse
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ВlВoВ`ВДВЕВЦВR                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
function divexact_by_3(num[0..n-1]):
#if 32bit
    inv3 = 0xAAAAAAAB
#else 64bit
    inv3 = 0xAAAAAAAAAAAAAAAB
#endif

	carry = 0
	for i = 0 .. n-1:
		t  = num[i] - carry
		qi = low_bits(t * inv3)
		num[i] = qi
		carry = high_bits(qi * 3 + carry)

	return num
*/
// pvdst[...] /= 3								Бж Assumes pvdst is always divisible by 3
void MPAdev3(UINT_PTR* pvdst, size_t nlimbSize)
{
	DEVBUFF		buf;
	UINT_PTR	carry=0;
	size_t		nLoop;

	for(nLoop=0; nLoop<nlimbSize; nLoop++) {
		UINT_PTR&	val=pvdst[nLoop];

#ifndef _WIN64
		buf.val = ::MPAmulR(::MPAsubR(val, carry), 0xAAAAAAAB);
#else	//_WIN64
		MPAUDINT	m64={ val, 0 };

		buf.val = ::MPAmulR(::MPAsubR(m64, carry), 0xAAAAAAAAAAAAAAAB);
#endif	//_WIN64
		val = buf.lo;

		buf.val = ::MPAaddR(::MPAmulT(buf.lo, 3), carry);
		carry = buf.hi;
		}
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ВlВoВ`ВДВЕВЦВT                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
function divexact_by_5(num[0..n-1]):
#if 32bit
    inv5 = 0xCCCCCCCD
#else 64bit
    inv5 = 0xCCCCCCCCCCCCCCCD
#endif

    carry = 0
    for i = 0 .. n-1:
        t  = num[i] - carry
        qi = low_bits(t * inv5)
        num[i] = qi
        carry = high_bits(qi * 5 + carry)

    return num
*/
// pvdst[...] /= 5								Бж Assumes pvdst is always divisible by 5
void MPAdev5(UINT_PTR* pvdst, size_t nlimbSize)
{
	DEVBUFF		buf;
	UINT_PTR	carry=0;
	size_t		nLoop;

	for(nLoop=0; nLoop<nlimbSize; nLoop++) {
		UINT_PTR&	val=pvdst[nLoop];

#ifndef _WIN64
		buf.val = ::MPAmulR(::MPAsubR(val, carry), 0xCCCCCCCD);
#else	//_WIN64
		MPAUDINT	m64={ val, 0 };

		buf.val = ::MPAmulR(::MPAsubR(m64, carry), 0xCCCCCCCCCCCCCCCD);
#endif	//_WIN64
		val = buf.lo;

		buf.val = ::MPAaddR(::MPAmulT(buf.lo, 5), carry);
		carry = buf.hi;
		}
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ВlВoВ`ВДВЕВЦВV                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
function divexact_by_7(num[0..n-1]):
#if 32bit
    inv7 = 0xB6DB6DB7
#else 64bit
    inv7 = 0x6DB6DB6DB6DB6DB7
#endif

    carry = 0
    for i = 0 .. n-1:
        t  = num[i] - carry
        qi = low_bits(t * inv7)
        num[i] = qi
        carry = high_bits(qi * 7 - t)

    return num
*/

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ВlВoВ`ВДВЕВЦВX                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*
function divexact_by_9(num[0..n-1])
#if 32bit
	inv9 = 0x38E38E39
#else 64bit
	inv9 = 0x8E38E38E38E38E39
#endif

	carry = 0
	for i = 0 .. n-1:
		t  = num[i] - carry
		qi = low_bits(t * inv9)
		num[i] = qi
		carry = high_bits(qi * 9 + carry)

    return num
*/
// pvdst[...] /= 9								Бж Assumes pvdst is always divisible by 9
void MPAdev9(UINT_PTR* pvdst, size_t nlimbSize)
{
#if 1
	DEVBUFF		buf;
	UINT_PTR	carry=0;
	size_t		nLoop;

	for(nLoop=0; nLoop<nlimbSize; nLoop++) {
		UINT_PTR&	val=pvdst[nLoop];

#ifndef _WIN64
		buf.val = ::MPAmulR(::MPAsubR(val, carry), 0x38E38E39);
#else	//_WIN64
		MPAUDINT	m64={ val, 0 };

		buf.val = ::MPAmulR(::MPAsubR(m64, carry), 0x8E38E38E38E38E39);		// 0xAAAAAAAAAAAAAAAB Б~ 0xAAAAAAAAAAAAAAAB
#endif	//_WIN64
		val = buf.lo;

		buf.val = ::MPAaddR(::MPAmulT(buf.lo, 9), carry);
		carry = buf.hi;
		}
#else
	MPAdev3(pvdst, nlimbSize);
	MPAdev3(pvdst, nlimbSize);
#endif
}
