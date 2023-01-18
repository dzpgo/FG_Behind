#ifndef _IPLATURE_INVALID_VALUE_H_
#define _IPLATURE_INVALID_VALUE_H_

namespace iPlature
{
	static int IPLATURE_INVALID_VALUE_WORK[2]={0,128};	//0,0x80

	const short I2_INV=0x8000;
	const int I_INV=0x80000000;
#ifndef __unix__
	const __int64 I8_INV=0x8000000000000000;
#endif
	const float F_INV=*((float *)(&IPLATURE_INVALID_VALUE_WORK[1]));
	const double D_INV=*((double *)IPLATURE_INVALID_VALUE_WORK);
}


#endif //_IPLATURE_INVALID_VALUE_H_
