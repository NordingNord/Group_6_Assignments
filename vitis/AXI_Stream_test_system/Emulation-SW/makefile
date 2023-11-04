#
# This file was created by Xilinx Vitis tool.
#


#
# tools
#

RM = rm -f
RMDIR = rm -rf


XILINX_VITIS ?= /tools/Xilinx/Vitis/2020.2
VPP ?= ${XILINX_VITIS}/bin/v++


VITIS_PLATFORM = u96v2_sbc_mp4d
VITIS_PLATFORM_DIR = /home/frank/Documents/Git/Group_6_Assignments/vitis/u96v2_sbc_mp4d/export/u96v2_sbc_mp4d
VITIS_PLATFORM_PATH = $(VITIS_PLATFORM_DIR)/u96v2_sbc_mp4d.xpfm


#
# variables
#


#
# primary build targets
#

all: package

package:
	-@echo Package not supported, if the system project is in Emulation Target, and only Baremetal Or Embedded Linux Applications present

clean:
	$(RMDIR) ./package.build
	${RMDIR} package

.PHONY: all package clean


