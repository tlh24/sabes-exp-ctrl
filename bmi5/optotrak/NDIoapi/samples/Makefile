###############################################################################
#   Platform specific variables for Linux builds.
#
#   Flags:
#       -ansi  	ANSI compatibility.
#       -O0     Disable all optimizations.
#
###############################################################################

EXE_EXT  =

all: $(EXES) $(CERTUS_EXES) $(YOUR_APPS)

# target definitions *******************************************************

CERTUS_AUX = certus_aux.o
OT_AUX = ot_aux.o

YOUR_APPS=

EXES=\
	sample1$(EXE_EXT)  sample2$(EXE_EXT)  sample3$(EXE_EXT)  sample4$(EXE_EXT)  \
	sample5$(EXE_EXT)  sample6$(EXE_EXT)  sample7$(EXE_EXT)  sample8$(EXE_EXT)  \
	sample9$(EXE_EXT)  sample10$(EXE_EXT)  sample11$(EXE_EXT)  sample12$(EXE_EXT) \
	sample13$(EXE_EXT)  sample14$(EXE_EXT)  sample15$(EXE_EXT)  sample16$(EXE_EXT)  \
	sample17$(EXE_EXT)  sample18$(EXE_EXT)  sample19$(EXE_EXT)  sample20$(EXE_EXT)  \
	sample21$(EXE_EXT)  sample22$(EXE_EXT)  \
	optsetup$(EXE_EXT)  download$(EXE_EXT)  register$(EXE_EXT)  align$(EXE_EXT)

CERTUS_EXES=\
	certus_sample$(EXE_EXT)  \
	certus_sample1$(EXE_EXT)  certus_sample2$(EXE_EXT)  certus_sample3$(EXE_EXT)  certus_sample4$(EXE_EXT)  \
	certus_sample11$(EXE_EXT)  certus_sample12$(EXE_EXT)  certus_sample13$(EXE_EXT)  certus_sample14$(EXE_EXT) \
	certus_sample15$(EXE_EXT)  certus_sample16$(EXE_EXT)  certus_sample17$(EXE_EXT)  certus_sample18$(EXE_EXT) \
	certus_sample19$(EXE_EXT) certus_sample20$(EXE_EXT)

# dependencies definition ***********************************************

$(EXES) $(CERTUS_EXES) $(YOUR_APPS): $(OT_AUX) $(CERTUS_AUX)

# makefile settings ******************************************************

.SUFFIXES:
.SUFFIXES: .c .o

CFLAGS	+= \
	-O0 \
	-g3 \
	-W \
	-Wimplicit-int  \
	-Wbad-function-cast \
	-Wparentheses \
	-Wmissing-braces \
	-Wreturn-type \
	-Wswitch -Wtrigraphs \
	-Wunused-function \
	-Wunused-label \
	-Wfloat-equal \
	-Wcast-align \
	-Wmissing-prototypes \
	-Wmissing-declarations \
	-Wunreachable-code \
	-Wredundant-decls \
	-Winline \
	-Wundef \
	-Wno-unused-parameter \
	-Wno-unused-value \
	-DPLATFORM_LINUX \
	-I ../ndlib/include -I ./ 
# 	-Wl,--rpath=/opt/eglibc/lib \
# 	-Wl,--rpath-link=/opt/eglibc/lib \
# 	-Wl,--dynamic-linker=/opt/eglibc/lib/ld-linux-x86-64.so.2
#	-I/opt/eglibc/include 

LDFLAGS = -lm -loapi -ldl

# makefile rules ***********************************************************

.PHONY : all clean cleanall install uninstall

all: $(EXES) $(CERTUS_EXES) $(YOUR_APPS)

cleanall: clean
clean:
	-rm -f $(EXES)
	-rm -f $(CERTUS_EXES)
	-rm -f *.o

install:
	cp ../ndlib/lib/liboapi.so /usr/local/lib
	ldconfig
	-touch  ../ndigital/realtime/system.nif
	-chmod 666 ../ndigital/realtime/system.nif
	-touch ../ndigital/realtime/standard.cam
	-chmod 666 ../ndigital/realtime/standard.cam
	-chmod 777 ../ndigital/logs
	-chmod 755 ../ndigital/settings
	-chmod 755 ../ndigital/rigid
	-chmod 755 ../ndigital/programs
	-chmod 755 ../ndigital/realtime

uninstall:
	rm /usr/local/lib/liboapi.so
	ldconfig
