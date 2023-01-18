top_srcdir = ${IPLATURE}

PROGRAM   :=  ../../../Bin/APP_Crane_4_6
SRCDIRS   := .
include ../../../Script/iplature_exegeneral
CXXFLAGS  +=  -I. -I../libProductLineAndCrane -I../../../Include/YardMap_dll -I../../../Include/CommonH -I../../../Include/InterfaceMessage_lib -I../../../Include/ORM_lib -I../../../Include/CraneSchedule_dll
CXXFLAGS  +=  -I../../../Include/CLTS -I../../../Include/CLTS/Slice
CXXFLAGS  +=  -I../../../python2.7/include/python2.7
LINKWITH  :=  -L ../../../Library/CLTS -lProductLineAndCrane-64 -lInterfaceMessage_lib -lCltsSlice-64 -lCLTS-64 $(LINKWITH)
LINKWITH  :=  -L ../../../Library/CLTS -lORM_lib $(LINKWITH)
LINKWITH  :=  -L ../../../Library/CLTS -lYardMap_dll -lCraneSchedule_dll $(LINKWITH)
LINKWITH  +=  -L ../../../python2.7/lib/ -lpython2.7 -lpthread -ldl -lutil -Xlinker -export-dynamic