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
	Delay m_delay_2;
	Delay m_delay_3;
	SineCycle m_cycle_14;
	SineData __sinedata;
	double m_feedforward_9;
	double m_mix_11;
	double m_depth_12;
	double m_time_10;
	double m_feedback_13;
	double m_repeats_8;
	double m_bleed_6;
	double m_delay_5;
	double m_cutoff_7;
	double m_y_1;
	double samplerate;
	double m_rate_4;
	int vectorsize;
	int __exception;
	// re-initialize all member variables;
	inline void reset(double __sr, int __vs) { 
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_y_1 = 0;
		m_delay_2.reset("m_delay_2", 44100);
		m_delay_3.reset("m_delay_3", 44100);
		m_rate_4 = 2;
		m_delay_5 = 0;
		m_bleed_6 = 0;
		m_cutoff_7 = 3000;
		m_repeats_8 = 75;
		m_feedforward_9 = 100;
		m_time_10 = 500;
		m_mix_11 = 100;
		m_depth_12 = 1;
		m_feedback_13 = 0;
		m_cycle_14.reset(samplerate, 0);
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
		double mul_164 = (m_mix_11 * 0.01);
		double mstosamps_191 = (m_time_10 * (samplerate * 0.001));
		double mul_166 = (m_bleed_6 * 0.01);
		double mul_165 = (m_feedforward_9 * 0.01);
		double mul_168 = (m_repeats_8 * 0.01);
		double expr_192 = safediv(((m_cutoff_7 * 2) * 3.1415926535898), 44100);
		double sin_172 = sin(expr_192);
		double clamp_173 = ((sin_172 <= 1e-05) ? 1e-05 : ((sin_172 >= 0.99999) ? 0.99999 : sin_172));
		double mul_167 = (m_feedback_13 * 0.01);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double tap_190 = m_delay_3.read_linear(mstosamps_191);
			double mix_200 = (m_y_1 + (clamp_173 * (tap_190 - m_y_1)));
			double mix_170 = mix_200;
			double mul_187 = (mix_170 * mul_168);
			m_cycle_14.freq(m_rate_4);
			double cycle_176 = m_cycle_14(__sinedata);
			double cycleindex_177 = m_cycle_14.phase();
			double add_175 = (cycle_176 + 1);
			double mul_174 = (add_175 * 0.5);
			double mul_179 = (m_depth_12 * mul_174);
			double add_178 = (m_delay_5 + mul_179);
			double mstosamps_169 = (add_178 * (samplerate * 0.001));
			double tap_184 = m_delay_2.read_linear(mstosamps_169);
			double mul_182 = (tap_184 * mul_165);
			double mul_180 = (tap_184 * mul_167);
			double add_186 = (mix_170 + mul_180);
			double mul_181 = (add_186 * mul_166);
			double add_185 = (mul_181 + mul_182);
			double mul_188 = (add_185 * mul_164);
			double out1 = (mul_188 + in1);
			double y0_next_193 = mix_170;
			m_delay_3.write((mul_187 + in1));
			m_delay_2.write(add_186);
			m_y_1 = y0_next_193;
			m_delay_2.step();
			m_delay_3.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			
		};
		return __exception;
		
	};
	inline void set_rate(double _value) {
		m_rate_4 = (_value < 0.1 ? 0.1 : (_value > 10 ? 10 : _value));
	};
	inline void set_delay(double _value) {
		m_delay_5 = (_value < 0 ? 0 : (_value > 30 ? 30 : _value));
	};
	inline void set_bleed(double _value) {
		m_bleed_6 = (_value < 0 ? 0 : (_value > 70 ? 70 : _value));
	};
	inline void set_cutoff(double _value) {
		m_cutoff_7 = (_value < 0 ? 0 : (_value > 6000 ? 6000 : _value));
	};
	inline void set_repeats(double _value) {
		m_repeats_8 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_feedforward(double _value) {
		m_feedforward_9 = (_value < 70 ? 70 : (_value > 100 ? 100 : _value));
	};
	inline void set_time(double _value) {
		m_time_10 = (_value < 10 ? 10 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_11 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_depth(double _value) {
		m_depth_12 = (_value < 0 ? 0 : (_value > 5 ? 5 : _value));
	};
	inline void set_feedback(double _value) {
		m_feedback_13 = (_value < -70 ? -70 : (_value > 70 ? 70 : _value));
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
int num_params() { return 10; }

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
		case 0: self->set_rate(value); break;
		case 1: self->set_delay(value); break;
		case 2: self->set_bleed(value); break;
		case 3: self->set_cutoff(value); break;
		case 4: self->set_repeats(value); break;
		case 5: self->set_feedforward(value); break;
		case 6: self->set_time(value); break;
		case 7: self->set_mix(value); break;
		case 8: self->set_depth(value); break;
		case 9: self->set_feedback(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_rate_4; break;
		case 1: *value = self->m_delay_5; break;
		case 2: *value = self->m_bleed_6; break;
		case 3: *value = self->m_cutoff_7; break;
		case 4: *value = self->m_repeats_8; break;
		case 5: *value = self->m_feedforward_9; break;
		case 6: *value = self->m_time_10; break;
		case 7: *value = self->m_mix_11; break;
		case 8: *value = self->m_depth_12; break;
		case 9: *value = self->m_feedback_13; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(10 * sizeof(ParamInfo));
	self->__commonstate.numparams = 10;
	// initialize parameter 0 ("m_rate_4")
	pi = self->__commonstate.params + 0;
	pi->name = "rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_rate_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_delay_5")
	pi = self->__commonstate.params + 1;
	pi->name = "delay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_delay_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_bleed_6")
	pi = self->__commonstate.params + 2;
	pi->name = "bleed";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_bleed_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 70;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_cutoff_7")
	pi = self->__commonstate.params + 3;
	pi->name = "cutoff";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cutoff_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 6000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_repeats_8")
	pi = self->__commonstate.params + 4;
	pi->name = "repeats";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_repeats_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_feedforward_9")
	pi = self->__commonstate.params + 5;
	pi->name = "feedforward";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_feedforward_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 70;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_time_10")
	pi = self->__commonstate.params + 6;
	pi->name = "time";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_time_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 10;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_mix_11")
	pi = self->__commonstate.params + 7;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_depth_12")
	pi = self->__commonstate.params + 8;
	pi->name = "depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_depth_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_feedback_13")
	pi = self->__commonstate.params + 9;
	pi->name = "feedback";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_feedback_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 70;
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
