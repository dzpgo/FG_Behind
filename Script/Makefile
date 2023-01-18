# **********************************************************************
#
# Copyright (c) 2003-2010 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

SUBDIRS		= ../Source/New_Server/ORM_lib \
                          ../Source/New_Server/Test_APP \
			  ../Source/New_Server/CheckSum_DataOrganization_dll
EVERYTHING		= all depend clean install 
$(EVERYTHING)::
	@for subdir in $(SUBDIRS); \
	do \
		if test -d $$subdir ; \
		then \
			echo "making $@ in $$subdir"; \
			( cd $$subdir && $(MAKE) $@ ) || exit 1; \
		fi; \
	done
