#
# Simple Makefile that compiles all .c and .s files in the same folder
#

# If you move this project you can change the directory
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = ../../gbdk/

LCC = $(GBDK_HOME)bin/lcc

# You can uncomment the line below to turn on debug output
# LCC = $(LCC) -debug

# You can set the name of the .gb ROM file here
PROJECTNAME    = pkmnttrs

BINS	    = $(PROJECTNAME).gbc
CSOURCES   := $(wildcard *.c)
ASMSOURCES := $(wildcard *.s)

all:	$(BINS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | sed s/mkdir\ \-p/mkdir/ | grep -v make >> compile.bat

# Compile and link all source files in a single call to LCC
$(BINS):	$(CSOURCES) $(ASMSOURCES)
	$(LCC)  -Wl-yt0x1A -Wl-yo4 -Wl-ya4 -Wm-yC  ../extern/obj/hUGEDriver.o -o $@ $(CSOURCES) $(ASMSOURCES) -Wall -Wextra

clean:
	rm -f *.o *.lst *.map *.gb *.gbc *.ihx *.sym *.cdb *.adb *.asm *.sav

