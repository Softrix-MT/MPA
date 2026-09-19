#ifndef _MPAHRESULT_H_
#define _MPAHRESULT_H_
#include  <wtypes.h>

class MPAHRESULT {
	public:
		HRESULT						hResult;
	public:
									MPAHRESULT(HRESULT h) { hResult=h; };
};

#endif	// _MPAHRESULT_H_

