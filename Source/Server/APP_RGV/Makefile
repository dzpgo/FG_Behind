top_srcdir = ${IPLATURE}

PROGRAM   :=  ../../../Bin/APP_RGV
SRCDIRS   := .
include $(IPLATURE)/source/iplature_exegeneral

CXXFLAGS  +=  -I. -I../../../Include/CommonH 
CXXFLAGS  +=  -I../../../Include/json 
CXXFLAGS  +=  -I../../../Include/iPlature64

LINKWITH :=  -L $(IPLATURE)/library/ -ltinyxml -lPowerTranser $(LINKWITH)

LINKWITH :=  -L ../../../Library/json -ljson $(LINKWITH)


