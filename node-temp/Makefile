# Default Makefile, for host native GNRC-based networking

# name of your application
APPLICATION = gcoap

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

BOARD_INSUFFICIENT_MEMORY := chronos msb-430 msb-430h nucleo32-f031 nucleo32-f042 \
                             nucleo32-l031 nucleo-f030 nucleo-f334 nucleo-l053 \
                             stm32f0discovery telosb weio wsn430-v1_3b wsn430-v1_4 z1

# Must read nordic_softdevice_ble package before nanocoap package. However,
# can't read it explicitly here because it is read later, as a dependency for
# the nrf52dk board.
BOARD_BLACKLIST := nrf52dk

## Uncomment to redefine port, for example use 61616 for RFC 6282 UDP compression.
#GCOAP_PORT = 5683
#CFLAGS += -DGCOAP_PORT=$(GCOAP_PORT)

## Uncomment to redefine request token length, max 8.
#GCOAP_TOKENLEN = 2
#CFLAGS += -DGCOAP_TOKENLEN=$(GCOAP_TOKENLEN)

FEATURES_REQUIRED = periph_i2c
USEPKG += nanocoap
# Required by nanocoap, but only due to issue #5959.
USEMODULE += posix

# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Specify the mandatory networking modules
USEMODULE += gnrc_ipv6_router_default
USEMODULE += gnrc_sock_udp
USEMODULE += gcoap
# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_icmpv6_echo

# Required by gcoap example
USEMODULE += od
USEMODULE += fmt
# Add also the shell, some shell commands
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += tmp006
USEMODULE += xtimer

TEST_TMP006_I2C       ?= I2C_DEV\(0\)
TEST_TMP006_ADDR      ?= 0x41
TEST_TMP006_CONFIG_CR ?= TMP006_CONFIG_CR_DEF

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP
CFLAGS += -DTEST_TMP006_I2C=$(TEST_TMP006_I2C)
CFLAGS += -DTEST_TMP006_ADDR=$(TEST_TMP006_ADDR)
CFLAGS += -DTEST_TMP006_CONFIG_CR=$(TEST_TMP006_CONFIG_CR)

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
