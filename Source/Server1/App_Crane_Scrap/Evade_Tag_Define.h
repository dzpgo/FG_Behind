

#pragma once 
#ifndef   _Evade_Tag_Define_ 
#define   _Evade_Tag_Define_ 

#include "DataAccess.h"
#include "log4cplus/LOG.h"

namespace Monitor
{




	class  Evade_Tag_Define
	{





	public:
		Evade_Tag_Define( void );
		~Evade_Tag_Define( void );




	public:


		


	public:
		static string  getTagName_Evade_Request(string craneNO) ;

		static string  getTagName_Evade_Cancel(string sender) ;
	
	};



}
#endif