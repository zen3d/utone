.PHONY: all clean install docs bootstrap util

default: all

VERSION = 0.0.1

INTERMEDIATES_PREFIX ?= .
PREFIX ?= /usr/local

LIBUTONE = $(INTERMEDIATES_PREFIX)/libutone.a
UTONEO = $(INTERMEDIATES_PREFIX)/utone.o
MODDIR = $(INTERMEDIATES_PREFIX)/modules
HDIR = $(INTERMEDIATES_PREFIX)/h
UTILDIR = $(INTERMEDIATES_PREFIX)/util
LIBDIR = $(INTERMEDIATES_PREFIX)/lib


ifndef CONFIG
CONFIG = $(INTERMEDIATES_PREFIX)/config.mk
endif

HPATHS += $(addprefix h/, $(addsuffix .h, $(MODULES)))
CPATHS += $(addprefix modules/, $(addsuffix .c, $(MODULES)))
MPATHS += $(addprefix $(MODDIR)/, $(addsuffix .o, $(MODULES)))

include $(CONFIG)

ifeq ($(USE_DOUBLE), 1)
CFLAGS+=-DUSE_DOUBLE
UTFLOAT=double
else
UTFLOAT=float
endif

CFLAGS += -DSP_VERSION=$(VERSION) -O3 -DUTFLOAT=${UTFLOAT} #-std=c99
CFLAGS += -I$(INTERMEDIATES_PREFIX)/h -Ih -I/usr/local/include -fPIC
UTIL += $(INTERMEDIATES_PREFIX)/util/wav2smp

$(INTERMEDIATES_PREFIX) \
$(INTERMEDIATES_PREFIX)/h \
$(INTERMEDIATES_PREFIX)/modules \
$(INTERMEDIATES_PREFIX)/util \
$(PREFIX)/include \
$(PREFIX)/lib \
$(PREFIX)/share/doc/utone:
	mkdir -p $@

$(LIBUTONE): $(MPATHS) $(LPATHS) | $(INTERMEDIATES_PREFIX)
	$(AR) rcs $@ $(MPATHS) $(LPATHS)

$(HDIR)/utone.h: $(HPATHS) | $(INTERMEDIATES_PREFIX)/h
	echo "#ifndef UTONE_H" >> $@
ifdef USE_DOUBLE
	echo "#define USE_DOUBLE" >> $@
endif
	echo "#define UTONE_H" >> $@
	cat $(HPATHS) >> $@
	echo "#endif" >> $@

$(HDIR)/ut_base.h: h/base.h 
	>$@
	echo "#ifndef UTONE_H" >> $@
ifdef USE_DOUBLE
	echo "#define USE_DOUBLE" >> $@
endif
	echo "#define UTONE_H" >> $@
	cat $< >> $@
	echo "#endif" >> $@

$(MODDIR)/%.o: modules/%.c h/%.h $(HDIR)/utone.h | $(MODDIR)
	$(CC) -Wall $(CFLAGS) -c -static $< -o $@

$(UTONEO): $(MPATHS) $(LPATHS) | $(INTERMEDIATES_PREFIX)
	$(CC) $(CFLAGS) -c -combine $(CPATHS) -o $@

$(INTERMEDIATES_PREFIX)/config.mk: config.def.mk | $(INTERMEDIATES_PREFIX)
	cp $< $@

$(UTILDIR)/wav2smp: util/wav2smp.c | $(UTILDIR)
	$(CC) $(CFLAGS) -L/usr/local/lib $< -lsndfile -o $@

stretcher: $(UTILDIR)/stretcher

$(UTILDIR)/stretcher: util/stretcher.c | $(UTILDIR)
	$(CC) $(CFLAGS) -L/usr/local/lib $< -L. -lutone -lsndfile -lm -o $@

$(INTERMEDIATES_PREFIX)/ut_dict.lua: | $(INTERMEDIATES_PREFIX)
	cat modules/data/*.lua > $@

bootstrap:
	util/module_bootstrap.sh $(MODULE_NAME)

docs:
	export INTERMEDIATES_PREFIX=$(INTERMEDIATES_PREFIX) && util/gendocs.sh

all: $(INTERMEDIATES_PREFIX)/config.mk \
	$(INTERMEDIATES_PREFIX)/libutone.a \
	$(INTERMEDIATES_PREFIX)/ut_dict.lua \
	$(HDIR)/ut_base.h

util: $(UTIL)

install: \
	$(INTERMEDIATES_PREFIX)/h/utone.h \
	$(INTERMEDIATES_PREFIX)/h/ut_base.h \
	$(INTERMEDIATES_PREFIX)/libutone.a | \
		$(PREFIX)/include \
		$(PREFIX)/lib
	install $(HDIR)/utone.h $(PREFIX)/include/
	install $(HDIR)/ut_base.h $(PREFIX)/include/
	install $(LIBUTONE) $(PREFIX)/lib/

clean:
	rm -rf $(HDIR)/utone.h
	rm -rf $(INTERMEDIATES_PREFIX)/docs
	rm -rf $(INTERMEDIATES_PREFIX)/gen_noise
	rm -rf $(INTERMEDIATES_PREFIX)/libutone.a
	rm -rf $(INTERMEDIATES_PREFIX)/utone.c
	rm -rf $(INTERMEDIATES_PREFIX)/ut_dict.lua
	rm -rf $(LPATHS)
	rm -rf $(MPATHS)
	rm -rf $(UTIL)
	rm -rf $(UTILDIR)/wav2smp.dSYM
	rm -rf $(HDIR)/ut_base.h
