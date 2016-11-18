#!/bin/bash

# make audio ports constant, they must never change
sed -i "/^int gen_kernel_numins = /{s/^/const /}" plugins/*/gen_exported.cpp
sed -i "/^int gen_kernel_numouts = /{s/^/const /}" plugins/*/gen_exported.cpp

# change prototype of param functions, no doubles!
sed -i "s/setparameter(CommonState *cself, long index, double value, void *ref)/setparameter(CommonState *cself, long index, t_param value, void *ref)/" plugins/*/gen_exported.cpp plugins/*/gen_exported.h
sed -i "s/getparameter(CommonState *cself, long index, double *value)/getparameter(CommonState *cself, long index, t_param *value)/" plugins/*/gen_exported.cpp plugins/*/gen_exported.h
sed -i "s/create(double sr, long vs)/create(t_param sr, long vs)/" plugins/*/gen_exported.cpp plugins/*/gen_exported.h

# use t_sample instead of forcing doubles
sed -i "s/double /t_sample /" plugins/*/gen_exported.cpp
