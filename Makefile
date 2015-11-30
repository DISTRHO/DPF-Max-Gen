#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

include Makefile.mk

all: plugins gen

# --------------------------------------------------------------

plugins:
	$(MAKE) all -C plugins/bitcrush
	$(MAKE) all -C plugins/freeverb
	$(MAKE) all -C plugins/gigaverb
	$(MAKE) all -C plugins/pitchshift
	$(MAKE) all -C plugins/shiroverb
	$(MAKE) all -C plugins/pitchotto

gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/bitcrush
	$(MAKE) clean -C plugins/freeverb
	$(MAKE) clean -C plugins/gigaverb
	$(MAKE) clean -C plugins/pitchshift
	$(MAKE) clean -C plugins/shiroverb
	$(MAKE) clean -C plugins/pitchotto

# --------------------------------------------------------------

.PHONY: plugins
