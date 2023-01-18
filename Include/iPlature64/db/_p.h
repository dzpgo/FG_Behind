//当前版本1.1有重大变化，自动释放资源
/*statement产生resultset，有两种方式：
1、st.select()，这个时候st并没有传入rs中，所以rs和st都需要单独释放
2、st绑定参数DT_RESULT_SET，绑定的时候产生parameter对象将st传入parameter中(bind_result_set)，当  
st[""]返回结果resultset，这个时候  在parameter中有：inline operator resultset，调用as_resultset ()
其中new resultset
3、在statement的cleanup时候会释放parameter对象，而parameter对象会释放由它产生的resultset。
*/

//最后修改时间2008-03-20
//最初开发时间2006-05-08



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

