#ifndef _WINtrial_H_
#define _WINtrial_H_

#include <windows.h>
#include <stdlib.h>
#include <tchar.h>

/*****************************************************************************/
/*                             プロトタイプ定義                              */
/*****************************************************************************/
#define isMAX(a, b)					(((a) > (b)) ? (a) : (b)) 
#define isMIN(a, b)					(((a) < (b)) ? (a) : (b)) 
#define memOPTIMUM(n)				((((size_t)(n) / sizeof(size_t)) + 1) * sizeof(size_t))

#if (_MSC_VER <= 1310)											// Visual C++ 7.1 (Visual Studio.NET 2003)
#define _countof(array)				(sizeof(array)/sizeof(array[0]))
#endif	// _MSC_VER <= 1310

typedef ULONGLONG					QWORD;


#endif

