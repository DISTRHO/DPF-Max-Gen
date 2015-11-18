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
	Delay m_delay_24;
	Delay m_delay_15;
	Delay m_delay_13;
	Delay m_delay_23;
	Delay m_delay_9;
	Delay m_delay_17;
	Delay m_delay_21;
	Delay m_delay_19;
	Delay m_delay_22;
	Delay m_delay_7;
	Delay m_delay_11;
	Delay m_delay_5;
	double m_history_6;
	double m_history_18;
	double m_spread_1;
	double m_history_20;
	double samplerate;
	double m_fb_2;
	double m_history_8;
	double m_history_16;
	double m_history_14;
	double m_damp_3;
	double m_history_12;
	double m_history_10;
	double m_fb_4;
	int vectorsize;
	int __exception;
	// re-initialize all member variables;
	inline void reset(double __sr, int __vs) { 
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_spread_1 = 0;
		m_fb_2 = 0.9;
		m_damp_3 = 0.5;
		m_fb_4 = 0.5;
		m_delay_5.reset("m_delay_5", 2000);
		m_history_6 = 0;
		m_delay_7.reset("m_delay_7", 2000);
		m_history_8 = 0;
		m_delay_9.reset("m_delay_9", 2000);
		m_history_10 = 0;
		m_delay_11.reset("m_delay_11", 2000);
		m_history_12 = 0;
		m_delay_13.reset("m_delay_13", 2000);
		m_history_14 = 0;
		m_delay_15.reset("m_delay_15", 2000);
		m_history_16 = 0;
		m_delay_17.reset("m_delay_17", 2000);
		m_history_18 = 0;
		m_delay_19.reset("m_delay_19", 2000);
		m_history_20 = 0;
		m_delay_21.reset("m_delay_21", 2000);
		m_delay_22.reset("m_delay_22", 2000);
		m_delay_23.reset("m_delay_23", 2000);
		m_delay_24.reset("m_delay_24", 2000);
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
		double mul_498 = (m_fb_4 * 0.5);
		double add_474 = (225 + m_spread_1);
		double add_481 = (341 + m_spread_1);
		double add_496 = (441 + m_spread_1);
		double add_467 = (556 + m_spread_1);
		double damp_379 = m_damp_3;
		double damp_377 = damp_379;
		double damp_376 = damp_379;
		double damp_378 = damp_379;
		double damp_380 = damp_379;
		double damp_381 = damp_379;
		double damp_382 = damp_379;
		double damp_383 = damp_379;
		double add_489 = (1557 + m_spread_1);
		double rsub_72 = (1 - damp_377);
		double add_488 = (1617 + m_spread_1);
		double rsub_510 = (1 - damp_376);
		double add_490 = (1491 + m_spread_1);
		double rsub_522 = (1 - damp_378);
		double add_491 = (1422 + m_spread_1);
		double rsub_537 = (1 - damp_379);
		double add_492 = (1356 + m_spread_1);
		double rsub_548 = (1 - damp_380);
		double add_493 = (1277 + m_spread_1);
		double rsub_561 = (1 - damp_381);
		double add_494 = (1188 + m_spread_1);
		double rsub_576 = (1 - damp_382);
		double add_495 = (1116 + m_spread_1);
		double rsub_585 = (1 - damp_383);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double mul_509 = (in1 * 0.015);
			double tap_79 = m_delay_5.read_linear(add_489);
			double gen_460 = tap_79;
			double mul_77 = (tap_79 * damp_377);
			double mul_75 = (m_history_6 * rsub_72);
			double add_76 = (mul_77 + mul_75);
			double mul_73 = (add_76 * m_fb_2);
			double add_80 = (mul_509 + mul_73);
			double history_74_next_81 = add_76;
			double tap_514 = m_delay_7.read_linear(add_488);
			double gen_508 = tap_514;
			double mul_518 = (tap_514 * damp_376);
			double mul_512 = (m_history_8 * rsub_510);
			double add_513 = (mul_518 + mul_512);
			double mul_515 = (add_513 * m_fb_2);
			double add_517 = (mul_509 + mul_515);
			double history_74_next_516 = add_513;
			double tap_526 = m_delay_9.read_linear(add_490);
			double gen_449 = tap_526;
			double mul_530 = (tap_526 * damp_378);
			double mul_524 = (m_history_10 * rsub_522);
			double add_525 = (mul_530 + mul_524);
			double mul_527 = (add_525 * m_fb_2);
			double add_529 = (mul_509 + mul_527);
			double history_74_next_528 = add_525;
			double tap_539 = m_delay_11.read_linear(add_491);
			double gen_438 = tap_539;
			double mul_536 = (tap_539 * damp_379);
			double mul_535 = (m_history_12 * rsub_537);
			double add_538 = (mul_536 + mul_535);
			double mul_540 = (add_538 * m_fb_2);
			double add_541 = (mul_509 + mul_540);
			double history_74_next_543 = add_538;
			double tap_550 = m_delay_13.read_linear(add_492);
			double gen_427 = tap_550;
			double mul_547 = (tap_550 * damp_380);
			double mul_546 = (m_history_14 * rsub_548);
			double add_549 = (mul_547 + mul_546);
			double mul_551 = (add_549 * m_fb_2);
			double add_553 = (mul_509 + mul_551);
			double history_74_next_555 = add_549;
			double tap_563 = m_delay_15.read_linear(add_493);
			double gen_416 = tap_563;
			double mul_560 = (tap_563 * damp_381);
			double mul_559 = (m_history_16 * rsub_561);
			double add_562 = (mul_560 + mul_559);
			double mul_564 = (add_562 * m_fb_2);
			double add_565 = (mul_509 + mul_564);
			double history_74_next_566 = add_562;
			double tap_574 = m_delay_17.read_linear(add_494);
			double gen_405 = tap_574;
			double mul_572 = (tap_574 * damp_382);
			double mul_571 = (m_history_18 * rsub_576);
			double add_573 = (mul_572 + mul_571);
			double mul_575 = (add_573 * m_fb_2);
			double add_577 = (mul_509 + mul_575);
			double history_74_next_579 = add_573;
			double tap_587 = m_delay_19.read_linear(add_495);
			double gen_394 = tap_587;
			double mul_584 = (tap_587 * damp_383);
			double mul_583 = (m_history_20 * rsub_585);
			double add_586 = (mul_584 + mul_583);
			double mul_588 = (add_586 * m_fb_2);
			double add_589 = (mul_509 + mul_588);
			double history_74_next_591 = add_586;
			double add_497 = ((((((((gen_394 + gen_405) + gen_416) + gen_427) + gen_438) + gen_449) + gen_508) + gen_460) + 0);
			double tap_60 = m_delay_21.read_linear(add_467);
			double sub_56 = (add_497 - tap_60);
			double mul_58 = (tap_60 * mul_498);
			double add_57 = (add_497 + mul_58);
			double tap_597 = m_delay_22.read_linear(add_496);
			double sub_594 = (sub_56 - tap_597);
			double mul_596 = (tap_597 * mul_498);
			double add_598 = (sub_56 + mul_596);
			double tap_603 = m_delay_23.read_linear(add_481);
			double sub_600 = (sub_594 - tap_603);
			double mul_602 = (tap_603 * mul_498);
			double add_604 = (sub_594 + mul_602);
			double tap_608 = m_delay_24.read_linear(add_474);
			double sub_606 = (sub_600 - tap_608);
			double mul_609 = (tap_608 * mul_498);
			double add_610 = (sub_600 + mul_609);
			double out1 = sub_606;
			m_delay_5.write(add_80);
			m_delay_24.write(add_610);
			m_delay_23.write(add_604);
			m_delay_22.write(add_598);
			m_delay_21.write(add_57);
			m_history_20 = history_74_next_591;
			m_delay_19.write(add_589);
			m_history_18 = history_74_next_579;
			m_delay_17.write(add_577);
			m_history_16 = history_74_next_566;
			m_delay_15.write(add_565);
			m_history_14 = history_74_next_555;
			m_delay_13.write(add_553);
			m_history_12 = history_74_next_543;
			m_delay_11.write(add_541);
			m_history_10 = history_74_next_528;
			m_delay_9.write(add_529);
			m_history_8 = history_74_next_516;
			m_delay_7.write(add_517);
			m_history_6 = history_74_next_81;
			m_delay_5.step();
			m_delay_7.step();
			m_delay_9.step();
			m_delay_11.step();
			m_delay_13.step();
			m_delay_15.step();
			m_delay_17.step();
			m_delay_19.step();
			m_delay_21.step();
			m_delay_22.step();
			m_delay_23.step();
			m_delay_24.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			
		};
		return __exception;
		
	};
	inline void set_spread(double _value) {
		m_spread_1 = (_value < 0 ? 0 : (_value > 400 ? 400 : _value));
	};
	inline void set_fb1(double _value) {
		m_fb_2 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_damp(double _value) {
		m_damp_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_fb2(double _value) {
		m_fb_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
int num_params() { return 4; }

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
		case 0: self->set_spread(value); break;
		case 1: self->set_fb1(value); break;
		case 2: self->set_damp(value); break;
		case 3: self->set_fb2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_spread_1; break;
		case 1: *value = self->m_fb_2; break;
		case 2: *value = self->m_damp_3; break;
		case 3: *value = self->m_fb_4; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_spread_1")
	pi = self->__commonstate.params + 0;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 400;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_fb_2")
	pi = self->__commonstate.params + 1;
	pi->name = "fb1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_fb_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_damp_3")
	pi = self->__commonstate.params + 2;
	pi->name = "damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damp_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_fb_4")
	pi = self->__commonstate.params + 3;
	pi->name = "fb2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_fb_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
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


} // freeverb::
