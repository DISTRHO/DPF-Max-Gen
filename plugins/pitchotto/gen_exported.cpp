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
	Delay m_delay_7;
	Delta m_delta_21;
	Delta m_delta_18;
	Delta m_delta_15;
	Delta m_delta_24;
	Phasor m_phasor_14;
	Sah m_sah_16;
	Sah m_sah_17;
	Sah m_sah_26;
	Sah m_sah_19;
	Sah m_sah_25;
	Sah m_sah_22;
	Sah m_sah_23;
	Sah m_sah_20;
	double samples_to_seconds;
	double m_blur_13;
	double m_window_12;
	double m_ratio_10;
	double m_history_2;
	double m_mix_11;
	double m_y_1;
	double samplerate;
	double m_history_4;
	double m_history_3;
	double m_y_6;
	double m_history_5;
	double m_cutoff_9;
	double m_resonance_8;
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
		m_y_6 = 0;
		m_delay_7.reset("m_delay_7", 88200);
		m_resonance_8 = 0;
		m_cutoff_9 = 3000;
		m_ratio_10 = 1;
		m_mix_11 = 1;
		m_window_12 = 100;
		m_blur_13 = 0.1;
		samples_to_seconds = (1 / samplerate);
		m_phasor_14.reset(0);
		m_delta_15.reset(0);
		m_sah_16.reset(0);
		m_sah_17.reset(0);
		m_delta_18.reset(0);
		m_sah_19.reset(0);
		m_sah_20.reset(0);
		m_delta_21.reset(0);
		m_sah_22.reset(0);
		m_sah_23.reset(0);
		m_delta_24.reset(0);
		m_sah_25.reset(0);
		m_sah_26.reset(0);
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
		double mul_246 = (m_resonance_8 * 0.125);
		double exp_247 = exp(mul_246);
		double mul_245 = (exp_247 * 0.882497);
		double mul_241 = (mul_245 * mul_245);
		double expr_359 = safediv(((m_cutoff_9 * 2) * 3.1415926535898), 44100);
		double cos_244 = cos(expr_359);
		double mul_243 = (cos_244 * mul_245);
		double mul_242 = (mul_243 * -2);
		double add_240 = ((mul_242 + mul_241) + 1);
		double mstosamps_138 = (m_window_12 * (samplerate * 0.001));
		double rsub_124 = (1 - m_ratio_10);
		double mul_123 = (rsub_124 * 1000);
		double div_122 = safediv(mul_123, m_window_12);
		samples_to_seconds = (1 / samplerate);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_73 = noise();
			double abs_91 = fabs(noise_73);
			double mul_95 = (abs_91 * m_blur_13);
			double noise_76 = noise();
			double abs_94 = fabs(noise_76);
			double mul_104 = (abs_94 * m_blur_13);
			double noise_75 = noise();
			double abs_93 = fabs(noise_75);
			double mul_101 = (abs_93 * m_blur_13);
			double noise_74 = noise();
			double abs_92 = fabs(noise_74);
			double mul_98 = (abs_92 * m_blur_13);
			double mul_237 = (mul_241 * m_y_6);
			double mul_238 = (mul_242 * m_y_1);
			double phasor_144 = m_phasor_14(div_122, samples_to_seconds);
			double add_115 = ((m_history_5 + phasor_144) + 0.75);
			double mod_114 = safemod(add_115, 1);
			double delta_97 = m_delta_15(mod_114);
			double sah_77 = m_sah_16(mul_95, delta_97, 0);
			double sah_96 = m_sah_17(mstosamps_138, delta_97, 0);
			double mul_87 = (sah_96 * mod_114);
			double sub_113 = (mod_114 - 0.5);
			double mul_112 = (sub_113 * 3.1415926535898);
			double cos_111 = cos(mul_112);
			double mul_106 = (cos_111 * cos_111);
			double add_143 = ((m_history_4 + phasor_144) + 0);
			double mod_142 = safemod(add_143, 1);
			double delta_84 = m_delta_18(mod_142);
			double sah_83 = m_sah_19(mul_104, delta_84, 0);
			double sah_105 = m_sah_20(mstosamps_138, delta_84, 0);
			double mul_90 = (sah_105 * mod_142);
			double sub_141 = (mod_142 - 0.5);
			double mul_140 = (sub_141 * 3.1415926535898);
			double cos_139 = cos(mul_140);
			double mul_109 = (cos_139 * cos_139);
			double add_137 = ((m_history_3 + phasor_144) + 0.25);
			double mod_136 = safemod(add_137, 1);
			double delta_103 = m_delta_21(mod_136);
			double sah_81 = m_sah_22(mul_101, delta_103, 0);
			double sah_102 = m_sah_23(mstosamps_138, delta_103, 0);
			double mul_89 = (sah_102 * mod_136);
			double sub_135 = (mod_136 - 0.5);
			double mul_134 = (sub_135 * 3.1415926535898);
			double cos_133 = cos(mul_134);
			double mul_108 = (cos_133 * cos_133);
			double add_121 = ((m_history_2 + phasor_144) + 0.5);
			double mod_120 = safemod(add_121, 1);
			double delta_100 = m_delta_24(mod_120);
			double sah_79 = m_sah_25(mul_98, delta_100, 0);
			double sah_99 = m_sah_26(mstosamps_138, delta_100, 0);
			double mul_88 = (sah_99 * mod_120);
			double tap_129 = m_delay_7.read_linear(mul_90);
			double tap_130 = m_delay_7.read_linear(mul_89);
			double tap_131 = m_delay_7.read_linear(mul_88);
			double tap_132 = m_delay_7.read_linear(mul_87);
			double mul_127 = (tap_129 * mul_109);
			double mul_110 = (tap_132 * mul_106);
			double mul_126 = (tap_130 * mul_108);
			double sub_119 = (mod_120 - 0.5);
			double mul_118 = (sub_119 * 3.1415926535898);
			double cos_117 = cos(mul_118);
			double mul_107 = (cos_117 * cos_117);
			double mul_116 = (tap_131 * mul_107);
			double mul_239 = ((((mul_126 + mul_110) + mul_127) + mul_116) * add_240);
			double sub_236 = (mul_239 - (mul_238 + mul_237));
			double mix_367 = (in1 + (m_mix_11 * (sub_236 - in1)));
			double out1 = mix_367;
			double y2_next_361 = m_y_1;
			double history_78_next_362 = sah_77;
			double history_85_next_363 = sah_83;
			double history_82_next_364 = sah_81;
			double history_80_next_365 = sah_79;
			double y1_next_366 = sub_236;
			m_delay_7.write(in1);
			m_y_6 = y2_next_361;
			m_history_5 = history_78_next_362;
			m_history_4 = history_85_next_363;
			m_history_3 = history_82_next_364;
			m_history_2 = history_80_next_365;
			m_y_1 = y1_next_366;
			m_delay_7.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			
		};
		return __exception;
		
	};
	inline void set_resonance(double _value) {
		m_resonance_8 = (_value < 0 ? 0 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_cutoff(double _value) {
		m_cutoff_9 = (_value < 0 ? 0 : (_value > 3000 ? 3000 : _value));
	};
	inline void set_ratio(double _value) {
		m_ratio_10 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_window(double _value) {
		m_window_12 = (_value < 0.1 ? 0.1 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_blur(double _value) {
		m_blur_13 = (_value < 0.1 ? 0.1 : (_value > 0.25 ? 0.25 : _value));
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
int num_params() { return 6; }

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
		case 0: self->set_resonance(value); break;
		case 1: self->set_cutoff(value); break;
		case 2: self->set_ratio(value); break;
		case 3: self->set_mix(value); break;
		case 4: self->set_window(value); break;
		case 5: self->set_blur(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_resonance_8; break;
		case 1: *value = self->m_cutoff_9; break;
		case 2: *value = self->m_ratio_10; break;
		case 3: *value = self->m_mix_11; break;
		case 4: *value = self->m_window_12; break;
		case 5: *value = self->m_blur_13; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(6 * sizeof(ParamInfo));
	self->__commonstate.numparams = 6;
	// initialize parameter 0 ("m_resonance_8")
	pi = self->__commonstate.params + 0;
	pi->name = "resonance";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_resonance_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_cutoff_9")
	pi = self->__commonstate.params + 1;
	pi->name = "cutoff";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cutoff_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 3000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ratio_10")
	pi = self->__commonstate.params + 2;
	pi->name = "ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_mix_11")
	pi = self->__commonstate.params + 3;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_window_12")
	pi = self->__commonstate.params + 4;
	pi->name = "window";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_window_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_blur_13")
	pi = self->__commonstate.params + 5;
	pi->name = "blur";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_blur_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.25;
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
