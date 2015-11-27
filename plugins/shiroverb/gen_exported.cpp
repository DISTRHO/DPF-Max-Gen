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
	Delay m_delay_14;
	Delay m_delay_18;
	Delay m_delay_19;
	Delay m_delay_15;
	Delay m_delay_12;
	Delay m_delay_17;
	Delay m_delay_13;
	Delay m_delay_21;
	Delay m_delay_20;
	Delay m_delay_22;
	Delay m_delay_24;
	Delay m_delay_23;
	Delay m_delay_16;
	Delta m_delta_43;
	Delta m_delta_49;
	Delta m_delta_46;
	Delta m_delta_40;
	Phasor m_phasor_39;
	Sah m_sah_50;
	Sah m_sah_51;
	Sah m_sah_47;
	Sah m_sah_48;
	Sah m_sah_45;
	Sah m_sah_42;
	Sah m_sah_44;
	Sah m_sah_41;
	double m_early_34;
	double m_cutoff_35;
	double m_resonance_36;
	double m_mix_38;
	double m_shimmer_33;
	double m_ratio_37;
	double samples_to_seconds;
	double m_tail_32;
	double m_window_25;
	double m_decay_30;
	double m_history_4;
	double m_history_5;
	double m_history_6;
	double m_history_3;
	double m_history_1;
	double m_y_2;
	double samplerate;
	double m_spread_31;
	double m_history_7;
	double m_history_9;
	double m_roomsize_28;
	double m_damping_29;
	double m_history_8;
	double m_tone_27;
	double m_y_11;
	double m_history_10;
	double m_blur_26;
	int vectorsize;
	int __exception;
	// re-initialize all member variables;
	inline void reset(double __sr, int __vs) { 
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = 0;
		m_y_2 = 0;
		m_history_3 = 0;
		m_history_4 = 0;
		m_history_5 = 0;
		m_history_6 = 0;
		m_history_7 = 0;
		m_history_8 = 0;
		m_history_9 = 0;
		m_history_10 = 0;
		m_y_11 = 0;
		m_delay_12.reset("m_delay_12", 5000);
		m_delay_13.reset("m_delay_13", 7000);
		m_delay_14.reset("m_delay_14", 15000);
		m_delay_15.reset("m_delay_15", 16000);
		m_delay_16.reset("m_delay_16", 6000);
		m_delay_17.reset("m_delay_17", 96000);
		m_delay_18.reset("m_delay_18", 48000);
		m_delay_19.reset("m_delay_19", 10000);
		m_delay_20.reset("m_delay_20", 12000);
		m_delay_21.reset("m_delay_21", 48000);
		m_delay_22.reset("m_delay_22", 48000);
		m_delay_23.reset("m_delay_23", 48000);
		m_delay_24.reset("m_delay_24", 48000);
		m_window_25 = 100;
		m_blur_26 = 0.25;
		m_tone_27 = 0.5;
		m_roomsize_28 = 150;
		m_damping_29 = 0.5;
		m_decay_30 = 180;
		m_spread_31 = 25;
		m_tail_32 = 0.25;
		m_shimmer_33 = 0.5;
		m_early_34 = 0.25;
		m_cutoff_35 = 3000;
		m_resonance_36 = 0;
		m_ratio_37 = 2;
		m_mix_38 = 0.5;
		samples_to_seconds = (1 / samplerate);
		m_phasor_39.reset(0);
		m_delta_40.reset(0);
		m_sah_41.reset(0);
		m_sah_42.reset(0);
		m_delta_43.reset(0);
		m_sah_44.reset(0);
		m_sah_45.reset(0);
		m_delta_46.reset(0);
		m_sah_47.reset(0);
		m_sah_48.reset(0);
		m_delta_49.reset(0);
		m_sah_50.reset(0);
		m_sah_51.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) { 
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) { 
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) { 
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		double rsub_605 = (1 - m_tone_27);
		double expr_747 = safepow(0.001, safediv(1, (m_decay_30 * 44100)));
		double expr_748 = safediv((m_roomsize_28 * 44100), 340);
		double mul_594 = (expr_748 * 0.63245);
		double expr_739 = (-safepow(expr_747, mul_594));
		double mul_597 = (expr_748 * 1);
		double expr_746 = (-safepow(expr_747, mul_597));
		double mul_596 = (expr_748 * 0.81649);
		double expr_741 = (-safepow(expr_747, mul_596));
		double mul_595 = (expr_748 * 0.7071);
		double expr_740 = (-safepow(expr_747, mul_595));
		double mul_379 = (m_resonance_36 * 0.125);
		double exp_380 = exp(mul_379);
		double mul_378 = (exp_380 * 0.882497);
		double mul_374 = (mul_378 * mul_378);
		double expr_738 = safediv(((m_cutoff_35 * 2) * 3.1415926535898), 44100);
		double cos_377 = cos(expr_738);
		double mul_376 = (cos_377 * mul_378);
		double mul_375 = (mul_376 * -2);
		double add_373 = ((mul_375 + mul_374) + 1);
		double mul_591 = (expr_748 * 0.000527);
		int int_590 = int(mul_591);
		double add_520 = (expr_748 + 5);
		double expr_742 = safepow(expr_747, add_520);
		double mstosamps_445 = (m_window_25 * (samplerate * 0.001));
		double mul_531 = (m_spread_31 * -0.380445);
		double add_530 = (mul_531 + 931);
		double rsub_527 = (1341 - add_530);
		double mul_540 = (int_590 * rsub_527);
		double mul_559 = (m_spread_31 * 0.376623);
		double add_558 = (mul_559 + 931);
		double rsub_555 = (1341 - add_558);
		double mul_566 = (int_590 * rsub_555);
		double mul_526 = (expr_748 * 0.41);
		double add_523 = (mul_526 + 5);
		double expr_745 = safepow(expr_747, add_523);
		double mul_525 = (expr_748 * 0.3);
		double add_522 = (mul_525 + 5);
		double expr_744 = safepow(expr_747, add_522);
		double mul_524 = (expr_748 * 0.155);
		double add_521 = (mul_524 + 5);
		double expr_743 = safepow(expr_747, add_521);
		double rsub_432 = (1 - m_ratio_37);
		double mul_431 = (rsub_432 * 1000);
		double div_430 = safediv(mul_431, m_window_25);
		samples_to_seconds = (1 / samplerate);
		double mul_589 = (expr_748 * 0.110732);
		double mul_533 = (m_spread_31 * -0.568366);
		double add_529 = (mul_533 + 369);
		double rsub_528 = (add_530 - add_529);
		double mul_547 = (int_590 * rsub_528);
		double mul_575 = (m_spread_31 * 0.125541);
		double add_557 = (mul_575 + 369);
		double rsub_556 = (add_558 - add_557);
		double mul_573 = (int_590 * rsub_556);
		double add_532 = (mul_533 + 159);
		double mul_554 = (int_590 * add_532);
		double add_574 = (mul_575 + 159);
		double mul_582 = (int_590 * add_574);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_381 = noise();
			double abs_399 = fabs(noise_381);
			double mul_403 = (abs_399 * m_blur_26);
			double noise_383 = noise();
			double abs_401 = fabs(noise_383);
			double mul_409 = (abs_401 * m_blur_26);
			double noise_382 = noise();
			double abs_400 = fabs(noise_382);
			double mul_406 = (abs_400 * m_blur_26);
			double noise_384 = noise();
			double abs_402 = fabs(noise_384);
			double mul_412 = (abs_402 * m_blur_26);
			double tap_494 = m_delay_24.read_linear(mul_594);
			double mul_490 = (tap_494 * expr_739);
			double mix_773 = (mul_490 + (m_damping_29 * (m_history_10 - mul_490)));
			double mix_492 = mix_773;
			double tap_602 = m_delay_23.read_linear(mul_597);
			double mul_593 = (tap_602 * expr_746);
			double mix_774 = (mul_593 + (m_damping_29 * (m_history_9 - mul_593)));
			double mix_600 = mix_774;
			double tap_506 = m_delay_22.read_linear(mul_596);
			double mul_502 = (tap_506 * expr_741);
			double mix_775 = (mul_502 + (m_damping_29 * (m_history_8 - mul_502)));
			double mix_504 = mix_775;
			double tap_500 = m_delay_21.read_linear(mul_595);
			double mul_496 = (tap_500 * expr_740);
			double mix_776 = (mul_496 + (m_damping_29 * (m_history_7 - mul_496)));
			double mix_498 = mix_776;
			double mul_370 = (mul_374 * m_y_11);
			double mul_371 = (mul_375 * m_y_2);
			double add_484 = (mix_600 + mix_504);
			double add_482 = (mix_498 + mix_492);
			double add_477 = (add_484 + add_482);
			double mul_460 = (add_477 * 0.5);
			double sub_481 = (add_484 - add_482);
			double mul_463 = (sub_481 * 0.5);
			double sub_483 = (mix_600 - mix_504);
			double sub_480 = (mix_498 - mix_492);
			double sub_479 = (sub_483 - sub_480);
			double mul_462 = (sub_479 * 0.5);
			double add_478 = (sub_483 + sub_480);
			double rsub_476 = (0 - add_478);
			double mul_461 = (rsub_476 * 0.5);
			double tap_539 = m_delay_20.read_linear(mul_540);
			double mul_537 = (tap_539 * 0.625);
			double tap_565 = m_delay_19.read_linear(mul_566);
			double mul_563 = (tap_565 * 0.625);
			double tap_508 = m_delay_18.read_linear(add_523);
			double tap_509 = m_delay_18.read_linear(add_522);
			double tap_510 = m_delay_18.read_linear(add_521);
			double tap_511 = m_delay_18.read_linear(add_520);
			double mul_512 = (tap_511 * expr_742);
			double add_485 = (mul_460 + mul_512);
			double mul_518 = (tap_508 * expr_745);
			double add_488 = (mul_463 + mul_518);
			double mul_516 = (tap_509 * expr_744);
			double add_487 = (mul_462 + mul_516);
			double mul_514 = (tap_510 * expr_743);
			double add_486 = (mul_461 + mul_514);
			double phasor_451 = m_phasor_39(div_430, samples_to_seconds);
			double add_423 = ((m_history_6 + phasor_451) + 0.75);
			double mod_422 = safemod(add_423, 1);
			double delta_405 = m_delta_40(mod_422);
			double sah_385 = m_sah_41(mul_403, delta_405, 0);
			double sah_404 = m_sah_42(mstosamps_445, delta_405, 0);
			double mul_395 = (sah_404 * mod_422);
			double sub_421 = (mod_422 - 0.5);
			double mul_420 = (sub_421 * 3.1415926535898);
			double cos_419 = cos(mul_420);
			double mul_414 = (cos_419 * cos_419);
			double add_444 = ((m_history_5 + phasor_451) + 0.25);
			double mod_443 = safemod(add_444, 1);
			double delta_411 = m_delta_43(mod_443);
			double sah_389 = m_sah_44(mul_409, delta_411, 0);
			double sah_410 = m_sah_45(mstosamps_445, delta_411, 0);
			double mul_397 = (sah_410 * mod_443);
			double sub_442 = (mod_443 - 0.5);
			double mul_441 = (sub_442 * 3.1415926535898);
			double cos_440 = cos(mul_441);
			double mul_416 = (cos_440 * cos_440);
			double add_429 = ((m_history_4 + phasor_451) + 0.5);
			double mod_428 = safemod(add_429, 1);
			double delta_408 = m_delta_46(mod_428);
			double sah_387 = m_sah_47(mul_406, delta_408, 0);
			double sah_407 = m_sah_48(mstosamps_445, delta_408, 0);
			double mul_396 = (sah_407 * mod_428);
			double sub_427 = (mod_428 - 0.5);
			double mul_426 = (sub_427 * 3.1415926535898);
			double cos_425 = cos(mul_426);
			double mul_415 = (cos_425 * cos_425);
			double add_450 = ((m_history_3 + phasor_451) + 0);
			double mod_449 = safemod(add_450, 1);
			double delta_392 = m_delta_49(mod_449);
			double sah_391 = m_sah_50(mul_412, delta_392, 0);
			double sah_413 = m_sah_51(mstosamps_445, delta_392, 0);
			double mul_398 = (sah_413 * mod_449);
			double tap_700 = m_delay_17.read_linear(mul_398);
			double tap_701 = m_delay_17.read_linear(mul_397);
			double tap_702 = m_delay_17.read_linear(mul_396);
			double tap_703 = m_delay_17.read_linear(mul_395);
			double mul_418 = (tap_703 * mul_414);
			double mul_424 = (tap_702 * mul_415);
			double mul_433 = (tap_701 * mul_416);
			double sub_448 = (mod_449 - 0.5);
			double mul_447 = (sub_448 * 3.1415926535898);
			double cos_446 = cos(mul_447);
			double mul_417 = (cos_446 * cos_446);
			double mul_434 = (tap_700 * mul_417);
			double mul_372 = ((((mul_434 + mul_433) + mul_424) + mul_418) * add_373);
			double sub_369 = (mul_372 - (mul_371 + mul_370));
			double mix_777 = (in1 + (m_shimmer_33 * (sub_369 - in1)));
			double mix_394 = mix_777;
			double mul_454 = (mix_394 * 0.707);
			double mix_778 = (mul_454 + (rsub_605 * (m_history_1 - mul_454)));
			double mix_604 = mix_778;
			double tap_588 = m_delay_16.read_linear(mul_589);
			double mul_586 = (tap_588 * 0.75);
			double sub_585 = (mix_604 - mul_586);
			double mul_584 = (sub_585 * 0.75);
			double add_583 = (mul_584 + tap_588);
			double tap_546 = m_delay_15.read_linear(mul_547);
			double mul_544 = (tap_546 * 0.625);
			double tap_572 = m_delay_14.read_linear(mul_573);
			double mul_570 = (tap_572 * 0.625);
			double tap_553 = m_delay_13.read_linear(mul_554);
			double mul_551 = (tap_553 * 0.75);
			double tap_581 = m_delay_12.read_linear(mul_582);
			double mul_579 = (tap_581 * 0.75);
			double mul_475 = (mul_463 * m_tail_32);
			double mul_473 = (mul_461 * m_tail_32);
			double add_459 = (mul_475 + mul_473);
			double mul_474 = (mul_462 * m_tail_32);
			double mul_472 = (mul_460 * m_tail_32);
			double add_458 = (mul_474 + mul_472);
			double sub_467 = (add_459 - add_458);
			double mul_471 = (mul_518 * m_early_34);
			double mul_469 = (mul_514 * m_early_34);
			double add_457 = (mul_471 + mul_469);
			double mul_470 = (mul_516 * m_early_34);
			double mul_468 = (mul_512 * m_early_34);
			double add_456 = (mul_470 + mul_468);
			double sub_466 = (add_457 - add_456);
			double add_453 = (sub_467 + sub_466);
			double add_455 = (add_453 + mix_394);
			double sub_550 = (add_455 - mul_551);
			double mul_549 = (sub_550 * 0.75);
			double add_548 = (mul_549 + tap_553);
			double sub_543 = (add_548 - mul_544);
			double mul_542 = (sub_543 * 0.625);
			double add_541 = (mul_542 + tap_546);
			double sub_536 = (add_541 - mul_537);
			double mul_535 = (sub_536 * 0.625);
			double add_534 = (mul_535 + tap_539);
			double mul_452 = (add_534 * m_mix_38);
			double out2 = (mul_452 + in1);
			double add_465 = (add_453 + mix_394);
			double sub_578 = (add_465 - mul_579);
			double mul_577 = (sub_578 * 0.75);
			double add_576 = (mul_577 + tap_581);
			double sub_569 = (add_576 - mul_570);
			double mul_568 = (sub_569 * 0.625);
			double add_567 = (mul_568 + tap_572);
			double sub_562 = (add_567 - mul_563);
			double mul_561 = (sub_562 * 0.625);
			double add_560 = (mul_561 + tap_565);
			double mul_464 = (add_560 * m_mix_38);
			double out1 = (mul_464 + in1);
			double y2_next_762 = m_y_2;
			double history_491_next_763 = mix_492;
			double history_599_next_764 = mix_600;
			double history_503_next_765 = mix_504;
			double history_497_next_766 = mix_498;
			double history_386_next_767 = sah_385;
			double history_390_next_768 = sah_389;
			double history_388_next_769 = sah_387;
			double history_393_next_770 = sah_391;
			double y1_next_771 = sub_369;
			double history_603_next_772 = mix_604;
			m_delay_24.write(add_485);
			m_delay_23.write(add_488);
			m_delay_22.write(add_487);
			m_delay_21.write(add_486);
			m_delay_20.write(sub_536);
			m_delay_19.write(sub_562);
			m_delay_18.write(add_583);
			m_delay_17.write(in1);
			m_delay_16.write(sub_585);
			m_delay_15.write(sub_543);
			m_delay_14.write(sub_569);
			m_delay_13.write(sub_550);
			m_delay_12.write(sub_578);
			m_y_11 = y2_next_762;
			m_history_10 = history_491_next_763;
			m_history_9 = history_599_next_764;
			m_history_8 = history_503_next_765;
			m_history_7 = history_497_next_766;
			m_history_6 = history_386_next_767;
			m_history_5 = history_390_next_768;
			m_history_4 = history_388_next_769;
			m_history_3 = history_393_next_770;
			m_y_2 = y1_next_771;
			m_history_1 = history_603_next_772;
			m_delay_12.step();
			m_delay_13.step();
			m_delay_14.step();
			m_delay_15.step();
			m_delay_16.step();
			m_delay_17.step();
			m_delay_18.step();
			m_delay_19.step();
			m_delay_20.step();
			m_delay_21.step();
			m_delay_22.step();
			m_delay_23.step();
			m_delay_24.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_window(double _value) {
		m_window_25 = (_value < 0.1 ? 0.1 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_blur(double _value) {
		m_blur_26 = (_value < 0.01 ? 0.01 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_tone(double _value) {
		m_tone_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_roomsize(double _value) {
		m_roomsize_28 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_damping(double _value) {
		m_damping_29 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_decay(double _value) {
		m_decay_30 = (_value < 0.1 ? 0.1 : (_value > 360 ? 360 : _value));
	};
	inline void set_spread(double _value) {
		m_spread_31 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_tail(double _value) {
		m_tail_32 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_shimmer(double _value) {
		m_shimmer_33 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_early(double _value) {
		m_early_34 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_cutoff(double _value) {
		m_cutoff_35 = (_value < 0 ? 0 : (_value > 6000 ? 6000 : _value));
	};
	inline void set_resonance(double _value) {
		m_resonance_36 = (_value < 0 ? 0 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_ratio(double _value) {
		m_ratio_37 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_38 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


/// 
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs 

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 14; }

/// Assistive lables for the signal inputs and outputs 

const char * gen_kernel_innames[] = { "in1" };
const char * gen_kernel_outnames[] = { "out1", "out2" };

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
		case 0: self->set_window(value); break;
		case 1: self->set_blur(value); break;
		case 2: self->set_tone(value); break;
		case 3: self->set_roomsize(value); break;
		case 4: self->set_damping(value); break;
		case 5: self->set_decay(value); break;
		case 6: self->set_spread(value); break;
		case 7: self->set_tail(value); break;
		case 8: self->set_shimmer(value); break;
		case 9: self->set_early(value); break;
		case 10: self->set_cutoff(value); break;
		case 11: self->set_resonance(value); break;
		case 12: self->set_ratio(value); break;
		case 13: self->set_mix(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_window_25; break;
		case 1: *value = self->m_blur_26; break;
		case 2: *value = self->m_tone_27; break;
		case 3: *value = self->m_roomsize_28; break;
		case 4: *value = self->m_damping_29; break;
		case 5: *value = self->m_decay_30; break;
		case 6: *value = self->m_spread_31; break;
		case 7: *value = self->m_tail_32; break;
		case 8: *value = self->m_shimmer_33; break;
		case 9: *value = self->m_early_34; break;
		case 10: *value = self->m_cutoff_35; break;
		case 11: *value = self->m_resonance_36; break;
		case 12: *value = self->m_ratio_37; break;
		case 13: *value = self->m_mix_38; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(14 * sizeof(ParamInfo));
	self->__commonstate.numparams = 14;
	// initialize parameter 0 ("m_window_25")
	pi = self->__commonstate.params + 0;
	pi->name = "window";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_window_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_blur_26")
	pi = self->__commonstate.params + 1;
	pi->name = "blur";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_blur_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_tone_27")
	pi = self->__commonstate.params + 2;
	pi->name = "tone";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tone_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_roomsize_28")
	pi = self->__commonstate.params + 3;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 300;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_damping_29")
	pi = self->__commonstate.params + 4;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_decay_30")
	pi = self->__commonstate.params + 5;
	pi->name = "decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decay_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 360;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_spread_31")
	pi = self->__commonstate.params + 6;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_tail_32")
	pi = self->__commonstate.params + 7;
	pi->name = "tail";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tail_32;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_shimmer_33")
	pi = self->__commonstate.params + 8;
	pi->name = "shimmer";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_shimmer_33;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_early_34")
	pi = self->__commonstate.params + 9;
	pi->name = "early";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_early_34;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_cutoff_35")
	pi = self->__commonstate.params + 10;
	pi->name = "cutoff";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cutoff_35;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 6000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_resonance_36")
	pi = self->__commonstate.params + 11;
	pi->name = "resonance";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_resonance_36;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_ratio_37")
	pi = self->__commonstate.params + 12;
	pi->name = "ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_37;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_mix_38")
	pi = self->__commonstate.params + 13;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_38;
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


} // gen_exported::
