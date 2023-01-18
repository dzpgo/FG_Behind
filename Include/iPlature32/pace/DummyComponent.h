/**
 * @file   :DummyComponent.h
 * 
 * @brief  : dummy component implementation
 * 
 * 
 * @version :1.0
 * @date    :2006年03月31日 11时50分47秒 CST
 * @revision: $Id: DummyComponent.h,v 1.1 2006/04/03 07:54:07 yinyunqiao Exp $  
 * 
 * @author  :Yin Yun Qiao(YYQ,yinyunqiao@gmail.com)
 * @company :Baosteel,Co,ltd.
 * 
 */
#ifndef __DUMMYCOMPONENT__
#define __DUMMYCOMPONENT__

//#include "stdafx.h"

//#include <pace/pace.h>
#include <pace/Component.h>
namespace iPlature
	{
	class DummyComponent : public iPlature::Component
		{
		public:
			virtual int start();
			virtual ~DummyComponent();
		};
	}
#endif



