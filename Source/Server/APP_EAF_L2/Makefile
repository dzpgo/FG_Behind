top_srcdir = ${IPLATURE}

PROGRAM   :=  ../../../Bin/APP_EAF_L2
SRCDIRS   := .
include $(IPLATURE)/source/iplature_exegeneral 

CXXFLAGS  +=  -I. -I../../../Include/CommonH 
CXXFLAGS  +=  -I../../../Include/iPlature64

LINKWITH  :=  -L $(IPLATURE)/library/ -lPowerTranser $(LINKWITH)

