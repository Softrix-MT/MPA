#ifndef _MPAtrial_H_
#define _MPAtrial_H_
#include <WINtrial.h>

/*****************************************************************************/
/*                                ГIГvГVГЗГУ                                 */
/*****************************************************************************/
#ifndef MPALIBRARY
	#ifndef _WIN64
		#ifndef _DEBUG
			#if (_MSC_VER <= 1000)								// VC++ 4.0
				#pragma comment(lib, "MPAtri04x86.lib")
			#elif (_MSC_VER <= 1100)							// VC++ 5.0
				#pragma comment(lib, "MPAtri05x86.lib")
			#elif (_MSC_VER <= 1200)							// VC++ 6.0
				#pragma comment(lib, "MPAtri06x86.lib")
//			#elif (_MSC_VER <= 1300)							// VC++ 7.0
//			#elif (_MSC_VER <= 1310)							// VC++ 7.1
//			#elif (_MSC_VER <= 1400)							// VC++ 8.0
//			#elif (_MSC_VER <= 1500)							// VC++ 9.0
			#elif (_MSC_VER <= 1600)							// VC++ 10.0
				#pragma comment(lib, "MPAtri10x86.lib")
//			#elif (_MSC_VER <= 1700)							// Visual C++ 11.0(Visual Studio 2012)
//			#elif (_MSC_VER <= 1800)							// Visual C++ 12.0(Visual Studio 2013)
//			#elif (_MSC_VER <= 1900)							// Visual C++ 14.0(Visual Studio 2015)
//			#elif (_MSC_VER <= 1910)							// Visual C++ 14.1(Visual Studio 2017)
			#elif (_MSC_VER <= 1920)							// Visual C++ 14.2(Visual Studio 2019)
				#pragma comment(lib, "MPAtriE2x86.lib")
			#else												// VC++ XX.X
				#pragma comment(lib, "MPAtriE2x86.lib")
			#endif
			#if !defined(_MT) || defined(_DLL)
				#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
			#endif
		#else
			#if (_MSC_VER <= 1000)								// VC++ 4.0
				#pragma comment(lib, "MPAtri04x86d.lib")
			#elif (_MSC_VER <= 1100)							// VC++ 5.0
				#pragma comment(lib, "MPAtri05x86d.lib")
			#elif (_MSC_VER <= 1200)							// VC++ 6.0
				#pragma comment(lib, "MPAtri06x86d.lib")
//			#elif (_MSC_VER <= 1300)							// VC++ 7.0
//			#elif (_MSC_VER <= 1310)							// VC++ 7.1
//			#elif (_MSC_VER <= 1400)							// VC++ 8.0
//			#elif (_MSC_VER <= 1500)							// VC++ 9.0
			#elif (_MSC_VER <= 1600)							// VC++ 10.0
				#pragma comment(lib, "MPAtri10x86d.lib")
//			#elif (_MSC_VER <= 1700)							// Visual C++ 11.0(Visual Studio 2012)
//			#elif (_MSC_VER <= 1800)							// Visual C++ 12.0(Visual Studio 2013)
//			#elif (_MSC_VER <= 1900)							// Visual C++ 14.0(Visual Studio 2015)
//			#elif (_MSC_VER <= 1910)							// Visual C++ 14.1(Visual Studio 2017)
			#elif (_MSC_VER <= 1920)							// Visual C++ 14.2(Visual Studio 2019)
				#pragma comment(lib, "MPAtriE2x86d.lib")
			#else												// VC++ XX.X
				#pragma comment(lib, "MPAtriE2x86d.lib")
			#endif
			#if !defined(_MT) || defined(_DLL)
				#pragma comment(linker, "/NODEFAULTLIB:libcmtd.lib")
			#endif
		#endif
	#else
		#ifndef _DEBUG
			#if (_MSC_VER <= 1600)								// VC++ 10.0
				#pragma comment(lib, "MPAtri10x64.lib")
//			#elif (_MSC_VER <= 1700)							// Visual C++ 11.0(Visual Studio 2012)
//			#elif (_MSC_VER <= 1800)							// Visual C++ 12.0(Visual Studio 2013)
//			#elif (_MSC_VER <= 1900)							// Visual C++ 14.0(Visual Studio 2015)
//			#elif (_MSC_VER <= 1910)							// Visual C++ 14.1(Visual Studio 2017)
			#elif (_MSC_VER <= 1920)							// Visual C++ 14.2(Visual Studio 2019)
				#pragma comment(lib, "MPAtriE2x64.lib")
			#else												// VC++ XX.X
				#pragma comment(lib, "MPAtriE2x64.lib")
			#endif
			#if !defined(_MT) || defined(_DLL)
				#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
			#endif
		#else
			#if (_MSC_VER <= 1600)								// VC++ 10.0
				#pragma comment(lib, "MPAtri10x64d.lib")
//			#elif (_MSC_VER <= 1700)							// Visual C++ 11.0(Visual Studio 2012)
//			#elif (_MSC_VER <= 1800)							// Visual C++ 12.0(Visual Studio 2013)
//			#elif (_MSC_VER <= 1900)							// Visual C++ 14.0(Visual Studio 2015)
//			#elif (_MSC_VER <= 1910)							// Visual C++ 14.1(Visual Studio 2017)
			#elif (_MSC_VER <= 1920)							// Visual C++ 14.2(Visual Studio 2019)
				#pragma comment(lib, "MPAtriE2x64d.lib")
			#else												// VC++ XX.X
				#pragma comment(lib, "MPAtriE2x64d.lib")
			#endif
			#if !defined(_MT) || defined(_DLL)
				#pragma comment(linker, "/NODEFAULTLIB:libcmtd.lib")
			#endif
		#endif
	#endif
#endif	//MPALIBRARY


/*****************************************************************************/
/*                                Н\СвС╠ТшЛ`                                 */
/*****************************************************************************/
#pragma pack(push, 1)

typedef struct tagMPAUDINT32 {
		DWORD						lo;
		DWORD						hi;
		} MPAUDINT32, *LPMPAUDINT32;

typedef struct tagMPAUDINT64 {
		QWORD						lo;
		QWORD						hi;
		} MPAUDINT64, *LPMPAUDINT64;

#ifndef _WIN64

typedef MPAUDINT32					MPAUDINT;

#else	//_WIN64

typedef MPAUDINT64					MPAUDINT;
/*
typedef struct tagMPUQINT {
		MPAUDINT64					lo;
		MPAUDINT64					hi;
		} MPUQINT, *LPMPUQINT;
*/
#endif	//_WIN64

typedef MPAUDINT					*LPMPAUDINT;

#pragma pack(pop)

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
#ifndef _WIN64
	typedef ULONGLONG				UDINT_PTR;
#else	//_WIN64
//	typedef __m128					UDINT_PTR;
	typedef MPAUDINT				UDINT_PTR;
#endif	//_WIN64

/*****************************************************************************/
/*                                Г}ГNГНТшЛ`                                 */
/*****************************************************************************/
/*****************************************************************************/
/*                                ГfБ[Г^Ч╠Иц                                 */
/*****************************************************************************/
#ifndef MPALIBRARY
	extern const INT_PTR*			_mpa_valueA;
	extern const INT_PTR*			_mpa_valueB;

	extern const UINT_PTR*			_mpa_girder[];
#endif	//MPALIBRARY

/*****************************************************************************/
/*                                 К╓РФТшЛ`                                  */
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВnВoВq                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
int			MPAbsr(UINT_PTR val);												// Bit Scan Reverse
int			MPAbsf(UINT_PTR val);												// Bit Scan Forward(Count Trailing Zeros)
void		MPAset(UINT_PTR* pvdst, UINT_PTR val, size_t nlimbSize);			// memset(pvdst, val, (nlimbSize*sizeof(UINT_PTR));
void		MPAcpy(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize);	// memcpy(pvdst, pvsrc, (nlimbSize*sizeof(UINT_PTR));
void		MPAnot(UINT_PTR* pvdst, size_t nlimbSize);							// ВPВ╠ХтРФ
void		MPAneg(UINT_PTR* pvdst, size_t nlimbSize);							// ВQВ╠ХтРФ
int			MPAcmpS(UDINT_PTR dbuf1, UDINT_PTR buf2);							// ФфКr
bool		MPAisZero(const UINT_PTR* pvsrc, size_t nlimbSize);					// ВOФ╗Тш(0:true В╗В╠С╝:false)

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВrВgВk                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
// pvdst[...] = pvsrc[...] << (bitsLIMB*nlimbShift + nbitsShift)
void		MPAshlL(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR nbitsShift/*, UINT_PTR padding*/);

// pvdst[...+nlimbShift] = pvsrc[...]
void		MPAshlM(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR padding);
inline void	MPAins(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR padding) { MPAshlM(pvdst, pvsrc, nlimbSize, nlimbShift, padding); }

// pvdst[...] = pvsrc[...] << 1...(bitsLIMB-1)
void		MPAshlS(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, UINT_PTR nbitsShift/*, UINT_PTR padding*/);

// pvdst[...] = pvsrc[...] << 1
void		MPAshl1(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize);

// val <<= shift
UDINT_PTR	MPAshlR(UDINT_PTR val, UINT_PTR shift);

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВrВgВq                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
// pvdst[...] = pvsrc[...] >> (bitsLIMB*nlimbShift + nbitsShift)
void		MPAshrL(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, size_t nlimbShift, UINT_PTR nbitsShift/*, UINT_PTR padding*/);

// pvdst[...] = pvsrc[...+nlimbShift]
void		MPAshrM(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, UINT_PTR nlimbShift, UINT_PTR padding);

// pvdst[...] = pvsrc[...] >> 1...(bitsLIMB-1)
void		MPAshrS(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize, UINT_PTR nbitsShift/*, UINT_PTR padding*/);

// pvdst[...] = pvsrc[...] >> 1
void		MPAshr1(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nlimbSize);

// val >>= shift
UDINT_PTR	MPAshrR(UDINT_PTR val, UINT_PTR shift);

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  В`ВcВc                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void		MPAadd(UINT_PTR* pvdst, size_t ndstSize, const UINT_PTR* pvsrc, size_t nsrcSize);
void		MPAaddV(UINT_PTR* pvdst, size_t ndstSize, UINT_PTR val);
UDINT_PTR	MPAaddR(UDINT_PTR num, UINT_PTR val);

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВrВtВa                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void		MPAsub(UINT_PTR* pvdst, size_t ndstSize, const UINT_PTR* pvsrc, size_t nsrcSize);
void		MPAsubV(UINT_PTR* pvdst, size_t ndstSize, UINT_PTR val);
UDINT_PTR	MPAsubR(UDINT_PTR num, UINT_PTR val);

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВlВtВk                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
void		MPAmul(UINT_PTR* pvdst, const UINT_PTR* pvsrc1, size_t nsrc1Size, const UINT_PTR* pvsrc2, size_t nsrc2Size);
void		MPAmulV(UINT_PTR* pvdst, const UINT_PTR* pvsrc, size_t nsrcSize, UINT_PTR val);
UDINT_PTR	MPAmulT(UINT_PTR num, UINT_PTR val);

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВcВhВu                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
UDINT_PTR	MPAdivR(UDINT_PTR num, UINT_PTR den);
UDINT_PTR	MPAdivE(UDINT_PTR num, UINT_PTR den, UINT_PTR* prem);

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                             ВcВЙВЦВdВШВБВГВФ                              */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
// pvdst[...] /= 3								Бж pvdstВ═3В┼ХKВ╕КДВшР╪ВъВщТlВ╔М└Вщ
void MPAdev3(UINT_PTR* pvdst, size_t nlimbSize);
// pvdst[...] /= 5								Бж pvdstВ═5В┼ХKВ╕КДВшР╪ВъВщТlВ╔М└Вщ
void MPAdev5(UINT_PTR* pvdst, size_t nlimbSize);
// pvdst[...] /= 5								Бж pvdstВ═9В┼ХKВ╕КДВшР╪ВъВщТlВ╔М└Вщ
void MPAdev9(UINT_PTR* pvdst, size_t nlimbSize);

#ifdef __cplusplus
}
#endif

#endif
