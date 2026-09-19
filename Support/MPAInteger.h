#ifndef _MPAInteger_H_
#define _MPAInteger_H_
#include <MPAtrial.h>
#include <MPAHRESULT.h>

/*****************************************************************************/
/*                             ГvГНГgГ^ГCГvТшЛ`                              */
/*****************************************************************************/
/*****************************************************************************/
/*                                Н\СвС╠ТшЛ`                                 */
/*****************************************************************************/
#pragma pack(push, 1)

typedef struct tagMPAUDINTBUFF {
		union {
			struct {
				UINT_PTR			lo;
				UINT_PTR			hi;
				};
			UDINT_PTR				val;
			};
		} MPAUDINTBUFF, *LPMPAUDINTBUFF;

#pragma pack(pop)

/*****************************************************************************/
/*                                ГNГЙГXТшЛ`                                 */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/*                  Multiple Precision Arithmetic Integers                   */ 
/*                           ВlВoВ`ВhВОВФВЕВЗВЕВТ                            */
/*---------------------------------------------------------------------------*/
class MPAInteger {
	protected:
		enum { bitsLIMB=(sizeof(UINT_PTR) * 8), maxBASE=62 };
	protected:
#ifndef _WIN64
		enum { mulKARATSUBA=64, mulTOOM3=512, mulTOOM4=1536, mulTOOM5=2048, mulTOOM6=4096 };
		enum { divBURNIKELZIEGLER=380, divNEWTONRAPHSON=1000 };
#else
		enum { mulKARATSUBA=180, mulTOOM3=512, mulTOOM4=8192, mulTOOM5=65535, mulTOOM6=524288 };
		enum { divBURNIKELZIEGLER=380, divNEWTONRAPHSON=1000 };
#endif
		enum { valDCP2=100, valDC=10, strDCP2=100, strDC=10 };

	private:
		struct {
			UINT_PTR*			data;
			size_t				limit;
			size_t				size;
			bool				constant;
			}						m_buf;
		int							m_sign;

	public:
									MPAInteger(void);
									MPAInteger(UINT_PTR val, bool sign=true);
									MPAInteger(LPCVOID pbuf, size_t nBytes, bool sign=true);
									MPAInteger(const MPAInteger& val);
		virtual						~MPAInteger(void);

	public:
		const UINT_PTR&				operator[](int index) const { return(m_buf.data[index]); }

	public:
		bool						IsEven(void) const { return(!(m_buf.data[0] & 0x01)); }
		virtual void				Empty(void) { m_buf.size=0; m_sign=1; }

	protected:
		virtual HRESULT				Reallocate(size_t nSize);
		HRESULT						BitSet(size_t nBits);
		static int					DigitToChar(UINT val);
		static void					Padding(LPTSTR str, TCHAR val, size_t length);
		size_t						BitScanReverse(void) const;
		size_t						BitScanForward(void) const;
		virtual void				Deallocate(void);

	public:
		HRESULT						Secure(size_t nSize, UINT_PTR val=0);
		size_t						Adjust(void);
		size_t						Length(void) const;
		HRESULT						Random(size_t nBytes, bool sign=true);
		HRESULT						Insert(size_t limb, UINT_PTR val=0);
		HRESULT						Higher(MPAInteger& high, size_t limb, bool allocation) const;	// abs(ans) -> high * 2^(limb*split)
		static void					Swap(MPAInteger& val1, MPAInteger& val2);
		HRESULT						SplitU(MPAInteger& high, MPAInteger& low, size_t limb, bool allocation) const;	// РтС╬ТlХкКД(abs(ans) -> high * 2^(limb*split) + low)
		HRESULT						Merge(size_t exp, const MPAInteger& val);

	public:
		virtual int					Cmp(const MPAInteger& val) const;
		int							CmpU(const MPAInteger& val) const;
		virtual int					Cmp(INT_PTR val) const;
		int							CmpU(UINT_PTR val) const;
	protected:
		int							CmpU(const MPAInteger& val, size_t shift) const;

	public:
		HRESULT						Value(UINT_PTR val, bool sign=true);
		HRESULT						Value(LPCVOID pbuf, size_t bytes, bool sign=true);
		HRESULT						Value(const MPAInteger& val);
		HRESULT						Value(LPCTSTR str, int base, size_t length=0);
	protected:
// Base Conversion
		HRESULT						ValueBCpow2(LPCTSTR str, int base, size_t length=0);
		HRESULT						ValueBC(LPCTSTR str, int base, size_t length=0);
// Divide and Conquer
		HRESULT						ValueDCpow2(LPCTSTR str, int base, size_t length=0);
		HRESULT						ValueDC(LPCTSTR str, int base, size_t length=0);

	public:
		size_t						GetStringLength(int base) const;
		HRESULT						GetString(LPTSTR str, size_t length, int base) const;
	protected:
// Base Conversion
		HRESULT						StringBCpow2(LPTSTR str, size_t length, int base) const;
		HRESULT						StringBC(LPTSTR str, size_t length, int base) const;
// Divide and Conquer
		HRESULT						StringDCpow2(LPTSTR str, size_t length, int base) const;
		HRESULT						StringDC(LPTSTR str, size_t length, int base) const;
	public:
		virtual void				NotValue(void);
		virtual void				NegValue(void);
		virtual void				NegSign(void);

	public:
		virtual HRESULT				Shift(INT_PTR nBits);
		HRESULT						Shl(UINT_PTR nBits);
		void						Shr(UINT_PTR nBits);

	public:
		HRESULT						Reciprocal(MPAInteger& val, size_t digits=0, bool denormalize=false);

	public:
		virtual HRESULT				Add(const MPAInteger& val);
		virtual HRESULT				Add(INT_PTR val);
		HRESULT						AddU(const MPAInteger& val);
		HRESULT						AddU(UINT_PTR nValue);
		HRESULT						Inc(void) { return(Add(1)); }

	public:
		virtual HRESULT				Sub(const MPAInteger& val);
		virtual HRESULT				Sub(INT_PTR nValue);
		HRESULT						SubU(const MPAInteger& val);
		HRESULT						SubU(UINT_PTR nValue);
		HRESULT						Dec(void) { return(Sub(1)); }

	public:
		virtual HRESULT				Mul(const MPAInteger& num, const MPAInteger& val);
		virtual HRESULT				Mul(INT_PTR val);
		virtual HRESULT				MulU(UINT_PTR val);
	protected:
// SchoolBook
		HRESULT						SingleMulU(UINT_PTR val, const UINT_PTR* pvsrc=NULL, size_t nsrcSize=0);
		HRESULT						SchoolBook(const MPAInteger& num, const MPAInteger& val);
// Divide and Conquer
		HRESULT						Karatsuba(const MPAInteger& num, const MPAInteger& val);
		HRESULT						ToomCook32(const MPAInteger& num, const MPAInteger& val);
		HRESULT						ToomCook33(const MPAInteger& num, const MPAInteger& val);
		HRESULT						ToomCook42(const MPAInteger& num, const MPAInteger& val);
		HRESULT						ToomCook43(const MPAInteger& num, const MPAInteger& val);
		HRESULT						ToomCook44(const MPAInteger& num, const MPAInteger& val);
		HRESULT						ToomCook52(const MPAInteger& num, const MPAInteger& val);
		HRESULT						ToomCook63(const MPAInteger& num, const MPAInteger& val);

	public:
		virtual HRESULT				Div(MPAInteger& num, INT_PTR den);
		virtual HRESULT				Div(MPAInteger& num, MPAInteger& den, bool denormalize);
		virtual HRESULT				Div(const MPAInteger& num, const MPAInteger& den, MPAInteger& rem);
		virtual HRESULT				DivU(MPAInteger& num, UINT_PTR den);
		virtual HRESULT				DivU(MPAInteger& num, MPAInteger& den, bool denormalize);
		virtual HRESULT				DivU(const MPAInteger& num, const MPAInteger& den, MPAInteger& rem);
	protected:
// Naive Division
		HRESULT						NaiveDivU(MPAInteger& num, UINT_PTR den);
// Knuth's Algorithm D
		HRESULT						KnuthBinary(MPAInteger& num, MPAInteger& den);
		HRESULT						KnuthLimb(MPAInteger& num, MPAInteger& den, bool denormalize);
// Divide and Conquer
		HRESULT						BurnikelZiegler(MPAInteger& num, MPAInteger& den, bool denormalize);
// Reciprocal Multiplication
		HRESULT						ReciprocalMultiplication(MPAInteger& num, MPAInteger& den);

	public:
		virtual HRESULT				pow(UINT_PTR val, UINT_PTR exp);
		virtual HRESULT				pow(MPAInteger& val, UINT_PTR exp);
		virtual HRESULT				pow(MPAInteger& val, MPAInteger& exp);
	protected:
// Binary Exponentiation
		HRESULT						powBinary(MPAInteger& num, UINT_PTR exp);
		HRESULT						powBinary(MPAInteger& num, MPAInteger& exp);
};

/*****************************************************************************/
/*                              ГCГУГЙГCГУТшЛ`                               */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/*                           ВlВoВ`ВhВОВФВЕВЗВЕВТ                            */
/*                                ВbВkВ`ВrВr                                 */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВP                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВqВЕВБВМВМВПВГВБВФВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Reallocate(size_t nSize)
{
	if (m_buf.constant) {
#if 0
		Deallocate();
#else
		::memset(&m_buf, 0 ,sizeof(m_buf));
		m_sign = 1;
		::DebugBreak();
#endif
		}

	if (m_buf.limit < nSize) {
		LPVOID	pbuf;

		if (!(pbuf=::realloc(m_buf.data, memOPTIMUM(nSize*sizeof(UINT_PTR))))) return(E_OUTOFMEMORY);
		m_buf.data = (UINT_PTR*)(pbuf);
		m_buf.limit = nSize;
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВaВЙВФВrВЕВФ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::BitSet(size_t nBits)
{
	MPAInteger&	ans=*this;
	size_t			nSize=(nBits - 1) / bitsLIMB + 1;
	HRESULT			hResult;

	if (nSize > ans.m_buf.size) {
		if (FAILED(hResult=ans.Secure(nSize))) return(hResult);
		}

	nSize = nBits / bitsLIMB;
	nBits = nBits % bitsLIMB;
	ans.m_buf.data[nSize] |= (UINT_PTR(1) << nBits);
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                          ВcВЙВЗВЙВФВsВПВbВИВБВТ                           */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline int MPAInteger::DigitToChar(UINT val)
{
static const BYTE	s_val[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; 

	return((val < maxBASE) ? s_val[val] : -1);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ВoВБВДВДВЙВОВЗ                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline void MPAInteger::Padding(LPTSTR str, TCHAR val, size_t length)
{
#ifdef UNICODE
	::wmemset(str, val, length);
#else
	::memset(str, val, length);
#endif
	str[length] = NULL;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                       ВaВЙВФВrВГВБВОВqВЕВЦВЕВТВУВЕ                        */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline size_t MPAInteger::BitScanReverse(void) const
{
	size_t		nIndex=Length();

	if (!nIndex) return(-1);

	nIndex -= 1;
	return((nIndex * bitsLIMB) + ::MPAbsr(m_buf.data[nIndex]));
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                       ВaВЙВФВrВГВБВОВeВПВТВЧВБВТВД                        */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline size_t MPAInteger::BitScanForward(void) const
{
	size_t		nLoop, nSize=Length();

	for(nLoop=0; nLoop<nSize; nLoop++) {
		if (m_buf.data[nLoop]) return((nLoop * bitsLIMB) + ::MPAbsf(m_buf.data[nLoop]));
		}

	return(-1);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВcВЕВБВМВМВПВГВБВФВЕ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline void MPAInteger::Deallocate(void)
{
	if ((!m_buf.constant) && (m_buf.data != NULL)) ::free(m_buf.data);
	::memset(&m_buf, 0 ,sizeof(m_buf));
	m_sign = 1;
}

/*---------------------------------------------------------------------------*/
/*                              ВbВkВ`ВrВr  ВO                               */
/*                           ВrВtВaВqВnВtВsВhВmВd                            */
/*---------------------------------------------------------------------------*/
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                              ГRГУГXГgГЙГNГ^                               */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline MPAInteger::MPAInteger(void)
{
	::memset(&m_buf, 0 ,sizeof(m_buf));
	m_sign = 1;
}
inline MPAInteger::MPAInteger(UINT_PTR val, bool sign)
{
	HRESULT		hResult;

	::memset(&m_buf, 0 ,sizeof(m_buf));
	m_sign = 1;

	if (FAILED(hResult=Value(val, sign))) {
		MPAHRESULT	error(hResult);
		throw(error);
		}
}
inline MPAInteger::MPAInteger(LPCVOID pbuf, size_t nBytes, bool sign)
{
	HRESULT		hResult;

	::memset(&m_buf, 0 ,sizeof(m_buf));
	m_sign = 1;

	if (FAILED(hResult=Value(pbuf, nBytes, sign))) {
		MPAHRESULT	error(hResult);
		throw(error);
		}
}
inline MPAInteger::MPAInteger(const MPAInteger& val)
{
	HRESULT		hResult;

	::memset(&m_buf, 0 ,sizeof(m_buf));
	m_sign = 1;

	if (FAILED(hResult=Value(val))) {
		MPAHRESULT	error(hResult);
		throw(error);
		}
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ГfГXГgГЙГNГ^                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline MPAInteger::~MPAInteger(void)
{
	Deallocate();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВrВЕВГВХВТВЕ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Secure(size_t nSize, UINT_PTR val)
{
	HRESULT		hResult;

	if (!nSize) m_sign = 1;
	if (FAILED(hResult=Reallocate(nSize))) return(hResult);

	if (m_buf.size < nSize) ::MPAset(&m_buf.data[m_buf.size], val, (nSize - m_buf.size));
	m_buf.size = nSize;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               В`ВДВКВХВУВФ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline size_t MPAInteger::Adjust(void)
{
	while((m_buf.size) && (!m_buf.data[m_buf.size-1])) m_buf.size--;
	if (!m_buf.size) m_sign = 1;

	return(m_buf.size);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВkВЕВОВЗВФВИ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline size_t MPAInteger::Length(void) const
{
	INT_PTR		nLoop;

	for(nLoop=(m_buf.size-1); nLoop>=0; nLoop--) {
		if (m_buf.data[nLoop]) return(nLoop+1);
		}

	return(0);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВqВБВОВДВПВН                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Random(size_t nBytes, bool sign)
{
	MPAInteger&	ans=*this;
	int				prand[8], nIndex;
	size_t			nLoop, nSize;
	LPBYTE			pbuf;
	HRESULT			hResult;

	nSize = ((nBytes - 1) / sizeof(UINT_PTR)) + 1;

	if (FAILED(hResult=ans.Reallocate(nSize))) return(hResult);
	ans.m_buf.size = nSize;
	ans.m_sign = (sign ? 1 : -1);
	ans.m_buf.data[nSize-1] = 0;

	for(nLoop=0; nLoop<_countof(prand); nLoop++) prand[nLoop] = ::rand();

	pbuf = LPBYTE(ans.m_buf.data);
	for(nLoop=0; nLoop<nBytes; nLoop++) {
		nIndex = (::rand() * 8) / (RAND_MAX + 1);
		*pbuf = BYTE(prand[nIndex] >> nIndex);
		prand[nIndex] = ::rand();
		pbuf++;
		}

	ans.Adjust();
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВhВОВУВЕВТВФ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Insert(size_t limb, UINT_PTR val)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	ans.Adjust();
	if (limb) {
		size_t		nSize=ans.m_buf.size + limb;

		if (FAILED(hResult=ans.Reallocate(nSize))) return(hResult);
		ans.m_buf.size = nSize;

		if (limb < nSize)
			::MPAins(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, limb, val);
		else
			::MPAset(ans.m_buf.data, val, ans.m_buf.size);
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                               ВgВЙВЗВИВЕВТ                                */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Higher(MPAInteger& high, size_t length, bool allocation) const
{
const MPAInteger&	ans=*this;
	size_t				split;
	HRESULT				hResult;

	if (ans.m_buf.size < length) length = ans.m_buf.size;

	split = ans.m_buf.size - length;
	if (allocation) {
		if (FAILED(hResult=high.Reallocate(length))) return(hResult);
		::MPAcpy(high.m_buf.data, &ans.m_buf.data[split], length);
		}
	else{
		high.Deallocate();
		high.m_buf.data = &ans.m_buf.data[split];
		high.m_buf.constant = true;
		}
	high.m_buf.size = length;
	high.m_sign = ans.m_sign;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                 ВrВЧВБВР                                  */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline void MPAInteger::Swap(MPAInteger& val1, MPAInteger& val2)
{
	UINT_PTR*	data=val1.m_buf.data;
	size_t		limit=val1.m_buf.limit;
	size_t		size=val1.m_buf.size;
	bool		constant=val1.m_buf.constant;
	int			sign=val1.m_sign;

	val1.m_buf = val2.m_buf;
	val1.m_sign = val2.m_sign;

	val2.m_buf.data = data;
	val2.m_buf.limit = limit;
	val2.m_buf.size = size;
	val2.m_buf.constant = constant;
	val2.m_sign = sign;
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВrВРВМВЙВФ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::SplitU(MPAInteger& high, MPAInteger& low, size_t split, bool allocation) const
{
const MPAInteger&	ans=*this;
	size_t				length=0;
	HRESULT				hResult;

	if (ans.m_buf.size < split) split = ans.m_buf.size;

	if (allocation) {
		if (FAILED(hResult=low.Reallocate(split))) return(hResult);
		if (split) {
			::MPAcpy(low.m_buf.data, ans.m_buf.data, split);
			}
		}
	else{
		low.Deallocate();
		low.m_buf.data = ans.m_buf.data;
		low.m_buf.constant = true;
		}
	low.m_buf.size = split;
	low.m_sign = 1;
	low.Adjust();

	if (split < ans.m_buf.size) {
		length = ans.m_buf.size - split;
		if (allocation) {
			if (FAILED(hResult=high.Reallocate(length))) return(hResult);
			::MPAcpy(high.m_buf.data, &ans.m_buf.data[split], length);
			}
		else{
			high.Deallocate();
			high.m_buf.data = &ans.m_buf.data[split];
			high.m_buf.constant = true;
			}
		}
	high.m_buf.size = length;
	high.m_sign = 1;
	high.Adjust();
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВlВЕВТВЗВЕ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Merge(size_t exp, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	size_t			len=val.Length();
	HRESULT			hResult;

	if (FAILED(hResult=ans.Insert(exp, 0))) return(hResult);

	if (len < exp) exp = len;
	if (exp) ::MPAcpy(ans.m_buf.data, val.m_buf.data, exp);

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВbВНВР                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline int MPAInteger::Cmp(const MPAInteger& val) const
{
const MPAInteger&	ans=*this;

	if (ans.m_sign > val.m_sign) return(1);
	if (ans.m_sign < val.m_sign) return(-1);

	return(ans.CmpU(val) * ans.m_sign);
}
inline int MPAInteger::CmpU(const MPAInteger& val) const
{
const MPAInteger&	ans=*this;
	const size_t		ansN=ans.Length();
	const size_t		valN=val.Length();
	size_t				nLoop;

	if (ansN > valN) return(1);
	if (ansN < valN) return(-1);

	for(nLoop=0; nLoop<ansN; nLoop++) {
		size_t	index=(ansN-1)-nLoop;

		if (ans.m_buf.data[index] > val.m_buf.data[index]) return(1);
		if (ans.m_buf.data[index] < val.m_buf.data[index]) return(-1);
		}
	return(0);
}
inline int MPAInteger::Cmp(INT_PTR val) const
{
const MPAInteger&	ans=*this;
	int					sign=((val < 0) ? -1 : 1);

	if (ans.m_sign > sign) return(1);
	if (ans.m_sign < sign) return(-1);

	return(ans.CmpU(::abs(val)) * ans.m_sign);
}
inline int MPAInteger::CmpU(UINT_PTR val) const
{
const MPAInteger&	ans=*this;
	const size_t		ansN=ans.Length();

	if (!ansN) return((val) ? -1 : 0);
	if (1 < ansN) return(1);

	if (ans.m_buf.data[0] > val) return(1);
	if (ans.m_buf.data[0] < val) return(-1);
	return(0);
}
inline int MPAInteger::CmpU(const MPAInteger& val, size_t shift) const
{
const MPAInteger&	ans=*this;
	const size_t		ansN=ans.Length();
	const size_t		valN=val.Length();
	size_t				nLoop;

	if (ansN > (valN+shift)) return(1);
	if (ansN < (valN+shift)) return(-1);

	for(nLoop=0; nLoop<valN; nLoop++) {
		size_t	index=(valN-1)-nLoop;

		if (ans.m_buf.data[index+shift] > val.m_buf.data[index]) return(1);
		if (ans.m_buf.data[index+shift] < val.m_buf.data[index]) return(-1);
		}
	for(nLoop=0; nLoop<shift; nLoop++) {
		if (ans.m_buf.data[nLoop] != 0) return(1);
		}

	return(0);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВuВБВМВХВЕ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Value(UINT_PTR val, bool sign)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (FAILED(hResult=ans.Reallocate(1))) return(hResult);
	ans.m_buf.data[0] = val;
	ans.m_buf.size = 1;
	ans.m_sign = ((sign) ? 1 : -1);

	return(NOERROR);
}
inline HRESULT MPAInteger::Value(LPCVOID pbuf, size_t bytes, bool sign)
{
	MPAInteger&	ans=*this;
	size_t			nSize=0;
	HRESULT			hResult;

	if (bytes) {
//		nSize = ((bytes - 1) / sizeof(UINT_PTR) + 1);
		nSize = (bytes + (sizeof(UINT_PTR) - 1)) / sizeof(UINT_PTR);
		if (FAILED(hResult=ans.Reallocate(nSize))) return(hResult);
		ans.m_buf.data[nSize-1] = 0;
		::memcpy(ans.m_buf.data, pbuf, bytes);
		}
	ans.m_buf.size = nSize;
	ans.m_sign = (sign ? 1 : -1);

	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::Value(const MPAInteger& val)
{
	MPAInteger&	ans=*this;

	if (val.m_buf.size) {
		HRESULT		hResult;

		if (FAILED(hResult=ans.Reallocate(val.m_buf.size))) return(hResult);
		::MPAcpy(ans.m_buf.data, val.m_buf.data, val.m_buf.size);
		}
	ans.m_buf.size = val.m_buf.size;
	ans.m_sign = val.m_sign;

	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::Value(LPCTSTR str, int base, size_t length)
{
	MPAInteger&	ans=*this;

	if ((base < 2) || (maxBASE < base)) base = 10;

	while((*str == 0x20) || (*str == TEXT('0'))) str++;
//	while((*str == 0x20) || (*str == TEXT('\t')) || (*str == TEXT('0'))) str++;

	ans.Empty();
	if (*str == TEXT('+')) str++;
	else if (*str == TEXT('-')) {
		ans.m_sign = -1;
		str++;
		}

	if ((base & (base-1)) == 0) return(ValueDCpow2(str, base, length)); // (Powers of 2)

	return(ValueDC(str, base, length));
}
inline HRESULT MPAInteger::ValueBCpow2(LPCTSTR str, int base, size_t length)
{
	MPAInteger&	ans=*this;
	const INT_PTR*	pdigit=((base <= 36) ? ::_mpa_valueA : ::_mpa_valueB);
	UINT			shift, bits=::MPAbsr(base);
	UINT_PTR*		pval;
	LPCTSTR			self;
	MPAUDINTBUFF	buf;
	size_t			block;
	HRESULT			hResult;

	ans.Empty();
//	if ((base < 2) || (maxBASE < base)) return(E_INVALIDARG);
	if ((base & (base-1)) != 0) return(E_INVALIDARG);					// (Other than powers of 2)

	if (!length) length = ::_tcslen(str);
	block = (((length * bits) - 1) / bitsLIMB) + 1;						// ceil(length(bits) / bitsLIMB)
	if (FAILED(hResult=ans.Reallocate(block))) return(hResult);
	ans.m_buf.size = block;
	pval = ans.m_buf.data;
	pval[block-1] = 0;

	buf.lo = buf.hi = 0;
	shift = 0;
	for(self=&str[length-1]; self>=str; self--) {
#ifndef _WIN64
		buf.val |= ::MPAshlR(pdigit[BYTE(*self)], shift);
#else	//_WIN64
		MPAUDINTBUFF	tmp={ UINT_PTR(pdigit[BYTE(*self)]), 0 };
		tmp.val = ::MPAshlR(tmp.val, shift);
		buf.lo |= tmp.lo;
		buf.hi |= tmp.hi;
#endif	//_WIN64
		shift += bits;
		if (bitsLIMB <= shift) {
			*pval = buf.lo;
			pval++;
			shift -= bitsLIMB;
			if (shift)
				buf.val = ::MPAshrR(buf.val, (bitsLIMB - shift));
			else{
				buf.lo = buf.hi;
				buf.hi = 0;
				}
			}
		}
	if (buf.lo != 0) *pval = buf.lo;

	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::ValueBC(LPCTSTR str, int base, size_t length)
{
	MPAInteger&		ans=*this;
	const INT_PTR*		pdigit=((base <= 36) ? ::_mpa_valueA : ::_mpa_valueB);
	const UINT_PTR*		pgirder;
	size_t				girder, nLoop;
#ifndef _WIN64
	TCHAR				self[32+4];										// (Maximum of 32 binary digitsand dummy)
#else	//_WIN64
	TCHAR				self[64+4];										// (Maximum of 64 binary digitsand dummy)
#endif	//_WIN64
	HRESULT				hResult;

	ans.Empty();
//	if ((base < 2) || (maxBASE < base)) return(E_INVALIDARG);
//	if ((base & (base-1)) == 0) return(ValueBCpow2(str, base, length)); // (Powers of 2)
	if (!length) length = ::_tcslen(str);

	pgirder = ::_mpa_girder[base];
	while(length) {
		UINT_PTR		val=0;

		girder = length;
		if ((pgirder[-1]-1) < girder) girder = pgirder[-1] - 1;
		::_tcsncpy(self, str, girder); self[girder] = NULL;

		if (FAILED(hResult=ans.SingleMulU(pgirder[girder]))) return(hResult);
		for(nLoop=0; nLoop<girder; nLoop++) {
			val *= base;
			val += pdigit[BYTE(self[nLoop])];
			}
		if (FAILED(hResult=ans.AddU(val))) return(hResult);
		str += girder;
		length -= girder;
		}

	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::ValueDCpow2(LPCTSTR str, int base, size_t length)
{
	MPAInteger&	ans=*this;
	MPAInteger	low;
	size_t			higher, lower;
	MPAUDINTBUFF	shift;
	HRESULT			hResult;

	ans.Empty();
//	if ((base < 2) || (maxBASE < base)) return(E_INVALIDARG);
	if ((base & (base-1)) != 0) return(E_INVALIDARG);
	if (!length) length = ::_tcslen(str);
	if (length <= valDCP2) return(ans.ValueBCpow2(str, base, length));

	shift.lo = ::MPAbsr(base);
	higher = (length + 1) / 2;								// higher = ceil(length/2)
	lower = length - higher;
	if (FAILED(hResult=low.ValueDCpow2(&str[higher], base, lower))) return(hResult);

	if (FAILED(hResult=ans.ValueDCpow2(str, base, higher))) return(hResult);
	shift.val = ::MPAmulT(lower, shift.lo);
	if (shift.hi) {
		if (FAILED(hResult=ans.Shl(shift.hi))) return(hResult);
		}
	if (FAILED(hResult=ans.Shl(shift.lo))) return(hResult);
	if (FAILED(hResult=ans.AddU(low))) return(hResult);

	return(NOERROR);
}
inline HRESULT MPAInteger::ValueDC(LPCTSTR str, int base, size_t length)
{
	MPAInteger&		ans=*this;
	MPAInteger		low, tmp, shift;
	size_t				threshold, higher, lower;
	const UINT_PTR*		pgirder;
	HRESULT				hResult;

	ans.Empty();
//	if ((base < 2) || (maxBASE < base)) return(E_INVALIDARG);
//	if ((base & (base-1)) == 0) return(ValueDCpow2(str, base, length));	// (Powers of 2)
	if (!length) length = ::_tcslen(str);

	pgirder = ::_mpa_girder[base];
	threshold = (pgirder[-1] * valDC) - 1;
	if (length <= threshold) return(ans.ValueBC(str, base, length));

	higher = (length + 1) / 2;								// higher = ceil(length/2)
	lower = length - higher;
	if (FAILED(hResult=low.ValueDC(&str[higher], base, lower))) return(hResult);

	if (FAILED(hResult=ans.ValueDC(str, base, higher))) return(hResult);
	if (lower < pgirder[-1]) {
		if (FAILED(hResult=ans.SingleMulU(pgirder[lower]))) return(hResult);
		}
	else{
		threshold = pgirder[-1] - 1;
		if (lower <= threshold) {
			if (FAILED(hResult=ans.SingleMulU(pgirder[threshold]))) return(hResult);
			}
		else{
			size_t			exp=lower/threshold;

#if 0
			if (FAILED(hResult=tmp.Value(ans))) return(hResult);
#else
			Swap(ans, tmp);											// ans <-> tmp
#endif
			if (1 < exp) {
				if (FAILED(hResult=shift.pow(pgirder[threshold], exp))) return(hResult);
				}
			else{
				if (FAILED(hResult=shift.Value(pgirder[threshold]))) return(hResult);
				}
			exp = lower % threshold;
			if (0 < exp) {
				if (FAILED(hResult=shift.SingleMulU(pgirder[exp]))) return(hResult);
				}
			if (FAILED(hResult=ans.SchoolBook(tmp, shift))) return(hResult);
			}
		}
	if (FAILED(hResult=ans.AddU(low))) return(hResult);

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                      ВfВЕВФВrВФВТВЙВОВЗВkВЕВОВЗВФВИ                       */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline size_t MPAInteger::GetStringLength(int base) const
{
const MPAInteger&	ans=*this;
	size_t				letter;
	const UINT_PTR*		pgirder;
	HRESULT				hResult;

	if ((base < 2) || (maxBASE < base)) return(0);

	if ((base & (base-1)) == 0) {
		size_t	rem;

		letter = ans.BitScanReverse()+1;
		if (letter == 1) return(0);

		base = ::MPAbsr(UINT_PTR(base));
		rem = letter % base;
		letter /= base;
		if (rem) letter += 1;
		}
	else{
		MPAInteger	num, exp, rem;
		size_t			girder;

		if (!ans.Length()) return(0);
		if (FAILED(hResult=rem.Value(ans))) return(0);

		letter = 0;
		pgirder = ::_mpa_girder[base];
		while(1 < rem.Length()) {
			girder = pgirder[-1] - 1;
			letter += girder;

			if (FAILED(hResult=exp.Value(pgirder[girder]))) return(hResult);
			if (FAILED(hResult=num.DivU(rem, exp, false))) return(hResult);
			if (FAILED(hResult=rem.Value(num))) return(hResult);
			}
		if (rem.Length() == 1) {
			UINT_PTR	val=rem.m_buf.data[0];

			girder = pgirder[1];
			while(val != 0) {
				val /= girder;
				letter++;
				}
			}
		}
	if (ans.m_sign < 0) letter += 1;

	return(letter);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                            ВfВЕВФВrВФВТВЙВОВЗ                             */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::GetString(LPTSTR str, size_t length, int base) const
{
const MPAInteger&	ans=*this;
	size_t				len;
	LPTSTR				tail;
	HRESULT				hResult;

	if ((base < 2) || (maxBASE < base)) return(E_INVALIDARG);
	if (!ans.Length()) {
		::_tcscpy(str, TEXT("0"));
		return(NOERROR);
		}
	if ((base & (base-1)) == 0) {									// (Powers of 2)
		if (FAILED(hResult=ans.StringDCpow2(str, length, base))) return(hResult);
		}
	else{
		if (FAILED(hResult=ans.StringDC(str, length, base))) return(hResult);
		}
	len = ::_tcslen(str);
	if ((ans.m_sign < 0) && ((len+1) < length)) {
		str[len++] = TEXT('-');
		str[len] = NULL;
		}
	for(tail=&str[len-1]; str<tail; str++, tail--) {
		TCHAR		tmp=*tail;
		*tail = *str;
		*str = tmp;
		}

	return(NOERROR);
}
inline HRESULT MPAInteger::StringBCpow2(LPTSTR str, size_t length, int base) const
{
const MPAInteger&	ans=*this;
	LPTSTR				self=str;
	MPAInteger		num;
	const UINT_PTR*		pgirder;
	UINT_PTR			val, mask, shift, move;
	HRESULT				hResult;

//	if ((base < 2) || (maxBASE < base)) return(E_INVALIDARG);
	if (!ans.Length()) return(NOERROR);
	if ((base & (base-1)) != 0) return(E_INVALIDARG);				// (Other than powers of 2)

	pgirder = ::_mpa_girder[base];
	mask = base - 1;
	shift = ::MPAbsr(base);
	move = shift * pgirder[-1];

	if (FAILED(hResult=num.Value(ans))) return(hResult);
	while(1 < length) {
		size_t		nLoop;

		val = num.m_buf.data[0];
		num.Shr(move);
		for(nLoop=0; nLoop<pgirder[-1]; nLoop++) {
			if ((!val) && (!num.m_buf.size)) break;
			*self = DigitToChar(UINT(val&mask));
			self++;
			if (--length <= 1) break;
			val >>= shift;
			}
		if (!num.m_buf.size) break;
		}

	*self = NULL;
	return(NOERROR);
}
inline HRESULT MPAInteger::StringBC(LPTSTR str, size_t length, int base) const
{
const MPAInteger&	ans=*this;
	LPTSTR				self=str;
	MPAInteger		num, exp, rem;
	UINT_PTR			val;
	const UINT_PTR*		pgirder;
	size_t				girder, nLoop;
	HRESULT				hResult;

//	if ((base < 2) || (maxBASE < base)) return(E_INVALIDARG);
	if (!ans.Length()) return(NOERROR);
//	if ((base & (base-1)) == 0) return(StringBCpow2(str, length, base)); // (Powers of 2)
	if (FAILED(hResult=rem.Value(ans))) return(hResult);
	pgirder = ::_mpa_girder[base];
	while(1 < length) {
		girder = pgirder[-1] - 1;
		if (FAILED(hResult=exp.Value(pgirder[girder]))) return(hResult);
		if (FAILED(hResult=num.DivU(rem, exp, false))) return(hResult);
		val = ((0 < rem.m_buf.size) ? rem.m_buf.data[0] : 0);
		for(nLoop=0; nLoop<girder; nLoop++) {
			if ((!val) && (!num.m_buf.size)) break;
			*self = DigitToChar(val%base);
			self++;
			if (--length <= 1) break;
			val /= base;
			}
		if ((length <= 1) || (!num.m_buf.size)) break;
		if (FAILED(hResult=rem.Value(num))) return(hResult);
		}

	*self = NULL;
	return(NOERROR);
}
inline HRESULT MPAInteger::StringDCpow2(LPTSTR str, size_t length, int base) const
{
const MPAInteger&	ans=*this;
	MPAInteger		ansH, ansL, exp;
	size_t				size, split, temp;
	const UINT_PTR*		pgirder;
	HRESULT				hResult;

//	if ((base < 2) || (maxBASE < base)) return(E_INVALIDARG);
	if (!(size=ans.Length())) return(NOERROR);
	if ((base & (base-1)) != 0) return(E_INVALIDARG);						// (Other than powers of 2)
	pgirder = ::_mpa_girder[base];

	if (size <= strDCP2) return(ans.StringBCpow2(str, length, base));

	split = size - ((size + 1) / 2);										// split = size - ceil(size/2)
	temp = ::MPAbsr(base);
	if (bitsLIMB%temp) split = (((split - 1) / temp) + 1) * temp;
	if (size <= split) return(ans.StringBCpow2(str, length, base));

	// ans = (ansH << split) + ansL
	if (FAILED(hResult=ans.SplitU(ansH, ansL, split, false))) return(hResult);		// (Since the base is a power of 2, using `Split` is fine)

	if (ansL.m_buf.size) {
		if (FAILED(hResult=ansL.StringDCpow2(str, length, base))) return(hResult);
		split = (split * pgirder[-1])- 1;
		if ((length-1) < split) split = length - 1;

		temp = ::_tcslen(str);
		if (temp < split) Padding(&str[temp], TEXT('0'), (split-temp));
		}
	else{
		split = (split * pgirder[-1])- 1;
		if ((length-1) < split) split = length - 1;

		Padding(str, TEXT('0'), split);
		}
	if ((temp=::_tcslen(str)) < (length-1)) {
		if (FAILED(hResult=ansH.StringDCpow2(&str[temp], (length-temp), base))) return(hResult);
		}

	return(NOERROR);
}
inline HRESULT MPAInteger::StringDC(LPTSTR str, size_t length, int base) const
{
const MPAInteger&	ans=*this;
	MPAInteger		ansH, ansL, exp;
	size_t				size, split, temp;
	const UINT_PTR*		pgirder;
	HRESULT				hResult;

//	if ((base < 2) || (maxBASE < base)) return(E_INVALIDARG);
	if (!(size=ans.Length())) return(NOERROR);
//	if ((base & (base-1)) == 0) return(StringDCpow2(str, length, base, false));	// (Powers of 2)
	if (size <= strDC) return(ans.StringBC(str, length, base));

	pgirder = ::_mpa_girder[base];
	size = (pgirder[-1] * size) - 1;										// (Rough estimate of the number of digits)
	split = size - ((size + 1) / 2);										// split = size - ceil(size/2)
	if (FAILED(hResult=exp.pow(base, split))) return(hResult);				// exp = base^split

	if (FAILED(hResult=ansL.Value(ans))) return(hResult);
	if (FAILED(hResult=ansH.DivU(ansL, exp, false))) return(hResult);		// ansH = floor(sna/exp), ansL = ans % exp
	if (ansL.m_buf.size) {
		if (FAILED(hResult=ansL.StringDC(str, length, base))) return(hResult);
		if ((length-1) < split) split = length - 1;

		temp = ::_tcslen(str);
		if (temp < split) Padding(&str[temp], TEXT('0'), (split-temp));
		}
	else{
		if ((length-1) < split) split = length - 1;

		Padding(str, TEXT('0'), split);
		}
	if ((temp=::_tcslen(str)) < (length-1)) {
		if (FAILED(hResult=ansH.StringDC(&str[temp], (length-temp), base))) return(hResult);
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВmВПВФ                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline void MPAInteger::NotValue(void)
{
	if (m_buf.size) ::MPAnot(m_buf.data, m_buf.size);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВmВЕВЗ                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline void MPAInteger::NegValue(void)
{
	if (m_buf.size) ::MPAneg(m_buf.data, m_buf.size);
}
inline void MPAInteger::NegSign(void)
{
	m_sign = ((m_buf.size) ? -m_sign : 1);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                ВrВИВЙВЖВФ                                 */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Shift(INT_PTR nBits)
{
	if (nBits < 0) {
		Shr(-nBits);
		return(NOERROR);
		}

	return(Shl(nBits));
}
inline HRESULT MPAInteger::Shl(UINT_PTR nBits)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if ((nBits != 0) && (ans.m_buf.size)) {
		size_t		nSize=(nBits - 1) / bitsLIMB + 1;

		if (FAILED(hResult=ans.Secure(ans.m_buf.size+nSize))) return(hResult);
#if 0
		::MPAshl(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, nBits);
#else
		size_t		nlimbShift=nBits / bitsLIMB;
		size_t		nbitsShift=nBits % bitsLIMB;

		if (!nlimbShift) {
			if (nbitsShift == 1)
				::MPAshl1(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size);
			else
				::MPAshlS(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, nbitsShift);
			}
		else{
			if (!nbitsShift)
				::MPAshlM(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, nlimbShift, 0);
			else
				::MPAshlL(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, nlimbShift, nbitsShift);
			}
#endif
		}

	ans.Adjust();
	return(NOERROR);
}
inline void MPAInteger::Shr(UINT_PTR nBits)
{
	MPAInteger&	ans=*this;

	if (nBits != 0) {
		size_t		nSize=(nBits + 1) / bitsLIMB;

		if (ans.m_buf.size <= nSize)
			ans.Empty();
		else{
#if 0
			::MPAshr(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, nBits);
#else
			size_t		nlimbShift=nBits / bitsLIMB;
			size_t		nbitsShift=nBits % bitsLIMB;

			if (!nlimbShift) {
				if (nbitsShift == 1)
					::MPAshr1(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size);
				else
					::MPAshrS(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, nbitsShift);
				}
			else{
				if (!nbitsShift)
					::MPAshrM(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, nlimbShift, 0);
				else
					::MPAshrL(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, nlimbShift, nbitsShift);
				ans.m_buf.size -= nlimbShift;
				}
			}
#endif
		}

	ans.Adjust();
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                           ВqВЕВГВЙВРВТВПВГВБВМ                            */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Reciprocal(MPAInteger& val, size_t digits, bool denormalize)
{
	MPAInteger&		ans=*this;
	MPAInteger		cal, cmp, tmp;
	MPAUDINTBUFF		numT={ 0, (UINT_PTR(1) << (bitsLIMB - 1)) };
	const size_t		valN=val.Length();
	UINT_PTR			valT;
	size_t				valid;
	UINT				shift, fixed;
	HRESULT				hResult;

	ans.Empty();
	if (!valN) return(E_INVALIDARG);
	if (!val.CmpU(1)) return(ans.Value(1));

	if (!digits) digits = valN;
	valid = digits + 2;

	if (FAILED(hResult=ans.Reallocate(valid+1))) return(hResult);
	if (FAILED(hResult=tmp.Reallocate(valid*2+1))) return(hResult);
	if (FAILED(hResult=cal.Reallocate(valid*2+3))) return(hResult);

	valT = val.m_buf.data[valN-1];
	fixed = ::MPAbsr(valT);
// (Normalization)
	shift = UINT(bitsLIMB - 1) - fixed;
	if ((bitsLIMB/2) < fixed) fixed -= bitsLIMB/2;
	if (shift) {
		if (FAILED(hResult=val.Shl(shift))) return(hResult);					// 0.5 БЕ val БГ 1
		}
	valT = val.m_buf.data[valN-1];
	if (FAILED(hResult=ans.Secure(2))) return(hResult);
	ans.m_sign = val.m_sign;													// (sign preservation)
	MPAUDINTBUFF&	qhat=*LPMPAUDINTBUFF(ans.m_buf.data);
// (Estimation of the quotient (q-hat) and correction)
	qhat.val = ::MPAdivR(numT.val, valT);										// qhat(ans) = (1 << ((limb * 2) - 1)) / (valT1 << shift)
	if (qhat.hi != 0) qhat.val = ::MPAsubR(qhat.val, 1);
	ans.Adjust();
// (Newton-Raphson method)
	for(;;) {
// cal = ans * (2 - (val * ans))
		if (FAILED(hResult=tmp.Mul(val, ans))) return(hResult);					// abs(tmp) = val * ans
		if (FAILED(hResult=tmp.Secure(tmp.m_buf.size+1))) return(hResult);

		if (FAILED(hResult=tmp.Higher(cmp, (valid+2), false))) return(hResult);
		::MPAneg(cmp.m_buf.data, cmp.m_buf.size);								// abs(tmp) *= -1
		cmp.m_buf.data[cmp.m_buf.size-1] += 2;									// abs(tmp) += 2 << (limb * (tmp.m_buf.size-1))
		if (FAILED(hResult=cal.Mul(ans, cmp))) return(hResult);					// cal = ans * abs(tmp) БF 1 БЕ cal БГ 2

		if (FAILED(hResult=cal.Higher(cmp, valid, false))) return(hResult);
		if (valid <= ans.m_buf.size) {
			if (valid < ans.m_buf.size) {
				::MPAshrM(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, (ans.m_buf.size-valid), 0);
				ans.m_buf.size = valid;
				}
// (Convergence criterionI
			if (FAILED(hResult=ans.SubU(cmp))) return(hResult);
			if ((ans.m_buf.size == 0)											// ans == cmp
			|| ((ans.m_buf.size == 1) && (*ans.m_buf.data == 1))) {				// ans == (cmp Б} 1)
				if (shift) {
					cal.Shr(shift+2+(fixed*2));									// (Fixed decimalization)
					if (denormalize) val.Shr(shift);
					}
				if (FAILED(hResult=cal.Higher(ans, digits, true))) return(hResult);
				break;
				}
			}
		if (FAILED(hResult=cal.Higher(ans, (valid+1), true))) return(hResult);
		}
// (Deallocate memory)
	cal.Deallocate();
// (Final adjustment)
	if (FAILED(hResult=tmp.Mul(val, ans))) return(hResult);						// abs(tmp) = val * ans
	if (FAILED(hResult=tmp.AddU(val))) return(hResult);							// abs(tmp) += abs(val)
	if ((tmp.m_buf.data[tmp.m_buf.size-1] == 1)
	&& (::MPAisZero(tmp.m_buf.data, (tmp.m_buf.size-1)))) {
		if (FAILED(hResult=ans.AddU(1))) return(hResult);
		}

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  В`ВДВД                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Add(const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (ans.m_sign != val.m_sign) {
		int		sign=((0 <= ans.CmpU(val)) ? ans.m_sign : val.m_sign);

		if (FAILED(hResult=ans.SubU(val))) return(hResult);
		ans.m_sign = (ans.m_buf.size ? sign : 1);
		return(NOERROR);
		}

	return(AddU(val));
}
inline HRESULT MPAInteger::Add(INT_PTR val)
{
	MPAInteger&	ans=*this;
	int				sign=((0 <= val) ? 1 : -1);
	UINT_PTR		absV=::abs(val);
	HRESULT			hResult;

	if (ans.m_sign != sign) {
		if (0 <= ans.CmpU(absV)) sign = ans.m_sign;

		if (FAILED(hResult=ans.SubU(absV))) return(hResult);
		ans.m_sign = (ans.m_buf.size ? sign : 1);
		return(NOERROR);
		}

	return(AddU(val));
}
inline HRESULT MPAInteger::AddU(const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (val.m_buf.size) {
		size_t		nSize=((ans.m_buf.size >= val.m_buf.size) ? ans.m_buf.size : val.m_buf.size);

		if (FAILED(hResult=ans.Secure(nSize+1))) return(hResult);
		::MPAadd(ans.m_buf.data, ans.m_buf.size, val.m_buf.data, val.m_buf.size);
		}

	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::AddU(UINT_PTR val)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (FAILED(hResult=ans.Secure(ans.m_buf.size+1))) return(hResult);
	::MPAaddV(ans.m_buf.data, ans.m_buf.size, val);

	ans.Adjust();
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВrВХВВ                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Sub(const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (ans.m_sign == val.m_sign) {
		int		sign=ans.m_sign;

		if (ans.CmpU(val) < 0) sign *= -1;

		if (FAILED(hResult=ans.SubU(val))) return(hResult);
		ans.m_sign = (ans.m_buf.size ? sign : 1);
		return(NOERROR);
		}

	return(ans.AddU(val));
}
inline HRESULT MPAInteger::Sub(INT_PTR val)
{
	MPAInteger&	ans=*this;
	int				sign=((0 <= val) ? 1 : -1);
	UINT_PTR		absV=::abs(val);
	HRESULT			hResult;

	if (ans.m_sign == sign) {
		if (ans.CmpU(absV) < 0) sign *= -1;

		if (FAILED(hResult=ans.SubU(absV))) return(hResult);
		ans.m_sign = (ans.m_buf.size ? sign : 1);
		return(NOERROR);
		}

	return(ans.AddU(val));
}
inline HRESULT MPAInteger::SubU(const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	size_t			valN=val.Length();
	HRESULT			hResult;

	if (valN) {
		int		cmp=ans.CmpU(val);

		if (cmp < 0) {											// ans < val
			if (FAILED(hResult=ans.Secure(valN+1))) return(hResult);
// (Two's complement addition)
			::MPAneg(ans.m_buf.data, valN);
			::MPAadd(ans.m_buf.data, ans.m_buf.size, val.m_buf.data, valN);
			ans.m_buf.size = valN;
			}													// ans > val
		else if (cmp > 0) {
			::MPAsub(ans.m_buf.data, ans.m_buf.size, val.m_buf.data, valN);
			}
		else{													// ans == val
			ans.m_buf.size = 0;
			}
		}

	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::SubU(UINT_PTR val)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (val) {
		int		cmp=ans.CmpU(val);

		if (cmp < 0) {
			if (FAILED(hResult=ans.Secure(1))) return(hResult);
			ans.m_buf.data[0] = val - ans.m_buf.data[0];
			ans.m_buf.size = 1;
			}
		else if (cmp > 0) {
			::MPAsubV(ans.m_buf.data, ans.m_buf.size, val);
			}
		else{
			ans.m_buf.size = 0;
			}
		}

	ans.Adjust();
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВlВХВМ                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Mul(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&		ans=*this;
	const MPAInteger	*pnum, *pval;
	const size_t		numN=num.Length();
	size_t				valN=val.Length();
	double				rate;
	HRESULT				hResult;

	ans.Empty();
	if ((!numN) || (!valN)) return(NOERROR);
	if (valN <= numN) {
		pnum = &num;
		pval = &val;
		rate = double(numN) / double(valN);
		}
	else{
		pnum = &val;
		pval = &num;
		rate = double(valN) / double(numN);
		valN = numN;
		}
	if (FAILED(hResult=ans.Reallocate(numN+valN))) return(hResult);

	if (valN < mulKARATSUBA) return(ans.SchoolBook(*pnum, *pval));
	if (valN < mulTOOM3) return(ans.Karatsuba(*pnum, *pval));
	if (valN < mulTOOM4) {
		if (1.4 <= rate) return(ans.ToomCook32(*pnum, *pval));
		return(ans.ToomCook33(*pnum, *pval));
		}
	if (valN < mulTOOM5) {
		if (2. <= rate) return(ans.ToomCook42(*pnum, *pval));
		if (1.3 <= rate) return(ans.ToomCook43(*pnum, *pval));
		return(ans.ToomCook44(*pnum, *pval));
		}
	if (valN < mulTOOM6) {
		return(ans.ToomCook52(*pnum, *pval));
		}

	return(ans.ToomCook63(*pnum, *pval));
}
inline HRESULT MPAInteger::Mul(INT_PTR val)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (FAILED(hResult=ans.SingleMulU(::abs(val)))) return(hResult);
	if ((val < 0) && (ans.Length())) ans.m_sign *= -1;

	return(NOERROR);
}
inline HRESULT MPAInteger::MulU(UINT_PTR val)
{
	return(SingleMulU(val));
}
inline HRESULT MPAInteger::SingleMulU(UINT_PTR val, const UINT_PTR* pvsrc, size_t nsrcSize)
{
	MPAInteger&	ans=*this;
	const size_t	ansN=ans.Length();
	HRESULT			hResult;

	if (!nsrcSize)
		nsrcSize = ansN;
	else
		ans.Empty();
	if ((!val) || (!nsrcSize)) {
		ans.Empty();
		return(NOERROR);
		}

	if (FAILED(hResult=ans.Secure(nsrcSize+1))) return(hResult);
	if (!pvsrc) pvsrc = ans.m_buf.data;
	::MPAmulV(ans.m_buf.data, pvsrc, nsrcSize, val);

	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::SchoolBook(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	const size_t	numN=num.Length();
	const size_t	valN=val.Length();
	HRESULT			hResult;

	ans.Empty();
	if ((!numN) || (!valN)) return(NOERROR);

	if (FAILED(hResult=ans.Secure(numN+valN+1))) return(hResult);
	::MPAmul(ans.m_buf.data, num.m_buf.data, numN, val.m_buf.data, valN);

	ans.m_sign = num.m_sign * val.m_sign;
	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::Karatsuba(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	MPAInteger	ansT[2];
	MPAInteger	numS[2], valS[2];
	const size_t	valN=num.Length();
	const size_t	split=(valN + 1) / 2;								// split = ceil(valN / 2)
	HRESULT			hResult;

	if (FAILED(hResult=num.SplitU(numS[1], numS[0], split, false))) return(hResult);
	if (FAILED(hResult=val.SplitU(valS[1], valS[0], split, false))) return(hResult);

// (Evaluation)&(Pointwise Multiplication)
// (Evaluation points)(x = 0,  1,  БЗ)
// P1(x=1)
	if (FAILED(hResult=ans.Value(numS[0]))) return(hResult);
	if (FAILED(hResult=ans.Add(numS[1]))) return(hResult);
	if (FAILED(hResult=ansT[0].Value(valS[0]))) return(hResult);
	if (FAILED(hResult=ansT[0].Add(valS[1]))) return(hResult);
	if (FAILED(hResult=ansT[1].Mul(ans, ansT[0]))) return(hResult);
// C0(x=0)
	if (FAILED(hResult=ansT[0].Mul(numS[0], valS[0]))) return(hResult);
// (C2)(x=БЗ)
	if (FAILED(hResult=ans.Mul(numS[1], valS[1]))) return(hResult);

// (Interpolation)
	if (FAILED(hResult=ansT[1].Sub(ansT[0]))) return(hResult);				// ansT[1] -= ansT[0]
	if (FAILED(hResult=ansT[1].Sub(ans))) return(hResult);					// ansT[1] -= ans

// (Recomposition)
	if (FAILED(hResult=ansT[1].Insert(split))) return(hResult);				// ansT[1](C1) <<= split
	if (FAILED(hResult=ansT[1].Add(ansT[0]))) return(hResult);				// ansT[1] += ansT[0](C0)
	if (FAILED(hResult=ans.Insert(split*2))) return(hResult);				// ans(C2) <<= (split * 2)
	if (FAILED(hResult=ans.Add(ansT[1]))) return(hResult);					// ans += ansT[1]

	ans.m_sign = num.m_sign * val.m_sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::ToomCook32(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	MPAInteger	ansT[3], aux[2];
	MPAInteger	numS[3], valS[2];
	MPAInteger&	fix=valS[0];
	const size_t	valN=val.Length();
	const size_t	split=(valN + 1) / 2;									// split = ceil(valN / 2)
	HRESULT			hResult;

	if (FAILED(hResult=num.SplitU(fix, numS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix.SplitU(numS[2], numS[1], split, false))) return(hResult);
	if (FAILED(hResult=val.SplitU(valS[1], valS[0], split, false))) return(hResult);

// (Evaluation) & (Pointwise Multiplication)
// (Evaluation points)(x = 0,  1,  -1,  БЗ)
// C0(x=0)
	if (FAILED(hResult=ansT[0].Mul(numS[0], valS[0]))) return(hResult);
// P1(x=1)
	if (FAILED(hResult=aux[0].Value(numS[0]))) return(hResult);
	if (FAILED(hResult=aux[0].Add(numS[1]))) return(hResult);
	if (FAILED(hResult=aux[0].Add(numS[2]))) return(hResult);
	if (FAILED(hResult=aux[1].Value(valS[0]))) return(hResult);
	if (FAILED(hResult=aux[1].Add(valS[1]))) return(hResult);
	if (FAILED(hResult=ansT[1].Mul(aux[0], aux[1]))) return(hResult);
// M1(x=-1)
	if (FAILED(hResult=aux[0].Value(numS[0]))) return(hResult);
	if (FAILED(hResult=aux[0].Sub(numS[1]))) return(hResult);
	if (FAILED(hResult=aux[0].Add(numS[2]))) return(hResult);
	if (FAILED(hResult=aux[1].Value(valS[0]))) return(hResult);
	if (FAILED(hResult=aux[1].Sub(valS[1]))) return(hResult);
	if (FAILED(hResult=ansT[2].Mul(aux[0], aux[1]))) return(hResult);
// C3(x=БЗ)
	if (FAILED(hResult=ans.Mul(numS[2], valS[1]))) return(hResult);

// (Interpolation/Matrix Inversion)
// Even coefficient))
// (C2)
	if (FAILED(hResult=aux[1].Value(ansT[1]))) return(hResult);				// aux[1] = ansT[1]
	if (FAILED(hResult=aux[1].Add(ansT[2]))) return(hResult);				// aux[1] += ansT[2]
	aux[1].Shr(1);															// aux[1] /= 2
	if (FAILED(hResult=aux[1].Sub(ansT[0]))) return(hResult);				// aux[1] -= ansT[0](C0)

// (Odd coefficient))
// (C1)
	if (FAILED(hResult=aux[0].Value(ansT[1]))) return(hResult);				// aux[0] = ansT[1]
	if (FAILED(hResult=aux[0].Sub(ansT[2]))) return(hResult);				// aux[0] -= ansT[2]
	aux[0].Shr(1);															// aux[0] /= 2
	if (FAILED(hResult=aux[0].Sub(ans))) return(hResult);					// aux[0] -= ans(C3)

// (Recomposition)
	if (FAILED(hResult=aux[0].Insert(split))) return(hResult);
	if (FAILED(hResult=aux[0].Add(ansT[0]))) return(hResult);
	if (FAILED(hResult=aux[1].Insert(split*2))) return(hResult);
	if (FAILED(hResult=aux[1].Add(aux[0]))) return(hResult);
	if (FAILED(hResult=ans.Insert(split*3))) return(hResult);
	if (FAILED(hResult=ans.Add(aux[1]))) return(hResult);

	ans.m_sign = num.m_sign * val.m_sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::ToomCook33(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	MPAInteger	ansT[4], tmp[2];
	MPAInteger	numS[3], valS[3], fix;
	const size_t	valN=val.Length();
	const size_t	split=(valN + 2) / 3;									// split = ceil(valN / 3)
	HRESULT			hResult;

	if (FAILED(hResult=num.SplitU(fix, numS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix.SplitU(numS[2], numS[1], split, false))) return(hResult);
	if (FAILED(hResult=val.SplitU(fix, valS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix.SplitU(valS[2], valS[1], split, false))) return(hResult);

// (Evaluation) & (Pointwise Multiplication)
// (Evaluation points)(x = 0, 1, -1, 2(-2), БЗ)
// C0(x=0)
	if (FAILED(hResult=ansT[0].Mul(numS[0], valS[0]))) return(hResult);		// ansT[1] = numS[0] * valS[0]
// P1(x=1)
	if (FAILED(hResult=tmp[0].Value(numS[2]))) return(hResult);				// tmp[0] = numS[2]
	if (FAILED(hResult=tmp[0].Add(numS[1]))) return(hResult);				// tmp[0] += numS[1]
	if (FAILED(hResult=tmp[0].Add(numS[0]))) return(hResult);				// tmp[0] += numS[0]
	if (FAILED(hResult=tmp[1].Value(valS[2]))) return(hResult);				// tmp[1] = valS[2]
	if (FAILED(hResult=tmp[1].Add(valS[1]))) return(hResult);				// tmp[1] += valS[1]
	if (FAILED(hResult=tmp[1].Add(valS[0]))) return(hResult);				// tmp[1] += valS[0]
	if (FAILED(hResult=ansT[1].Mul(tmp[0], tmp[1]))) return(hResult);		// ansT[1] = tmp[0] * tmp[1]
// M1(x=-1)
	if (FAILED(hResult=tmp[0].Value(numS[2]))) return(hResult);				// tmp[0] = numS[2]
	if (FAILED(hResult=tmp[0].Sub(numS[1]))) return(hResult);				// tmp[0] -= numS[1]
	if (FAILED(hResult=tmp[0].Add(numS[0]))) return(hResult);				// tmp[0] += numS[0]
	if (FAILED(hResult=tmp[1].Value(valS[2]))) return(hResult);				// tmp[1] = valS[2]
	if (FAILED(hResult=tmp[1].Sub(valS[1]))) return(hResult);				// tmp[1] -= valS[1]
	if (FAILED(hResult=tmp[1].Add(valS[0]))) return(hResult);				// tmp[1] += valS[0]
	if (FAILED(hResult=ansT[2].Mul(tmp[0], tmp[1]))) return(hResult);		// ansT[2] = tmp[0] * tmp[1]
// P2(x=2)
	if (FAILED(hResult=tmp[0].Value(numS[2]))) return(hResult);				// tmp[0] = numS[2]
	if (FAILED(hResult=tmp[0].Shl(1))) return(hResult);						// tmp[0] *= 2
	if (FAILED(hResult=tmp[0].Sub(numS[1]))) return(hResult);				// tmp[0] -= numS[1]
	if (FAILED(hResult=tmp[0].Shl(1))) return(hResult);						// tmp[0] *= 2
	if (FAILED(hResult=tmp[0].Add(numS[0]))) return(hResult);				// tmp[0] += numS[0]
	if (FAILED(hResult=tmp[1].Value(valS[2]))) return(hResult);				// tmp[1] = valS[2]
	if (FAILED(hResult=tmp[1].Shl(1))) return(hResult);						// tmp[1] *= 2
	if (FAILED(hResult=tmp[1].Sub(valS[1]))) return(hResult);				// tmp[1] -= valS[1]
	if (FAILED(hResult=tmp[1].Shl(1))) return(hResult);						// tmp[1] *= 2
	if (FAILED(hResult=tmp[1].Add(valS[0]))) return(hResult);				// tmp[1] += valS[0]
	if (FAILED(hResult=ansT[3].Mul(tmp[0], tmp[1]))) return(hResult);		// ansT[3] = tmp[0] * tmp[1]
// (C4)(x=БЗ)
	if (FAILED(hResult=ans.Mul(numS[2], valS[2]))) return(hResult);			// ans = numS[2] * valS[2]

// (Interpolation)
	if (FAILED(hResult=ansT[3].Sub(ansT[1]))) return(hResult);				// ansT[3] -= ansT[1]
	::MPAdev3(ansT[3].m_buf.data, ansT[3].m_buf.size);						// ansT[3] /= 3
	ansT[3].Adjust();
	if (FAILED(hResult=ansT[1].Sub(ansT[2]))) return(hResult);				// ansT[1] -= ansT[2]
	ansT[1].Shr(1);															// ansT[1] /= 2
	if (FAILED(hResult=ansT[2].Sub(ansT[0]))) return(hResult);				// ansT[2] -= ansT[0]

// (C3)
	ansT[3].m_sign *= -1;													// ansT[3] *= -1	// ansT[3].NegSign();
	if (FAILED(hResult=ansT[3].Add(ansT[2]))) return(hResult);				// ansT[3] = -ansT[3] + ansT[2]
	ansT[3].Shr(1);															// ansT[3] /= 2
	if (FAILED(hResult=tmp[0].Value(ans))) return(hResult);					// tmp[0] = ans
	if (FAILED(hResult=tmp[0].Shl(1))) return(hResult);						// tmp[0] *= 2
	if (FAILED(hResult=ansT[3].Add(tmp[0]))) return(hResult);				// ansT[3] += tmp[0]
// (C2)
	if (FAILED(hResult=ansT[2].Add(ansT[1]))) return(hResult);				// ansT[2] += ansT[1]
	if (FAILED(hResult=ansT[2].Sub(ans))) return(hResult);					// ansT[2] += ans
// (C1)
	if (FAILED(hResult=ansT[1].Sub(ansT[3]))) return(hResult);				// ansT[1] -= ansT[3]

// (Recomposition)
	if (FAILED(hResult=ansT[1].Insert(split))) return(hResult);
	if (FAILED(hResult=ansT[1].Add(ansT[0]))) return(hResult);
	if (FAILED(hResult=ansT[2].Insert(split*2))) return(hResult);
	if (FAILED(hResult=ansT[2].Add(ansT[1]))) return(hResult);
	if (FAILED(hResult=ansT[3].Insert(split*3))) return(hResult);
	if (FAILED(hResult=ansT[3].Add(ansT[2]))) return(hResult);
	if (FAILED(hResult=ans.Insert(split*4))) return(hResult);
	if (FAILED(hResult=ans.Add(ansT[3]))) return(hResult);

	ans.m_sign = num.m_sign * val.m_sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::ToomCook42(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	MPAInteger	ansT[4], tmp[2];
	MPAInteger	numS[4], valS[2];
	MPAInteger&	fix1=valS[0];
	MPAInteger&	fix2=valS[1];
	const size_t	valN=val.Length();
	const size_t	split=(valN + 1) / 2;									// split = ceil(valN / 2)
	HRESULT			hResult;

	if (FAILED(hResult=num.SplitU(fix1, numS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix1.SplitU(fix2, numS[1], split, false))) return(hResult);
	if (FAILED(hResult=fix2.SplitU(numS[3], numS[2], split, false))) return(hResult);
	if (FAILED(hResult=val.SplitU(valS[1], valS[0], split, false))) return(hResult);

// (Evaluation) & (Pointwise Multiplication)
// (Evaluation points)(x = 0, 1, -1, 2(-2), БЗ)
// C0(x=0)
	if (FAILED(hResult=ansT[0].Mul(numS[0], valS[0]))) return(hResult);
// P1(x=1)
	if (FAILED(hResult=tmp[0].Value(numS[0]))) return(hResult);						// tmp[0] = numS[0]
	if (FAILED(hResult=tmp[0].Add(numS[1]))) return(hResult);						// tmp[0] += numS[1]
	if (FAILED(hResult=tmp[0].Add(numS[2]))) return(hResult);						// tmp[0] += numS[2]
	if (FAILED(hResult=tmp[0].Add(numS[3]))) return(hResult);						// tmp[0] += numS[3]
	if (FAILED(hResult=tmp[1].Value(valS[0]))) return(hResult);						// tmp[1] = valS[0]
	if (FAILED(hResult=tmp[1].Add(valS[1]))) return(hResult);						// tmp[1] += valS[1]
	if (FAILED(hResult=ansT[1].Mul(tmp[0], tmp[1]))) return(hResult);				// ansT[1] = tmp[0] * tmp[1]
// M1(x=-1)
	if (FAILED(hResult=tmp[0].Value(numS[0]))) return(hResult);						// tmp[0] = numS[0]
	if (FAILED(hResult=tmp[0].Sub(numS[1]))) return(hResult);						// tmp[0] -= numS[1]
	if (FAILED(hResult=tmp[0].Add(numS[2]))) return(hResult);						// tmp[0] += numS[2]
	if (FAILED(hResult=tmp[0].Sub(numS[3]))) return(hResult);						// tmp[0] -= numS[3]
	if (FAILED(hResult=tmp[1].Value(valS[0]))) return(hResult);						// tmp[1] = valS[0]
	if (FAILED(hResult=tmp[1].Sub(valS[1]))) return(hResult);						// tmp[1] -= valS[1]
	if (FAILED(hResult=ansT[2].Mul(tmp[0], tmp[1]))) return(hResult);				// ansT[2] = tmp[0] * tmp[1]
// P2(x=2)
	if (FAILED(hResult=tmp[0].Value(numS[3]))) return(hResult);						// tmp[0] = numS[3]
	if (FAILED(hResult=tmp[0].Shl(1))) return(hResult);								// tmp[0] *= 2
	if (FAILED(hResult=tmp[0].Add(numS[2]))) return(hResult);						// tmp[0] = numS[2]
	if (FAILED(hResult=tmp[0].Shl(1))) return(hResult);								// tmp[0] *= 2
	if (FAILED(hResult=tmp[0].Add(numS[1]))) return(hResult);						// tmp[0] = numS[1]
	if (FAILED(hResult=tmp[0].Shl(1))) return(hResult);								// tmp[0] *= 2
	if (FAILED(hResult=tmp[0].Add(numS[0]))) return(hResult);						// tmp[0] = numS[0]
	if (FAILED(hResult=tmp[1].Value(valS[1]))) return(hResult);						// tmp[1] = valS[1]
	if (FAILED(hResult=tmp[1].Shl(1))) return(hResult);								// tmp[1] *= 2
	if (FAILED(hResult=tmp[1].Add(valS[0]))) return(hResult);						// tmp[1] += valS[0]
	if (FAILED(hResult=ansT[3].Mul(tmp[0], tmp[1]))) return(hResult);				// ansT[2] = tmp[0] * tmp[1]
// (C4)(x=БЗ)
	if (FAILED(hResult=ans.Mul(numS[3], valS[1]))) return(hResult);

// (Interpolation/Matrix Inversion)
// (T1)
	if (FAILED(hResult=tmp[0].Value(ansT[1]))) return(hResult);						// tmp[0] = ansT[1]
	if (FAILED(hResult=tmp[0].Sub(ansT[2]))) return(hResult);						// tmp[0] -= ansT[2]
	tmp[0].Shr(1);																	// tmp[0] /= 2
// (T2)
	if (FAILED(hResult=tmp[1].Value(ansT[1]))) return(hResult);						// tmp[1] = ansT[1]
	if (FAILED(hResult=tmp[1].Add(ansT[2]))) return(hResult);						// tmp[1] += ansT[2]
	tmp[1].Shr(1);																	// tmp[1] /= 2
// (C2)
	if (FAILED(hResult=tmp[1].Sub(ansT[0]))) return(hResult);						// tmp[1] -= ansT[0]
	if (FAILED(hResult=tmp[1].Sub(ans))) return(hResult);							// tmp[1] -= ans(C4)

// (C3)
	if (FAILED(hResult=ansT[3].Sub(ansT[0]))) return(hResult);						// ansT[3] -= ansT[0]
	if (FAILED(hResult=ansT[1].Value(ans))) return(hResult);						// ansT[1] = ans
	if (FAILED(hResult=ansT[1].Shl(2))) return(hResult);							// ansT[1] *= 4
	if (FAILED(hResult=ansT[1].Add(tmp[1]))) return(hResult);						// ansT[1] += tmp[1]
	if (FAILED(hResult=ansT[1].Shl(2))) return(hResult);							// ansT[1] *= 4
	if (FAILED(hResult=ansT[3].Sub(ansT[1]))) return(hResult);						// ansT[3] -= ansT[1]
	if (FAILED(hResult=ansT[1].Value(tmp[0]))) return(hResult);						// ansT[1] = tmp[0]
	if (FAILED(hResult=ansT[1].Shl(1))) return(hResult);							// ansT[1] *= 2
	if (FAILED(hResult=ansT[3].Sub(ansT[1]))) return(hResult);						// ansT[3] -= ansT[1]
	::MPAdev3(ansT[3].m_buf.data, ansT[3].m_buf.size);								// ansT[3] /= 3
	ansT[3].Adjust();
	ansT[3].Shr(1);																	// ansT[3] /= 2

// (C1)
	if (FAILED(hResult=tmp[0].Sub(ansT[3]))) return(hResult);						// tmp[0] -= ansT[3]

// (Recomposition)
	if (FAILED(hResult=tmp[0].Insert(split))) return(hResult);						// tmp[0](C1) <<= split
	if (FAILED(hResult=tmp[0].Add(ansT[0]))) return(hResult);						// tmp[0] += ansT[0](C0)
	if (FAILED(hResult=tmp[1].Insert(split*2))) return(hResult);					// tmp[1](C2) <<= (split * 2)
	if (FAILED(hResult=tmp[1].Add(tmp[0]))) return(hResult);						// tmp[1] += tmp[0]
	if (FAILED(hResult=ansT[3].Insert(split*3))) return(hResult);					// ansT[3](C3) <<= (split * 3)
	if (FAILED(hResult=ansT[3].Add(tmp[1]))) return(hResult);						// ansT[3] += tmp[1]
	if (FAILED(hResult=ans.Insert(split*4))) return(hResult);						// ans(C4) <<= (split * 4)
	if (FAILED(hResult=ans.Add(ansT[3]))) return(hResult);							// ans += ansT[3]

	ans.m_sign = num.m_sign * val.m_sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::ToomCook43(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	MPAInteger	ansT[5], even[2], tmp;
	MPAInteger	numS[4], valS[3], fix[2];
	const size_t	valN=val.Length();
	const size_t	split=(valN + 2) / 3;									// split = ceil(valN / 3)
	HRESULT			hResult;

	if (FAILED(hResult=num.SplitU(fix[0], numS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix[0].SplitU(fix[1], numS[1], split, false))) return(hResult);
	if (FAILED(hResult=fix[1].SplitU(numS[3], numS[2], split, false))) return(hResult);
	if (FAILED(hResult=val.SplitU(fix[0], valS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix[0].SplitU(valS[2], valS[1], split, false))) return(hResult);

// (Evaluation) & (Pointwise Multiplication)
// (Evaluation points)(x = 0, 1, -1, 2, -2, БЗ)
// C0(x=0)
	if (FAILED(hResult=ansT[0].Mul(numS[0], valS[0]))) return(hResult);
// P1(x=1)
	if (FAILED(hResult=even[0].Value(numS[0]))) return(hResult);			// even[0] = numS[0]
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Add(numS[3]))) return(hResult);				// even[0] += numS[3]
	if (FAILED(hResult=even[1].Value(valS[0]))) return(hResult);			// even[1] = valS[0]
	if (FAILED(hResult=even[1].Add(valS[1]))) return(hResult);				// even[1] += valS[1]
	if (FAILED(hResult=even[1].Add(valS[2]))) return(hResult);				// even[1] += valS[2]
	if (FAILED(hResult=ansT[1].Mul(even[0], even[1]))) return(hResult);		// ansT[1] = even[0] * even[1]
// M1(x=-1)
	if (FAILED(hResult=even[0].Value(numS[0]))) return(hResult);			// even[0] = numS[0]
	if (FAILED(hResult=even[0].Sub(numS[1]))) return(hResult);				// even[0] -= numS[1]
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Sub(numS[3]))) return(hResult);				// even[0] -= numS[3]
	if (FAILED(hResult=even[1].Value(valS[0]))) return(hResult);			// even[1] = valS[0]
	if (FAILED(hResult=even[1].Sub(valS[1]))) return(hResult);				// even[1] -= valS[1]
	if (FAILED(hResult=even[1].Add(valS[2]))) return(hResult);				// even[1] += valS[2]
	if (FAILED(hResult=ansT[2].Mul(even[0], even[1]))) return(hResult);		// ansT[2] = even[0] * even[1]
// P2(x=2)
	if (FAILED(hResult=even[0].Value(numS[3]))) return(hResult);			// even[0] = numS[3]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[2]))) return(hResult);			// even[1] = valS[2]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[1]))) return(hResult);				// even[1] += valS[1]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[3].Mul(even[0], even[1]))) return(hResult);		// ansT[3] = even[0] * even[1]
// M2(x=-2)
	if (FAILED(hResult=even[0].Value(numS[3]))) return(hResult);			// even[0] = numS[3]
	even[0].m_sign *= -1;													// even[0] *= -1	// even[0].NegSign();
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Sub(numS[1]))) return(hResult);				// even[0] -= numS[1]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[2]))) return(hResult);			// even[1] = valS[2]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Sub(valS[1]))) return(hResult);				// even[1] -= valS[1]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[4].Mul(even[0], even[1]))) return(hResult);		// ansT[4] = even[0] * even[1]
// (C5)(x=БЗ)
	if (FAILED(hResult=ans.Mul(numS[3], valS[2]))) return(hResult);

// (Interpolation)
// (Even coefficient)
// (E1)
	if (FAILED(hResult=even[0].Value(ansT[1]))) return(hResult);			// even[0] = ansT[1]
	if (FAILED(hResult=even[0].Add(ansT[2]))) return(hResult);				// even[0] += ansT[2]
	even[0].Shr(1);															// even[0] /= 2
	if (FAILED(hResult=even[0].Sub(ansT[0]))) return(hResult);				// even[0] -= ansT[0]
// (E2)
	if (FAILED(hResult=even[1].Value(ansT[3]))) return(hResult);			// even[1] = ansT[3]
	if (FAILED(hResult=even[1].Add(ansT[4]))) return(hResult);				// even[1] += ansT[4]
	even[1].Shr(1);															// even[1] /= 2
	if (FAILED(hResult=even[1].Sub(ansT[0]))) return(hResult);				// even[1] -= ansT[0]
	even[1].Shr(2);															// even[1] /= 4
// (C4)
	if (FAILED(hResult=even[1].Sub(even[0]))) return(hResult);				// even[1] -= even[0]
	::MPAdev3(even[1].m_buf.data, even[1].m_buf.size);						// even[1] /= 3
	even[1].Adjust();
// (C2)
	if (FAILED(hResult=even[0].Sub(even[1]))) return(hResult);				// even[0] -= even[1]

// (Odd coefficient)
// (O1)
	if (FAILED(hResult=ansT[1].Sub(ansT[2]))) return(hResult);				// ansT[1] -= ansT[2]
	ansT[1].Shr(1);															// ansT[1] /= 2
	if (FAILED(hResult=ansT[1].Sub(ans))) return(hResult);					// ansT[1] -= ans(C5)
// (O2)
	if (FAILED(hResult=ansT[3].Sub(ansT[4]))) return(hResult);				// ansT[3] -= ansT[4]
	ansT[3].Shr(2);															// ansT[3] /= 4
	if (FAILED(hResult=tmp.Value(ans))) return(hResult);					// tmp = ans(C5)
	if (FAILED(hResult=tmp.Shl(4))) return(hResult);						// tmp *= 16
	if (FAILED(hResult=ansT[3].Sub(tmp))) return(hResult);					// ansT[3] -= tmp
// (C3)
	if (FAILED(hResult=ansT[3].Sub(ansT[1]))) return(hResult);				// ansT[3] -= ansT[1]
	::MPAdev3(ansT[3].m_buf.data, ansT[3].m_buf.size);						// ansT[3] /= 3
	ansT[3].Adjust();
// (C1)
	if (FAILED(hResult=ansT[1].Sub(ansT[3]))) return(hResult);				// ansT[1] -= ansT[3]

// (Recomposition)
	if (FAILED(hResult=ansT[1].Insert(split))) return(hResult);				// ansT[1](C1) <<= split
	if (FAILED(hResult=ansT[1].Add(ansT[0]))) return(hResult);				// ansT[1] += ansT[0](C0)
	if (FAILED(hResult=even[0].Insert(split*2))) return(hResult);			// even[0](C2) <<= (split * 2)
	if (FAILED(hResult=even[0].Add(ansT[1]))) return(hResult);				// even[0] += ansT[1]
	if (FAILED(hResult=ansT[3].Insert(split*3))) return(hResult);			// ansT[3](C3) <<= (split * 3)
	if (FAILED(hResult=ansT[3].Add(even[0]))) return(hResult);				// ansT[3] += even[0]
	if (FAILED(hResult=even[1].Insert(split*4))) return(hResult);			// even[1](C4) <<= (split * 4)
	if (FAILED(hResult=even[1].Add(ansT[3]))) return(hResult);				// even[1] += ansT[3]
	if (FAILED(hResult=ans.Insert(split*5))) return(hResult);				// ans(C5) <<= (split * 5)
	if (FAILED(hResult=ans.Add(even[1]))) return(hResult);					// ans += even[1]

	ans.m_sign = num.m_sign * val.m_sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::ToomCook44(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	MPAInteger	ansT[6], even[2], tmp;
	MPAInteger	numS[4], valS[4], fix[2];
	const size_t	valN=val.Length();
	const size_t	split=(valN + 3) / 4;									// split = ceil(valN / 4)
	HRESULT			hResult;

	if (FAILED(hResult=num.SplitU(fix[0], numS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix[0].SplitU(fix[1], numS[1], split, false))) return(hResult);
	if (FAILED(hResult=fix[1].SplitU(numS[3], numS[2], split, false))) return(hResult);
	if (FAILED(hResult=val.SplitU(fix[0], valS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix[0].SplitU(fix[1], valS[1], split, false))) return(hResult);
	if (FAILED(hResult=fix[1].SplitU(valS[3], valS[2], split, false))) return(hResult);

// (Evaluation) & (Pointwise Multiplication)
// (Evaluation points)(x = 0, 1, -1, 2, -2, 3, БЗ)
// C0(x=0)
	if (FAILED(hResult=ansT[0].Mul(numS[0], valS[0]))) return(hResult);
// P1(x=1)
	if (FAILED(hResult=even[0].Value(numS[0]))) return(hResult);			// even[0] = numS[0]
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Add(numS[3]))) return(hResult);				// even[0] += numS[3]
	if (FAILED(hResult=even[1].Value(valS[0]))) return(hResult);			// even[1] = valS[0]
	if (FAILED(hResult=even[1].Add(valS[1]))) return(hResult);				// even[1] += valS[1]
	if (FAILED(hResult=even[1].Add(valS[2]))) return(hResult);				// even[1] += valS[2]
	if (FAILED(hResult=even[1].Add(valS[3]))) return(hResult);				// even[1] += valS[3]
	if (FAILED(hResult=ansT[1].Mul(even[0], even[1]))) return(hResult);		// ansT[1] = even[0] * even[1]
// M1(x=-1)
	if (FAILED(hResult=even[0].Value(numS[0]))) return(hResult);			// even[0] = numS[0]
	if (FAILED(hResult=even[0].Sub(numS[1]))) return(hResult);				// even[0] -= numS[1]
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Sub(numS[3]))) return(hResult);				// even[0] -= numS[3]
	if (FAILED(hResult=even[1].Value(valS[0]))) return(hResult);			// even[1] = valS[0]
	if (FAILED(hResult=even[1].Sub(valS[1]))) return(hResult);				// even[1] -= valS[1]
	if (FAILED(hResult=even[1].Add(valS[2]))) return(hResult);				// even[1] += valS[2]
	if (FAILED(hResult=even[1].Sub(valS[3]))) return(hResult);				// even[1] -= valS[3]
	if (FAILED(hResult=ansT[2].Mul(even[0], even[1]))) return(hResult);		// ansT[2] = even[0] * even[1]
// P2(x=2)
	if (FAILED(hResult=even[0].Value(numS[3]))) return(hResult);			// even[0] = numS[3]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[3]))) return(hResult);			// even[1] = valS[3]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[2]))) return(hResult);				// even[1] += valS[2]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[1]))) return(hResult);				// even[1] += valS[1]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[3].Mul(even[0], even[1]))) return(hResult);		// ansT[3] = even[0] * even[1]
// M2(x=-2)
	if (FAILED(hResult=even[0].Value(numS[3]))) return(hResult);			// even[0] = numS[3]
	even[0].m_sign *= -1;													// even[0] *= -1	// even[0].NegSign();
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Sub(numS[1]))) return(hResult);				// even[0] -= numS[1]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[3]))) return(hResult);			// even[1] = valS[3]
	even[1].m_sign *= -1;													// even[1] *= -1	// even[1].NegSign();
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[2]))) return(hResult);				// even[1] += valS[2]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Sub(valS[1]))) return(hResult);				// even[1] -= valS[1]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[4].Mul(even[0], even[1]))) return(hResult);		// ansT[4] = even[0] * even[1]
// P3(x=3)
	if (FAILED(hResult=even[0].Value(numS[3]))) return(hResult);			// even[0] = numS[3]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[3]))) return(hResult);			// even[1] = valS[3]
	if (FAILED(hResult=even[1].SingleMulU(3))) return(hResult);				// even[1] *= 3
	if (FAILED(hResult=even[1].Add(valS[2]))) return(hResult);				// even[1] += valS[2]
	if (FAILED(hResult=even[1].SingleMulU(3))) return(hResult);				// even[1] *= 3
	if (FAILED(hResult=even[1].Add(valS[1]))) return(hResult);				// even[1] += valS[1]
	if (FAILED(hResult=even[1].SingleMulU(3))) return(hResult);				// even[1] *= 3
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[5].Mul(even[0], even[1]))) return(hResult);		// ansT[5] = even[0] * even[1]
// (C6)(x=БЗ)
	if (FAILED(hResult=ans.Mul(numS[3], valS[3]))) return(hResult);

// (Interpolation)
// (Even coefficient)
// (E1)
	if (FAILED(hResult=even[0].Value(ansT[1]))) return(hResult);			// even[0] = ansT[1]
	if (FAILED(hResult=even[0].Add(ansT[2]))) return(hResult);				// even[0] += ansT[2]
	even[0].Shr(1);															// even[0] /= 2
	if (FAILED(hResult=even[0].Sub(ansT[0]))) return(hResult);				// even[0] -= ansT[0]
	if (FAILED(hResult=even[0].Sub(ans))) return(hResult);					// even[0] -= ans
// (E2)
	if (FAILED(hResult=even[1].Value(ansT[3]))) return(hResult);			// even[1] = ansT[3]
	if (FAILED(hResult=even[1].Add(ansT[4]))) return(hResult);				// even[1] += ansT[4]
	even[1].Shr(1);															// even[1] /= 2
	if (FAILED(hResult=even[1].Sub(ansT[0]))) return(hResult);				// even[1] -= ansT[0]
	if (FAILED(hResult=tmp.Value(ans))) return(hResult);					// tmp = ans
	if (FAILED(hResult=tmp.Shl(6))) return(hResult);						// tmp *= 64
	if (FAILED(hResult=even[1].Sub(tmp))) return(hResult);					// even[1] -= tmp
	even[1].Shr(2);															// even[1] /= 4

// (C4)
	if (FAILED(hResult=even[1].Sub(even[0]))) return(hResult);				// even[1] -= even[0]
	::MPAdev3(even[1].m_buf.data, even[1].m_buf.size);						// even[1] /= 3
	even[1].Adjust();
// (C2)
	if (FAILED(hResult=even[0].Sub(even[1]))) return(hResult);				// even[0] -= even[1]

// (Odd coefficient)
// (O1)
	if (FAILED(hResult=ansT[1].Sub(ansT[2]))) return(hResult);				// ansT[1] -= ansT[2]
	ansT[1].Shr(1);															// ansT[1] /= 2
// (O2)
	if (FAILED(hResult=ansT[3].Sub(ansT[4]))) return(hResult);				// ansT[3] -= ansT[4]
	ansT[3].Shr(2);															// ansT[3] /= 4
	if (FAILED(hResult=ansT[3].Sub(ansT[1]))) return(hResult);				// ansT[3] -= ansT[1]
	::MPAdev3(ansT[3].m_buf.data, ansT[3].m_buf.size);						// ansT[3] /= 3
	ansT[3].Adjust();

// (W)
	if (FAILED(hResult=tmp.Value(ans))) return(hResult);					// tmp = ans
	if (FAILED(hResult=tmp.SingleMulU(9))) return(hResult);					// tmp *= 9
	if (FAILED(hResult=tmp.Add(even[1]))) return(hResult);					// tmp += even[1]
	if (FAILED(hResult=tmp.SingleMulU(9))) return(hResult);					// tmp *= 9
	if (FAILED(hResult=tmp.Add(even[0]))) return(hResult);					// tmp += even[0]
	if (FAILED(hResult=tmp.SingleMulU(9))) return(hResult);					// tmp *= 9
	if (FAILED(hResult=tmp.Add(ansT[0]))) return(hResult);					// tmp += ansT[0]
// (T3)
	if (FAILED(hResult=ansT[5].Sub(tmp))) return(hResult);					// ansT[5] -= tmp
	::MPAdev3(ansT[5].m_buf.data, ansT[5].m_buf.size);						// ansT[5] /= 3
	ansT[5].Adjust();
	if (FAILED(hResult=ansT[5].Sub(ansT[1]))) return(hResult);				// ansT[5] -= ansT[1]
	ansT[5].Shr(3);															// ansT[5] /= 8

// (C5)
	if (FAILED(hResult=ansT[5].Sub(ansT[3]))) return(hResult);				// ansT[5] -= ansT[3]
	::MPAdev5(ansT[5].m_buf.data, ansT[5].m_buf.size);						// ansT[5] /= 5
	ansT[5].Adjust();
// (C3)
	if (FAILED(hResult=tmp.Value(ansT[5]))) return(hResult);				// tmp = ansT[5]
	if (FAILED(hResult=tmp.SingleMulU(5))) return(hResult);					// tmp *= 5
	if (FAILED(hResult=ansT[3].Sub(tmp))) return(hResult);					// ansT[3] -= tmp
// (C1)
	if (FAILED(hResult=ansT[1].Sub(ansT[3]))) return(hResult);				// ansT[1] -= ansT[3]
	if (FAILED(hResult=ansT[1].Sub(ansT[5]))) return(hResult);				// ansT[1] -= ansT[5]

// (Recomposition)
	if (FAILED(hResult=ansT[1].Insert(split))) return(hResult);				// ansT[1](C1) <<= split
	if (FAILED(hResult=ansT[1].Add(ansT[0]))) return(hResult);				// ansT[1] += ansT[0](C0)
	if (FAILED(hResult=even[0].Insert(split*2))) return(hResult);			// even[0](C2) <<= (split * 2)
	if (FAILED(hResult=even[0].Add(ansT[1]))) return(hResult);				// even[0] += ansT[1]
	if (FAILED(hResult=ansT[3].Insert(split*3))) return(hResult);			// ansT[3](C3) <<= (split * 3)
	if (FAILED(hResult=ansT[3].Add(even[0]))) return(hResult);				// ansT[3] += even[0]
	if (FAILED(hResult=even[1].Insert(split*4))) return(hResult);			// even[1](C4) <<= (split * 4)
	if (FAILED(hResult=even[1].Add(ansT[3]))) return(hResult);				// even[1] += ansT[3]
	if (FAILED(hResult=ansT[5].Insert(split*5))) return(hResult);			// ansT[5](C5) <<= (split * 5)
	if (FAILED(hResult=ansT[5].Add(even[1]))) return(hResult);				// ansT[5] += even[1]
	if (FAILED(hResult=ans.Insert(split*6))) return(hResult);				// ans(C6) <<= (split * 6)
	if (FAILED(hResult=ans.Add(ansT[5]))) return(hResult);					// ans += ansT[5]

	ans.m_sign = num.m_sign * val.m_sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::ToomCook52(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	MPAInteger	ansT[5], even[3], aux, tmp;
	MPAInteger	numS[5], valS[2], fix[2];
	const size_t	valN=val.Length();
	const size_t	split=(valN + 1) / 2;									// split = ceil(valN / 2)
	HRESULT			hResult;

	if (FAILED(hResult=num.SplitU(fix[0], numS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix[0].SplitU(fix[1], numS[1], split, false))) return(hResult);
	if (FAILED(hResult=fix[1].SplitU(fix[0], numS[2], split, false))) return(hResult);
	if (FAILED(hResult=fix[0].SplitU(numS[4], numS[3], split, false))) return(hResult);
	if (FAILED(hResult=val.SplitU(valS[1], valS[0], split, false))) return(hResult);

// (Evaluation) & (Pointwise Multiplication)
// (Evaluation points)(x = 0,  1, -1, 2, -2,  БЗ)
// C0(x=0)
	if (FAILED(hResult=ansT[0].Mul(numS[0], valS[0]))) return(hResult);
// P1(x=1)
	if (FAILED(hResult=even[0].Value(numS[0]))) return(hResult);			// even[0] = numS[0]
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Add(numS[3]))) return(hResult);				// even[0] += numS[3]
	if (FAILED(hResult=even[0].Add(numS[4]))) return(hResult);				// even[0] += numS[4]
	if (FAILED(hResult=even[1].Value(valS[0]))) return(hResult);			// even[1] = valS[0]
	if (FAILED(hResult=even[1].Add(valS[1]))) return(hResult);				// even[1] += valS[1]
	if (FAILED(hResult=ansT[1].Mul(even[0], even[1]))) return(hResult);		// ansT[1] = even[0] * even[1]
// M1(x=-1)
	if (FAILED(hResult=even[0].Value(numS[0]))) return(hResult);			// even[0] = numS[0]
	if (FAILED(hResult=even[0].Sub(numS[1]))) return(hResult);				// even[0] -= numS[1]
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Sub(numS[3]))) return(hResult);				// even[0] -= numS[3]
	if (FAILED(hResult=even[0].Add(numS[4]))) return(hResult);				// even[0] += numS[4]
	if (FAILED(hResult=even[1].Value(valS[0]))) return(hResult);			// even[1] = valS[0]
	if (FAILED(hResult=even[1].Sub(valS[1]))) return(hResult);				// even[1] -= valS[1]
	if (FAILED(hResult=ansT[2].Mul(even[0], even[1]))) return(hResult);		// ansT[2] = even[0] * even[1]
// P2(x=2)
	if (FAILED(hResult=even[0].Value(numS[4]))) return(hResult);			// even[0] = numS[4]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[3]))) return(hResult);				// even[0] += numS[3]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[1]))) return(hResult);			// even[1] = valS[1]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[3].Mul(even[0], even[1]))) return(hResult);		// ansT[3] = even[0] * even[1]
// M2(x=-2)
	if (FAILED(hResult=even[0].Value(numS[4]))) return(hResult);			// even[0] = numS[4]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Sub(numS[3]))) return(hResult);				// even[0] -= numS[3]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Sub(numS[1]))) return(hResult);				// even[0] -= numS[1]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[1]))) return(hResult);			// even[1] = valS[1]
	even[1].m_sign *= -1;													// even[1] *= -1	// even[1].NegSign();
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[4].Mul(even[0], even[1]))) return(hResult);		// ansT[4] = even[0] * even[1]
// (C5)(x=БЗ)
	if (FAILED(hResult=ans.Mul(numS[4], valS[1]))) return(hResult);

// (Interpolation)
// (Even coefficient)
// (E1)
	if (FAILED(hResult=even[0].Value(ansT[1]))) return(hResult);			// even[0] = ansT[1]
	if (FAILED(hResult=even[0].Add(ansT[2]))) return(hResult);				// even[0] += ansT[2]
	even[0].Shr(1);															// even[0] /= 2
	if (FAILED(hResult=even[0].Sub(ansT[0]))) return(hResult);				// even[0] -= ansT[0]
// (E2)
	if (FAILED(hResult=even[1].Value(ansT[3]))) return(hResult);			// even[1] = ansT[3]
	if (FAILED(hResult=even[1].Add(ansT[4]))) return(hResult);				// even[1] += ansT[4]
	even[1].Shr(1);															// even[1] /= 2
	if (FAILED(hResult=even[1].Sub(ansT[0]))) return(hResult);				// even[1] -= ansT[0]
	even[1].Shr(2);															// even[1] /= 4

// (C4)
	if (FAILED(hResult=even[1].Sub(even[0]))) return(hResult);				// even[1] -= even[0]
	::MPAdev3(even[1].m_buf.data, even[1].m_buf.size);						// even[1] /= 3
	even[1].Adjust();
// (C2)
	if (FAILED(hResult=even[0].Sub(even[1]))) return(hResult);				// even[0] -= even[1]

// (Odd coefficient)
// (O1)
	if (FAILED(hResult=ansT[1].Sub(ansT[2]))) return(hResult);				// ansT[1] -= ansT[2]
	ansT[1].Shr(1);															// ansT[1] /= 2
	if (FAILED(hResult=ansT[1].Sub(ans))) return(hResult);					// ansT[1] -= ans
// (O2)
	if (FAILED(hResult=ansT[3].Sub(ansT[4]))) return(hResult);				// ansT[3] -= ansT[4]
	ansT[3].Shr(2);															// ansT[3] /= 4
	if (FAILED(hResult=tmp.Value(ans))) return(hResult);					// tmp = ans
	if (FAILED(hResult=tmp.Shl(4))) return(hResult);						// tmp *= 16
	if (FAILED(hResult=ansT[3].Sub(tmp))) return(hResult);					// ansT[3] -= tmp

// (C3)
	if (FAILED(hResult=ansT[3].Sub(ansT[1]))) return(hResult);				// ansT[3] -= ansT[1]
	::MPAdev3(ansT[3].m_buf.data, ansT[3].m_buf.size);						// ansT[3] /= 3
	ansT[3].Adjust();
// (C1)
	if (FAILED(hResult=ansT[1].Sub(ansT[3]))) return(hResult);				// ansT[1] -= ansT[3]

// (Recomposition)
	if (FAILED(hResult=ansT[1].Insert(split))) return(hResult);				// ansT[1](C1) <<= split
	if (FAILED(hResult=ansT[1].Add(ansT[0]))) return(hResult);				// ansT[1] += ansT[0](C0)
	if (FAILED(hResult=even[0].Insert(split*2))) return(hResult);			// even[0](C2) <<= (split * 2)
	if (FAILED(hResult=even[0].Add(ansT[1]))) return(hResult);				// even[0] += ansT[1]
	if (FAILED(hResult=ansT[3].Insert(split*3))) return(hResult);			// ansT[3](C3) <<= (split * 3)
	if (FAILED(hResult=ansT[3].Add(even[0]))) return(hResult);				// ansT[3] += even[0]
	if (FAILED(hResult=even[1].Insert(split*4))) return(hResult);			// even[1](C4) <<= (split * 4)
	if (FAILED(hResult=even[1].Add(ansT[3]))) return(hResult);				// even[1] += ansT[3]
	if (FAILED(hResult=ans.Insert(split*5))) return(hResult);				// ans(C7) <<= (split * 7)
	if (FAILED(hResult=ans.Add(even[1]))) return(hResult);					// ans += even[1]

	ans.m_sign = num.m_sign * val.m_sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::ToomCook63(const MPAInteger& num, const MPAInteger& val)
{
	MPAInteger&	ans=*this;
	MPAInteger	ansT[7], even[3], aux, tmp;
	MPAInteger	numS[6], valS[3], fix[2];
	const size_t	valN=val.Length();
	const size_t	split=(valN + 2) / 3;									// split = ceil(valN / 3)
	HRESULT			hResult;

	if (FAILED(hResult=num.SplitU(fix[0], numS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix[0].SplitU(fix[1], numS[1], split, false))) return(hResult);
	if (FAILED(hResult=fix[1].SplitU(fix[0], numS[2], split, false))) return(hResult);
	if (FAILED(hResult=fix[0].SplitU(fix[1], numS[3], split, false))) return(hResult);
	if (FAILED(hResult=fix[1].SplitU(numS[5], numS[4], split, false))) return(hResult);
	if (FAILED(hResult=val.SplitU(fix[0], valS[0], split, false))) return(hResult);
	if (FAILED(hResult=fix[0].SplitU(valS[2], valS[1], split, false))) return(hResult);

// (Evaluation) & (Pointwise Multiplication)
// (Evaluation points)(x = 0, 1, -1, 2, -2, 3, -3, БЗ)
// C0(x=0)
	if (FAILED(hResult=ansT[0].Mul(numS[0], valS[0]))) return(hResult);
// P1(x=1)
	if (FAILED(hResult=even[0].Value(numS[0]))) return(hResult);			// even[0] = numS[0]
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Add(numS[3]))) return(hResult);				// even[0] += numS[3]
	if (FAILED(hResult=even[0].Add(numS[4]))) return(hResult);				// even[0] += numS[4]
	if (FAILED(hResult=even[0].Add(numS[5]))) return(hResult);				// even[0] += numS[5]
	if (FAILED(hResult=even[1].Value(valS[0]))) return(hResult);			// even[1] = valS[0]
	if (FAILED(hResult=even[1].Add(valS[1]))) return(hResult);				// even[1] += valS[1]
	if (FAILED(hResult=even[1].Add(valS[2]))) return(hResult);				// even[1] += valS[2]
	if (FAILED(hResult=ansT[1].Mul(even[0], even[1]))) return(hResult);		// ansT[1] = even[0] * even[1]
// M1(x=-1)
	if (FAILED(hResult=even[0].Value(numS[0]))) return(hResult);			// even[0] = numS[0]
	if (FAILED(hResult=even[0].Sub(numS[1]))) return(hResult);				// even[0] -= numS[1]
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Sub(numS[3]))) return(hResult);				// even[0] -= numS[3]
	if (FAILED(hResult=even[0].Add(numS[4]))) return(hResult);				// even[0] += numS[4]
	if (FAILED(hResult=even[0].Sub(numS[5]))) return(hResult);				// even[0] -= numS[5]
	if (FAILED(hResult=even[1].Value(valS[0]))) return(hResult);			// even[1] = valS[0]
	if (FAILED(hResult=even[1].Sub(valS[1]))) return(hResult);				// even[1] -= valS[1]
	if (FAILED(hResult=even[1].Add(valS[2]))) return(hResult);				// even[1] += valS[2]
	if (FAILED(hResult=ansT[2].Mul(even[0], even[1]))) return(hResult);		// ansT[2] = even[0] * even[1]
// P2(x=2)
	if (FAILED(hResult=even[0].Value(numS[5]))) return(hResult);			// even[0] = numS[5]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[4]))) return(hResult);				// even[0] += numS[4]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[3]))) return(hResult);				// even[0] += numS[3]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[2]))) return(hResult);			// even[1] = valS[2]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[1]))) return(hResult);				// even[1] += valS[1]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[3].Mul(even[0], even[1]))) return(hResult);		// ansT[3] = even[0] * even[1]
// M2(x=-2)
	if (FAILED(hResult=even[0].Value(numS[5]))) return(hResult);			// even[0] = numS[5]
	even[0].m_sign *= -1;													// even[0] *= -1	// even[0].NegSign();
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[4]))) return(hResult);				// even[0] += numS[4]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Sub(numS[3]))) return(hResult);				// even[0] -= numS[3]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Sub(numS[1]))) return(hResult);				// even[0] -= numS[1]
	if (FAILED(hResult=even[0].Shl(1))) return(hResult);					// even[0] *= 2
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[2]))) return(hResult);			// even[1] = valS[2]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Sub(valS[1]))) return(hResult);				// even[1] -= valS[1]
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[4].Mul(even[0], even[1]))) return(hResult);		// ansT[4] = even[0] * even[1]
// P3(x=3)
	if (FAILED(hResult=even[0].Value(numS[5]))) return(hResult);			// even[0] = numS[5]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[4]))) return(hResult);				// even[0] += numS[4]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[3]))) return(hResult);				// even[0] += numS[3]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[1]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[1]
	if (FAILED(hResult=even[1].Value(valS[2]))) return(hResult);			// even[1] = valS[2]
	if (FAILED(hResult=even[1].SingleMulU(3))) return(hResult);				// even[1] *= 3
	if (FAILED(hResult=even[1].Add(valS[1]))) return(hResult);				// even[1] += valS[1]
	if (FAILED(hResult=even[1].SingleMulU(3))) return(hResult);				// even[1] *= 3
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[5].Mul(even[0], even[1]))) return(hResult);		// ansT[5] = even[0] * even[1]
// M3(x=-3)
	if (FAILED(hResult=even[0].Value(numS[5]))) return(hResult);			// even[0] = numS[5]
	even[0].m_sign *= -1;													// even[0] *= -1	// even[0].NegSign();
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[4]))) return(hResult);				// even[0] += numS[4]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Sub(numS[3]))) return(hResult);				// even[0] -= numS[3]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[2]))) return(hResult);				// even[0] += numS[2]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Sub(numS[1]))) return(hResult);				// even[0] -= numS[1]
	if (FAILED(hResult=even[0].SingleMulU(3))) return(hResult);				// even[0] *= 3
	if (FAILED(hResult=even[0].Add(numS[0]))) return(hResult);				// even[0] += numS[0]
	if (FAILED(hResult=even[1].Value(valS[2]))) return(hResult);			// even[1] = valS[2]
	if (FAILED(hResult=even[1].SingleMulU(3))) return(hResult);				// even[1] *= 3
	if (FAILED(hResult=even[1].Sub(valS[1]))) return(hResult);				// even[1] -= valS[1]
	if (FAILED(hResult=even[1].SingleMulU(3))) return(hResult);				// even[1] *= 3
	if (FAILED(hResult=even[1].Add(valS[0]))) return(hResult);				// even[1] += valS[0]
	if (FAILED(hResult=ansT[6].Mul(even[0], even[1]))) return(hResult);		// ansT[6] = even[0] * even[1]
// C7(x=БЗ)
	if (FAILED(hResult=ans.Mul(numS[5], valS[2]))) return(hResult);

// (Interpolation)
// (Even coefficient)
// (E1)
	if (FAILED(hResult=even[0].Value(ansT[1]))) return(hResult);			// even[0] = ansT[1]
	if (FAILED(hResult=even[0].Add(ansT[2]))) return(hResult);				// even[0] += ansT[2]
	even[0].Shr(1);															// even[0] /= 2
	if (FAILED(hResult=even[0].Sub(ansT[0]))) return(hResult);				// even[0] -= ansT[0]
// (E2)
	if (FAILED(hResult=even[1].Value(ansT[3]))) return(hResult);			// even[1] = ansT[3]
	if (FAILED(hResult=even[1].Add(ansT[4]))) return(hResult);				// even[1] += ansT[4]
	even[1].Shr(1);															// even[1] /= 2
	if (FAILED(hResult=even[1].Sub(ansT[0]))) return(hResult);				// even[1] -= ansT[0]
	even[1].Shr(2);															// even[1] /= 4
	if (FAILED(hResult=even[1].Sub(even[0]))) return(hResult);				// even[1] -= even[0]
	::MPAdev3(even[1].m_buf.data, even[1].m_buf.size);						// even[1] /= 3
	even[1].Adjust();
// (E3)
	if (FAILED(hResult=aux.Value(ansT[5]))) return(hResult);				// aux = ansT[5]
	if (FAILED(hResult=aux.Add(ansT[6]))) return(hResult);					// aux += ansT[6]
	aux.Shr(1);																// aux /= 2
	if (FAILED(hResult=aux.Sub(ansT[0]))) return(hResult);					// aux -= ansT[0]
	::MPAdev9(aux.m_buf.data, aux.m_buf.size);								// aux /= 9
	aux.Adjust();
	if (FAILED(hResult=aux.Sub(even[0]))) return(hResult);					// aux -= even[0]
	aux.Shr(3);																// aux /= 8
    
// (C6)
	if (FAILED(hResult=even[2].Value(aux))) return(hResult);				// even[2] = aux
	if (FAILED(hResult=even[2].Sub(even[1]))) return(hResult);				// even[2] -= even[1]
	::MPAdev5(even[2].m_buf.data, even[2].m_buf.size);						// even[2] /= 5
	even[2].Adjust();
// (C4)
	if (FAILED(hResult=even[1].Shl(1))) return(hResult);					// even[1] *= 2
	if (FAILED(hResult=even[1].Sub(aux))) return(hResult);					// even[1] -= aux
// (C2)
	if (FAILED(hResult=even[0].Sub(even[1]))) return(hResult);				// even[0] -= even[1]
	if (FAILED(hResult=even[0].Sub(even[2]))) return(hResult);				// even[0] -= even[2]

// (Odd coefficient)
// (O1)
	if (FAILED(hResult=ansT[1].Sub(ansT[2]))) return(hResult);				// ansT[1] -= ansT[2]
	ansT[1].Shr(1);															// ansT[1] /= 2
	if (FAILED(hResult=ansT[1].Sub(ans))) return(hResult);					// ansT[1] -= ans
// (O2)
	if (FAILED(hResult=ansT[3].Sub(ansT[4]))) return(hResult);				// ansT[3] -= ansT[4]
	ansT[3].Shr(2);															// ansT[3] /= 4
	if (FAILED(hResult=tmp.Value(ans))) return(hResult);					// tmp = ans
	if (FAILED(hResult=tmp.Shl(6))) return(hResult);						// tmp *= 64
	if (FAILED(hResult=ansT[3].Sub(tmp))) return(hResult);					// ansT[3] -= tmp
	if (FAILED(hResult=ansT[3].Sub(ansT[1]))) return(hResult);				// ansT[3] -= ansT[1]
	::MPAdev3(ansT[3].m_buf.data, ansT[3].m_buf.size);						// ansT[3] /= 3
	ansT[3].Adjust();
// (O3)
	if (FAILED(hResult=aux.Value(ansT[5]))) return(hResult);				// aux = ansT[5]
	if (FAILED(hResult=aux.Sub(ansT[6]))) return(hResult);					// aux -= ansT[6]
	::MPAdev3(aux.m_buf.data, aux.m_buf.size);								// aux /= 3
	aux.Adjust();
	aux.Shr(1);																// aux /= 2
	if (FAILED(hResult=tmp.Value(ans))) return(hResult);					// tmp = ans
	if (FAILED(hResult=tmp.SingleMulU(729))) return(hResult);				// tmp *= 729
	if (FAILED(hResult=aux.Sub(tmp))) return(hResult);						// aux -= tmp
	if (FAILED(hResult=aux.Sub(ansT[1]))) return(hResult);					// aux -= ansT[1]
	aux.Shr(3);																// aux /= 8

// (C5)
	if (FAILED(hResult=ansT[5].Value(aux))) return(hResult);				// ansT[5] = aux
	if (FAILED(hResult=ansT[5].Sub(ansT[3]))) return(hResult);				// ansT[5] -= ansT[3]
	::MPAdev5(ansT[5].m_buf.data, ansT[5].m_buf.size);						// ansT[5] /= 5
	ansT[5].Adjust();
// (C3)
	if (FAILED(hResult=ansT[3].Shl(1))) return(hResult);					// ansT[3] *= 2
	if (FAILED(hResult=ansT[3].Sub(aux))) return(hResult);					// ansT[3] -= aux
// (C1)
	if (FAILED(hResult=ansT[1].Sub(ansT[3]))) return(hResult);				// ansT[1] -= ansT[3]
	if (FAILED(hResult=ansT[1].Sub(ansT[5]))) return(hResult);				// ansT[1] -= ansT[5]
// (Deallocate memory)
	aux.Deallocate();
// (Recomposition)
	if (FAILED(hResult=ansT[1].Insert(split))) return(hResult);				// ansT[1](C1) <<= split
	if (FAILED(hResult=ansT[1].Add(ansT[0]))) return(hResult);				// ansT[1] += ansT[0](C0)
	if (FAILED(hResult=even[0].Insert(split*2))) return(hResult);			// even[0](C2) <<= (split * 2)
	if (FAILED(hResult=even[0].Add(ansT[1]))) return(hResult);				// even[0] += ansT[1]
	if (FAILED(hResult=ansT[3].Insert(split*3))) return(hResult);			// ansT[3](C3) <<= (split * 3)
	if (FAILED(hResult=ansT[3].Add(even[0]))) return(hResult);				// ansT[3] += even[0]
	if (FAILED(hResult=even[1].Insert(split*4))) return(hResult);			// even[1](C4) <<= (split * 4)
	if (FAILED(hResult=even[1].Add(ansT[3]))) return(hResult);				// even[1] += ansT[3]
	if (FAILED(hResult=ansT[5].Insert(split*5))) return(hResult);			// ansT[5](C5) <<= (split * 5)
	if (FAILED(hResult=ansT[5].Add(even[1]))) return(hResult);				// ansT[5] += even[1]
	if (FAILED(hResult=even[2].Insert(split*6))) return(hResult);			// even[2](C6) <<= (split * 6)
	if (FAILED(hResult=even[2].Add(ansT[5]))) return(hResult);				// even[2] += ansT[5]
	if (FAILED(hResult=ans.Insert(split*7))) return(hResult);				// ans(C7) <<= (split * 7)
	if (FAILED(hResult=ans.Add(even[2]))) return(hResult);					// ans += even[2]

	ans.m_sign = num.m_sign * val.m_sign;
	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВcВЙВЦ                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::Div(MPAInteger& num, INT_PTR den)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (FAILED(hResult=ans.NaiveDivU(num, ::abs(den)))) return(hResult);
	if ((den < 0) && (ans.Length())) ans.m_sign *= -1;

	return(NOERROR);
}
inline HRESULT MPAInteger::Div(MPAInteger& num, MPAInteger& den, bool denormalize)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (FAILED(hResult=ans.DivU(num, den, denormalize))) return(hResult);

	ans.m_sign = num.m_sign * den.m_sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::Div(const MPAInteger& num, const MPAInteger& den, MPAInteger& rem)
{
	MPAInteger&	ans=*this;
	HRESULT			hResult;

	if (FAILED(hResult=ans.DivU(num, den, rem))) return(hResult);

	ans.m_sign = num.m_sign * den.m_sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::DivU(MPAInteger& num, UINT_PTR den)
{
	return(NaiveDivU(num, den));
}
inline HRESULT MPAInteger::DivU(MPAInteger& num, MPAInteger& den, bool denormalize)
{
	MPAInteger&	ans=*this;
	const int		numS=num.m_sign;
	const int		denS=den.m_sign;
	HRESULT			hResult;

	num.m_sign = den.m_sign = 1;

	const size_t	numN=num.Length();
	const size_t	denN=den.Length();
	double			rate=double(numN) / double(denN);
	if ((numN < divBURNIKELZIEGLER) && (rate < 60.)) {
//		if (FAILED(hResult=ans.KnuthBinary(num, den))) return(hResult);
		if (FAILED(hResult=ans.KnuthLimb(num, den, denormalize))) return(hResult);
		}
	else if (numN < divNEWTONRAPHSON) {
		if (FAILED(hResult=ans.BurnikelZiegler(num, den, denormalize))) return(hResult);
		}
	else{
		if (FAILED(hResult=ans.ReciprocalMultiplication(num, den))) return(hResult);
		}

	num.m_sign = numS;
	den.m_sign = denS;
	ans.m_sign = numS * denS;
	return(NOERROR);
}
inline HRESULT MPAInteger::DivU(const MPAInteger& num, const MPAInteger& denB, MPAInteger& rem)	// *this = num / den Ч]Вшrem
{
	MPAInteger&	ans=*this;
	MPAInteger	den;
	HRESULT			hResult;

	if (FAILED(hResult=rem.Value(num))) return(hResult);
	if (FAILED(hResult=den.Value(denB))) return(hResult);
	return(ans.DivU(rem, den, false));
}
inline HRESULT MPAInteger::NaiveDivU(MPAInteger& num, UINT_PTR den)
{
	MPAInteger&	ans=*this;
	UINT_PTR		rem=0;
	UINT			shift=0;
	MPAUDINTBUFF	buf;
	size_t			numN, nLoop;
	HRESULT			hResult;

	ans.Empty();
	if (!den) return(E_INVALIDARG);
	if (num.CmpU(den) < 0) return(NOERROR);								// if (num < den) return(NOERROR);

// (Normalization)
	shift = UINT((bitsLIMB - 1) - ::MPAbsr(den));
	if (shift) {
		den <<= shift;
		if (FAILED(hResult=num.Shl(shift))) return(hResult);
		}
	numN = num.Length();

	if (FAILED(hResult=ans.Reallocate(numN))) return(hResult);
	ans.m_buf.size = numN;
// (Division)
	for(nLoop=numN; nLoop>0; nLoop--) {
		size_t		index=nLoop-1;

		buf.lo = num.m_buf.data[index];
		buf.hi = rem;
		buf.val = ::MPAdivE(buf.val, den, &rem);
		ans.m_buf.data[index] = buf.lo;
		}
	ans.m_sign = num.m_sign;
	ans.Adjust();

// (Denormalization)
	if (shift) {
		rem >>= shift;
		}
// (Remainder)
	if (rem) {
		num.m_buf.data[0] = rem;
		num.m_buf.size = 1;
		}
	else{
		num.Empty();
		}
	return(NOERROR);
}
inline HRESULT MPAInteger::KnuthBinary(MPAInteger& num, MPAInteger& den)
{
	MPAInteger&	ans=*this;
	const size_t	denN=den.Length();
	size_t			shift;
	HRESULT			hResult;

	ans.Empty();
	if (!denN) return(E_INVALIDARG);
	if (num.CmpU(den) < 0) return(NOERROR);								// if (num < den) return(NOERROR);

	if (FAILED(hResult=ans.Secure(num.m_buf.size-den.m_buf.size+1))) return(hResult);
// (Divisor alignment)
	shift = num.BitScanReverse() - den.BitScanReverse();
	if (shift) {
		if (FAILED(hResult=den.Shl(shift))) return(hResult);
		}
// (МЕМ╕ОZ)
	for(;;) {
		if (0 <= num.CmpU(den)) {										// if (rem >= den) {
			::MPAsub(num.m_buf.data, num.m_buf.size, den.m_buf.data, den.m_buf.size);
			num.Adjust();
			if (FAILED(hResult=ans.BitSet(shift))) return(hResult);
			}
		if (!shift--) break;
		den.Shr(1);
		}

	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::KnuthLimb(MPAInteger& num, MPAInteger& den, bool denormalize)
{
	MPAInteger&	ans=*this;
	MPAInteger	sub;
	size_t			numN;
	const size_t	denN=den.Length();
	MPAUDINTBUFF	numT, qhat;
	UINT			shift=0;
	size_t			nLoop;
	HRESULT			hResult;

	ans.Empty();
	if (!denN) return(E_INVALIDARG);
	if (num.CmpU(den) < 0) return(NOERROR);								// if (num < den) return(NOERROR);

// (Normalization)
	shift = UINT((bitsLIMB - 1) - ::MPAbsr(den.m_buf.data[denN-1]));
	if (shift) {
		if (FAILED(hResult=den.Shl(shift))) return(hResult);
		if (FAILED(hResult=num.Shl(shift))) return(hResult);
		}
	numN = num.Length();
	if (FAILED(hResult=ans.Secure(numN+1))) return(hResult);

	const UINT_PTR&	denT1=den.m_buf.data[denN-1];
	const UINT_PTR	denT2=((2 <= denN) ? den.m_buf.data[denN-2] : 0);
// (Calculation of the more significant digits of num/den)
	numT.lo = 0;
	for(nLoop=0; nLoop<=(numN-denN); nLoop++) {
		size_t		index=(numN-1)-nLoop;								// index Б╕ (numN-1)...(denN-1)
		size_t		girder=(numN-denN)-nLoop;							// girder Б╕ (numN-denN)...0

		numT.hi = numT.lo;												// numT = num[index+1] << limb | num[index] 
		numT.lo = num.m_buf.data[index];
// (Estimation of the quotient (q-hat) and correction)
#if 1
		MPAUDINTBUFF	rhat;
		qhat.val = ::MPAdivE(numT.val, denT1, &rhat.hi);				// qhat = floor(numT / denT1), rhat.hi = numT % denT1
		rhat.lo = ((1 <= index) ? num.m_buf.data[index-1] : 0);			// rhat = (numT % denT1) << limb | num[index-1]
		while(0 < ::MPAcmpS(::MPAmulT(qhat.lo, denT2), rhat.val)) {		// while((qhat.lo * denT2) > rhat) {
			qhat.lo--;													// qhat--;
			rhat.val = ::MPAaddR(rhat.val, denT1);						// rhat += denT1;
			if (rhat.hi != 0) break;
			}
#else
		qhat.val = ::MPAdivR(numT.val, denT1);							// qhat = floor(numT / denT1)
#endif
// (Initial approximation)БFsub = den * qhat.lo
		sub.Empty();
		if (qhat.lo) {
			if (FAILED(hResult=sub.Secure(denN+1))) return(hResult);
			::MPAmulV(sub.m_buf.data, den.m_buf.data, denN, qhat.lo);
			sub.Adjust();
// (Adjusting the quotient)
			while(num.CmpU(sub, girder) < 0) {							// while(num < sub(den * qhat)) {
				qhat.lo--;
				::MPAsub(sub.m_buf.data, sub.m_buf.size, den.m_buf.data, denN);
				sub.Adjust();
				}
// (Storing quotient)
			if (sub.m_buf.size) {
				::MPAsub(&num.m_buf.data[girder], (numN-girder), sub.m_buf.data, sub.m_buf.size);
				numT.lo = num.m_buf.data[index];
				}
			ans.m_buf.data[index-(denN-1)] = qhat.lo;
			}
		}
// (Denormalization)
	if (shift) {
		num.Shr(shift);
		if (denormalize) den.Shr(shift);
		}
	else
		num.Adjust();
	ans.Adjust();
	return(NOERROR);
}
inline HRESULT MPAInteger::BurnikelZiegler(MPAInteger& num, MPAInteger& den, bool denormalize)
{
	MPAInteger&	ans=*this;
	MPAInteger	numH, numL, tmp, mul;
	size_t			numN=num.Length();
	const size_t	denN=den.Length();
	size_t			shift=0;
	HRESULT			hResult;

// (Support for Recursive Calls)
	ans.Empty();
	if (!denN) return(E_INVALIDARG);
	if (num.CmpU(den) < 0) return(NOERROR);								// if (num < den) return(NOERROR);
	if (numN <= (denN*2)) return(ans.KnuthLimb(num, den, denormalize));

	shift = UINT((bitsLIMB - 1) - ::MPAbsr(den.m_buf.data[denN-1]));
	if (shift) {
		if (FAILED(hResult=den.Shl(shift))) return(hResult);
		if (FAILED(hResult=num.Shl(shift))) return(hResult);
		numN = num.Length();
		}
// (Segmented division)
	size_t		exp=(((numN - 1) / denN) - 1) * denN;					// exp  Б╕ (numN-(denN*2-Г┐))...0
	for(; exp>0; exp-=denN) {
// (Split dividend)
		if (FAILED(hResult=num.SplitU(numH, numL, exp, true))) return(hResult);
// (Recursively divide upper part)
	    if (FAILED(hResult=tmp.BurnikelZiegler(numH, den, false))) return(hResult);
		if (tmp.m_buf.size) {
// (Initial approximation)
		    if (FAILED(hResult=mul.Mul(tmp, den))) return(hResult);
// (Adjusting the quotient)
			while(num.CmpU(mul, exp) < 0) {								// while(num < (mul * (limb^exp))) {
				::MPAsubV(tmp.m_buf.data, tmp.m_buf.size, 1);
				::MPAsub(mul.m_buf.data, mul.m_buf.size, den.m_buf.data, den.m_buf.size);
				}
			}
// (Storing quotient)
		if (FAILED(hResult=ans.Merge(denN, tmp))) return(hResult);
// (Combine remainder and lower part)
		if (FAILED(hResult=num.Value(numH))) return(hResult);
		if (FAILED(hResult=num.Merge(exp, numL))) return(hResult);
		}
// (Recursively divide lower part)
	if (FAILED(hResult=tmp.BurnikelZiegler(num, den, false))) return(hResult);
	if (FAILED(hResult=ans.Merge(denN, tmp))) return(hResult);
// (Denormalization)
	if (shift) {
		num.Shr(shift);
		if (denormalize) den.Shr(shift);
		}

	return(NOERROR);
}
inline HRESULT MPAInteger::ReciprocalMultiplication(MPAInteger& num, MPAInteger& den)
{
	MPAInteger&	ans=*this;
	MPAInteger	inv, tmp;
	const size_t	numN=num.Length();
	const size_t	denN=den.Length();
	HRESULT			hResult;

	ans.Empty();
	if (!denN) return(E_INVALIDARG);
	if (num.CmpU(den) < 0) return(NOERROR);								// if (num < den) return(NOERROR);

// (Approximate reciprocal)
	if (FAILED(hResult=inv.Reciprocal(den, (numN-denN+1), true))) return(hResult);
// (Initial quotient estimate)
	if (FAILED(hResult=num.Higher(tmp, (numN-denN+1), false))) return(hResult);
	if (FAILED(hResult=ans.Mul(tmp, inv))) return(hResult);
	::MPAshrM(ans.m_buf.data, ans.m_buf.data, ans.m_buf.size, inv.Length(), 0);
	ans.m_buf.size -= inv.Length();
// (Quotient adjustment)
	tmp.Deallocate();
	if (FAILED(hResult=tmp.Mul(ans, den))) return(hResult);				// abs(tmp) = ans * den
	while(tmp.CmpU(num) < 0) {
		int		cmp;

		if (FAILED(hResult=tmp.AddU(den))) return(hResult);				// abs(tmp) += abs(den)
		if (0 < (cmp=tmp.CmpU(num))) {
			if (FAILED(hResult=tmp.SubU(den))) return(hResult);			// abs(tmp) += abs(den)
			break;
			}
		if (FAILED(hResult=ans.AddU(1))) return(hResult);				// abs(ans) += 1;
		if (!cmp) break;
		}
// (Calculate remainder)
	if (FAILED(hResult=num.SubU(tmp))) return(hResult);					// abs(num) -= abs(tmp)

	return(NOERROR);
}

/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
/*                                  ВРВПВЧ                                   */
/*еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее*/
inline HRESULT MPAInteger::pow(UINT_PTR val, UINT_PTR exp)
{
	MPAInteger&	ans=*this;
	MPAInteger	num;
	HRESULT			hResult;

	if (FAILED(hResult=num.Value(val))) return(hResult);
	return(ans.pow(num, exp));
}
inline HRESULT MPAInteger::pow(MPAInteger& val, UINT_PTR exp)
{
	MPAInteger&	ans=*this;
	return(ans.powBinary(val, exp));
}
inline HRESULT MPAInteger::pow(MPAInteger& val, MPAInteger& exp)
{
	MPAInteger&	ans=*this;
	return(ans.powBinary(val, exp));
}
inline HRESULT MPAInteger::powBinary(MPAInteger& num, UINT_PTR exp)
{
	const int		sign=((exp&0x01) ? num.m_sign : 1);
	MPAInteger&	ans=*this;
	MPAInteger	tmp;
	HRESULT			hResult;

	if (FAILED(hResult=ans.Value(1))) return(hResult);
	if (exp) {
		for(;;) {
			if ((exp & 0x01) != 0) {
				if (FAILED(hResult=tmp.Value(ans))) return(hResult);
				if (FAILED(hResult=ans.Mul(tmp, num))) return(hResult);		// ans *= num;
				}
			exp >>= 1;
			if (!exp) break;

			if (FAILED(hResult=tmp.Value(num))) return(hResult);
			if (FAILED(hResult=num.Mul(tmp, tmp))) return(hResult);			// num *= num;
			}
		}

	ans.m_sign = sign;
	return(NOERROR);
}
inline HRESULT MPAInteger::powBinary(MPAInteger& num, MPAInteger& exp)
{
	MPAInteger&	ans=*this;
	MPAInteger	tmp;
	HRESULT			hResult;

	if (FAILED(hResult=ans.Value(1))) return(hResult);
	if (exp.Length()) {
		const int	sign=((exp.m_buf.data[0]&0x01) ? num.m_sign : 1);

		for(;;) {
			if ((exp.m_buf.data[0]&0x01) != 0) {
				if (FAILED(hResult=tmp.Value(ans))) return(hResult);		// tmp = ans
				if (FAILED(hResult=ans.Mul(tmp, num))) return(hResult);		// ans = tmp * num;
				}
			exp.Shr(1);
			if (!exp.m_buf.size) break;
			if (FAILED(hResult=tmp.Value(num))) return(hResult);			// tmp = num
			if (FAILED(hResult=num.Mul(tmp, tmp))) return(hResult);			// num = tmp * num;
			}
		ans.m_sign = sign;
		}

	return(NOERROR);
}


#endif
