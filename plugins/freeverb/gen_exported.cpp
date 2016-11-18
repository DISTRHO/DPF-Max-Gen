#include "gen_exported.h"

namespace gen_exported {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
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
	int vectorsize;
	int __exception;
	t_sample m_fb_1;
	t_sample m_history_20;
	t_sample samplerate;
	t_sample m_history_18;
	t_sample m_spread_2;
	t_sample m_history_16;
	t_sample m_damp_3;
	t_sample m_history_10;
	t_sample m_history_8;
	t_sample m_history_12;
	t_sample m_history_14;
	t_sample m_fb_4;
	t_sample m_history_6;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_fb_1 = 0.5;
		m_spread_2 = 0;
		m_damp_3 = 0.5;
		m_fb_4 = 0.9;
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
		t_sample mul_408 = (m_fb_1 * 0.5);
		t_sample add_394 = (225 + m_spread_2);
		t_sample add_396 = (341 + m_spread_2);
		t_sample add_406 = (441 + m_spread_2);
		t_sample add_392 = (556 + m_spread_2);
		t_sample damp_378 = m_damp_3;
		t_sample damp_377 = damp_378;
		t_sample damp_376 = damp_378;
		t_sample damp_379 = damp_378;
		t_sample damp_380 = damp_378;
		t_sample damp_381 = damp_378;
		t_sample damp_382 = damp_378;
		t_sample damp_383 = damp_378;
		t_sample add_399 = (1557 + m_spread_2);
		t_sample rsub_345 = (1 - damp_377);
		t_sample add_398 = (1617 + m_spread_2);
		t_sample rsub_525 = (1 - damp_376);
		t_sample add_400 = (1491 + m_spread_2);
		t_sample rsub_537 = (1 - damp_378);
		t_sample add_401 = (1422 + m_spread_2);
		t_sample rsub_549 = (1 - damp_379);
		t_sample add_402 = (1356 + m_spread_2);
		t_sample rsub_561 = (1 - damp_380);
		t_sample add_403 = (1277 + m_spread_2);
		t_sample rsub_573 = (1 - damp_381);
		t_sample add_404 = (1188 + m_spread_2);
		t_sample rsub_585 = (1 - damp_382);
		t_sample add_405 = (1116 + m_spread_2);
		t_sample rsub_597 = (1 - damp_383);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample mul_419 = (in1 * 0.015);
			t_sample tap_352 = m_delay_5.read_linear(add_399);
			t_sample gen_390 = tap_352;
			t_sample mul_350 = (tap_352 * damp_377);
			t_sample mul_348 = (m_history_6 * rsub_345);
			t_sample add_349 = (mul_350 + mul_348);
			t_sample mul_346 = (add_349 * m_fb_4);
			t_sample add_353 = (mul_419 + mul_346);
			t_sample history_347_next_354 = fixdenorm(add_349);
			t_sample tap_533 = m_delay_7.read_linear(add_398);
			t_sample gen_418 = tap_533;
			t_sample mul_528 = (tap_533 * damp_376);
			t_sample mul_530 = (m_history_8 * rsub_525);
			t_sample add_527 = (mul_528 + mul_530);
			t_sample mul_529 = (add_527 * m_fb_4);
			t_sample add_532 = (mul_419 + mul_529);
			t_sample history_347_next_531 = fixdenorm(add_527);
			t_sample tap_545 = m_delay_9.read_linear(add_400);
			t_sample gen_389 = tap_545;
			t_sample mul_540 = (tap_545 * damp_378);
			t_sample mul_542 = (m_history_10 * rsub_537);
			t_sample add_539 = (mul_540 + mul_542);
			t_sample mul_541 = (add_539 * m_fb_4);
			t_sample add_544 = (mul_419 + mul_541);
			t_sample history_347_next_543 = fixdenorm(add_539);
			t_sample tap_558 = m_delay_11.read_linear(add_401);
			t_sample gen_388 = tap_558;
			t_sample mul_556 = (tap_558 * damp_379);
			t_sample mul_557 = (m_history_12 * rsub_549);
			t_sample add_554 = (mul_556 + mul_557);
			t_sample mul_551 = (add_554 * m_fb_4);
			t_sample add_555 = (mul_419 + mul_551);
			t_sample history_347_next_552 = fixdenorm(add_554);
			t_sample tap_568 = m_delay_13.read_linear(add_402);
			t_sample gen_387 = tap_568;
			t_sample mul_567 = (tap_568 * damp_380);
			t_sample mul_569 = (m_history_14 * rsub_561);
			t_sample add_565 = (mul_567 + mul_569);
			t_sample mul_563 = (add_565 * m_fb_4);
			t_sample add_566 = (mul_419 + mul_563);
			t_sample history_347_next_570 = fixdenorm(add_565);
			t_sample tap_581 = m_delay_15.read_linear(add_403);
			t_sample gen_386 = tap_581;
			t_sample mul_580 = (tap_581 * damp_381);
			t_sample mul_582 = (m_history_16 * rsub_573);
			t_sample add_578 = (mul_580 + mul_582);
			t_sample mul_575 = (add_578 * m_fb_4);
			t_sample add_579 = (mul_419 + mul_575);
			t_sample history_347_next_576 = fixdenorm(add_578);
			t_sample tap_594 = m_delay_17.read_linear(add_404);
			t_sample gen_385 = tap_594;
			t_sample mul_591 = (tap_594 * damp_382);
			t_sample mul_592 = (m_history_18 * rsub_585);
			t_sample add_589 = (mul_591 + mul_592);
			t_sample mul_587 = (add_589 * m_fb_4);
			t_sample add_590 = (mul_419 + mul_587);
			t_sample history_347_next_593 = fixdenorm(add_589);
			t_sample tap_605 = m_delay_19.read_linear(add_405);
			t_sample gen_384 = tap_605;
			t_sample mul_604 = (tap_605 * damp_383);
			t_sample mul_606 = (m_history_20 * rsub_597);
			t_sample add_602 = (mul_604 + mul_606);
			t_sample mul_599 = (add_602 * m_fb_4);
			t_sample add_603 = (mul_419 + mul_599);
			t_sample history_347_next_600 = fixdenorm(add_602);
			t_sample add_407 = ((((((((gen_384 + gen_385) + gen_386) + gen_387) + gen_388) + gen_389) + gen_418) + gen_390) + 0);
			t_sample tap_343 = m_delay_21.read_linear(add_392);
			t_sample sub_339 = (add_407 - tap_343);
			t_sample mul_341 = (tap_343 * mul_408);
			t_sample add_340 = (add_407 + mul_341);
			t_sample tap_612 = m_delay_22.read_linear(add_406);
			t_sample sub_611 = (sub_339 - tap_612);
			t_sample mul_609 = (tap_612 * mul_408);
			t_sample add_610 = (sub_339 + mul_609);
			t_sample tap_618 = m_delay_23.read_linear(add_396);
			t_sample sub_617 = (sub_611 - tap_618);
			t_sample mul_615 = (tap_618 * mul_408);
			t_sample add_616 = (sub_611 + mul_615);
			t_sample tap_624 = m_delay_24.read_linear(add_394);
			t_sample sub_623 = (sub_617 - tap_624);
			t_sample mul_621 = (tap_624 * mul_408);
			t_sample add_622 = (sub_617 + mul_621);
			t_sample out1 = sub_623;
			m_delay_5.write(add_353);
			m_delay_24.write(add_622);
			m_delay_23.write(add_616);
			m_delay_22.write(add_610);
			m_delay_21.write(add_340);
			m_history_20 = history_347_next_600;
			m_delay_19.write(add_603);
			m_history_18 = history_347_next_593;
			m_delay_17.write(add_590);
			m_history_16 = history_347_next_576;
			m_delay_15.write(add_579);
			m_history_14 = history_347_next_570;
			m_delay_13.write(add_566);
			m_history_12 = history_347_next_552;
			m_delay_11.write(add_555);
			m_history_10 = history_347_next_543;
			m_delay_9.write(add_544);
			m_history_8 = history_347_next_531;
			m_delay_7.write(add_532);
			m_history_6 = history_347_next_354;
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
	inline void set_fb2(t_param _value) {
		m_fb_1 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_spread(t_param _value) {
		m_spread_2 = (_value < 0 ? 0 : (_value > 400 ? 400 : _value));
	};
	inline void set_damp(t_param _value) {
		m_damp_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_fb1(t_param _value) {
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

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_damp(value); break;
		case 1: self->set_fb1(value); break;
		case 2: self->set_fb2(value); break;
		case 3: self->set_spread(value); break;

		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_damp_3; break;
		case 1: *value = self->m_fb_4; break;
		case 2: *value = self->m_fb_1; break;
		case 3: *value = self->m_spread_2; break;

		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
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
	// initialize parameter 0 ("m_damp_3")
	pi = self->__commonstate.params + 0;
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
	// initialize parameter 1 ("m_fb_4")
	pi = self->__commonstate.params + 1;
	pi->name = "fb1";
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
	// initialize parameter 2 ("m_fb_1")
	pi = self->__commonstate.params + 2;
	pi->name = "fb2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_fb_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_spread_2")
	pi = self->__commonstate.params + 3;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 400;
	pi->exp = 0;
	pi->units = "";		// no units defined

	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);

	delete self;
}


} // gen_exported::
