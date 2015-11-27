#include "gen_exported.h"

namespace gen_exported {


/*******************************************************************************************************************
Copyright (c) 2012 Cycling '74

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/


// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State { 
	CommonState __commonstate;
	Delay m_delay_12;
	Delay m_delay_11;
	Delta m_delta_22;
	Delta m_delta_38;
	Delta m_delta_41;
	Delta m_delta_31;
	Delta m_delta_28;
	Delta m_delta_25;
	Delta m_delta_44;
	Delta m_delta_35;
	Phasor m_phasor_34;
	Phasor m_phasor_21;
	Sah m_sah_23;
	Sah m_sah_27;
	Sah m_sah_42;
	Sah m_sah_26;
	Sah m_sah_24;
	Sah m_sah_43;
	Sah m_sah_36;
	Sah m_sah_29;
	Sah m_sah_40;
	Sah m_sah_37;
	Sah m_sah_30;
	Sah m_sah_39;
	Sah m_sah_32;
	Sah m_sah_33;
	Sah m_sah_46;
	Sah m_sah_45;
	double m_history_5;
	double m_history_6;
	double m_history_7;
	double samples_to_seconds;
	double m_history_4;
	double m_history_2;
	double m_history_3;
	double samplerate;
	double m_y_1;
	double m_history_9;
	double m_history_8;
	double m_mix_13;
	double m_y_10;
	double m_resonance_19;
	double m_window_20;
	double m_window_17;
	double m_cutoff_18;
	double m_ratio_15;
	double m_blur_14;
	double m_ratio_16;
	int vectorsize;
	int __exception;
	// re-initialize all member variables;
	inline void reset(double __sr, int __vs) { 
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_y_1 = 0;
		m_history_2 = 0;
		m_history_3 = 0;
		m_history_4 = 0;
		m_history_5 = 0;
		m_history_6 = 0;
		m_history_7 = 0;
		m_history_8 = 0;
		m_history_9 = 0;
		m_y_10 = 0;
		m_delay_11.reset("m_delay_11", 96000);
		m_delay_12.reset("m_delay_12", 96000);
		m_mix_13 = 1;
		m_blur_14 = 0.01;
		m_ratio_15 = 0.5;
		m_ratio_16 = 2;
		m_window_17 = 100;
		m_cutoff_18 = 3000;
		m_resonance_19 = 0;
		m_window_20 = 100;
		samples_to_seconds = (1 / samplerate);
		m_phasor_21.reset(0);
		m_delta_22.reset(0);
		m_sah_23.reset(0);
		m_sah_24.reset(0);
		m_delta_25.reset(0);
		m_sah_26.reset(0);
		m_sah_27.reset(0);
		m_delta_28.reset(0);
		m_sah_29.reset(0);
		m_sah_30.reset(0);
		m_delta_31.reset(0);
		m_sah_32.reset(0);
		m_sah_33.reset(0);
		m_phasor_34.reset(0);
		m_delta_35.reset(0);
		m_sah_36.reset(0);
		m_sah_37.reset(0);
		m_delta_38.reset(0);
		m_sah_39.reset(0);
		m_sah_40.reset(0);
		m_delta_41.reset(0);
		m_sah_42.reset(0);
		m_sah_43.reset(0);
		m_delta_44.reset(0);
		m_sah_45.reset(0);
		m_sah_46.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) { 
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		if (__exception) { 
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) )) { 
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		double mul_2017 = (m_resonance_19 * 0.125);
		double exp_2018 = exp(mul_2017);
		double mul_2016 = (exp_2018 * 0.882497);
		double mul_2012 = (mul_2016 * mul_2016);
		double expr_2006 = safediv(((m_cutoff_18 * 2) * 3.1415926535898), 44100);
		double cos_2015 = cos(expr_2006);
		double mul_2014 = (cos_2015 * mul_2016);
		double mul_2013 = (mul_2014 * -2);
		double add_2011 = ((mul_2013 + mul_2012) + 1);
		double mstosamps_2078 = (m_window_20 * (samplerate * 0.001));
		double mstosamps_2153 = (m_window_17 * (samplerate * 0.001));
		double rsub_2140 = (1 - m_ratio_16);
		double mul_2139 = (rsub_2140 * 1000);
		double div_2138 = safediv(mul_2139, m_window_17);
		samples_to_seconds = (1 / samplerate);
		double rsub_2070 = (1 - m_ratio_15);
		double mul_2069 = (rsub_2070 * 1000);
		double div_2068 = safediv(mul_2069, m_window_20);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_2090 = noise();
			double abs_2107 = fabs(noise_2090);
			double mul_2111 = (abs_2107 * m_blur_14);
			double noise_2019 = noise();
			double abs_2037 = fabs(noise_2019);
			double mul_2041 = (abs_2037 * m_blur_14);
			double noise_2020 = noise();
			double abs_2038 = fabs(noise_2020);
			double mul_2044 = (abs_2038 * m_blur_14);
			double noise_2022 = noise();
			double abs_2040 = fabs(noise_2022);
			double mul_2050 = (abs_2040 * m_blur_14);
			double noise_2021 = noise();
			double abs_2039 = fabs(noise_2021);
			double mul_2047 = (abs_2039 * m_blur_14);
			double noise_2092 = noise();
			double abs_2109 = fabs(noise_2092);
			double mul_2117 = (abs_2109 * m_blur_14);
			double noise_2091 = noise();
			double abs_2108 = fabs(noise_2091);
			double mul_2114 = (abs_2108 * m_blur_14);
			double noise_2093 = noise();
			double abs_2110 = fabs(noise_2093);
			double mul_2120 = (abs_2110 * m_blur_14);
			double mul_2008 = (mul_2012 * m_y_10);
			double mul_2009 = (mul_2013 * m_y_1);
			double phasor_2159 = m_phasor_21(div_2138, samples_to_seconds);
			double add_2131 = ((phasor_2159 + m_history_9) + 0.75);
			double mod_2130 = safemod(add_2131, 1);
			double delta_2113 = m_delta_22(mod_2130);
			double sah_2094 = m_sah_23(mul_2111, delta_2113, 0);
			double sah_2112 = m_sah_24(mstosamps_2153, delta_2113, 0);
			double mul_2103 = (sah_2112 * mod_2130);
			double sub_2129 = (mod_2130 - 0.5);
			double mul_2128 = (sub_2129 * 3.1415926535898);
			double cos_2127 = cos(mul_2128);
			double mul_2122 = (cos_2127 * cos_2127);
			double add_2152 = ((phasor_2159 + m_history_8) + 0.25);
			double mod_2151 = safemod(add_2152, 1);
			double delta_2119 = m_delta_25(mod_2151);
			double sah_2098 = m_sah_26(mul_2117, delta_2119, 0);
			double sah_2118 = m_sah_27(mstosamps_2153, delta_2119, 0);
			double mul_2105 = (sah_2118 * mod_2151);
			double sub_2150 = (mod_2151 - 0.5);
			double mul_2149 = (sub_2150 * 3.1415926535898);
			double cos_2148 = cos(mul_2149);
			double mul_2124 = (cos_2148 * cos_2148);
			double add_2137 = ((phasor_2159 + m_history_7) + 0.5);
			double mod_2136 = safemod(add_2137, 1);
			double delta_2116 = m_delta_28(mod_2136);
			double sah_2096 = m_sah_29(mul_2114, delta_2116, 0);
			double sah_2115 = m_sah_30(mstosamps_2153, delta_2116, 0);
			double mul_2104 = (sah_2115 * mod_2136);
			double sub_2135 = (mod_2136 - 0.5);
			double mul_2134 = (sub_2135 * 3.1415926535898);
			double cos_2133 = cos(mul_2134);
			double mul_2123 = (cos_2133 * cos_2133);
			double add_2158 = ((phasor_2159 + m_history_6) + 0);
			double mod_2157 = safemod(add_2158, 1);
			double delta_2101 = m_delta_31(mod_2157);
			double sah_2100 = m_sah_32(mul_2120, delta_2101, 0);
			double sah_2121 = m_sah_33(mstosamps_2153, delta_2101, 0);
			double mul_2106 = (sah_2121 * mod_2157);
			double tap_2144 = m_delay_12.read_linear(mul_2106);
			double tap_2145 = m_delay_12.read_linear(mul_2105);
			double tap_2146 = m_delay_12.read_linear(mul_2104);
			double tap_2147 = m_delay_12.read_linear(mul_2103);
			double mul_2141 = (tap_2145 * mul_2124);
			double mul_2132 = (tap_2146 * mul_2123);
			double mul_2126 = (tap_2147 * mul_2122);
			double sub_2156 = (mod_2157 - 0.5);
			double mul_2155 = (sub_2156 * 3.1415926535898);
			double cos_2154 = cos(mul_2155);
			double mul_2125 = (cos_2154 * cos_2154);
			double mul_2142 = (tap_2144 * mul_2125);
			double phasor_2084 = m_phasor_34(div_2068, samples_to_seconds);
			double add_2061 = ((m_history_5 + phasor_2084) + 0.75);
			double mod_2060 = safemod(add_2061, 1);
			double delta_2043 = m_delta_35(mod_2060);
			double sah_2023 = m_sah_36(mul_2041, delta_2043, 0);
			double sah_2042 = m_sah_37(mstosamps_2078, delta_2043, 0);
			double mul_2033 = (sah_2042 * mod_2060);
			double sub_2059 = (mod_2060 - 0.5);
			double mul_2058 = (sub_2059 * 3.1415926535898);
			double cos_2057 = cos(mul_2058);
			double mul_2052 = (cos_2057 * cos_2057);
			double add_2067 = ((m_history_4 + phasor_2084) + 0.5);
			double mod_2066 = safemod(add_2067, 1);
			double delta_2046 = m_delta_38(mod_2066);
			double sah_2025 = m_sah_39(mul_2044, delta_2046, 0);
			double sah_2045 = m_sah_40(mstosamps_2078, delta_2046, 0);
			double mul_2034 = (sah_2045 * mod_2066);
			double sub_2065 = (mod_2066 - 0.5);
			double mul_2064 = (sub_2065 * 3.1415926535898);
			double cos_2063 = cos(mul_2064);
			double mul_2053 = (cos_2063 * cos_2063);
			double add_2083 = ((m_history_3 + phasor_2084) + 0);
			double mod_2082 = safemod(add_2083, 1);
			double delta_2030 = m_delta_41(mod_2082);
			double sah_2029 = m_sah_42(mul_2050, delta_2030, 0);
			double sah_2051 = m_sah_43(mstosamps_2078, delta_2030, 0);
			double mul_2036 = (sah_2051 * mod_2082);
			double sub_2081 = (mod_2082 - 0.5);
			double mul_2080 = (sub_2081 * 3.1415926535898);
			double cos_2079 = cos(mul_2080);
			double mul_2055 = (cos_2079 * cos_2079);
			double add_2077 = ((m_history_2 + phasor_2084) + 0.25);
			double mod_2076 = safemod(add_2077, 1);
			double delta_2049 = m_delta_44(mod_2076);
			double sah_2027 = m_sah_45(mul_2047, delta_2049, 0);
			double sah_2048 = m_sah_46(mstosamps_2078, delta_2049, 0);
			double mul_2035 = (sah_2048 * mod_2076);
			double tap_2086 = m_delay_11.read_linear(mul_2036);
			double tap_2087 = m_delay_11.read_linear(mul_2035);
			double tap_2088 = m_delay_11.read_linear(mul_2034);
			double tap_2089 = m_delay_11.read_linear(mul_2033);
			double mul_2056 = (tap_2089 * mul_2052);
			double mul_2062 = (tap_2088 * mul_2053);
			double mul_2072 = (tap_2086 * mul_2055);
			double sub_2075 = (mod_2076 - 0.5);
			double mul_2074 = (sub_2075 * 3.1415926535898);
			double cos_2073 = cos(mul_2074);
			double mul_2054 = (cos_2073 * cos_2073);
			double mul_2071 = (tap_2087 * mul_2054);
			double mul_2010 = ((((((((mul_2126 + mul_2132) + mul_2141) + mul_2142) + mul_2072) + mul_2071) + mul_2062) + mul_2056) * add_2011);
			double sub_2007 = (mul_2010 - (mul_2009 + mul_2008));
			double mix_2172 = (in1 + (m_mix_13 * (sub_2007 - in1)));
			double out1 = mix_2172;
			double y2_next_2160 = m_y_1;
			double history_2095_next_2161 = sah_2094;
			double history_2099_next_2162 = sah_2098;
			double history_2097_next_2163 = sah_2096;
			double history_2102_next_2164 = sah_2100;
			double history_2024_next_2165 = sah_2023;
			double history_2026_next_2166 = sah_2025;
			double history_2031_next_2167 = sah_2029;
			double history_2028_next_2168 = sah_2027;
			double y1_next_2169 = sub_2007;
			m_delay_12.write(in1);
			m_delay_11.write(in1);
			m_y_10 = y2_next_2160;
			m_history_9 = history_2095_next_2161;
			m_history_8 = history_2099_next_2162;
			m_history_7 = history_2097_next_2163;
			m_history_6 = history_2102_next_2164;
			m_history_5 = history_2024_next_2165;
			m_history_4 = history_2026_next_2166;
			m_history_3 = history_2031_next_2167;
			m_history_2 = history_2028_next_2168;
			m_y_1 = y1_next_2169;
			m_delay_11.step();
			m_delay_12.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			
		};
		return __exception;
		
	};
	inline void set_mix(double _value) {
		m_mix_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_blur(double _value) {
		m_blur_14 = (_value < 0.01 ? 0.01 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_ratio1(double _value) {
		m_ratio_15 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_ratio2(double _value) {
		m_ratio_16 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_window2(double _value) {
		m_window_17 = (_value < 0.1 ? 0.1 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_cutoff(double _value) {
		m_cutoff_18 = (_value < 0 ? 0 : (_value > 3000 ? 3000 : _value));
	};
	inline void set_resonance(double _value) {
		m_resonance_19 = (_value < 0 ? 0 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_window1(double _value) {
		m_window_20 = (_value < 0.1 ? 0.1 : (_value > 1000 ? 1000 : _value));
	};
	
} State;


/// 
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs 

int gen_kernel_numins = 1;
int gen_kernel_numouts = 1;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 8; }

/// Assistive lables for the signal inputs and outputs 

const char * gen_kernel_innames[] = { "in1" };
const char * gen_kernel_outnames[] = { "out1" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) { 
	State * self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) { 
	State * self = (State *)cself;
	self->reset(cself->sr, cself->vs); 
}

/// Set a parameter of a State object 

void setparameter(CommonState *cself, long index, double value, void *ref) {
	State * self = (State *)cself;
	switch (index) {
		case 0: self->set_mix(value); break;
		case 1: self->set_blur(value); break;
		case 2: self->set_ratio1(value); break;
		case 3: self->set_ratio2(value); break;
		case 4: self->set_window2(value); break;
		case 5: self->set_cutoff(value); break;
		case 6: self->set_resonance(value); break;
		case 7: self->set_window1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_mix_13; break;
		case 1: *value = self->m_blur_14; break;
		case 2: *value = self->m_ratio_15; break;
		case 3: *value = self->m_ratio_16; break;
		case 4: *value = self->m_window_17; break;
		case 5: *value = self->m_cutoff_18; break;
		case 6: *value = self->m_resonance_19; break;
		case 7: *value = self->m_window_20; break;
		
		default: break;
	}
}

/// Allocate and configure a new State object and it's internal CommonState:

void * create(double sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(8 * sizeof(ParamInfo));
	self->__commonstate.numparams = 8;
	// initialize parameter 0 ("m_mix_13")
	pi = self->__commonstate.params + 0;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_blur_14")
	pi = self->__commonstate.params + 1;
	pi->name = "blur";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_blur_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ratio_15")
	pi = self->__commonstate.params + 2;
	pi->name = "ratio1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ratio_16")
	pi = self->__commonstate.params + 3;
	pi->name = "ratio2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_window_17")
	pi = self->__commonstate.params + 4;
	pi->name = "window2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_window_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_cutoff_18")
	pi = self->__commonstate.params + 5;
	pi->name = "cutoff";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cutoff_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 3000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_resonance_19")
	pi = self->__commonstate.params + 6;
	pi->name = "resonance";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_resonance_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_window_20")
	pi = self->__commonstate.params + 7;
	pi->name = "window1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_window_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) { 
	State * self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self; 
}


} // gen_exported::
