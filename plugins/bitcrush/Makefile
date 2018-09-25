#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = MaBitcrush

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	DistrhoPluginMaxGen.cpp

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Extra flags

BUILD_CXX_FLAGS += -I../common -I../common/gen_dsp

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(BUILD_JACK),true)
ifeq ($(HAVE_JACK),true)
TARGETS += jack
endif
endif

<<<<<<< HEAD
TARGETS += ladspa
=======
ifeq ($(BUILD_LADSPA),true)
TARGETS += ladspa
endif

ifeq ($(BUILD_LV2),true)
>>>>>>> 32c2796b78396662fcc5bfce3bd6a02e8958a44a
TARGETS += lv2_dsp
endif

ifeq ($(BUILD_VST2),true)
TARGETS += vst
endif

all: $(TARGETS)

# --------------------------------------------------------------
