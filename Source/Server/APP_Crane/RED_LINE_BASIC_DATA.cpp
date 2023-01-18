#include "RED_LINE_BASIC_DATA.h"



using namespace Monitor;


//行车与行车之间的最小间距  从车中心到车中心  //25000mm   25M
//2017.12.5 zhangyuhong add
//C612 同跨行车间的极限距离 = 25米
const long RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES = 25000;


//为了避免临界而给出的补偿量   100mm  
const  long   RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE=100;


//追随的最小拉开距离   27米
const  long   RED_LINE_BASIC_DATA::FOLLOW_MIN_DISTANCE=27000;


RED_LINE_BASIC_DATA :: RED_LINE_BASIC_DATA(void)
{


}



RED_LINE_BASIC_DATA :: ~RED_LINE_BASIC_DATA(void)
{



}


