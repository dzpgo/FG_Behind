//��ǰ�汾1.1���ش�仯���Զ��ͷ���Դ
/*statement����resultset�������ַ�ʽ��
1��st.select()�����ʱ��st��û�д���rs�У�����rs��st����Ҫ�����ͷ�
2��st�󶨲���DT_RESULT_SET���󶨵�ʱ�����parameter����st����parameter��(bind_result_set)����  
st[""]���ؽ��resultset�����ʱ��  ��parameter���У�inline operator resultset������as_resultset ()
����new resultset
3����statement��cleanupʱ����ͷ�parameter���󣬶�parameter������ͷ�����������resultset��
*/

//����޸�ʱ��2008-03-20
//�������ʱ��2006-05-08



#if	defined (_MSC_VER) // Microsoft Visual C++
#	define	_CRTDBG_MAP_ALLOC
#endif

// disable following Microsoft Visual C++ warnings
// (most of them will appear in release mode only)
#if defined (_MSC_VER)
#	pragma warning (disable: 4786) // id truncated to '255' chars in the browser info
#	pragma warning (disable: 4290) // C++ exception specification ignored
#	pragma warning (disable: 4710) // function 'xxx' not inlined
#endif

// STD C headers
#include <cstdio>
#include <ctime>
#include <cassert>
#include <cctype>
#include <cmath>
//#include <tchar.h>

#if	defined (_WIN32) // Windows platform
#	include <windows.h>
#endif

#if defined (_MSC_VER) // Microsoft Visual C++
#	include <crtdbg.h>
#endif

// STL headers
#include <iostream>
#include <map>
#include <string>
#include <vector>

#ifndef	ASSERT
#	define	ASSERT	assert
#endif

// Oracle headers
#ifndef	__STDC__
#	define	__STDC__	1
#	include <oci.h>
#	undef	__STDC__
#else
#	include <oci.h>
#endif

// debug memory tracking
#if	defined (_MSC_VER) && defined (_DEBUG)
#	define	new	new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#if	defined (_WIN32) // Windows platform
#	define	SLEEP	Sleep
#else
#   define	SLEEP	sleep 
#endif


// vsnprintf is used in error.cpp
#if	defined (_MSC_VER)
// Microsoft Visual C++ 6.0
#	define	VSNPRINTF	vsnprintf
#elif defined (_MINGW)
// MinGW
#	define	VSNPRINTF	_vsnprintf
#else
// Borland C++ 5.5 (free command-line tools)
#	define	VSNPRINTF	std::vsnprintf
#endif

