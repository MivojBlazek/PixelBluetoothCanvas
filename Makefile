# 
# PixelNetCanvas
#
# File: Makefile
#
# Description: Makefile to compile and run program on Linux.
# 
# Author: Michal Blažek
#

PROJECT_NAME=PixelNetCanvas
SOURCE_DIR=src/
BUILD_DIR=build/
PROJECT=$(SOURCE_DIR)$(PROJECT_NAME)
BINARY=$(BUILD_DIR)$(PROJECT_NAME)

compile: 
	qmake $(PROJECT).pro -o $(BUILD_DIR)Makefile
	$(MAKE) -C $(BUILD_DIR)

all: compile run

run:
	$(BINARY)

clean:
	rm -rf $(BUILD_DIR)