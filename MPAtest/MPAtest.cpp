// MPAtest.cpp : コンソール アプリケーション用のエントリ ポイントの定義
//

#include <stdafx.h>
#include <time.h>
#include <MPAInteger.h>

static const int					s_base=10;

static LARGE_INTEGER				s_frequency;
static TCHAR						s_str[0x1000000];

HRESULT OnShiftTest(void)
{
	const size_t	numN=10;
	MPAInteger		num, val;
	HRESULT			hResult;

	printf(TEXT("SHIFT TEST\n"));
	if (FAILED(hResult=num.Random(numN * sizeof(UINT_PTR)))) return(hResult);

	if (FAILED(hResult=num.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num:%s\n"), s_str);

	if (FAILED(hResult=val.Value(num))) return(hResult);
	if (FAILED(hResult=val.Shl(1))) return(hResult);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num<<1:%s\n"), s_str);

	if (FAILED(hResult=val.Value(num))) return(hResult);
	if (FAILED(hResult=val.Shl(4))) return(hResult);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num<<4:%s\n"), s_str);

	if (FAILED(hResult=val.Value(num))) return(hResult);
	if (FAILED(hResult=val.Shl(32))) return(hResult);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num<<32:%s\n"), s_str);

	if (FAILED(hResult=val.Value(num))) return(hResult);
	val.Shr(1);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num>>1:%s\n"), s_str);

	if (FAILED(hResult=val.Value(num))) return(hResult);
	val.Shr(4);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num>>4:%s\n"), s_str);

	if (FAILED(hResult=val.Value(num))) return(hResult);
	val.Shr(32);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num>>32:%s\n"), s_str);

	printf(TEXT("\n"));
	return(NOERROR);
}

HRESULT OnAddTest(void)
{
	const size_t	numN=10;
	MPAInteger		num, val;
	int				i;
	HRESULT			hResult;

	printf(TEXT("ADD TEST\n"));
	if (FAILED(hResult=num.Random(numN * sizeof(UINT_PTR)))) return(hResult);

	if (FAILED(hResult=num.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num:%s\n"), s_str);

	if (FAILED(hResult=val.Value(num))) return(hResult);
	if (FAILED(hResult=val.Add(num))) return(hResult);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("val=num+num:%s\n"), s_str);

	val.Shr(1);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("val>>1:%s\n"), s_str);

	val.Empty();
	for(i=0; i<4; i++) {
		if (FAILED(hResult=val.Add(num))) return(hResult);
		}
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("val+=num %d time:%s\n"), i, s_str);

	val.Shr(2);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("val>>2:%s\n"), s_str);

	printf(TEXT("\n"));
	return(NOERROR);
}

HRESULT OnSubTest(void)
{
	const size_t	numN=10;
	const size_t	valN=8;
	MPAInteger		num, val, tmp;
	HRESULT			hResult;

	printf(TEXT("SUB TEST\n"));
	if (FAILED(hResult=num.Random(numN * sizeof(UINT_PTR)))) return(hResult);
	if (FAILED(hResult=val.Random(valN * sizeof(UINT_PTR)))) return(hResult);

	if (FAILED(hResult=num.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num:%s\n"), s_str);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("val:%s\n"), s_str);

	if (FAILED(hResult=tmp.Value(num))) return(hResult);
	if (FAILED(hResult=tmp.Sub(val))) return(hResult);
	if (FAILED(hResult=tmp.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("tmp=num-val:%s\n"), s_str);

	if (FAILED(hResult=tmp.Add(val))) return(hResult);
	if (FAILED(hResult=tmp.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("tmp+val1:%s\n"), s_str);

	printf(TEXT("\n"));
	return(NOERROR);
}

HRESULT OnMulTest(void)
{
	const size_t	numN=10;
	const size_t	valN=8;
	MPAInteger		num, val, ans;
	HRESULT			hResult;

	printf(TEXT("MUL TEST\n"));
	if (FAILED(hResult=num.Random(numN * sizeof(UINT_PTR)))) return(hResult);
	if (FAILED(hResult=val.Random(valN * sizeof(UINT_PTR)))) return(hResult);

	if (FAILED(hResult=num.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num:%s\n"), s_str);
	if (FAILED(hResult=val.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("val:%s\n"), s_str);

	if (FAILED(hResult=ans.Mul(num, val))) return(hResult);
	if (FAILED(hResult=ans.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num*val:%s\n"), s_str);

	printf(TEXT("\n"));
	return(NOERROR);
}

HRESULT OnDivTest(void)
{
	const size_t	numN=10;
	const size_t	denN=8;
	MPAInteger		num, den, ans, rem;
	HRESULT			hResult;

	printf(TEXT("DIV TEST\n"));
	if (FAILED(hResult=num.Random(numN * sizeof(UINT_PTR)))) return(hResult);
	if (FAILED(hResult=den.Random(denN * sizeof(UINT_PTR)))) return(hResult);

	if (FAILED(hResult=num.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num:%s\n"), s_str);
	if (FAILED(hResult=den.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("den:%s\n"), s_str);

	if (FAILED(hResult=ans.Div(num, den, rem))) return(hResult);
	if (FAILED(hResult=ans.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num/den:%s\n"), s_str);
	if (FAILED(hResult=rem.GetString(s_str, _countof(s_str), s_base))) return(hResult);
	printf(TEXT("num%%den:%s\n"), s_str);

	printf(TEXT("\n"));
	return(NOERROR);
}

int main(int argc, char* argv[])
{
	HRESULT		hResult;

	::srand(time(NULL));
	if (!::QueryPerformanceFrequency(&s_frequency)) return(-1);

	if (FAILED(hResult=OnShiftTest())) return(hResult);
	if (FAILED(hResult=OnAddTest())) return(hResult);
	if (FAILED(hResult=OnSubTest())) return(hResult);
	if (FAILED(hResult=OnMulTest())) return(hResult);
	if (FAILED(hResult=OnDivTest())) return(hResult);

	return 0;
}

