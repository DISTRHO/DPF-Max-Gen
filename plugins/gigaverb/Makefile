#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = MaGigaverb

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
BUILD_CXX_FLAGS += -Wno-unused-parameter

# --------------------------------------------------------------
# Enable all possible plugin types

all: jack ladspa lv2_dsp vst2 vst3 clap

# --------------------------------------------------------------
