##############################################################################
# Main makefile for basic_modem
##############################################################################
-include app_makefiles/app_printing.mk
-include app_makefiles/app_options.mk


#-----------------------------------------------------------------------------
# default action: print help
#-----------------------------------------------------------------------------
help:
	$(call echo_help_b, "Available TARGETs:	sx1261	sx1262	sx1268")
	$(call echo_help, "")
	$(call echo_help_b, "-------------------------------- Clean -------------------------------------")
	$(call echo_help, " * make clean_<TARGET>             : clean basic_modem hal and lib for a given target")
	$(call echo_help, " * make clean_all                  : clean all")
	$(call echo_help, " * make clean_app                  : clean basic_modem hal")
	$(call echo_help, "")
	$(call echo_help_b, "----------------------------- Compilation ----------------------------------")
	$(call echo_help, " * make <TARGET>                   : build basic_modem hal and lib on a given target")
	$(call echo_help, "")
	$(call echo_help_b, "---------------------------- All inclusive ---------------------------------")
	$(call echo_help, " * make full_<TARGET>              : clean and build hal on a given target")
	$(call echo_help, "")
	$(call echo_help_b, "---------------------- Optional build parameters ---------------------------")
	$(call echo_help, " * BOARD=xxx                       : choose which mcu board will be used:(default is NUCLEO_U073)")
	$(call echo_help, " *                                  - NUCLEO_U073")
	$(call echo_help, " * APP_TRACE=yes/no                : choose to enable or disable application trace print (default: trace is ON)")
	$(call echo_help_b, "-------------------- Optional makefile parameters --------------------------")
	$(call echo_help, " * MULTITHREAD=no                  : Disable multithreaded build")
	$(call echo_help, " * VERBOSE=yes                     : Increase build verbosity")
	$(call echo_help, " * SIZE=yes                        : Display size for all objects")
	$(call echo_help, " * DEBUG=yes                       : Compile library and application with debug symbols")



#-----------------------------------------------------------------------------
# Makefile include selection
#-----------------------------------------------------------------------------
ifeq ($(TARGET_RADIO),sx1261)
-include app_makefiles/app_sx126x.mk
endif

ifeq ($(TARGET_RADIO),sx1262)
-include app_makefiles/app_sx126x.mk
endif

ifeq ($(TARGET_RADIO),sx1268)
-include app_makefiles/app_sx126x.mk
endif

#-----------------------------------------------------------------------------
-include app_makefiles/app_common.mk

.PHONY: clean_all help

#-----------------------------------------------------------------------------
# Clean
#-----------------------------------------------------------------------------
clean_all: clean_app

clean_sx1261:
	$(MAKE) clean_target TARGET_RADIO=sx1261

clean_sx1262:
	$(MAKE) clean_target TARGET_RADIO=sx1262

clean_sx1268:
	$(MAKE) clean_target TARGET_RADIO=sx1268

clean:
	$(MAKE) clean_target

clean_app:
	-rm -rf $(APPBUILD_ROOT)*


#-----------------------------------------------------------------------------
# Application Compilation
#-----------------------------------------------------------------------------

#-- Generic -------------------------------------------------------------------
app:
ifeq ($(TARGET_RADIO),nc)
	$(call echo_error,"No radio selected! Please specified the target radio using TARGET_RADIO=radio_name option")
else
	$(MAKE) app_build
endif

#-- SX1261 -------------------------------------------------------------------
sx1261:
	$(MAKE) app TARGET_RADIO=sx1261 $(MTHREAD_FLAG)

full_sx1261:
	$(MAKE) clean_target TARGET_RADIO=sx1261
	$(MAKE) app TARGET_RADIO=sx1261 $(MTHREAD_FLAG)

#-- SX1262 -------------------------------------------------------------------
sx1262:
	$(MAKE) app TARGET_RADIO=sx1262 $(MTHREAD_FLAG)

full_sx1262:
	$(MAKE) clean_target TARGET_RADIO=sx1262
	$(MAKE) app TARGET_RADIO=sx1262 $(MTHREAD_FLAG)

#-- SX1268 -------------------------------------------------------------------
sx1268:
	$(MAKE) app TARGET_RADIO=sx1268 $(MTHREAD_FLAG)

full_sx1268:
	$(MAKE) clean_target TARGET_RADIO=sx1268
	$(MAKE) app TARGET_RADIO=sx1268 $(MTHREAD_FLAG)
