top_srcdir = ${IPLATURE}

PROGRAM   :=  ../../../Bin/APP_SAFE_PLC
SRCDIRS   := .
include $(IPLATURE)/source/iplature_exegeneral

CXXFLAGS  +=  -I. -I../../../Include/CommonH 
CXXFLAGS  +=  -I../../../Include/iPlature64

LINKWITH  := -L ${IXCOMPCS}/Library -liXcomTCP2 -lXmlRpc -lCommonLibrary -lboost_thread -lTinyXml -lCppSQLite3 -ldl -lpthread -lrt $(LINKWITH)
LINKWITH  := -L ${IXCOMPCS}/Library  -lLOG -llog4cplus -lLic  -lutility $(LINKWITH)

LINKWITH  :=  -L $(IPLATURE)/library/ -ltinyxml -lPowerTranser $(LINKWITH)


