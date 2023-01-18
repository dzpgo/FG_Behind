#pragma once
#include <pace/pace.h>

namespace iPlature{

	class ConnectWrapper
	{
	public:
		ConnectWrapper();
		~ConnectWrapper();
		static void updateConnect(const string& ConnectName,int ConnectStatus);
	};

}