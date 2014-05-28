# name of your application
export APPLICATION = hello-world

# If no BOARD is found in the environment, use this default:
export BOARD ?= msp-ts430pm64

# This has to be the absolute path to the RIOT base directory:
export RIOTBASE ?= $(CURDIR)/../..

# Change this to 0 show compiler invocation lines by default:
export QUIET ?= 0

export CFLAGS += -g -gdwarf-2
export ASFLAGS += -g --gdwarf-2

#USEMODULE += sixlowpan
#USEMODULE += ieee802154
#USEMODULE += cc110x_ng
#USEMODULE += net_if
USEMODULE += vtimer
USEMODULE += auto_init

include $(RIOTBASE)/Makefile.include
