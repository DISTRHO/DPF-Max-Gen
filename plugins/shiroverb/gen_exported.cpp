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
	double m_mix_34;
	double m_resonance_35;
	double m_cutoff_36;
	double m_window_38;
	double m_blur_33;
	double m_shift_37;
	double samples_to_seconds;
	double m_tail_32;
	double m_ratio_25;
	double m_damping_30;
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
	double m_decay_29;
	double m_history_8;
	double m_early_27;
	double m_y_11;
	double m_history_10;
	double m_tone_26;
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
		m_delay_12.reset("m_delay_12", 7000);
		m_delay_13.reset("m_delay_13", 5000);
		m_delay_14.reset("m_delay_14", 16000);
		m_delay_15.reset("m_delay_15", 15000);
		m_delay_16.reset("m_delay_16", 6000);
		m_delay_17.reset("m_delay_17", 88200);
		m_delay_18.reset("m_delay_18", 48000);
		m_delay_19.reset("m_delay_19", 12000);
		m_delay_20.reset("m_delay_20", 10000);
		m_delay_21.reset("m_delay_21", 48000);
		m_delay_22.reset("m_delay_22", 48000);
		m_delay_23.reset("m_delay_23", 48000);
		m_delay_24.reset("m_delay_24", 48000);
		m_ratio_25 = 2;
		m_tone_26 = 0.5;
		m_early_27 = 0.25;
		m_roomsize_28 = 75;
		m_decay_29 = 11;
		m_damping_30 = 0.7;
		m_spread_31 = 23;
		m_tail_32 = 0.25;
		m_blur_33 = 0;
		m_mix_34 = 1;
		m_resonance_35 = 0;
		m_cutoff_36 = 8000;
		m_shift_37 = 1;
		m_window_38 = 100;
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
		double rsub_11547 = (1 - m_tone_26);
		double expr_11686 = safepow(0.001, safediv(1, (m_decay_29 * 44100)));
		double expr_11687 = safediv((m_roomsize_28 * 44100), 340);
		double mul_11539 = (expr_11687 * 1);
		double expr_11685 = (-safepow(expr_11686, mul_11539));
		double mul_11537 = (expr_11687 * 0.7071);
		double expr_11679 = (-safepow(expr_11686, mul_11537));
		double mul_11538 = (expr_11687 * 0.81649);
		double expr_11680 = (-safepow(expr_11686, mul_11538));
		double mul_11536 = (expr_11687 * 0.63245);
		double expr_11678 = (-safepow(expr_11686, mul_11536));
		double expr_11677 = safediv(((m_cutoff_36 * 2) * 3.1415926535898), 44100);
		double cos_11390 = cos(expr_11677);
		double mul_11392 = (m_resonance_35 * 0.125);
		double exp_11393 = exp(mul_11392);
		double mul_11391 = (exp_11393 * 0.882497);
		double mul_11387 = (mul_11391 * mul_11391);
		double mul_11389 = (cos_11390 * mul_11391);
		double mul_11388 = (mul_11389 * -2);
		double add_11386 = ((mul_11387 + mul_11388) + 1);
		double mul_11533 = (expr_11687 * 0.000527);
		int int_11532 = int(mul_11533);
		double mstosamps_11374 = (m_window_38 * (samplerate * 0.001));
		double add_11462 = (expr_11687 + 5);
		double expr_11681 = safepow(expr_11686, add_11462);
		double mul_11501 = (m_spread_31 * 0.376623);
		double add_11500 = (mul_11501 + 931);
		double rsub_11497 = (1341 - add_11500);
		double mul_11508 = (int_11532 * rsub_11497);
		double mul_11473 = (m_spread_31 * -0.380445);
		double add_11472 = (mul_11473 + 931);
		double rsub_11469 = (1341 - add_11472);
		double mul_11482 = (int_11532 * rsub_11469);
		double mul_11468 = (expr_11687 * 0.41);
		double add_11465 = (mul_11468 + 5);
		double expr_11684 = safepow(expr_11686, add_11465);
		double mul_11467 = (expr_11687 * 0.3);
		double add_11464 = (mul_11467 + 5);
		double expr_11683 = safepow(expr_11686, add_11464);
		double mul_11466 = (expr_11687 * 0.155);
		double add_11463 = (mul_11466 + 5);
		double expr_11682 = safepow(expr_11686, add_11463);
		double rsub_11361 = (1 - m_ratio_25);
		double mul_11360 = (rsub_11361 * 1000);
		double div_11359 = safediv(mul_11360, m_window_38);
		samples_to_seconds = (1 / samplerate);
		double mul_11531 = (expr_11687 * 0.110732);
		double mul_11517 = (m_spread_31 * 0.125541);
		double add_11499 = (mul_11517 + 369);
		double rsub_11498 = (add_11500 - add_11499);
		double mul_11515 = (int_11532 * rsub_11498);
		double mul_11475 = (m_spread_31 * -0.568366);
		double add_11471 = (mul_11475 + 369);
		double rsub_11470 = (add_11472 - add_11471);
		double mul_11489 = (int_11532 * rsub_11470);
		double add_11516 = (mul_11517 + 159);
		double mul_11524 = (int_11532 * add_11516);
		double add_11474 = (mul_11475 + 159);
		double mul_11496 = (int_11532 * add_11474);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_11310 = noise();
			double abs_11328 = fabs(noise_11310);
			double mul_11332 = (abs_11328 * m_blur_33);
			double noise_11311 = noise();
			double abs_11329 = fabs(noise_11311);
			double mul_11335 = (abs_11329 * m_blur_33);
			double noise_11313 = noise();
			double abs_11331 = fabs(noise_11313);
			double mul_11341 = (abs_11331 * m_blur_33);
			double noise_11312 = noise();
			double abs_11330 = fabs(noise_11312);
			double mul_11338 = (abs_11330 * m_blur_33);
			double tap_11544 = m_delay_24.read_linear(mul_11539);
			double mul_11535 = (tap_11544 * expr_11685);
			double mix_11730 = (mul_11535 + (m_damping_30 * (m_history_10 - mul_11535)));
			double mix_11542 = mix_11730;
			double tap_11442 = m_delay_23.read_linear(mul_11537);
			double mul_11438 = (tap_11442 * expr_11679);
			double mix_11731 = (mul_11438 + (m_damping_30 * (m_history_9 - mul_11438)));
			double mix_11440 = mix_11731;
			double tap_11448 = m_delay_22.read_linear(mul_11538);
			double mul_11444 = (tap_11448 * expr_11680);
			double mix_11732 = (mul_11444 + (m_damping_30 * (m_history_8 - mul_11444)));
			double mix_11446 = mix_11732;
			double tap_11436 = m_delay_21.read_linear(mul_11536);
			double mul_11432 = (tap_11436 * expr_11678);
			double mix_11733 = (mul_11432 + (m_damping_30 * (m_history_7 - mul_11432)));
			double mix_11434 = mix_11733;
			double mul_11383 = (mul_11387 * m_y_11);
			double mul_11384 = (mul_11388 * m_y_2);
			double add_11426 = (mix_11542 + mix_11446);
			double add_11424 = (mix_11440 + mix_11434);
			double sub_11423 = (add_11426 - add_11424);
			double mul_11405 = (sub_11423 * 0.5);
			double add_11419 = (add_11426 + add_11424);
			double mul_11402 = (add_11419 * 0.5);
			double tap_11507 = m_delay_20.read_linear(mul_11508);
			double mul_11505 = (tap_11507 * 0.625);
			double tap_11481 = m_delay_19.read_linear(mul_11482);
			double mul_11479 = (tap_11481 * 0.625);
			double sub_11425 = (mix_11542 - mix_11446);
			double sub_11422 = (mix_11440 - mix_11434);
			double sub_11421 = (sub_11425 - sub_11422);
			double mul_11404 = (sub_11421 * 0.5);
			double add_11420 = (sub_11425 + sub_11422);
			double rsub_11418 = (0 - add_11420);
			double mul_11403 = (rsub_11418 * 0.5);
			double tap_11450 = m_delay_18.read_linear(add_11465);
			double tap_11451 = m_delay_18.read_linear(add_11464);
			double tap_11452 = m_delay_18.read_linear(add_11463);
			double tap_11453 = m_delay_18.read_linear(add_11462);
			double mul_11460 = (tap_11450 * expr_11684);
			double add_11430 = (mul_11405 + mul_11460);
			double mul_11458 = (tap_11451 * expr_11683);
			double add_11429 = (mul_11404 + mul_11458);
			double mul_11454 = (tap_11453 * expr_11681);
			double add_11427 = (mul_11402 + mul_11454);
			double mul_11456 = (tap_11452 * expr_11682);
			double add_11428 = (mul_11403 + mul_11456);
			double phasor_11380 = m_phasor_39(div_11359, samples_to_seconds);
			double add_11352 = ((m_history_6 + phasor_11380) + 0.75);
			double mod_11351 = safemod(add_11352, 1);
			double delta_11334 = m_delta_40(mod_11351);
			double sah_11314 = m_sah_41(mul_11332, delta_11334, 0);
			double sah_11333 = m_sah_42(mstosamps_11374, delta_11334, 0);
			double mul_11324 = (sah_11333 * mod_11351);
			double sub_11350 = (mod_11351 - 0.5);
			double mul_11349 = (sub_11350 * 3.1415926535898);
			double cos_11348 = cos(mul_11349);
			double mul_11343 = (cos_11348 * cos_11348);
			double add_11358 = ((m_history_5 + phasor_11380) + 0.5);
			double mod_11357 = safemod(add_11358, 1);
			double delta_11337 = m_delta_43(mod_11357);
			double sah_11316 = m_sah_44(mul_11335, delta_11337, 0);
			double sah_11336 = m_sah_45(mstosamps_11374, delta_11337, 0);
			double mul_11325 = (sah_11336 * mod_11357);
			double sub_11356 = (mod_11357 - 0.5);
			double mul_11355 = (sub_11356 * 3.1415926535898);
			double cos_11354 = cos(mul_11355);
			double mul_11344 = (cos_11354 * cos_11354);
			double add_11379 = ((m_history_4 + phasor_11380) + 0);
			double mod_11378 = safemod(add_11379, 1);
			double delta_11321 = m_delta_46(mod_11378);
			double sah_11320 = m_sah_47(mul_11341, delta_11321, 0);
			double sah_11342 = m_sah_48(mstosamps_11374, delta_11321, 0);
			double mul_11327 = (sah_11342 * mod_11378);
			double sub_11377 = (mod_11378 - 0.5);
			double mul_11376 = (sub_11377 * 3.1415926535898);
			double cos_11375 = cos(mul_11376);
			double mul_11346 = (cos_11375 * cos_11375);
			double add_11373 = ((m_history_3 + phasor_11380) + 0.25);
			double mod_11372 = safemod(add_11373, 1);
			double delta_11340 = m_delta_49(mod_11372);
			double sah_11318 = m_sah_50(mul_11338, delta_11340, 0);
			double sah_11339 = m_sah_51(mstosamps_11374, delta_11340, 0);
			double mul_11326 = (sah_11339 * mod_11372);
			double tap_11365 = m_delay_17.read_linear(mul_11327);
			double tap_11366 = m_delay_17.read_linear(mul_11326);
			double tap_11367 = m_delay_17.read_linear(mul_11325);
			double tap_11368 = m_delay_17.read_linear(mul_11324);
			double mul_11347 = (tap_11368 * mul_11343);
			double mul_11353 = (tap_11367 * mul_11344);
			double mul_11363 = (tap_11365 * mul_11346);
			double sub_11371 = (mod_11372 - 0.5);
			double mul_11370 = (sub_11371 * 3.1415926535898);
			double cos_11369 = cos(mul_11370);
			double mul_11345 = (cos_11369 * cos_11369);
			double mul_11362 = (tap_11366 * mul_11345);
			double mul_11385 = ((((mul_11363 + mul_11362) + mul_11353) + mul_11347) * add_11386);
			double sub_11382 = (mul_11385 - (mul_11383 + mul_11384));
			double mix_11734 = (in1 + (m_shift_37 * (sub_11382 - in1)));
			double mix_11323 = mix_11734;
			double mul_11396 = (mix_11323 * 0.707);
			double mix_11735 = (mul_11396 + (rsub_11547 * (m_history_1 - mul_11396)));
			double mix_11546 = mix_11735;
			double tap_11530 = m_delay_16.read_linear(mul_11531);
			double mul_11528 = (tap_11530 * 0.75);
			double sub_11527 = (mix_11546 - mul_11528);
			double mul_11526 = (sub_11527 * 0.75);
			double add_11525 = (mul_11526 + tap_11530);
			double tap_11514 = m_delay_15.read_linear(mul_11515);
			double mul_11512 = (tap_11514 * 0.625);
			double tap_11488 = m_delay_14.read_linear(mul_11489);
			double mul_11486 = (tap_11488 * 0.625);
			double tap_11523 = m_delay_13.read_linear(mul_11524);
			double mul_11521 = (tap_11523 * 0.75);
			double tap_11495 = m_delay_12.read_linear(mul_11496);
			double mul_11493 = (tap_11495 * 0.75);
			double mul_11417 = (mul_11405 * m_tail_32);
			double mul_11415 = (mul_11403 * m_tail_32);
			double add_11401 = (mul_11417 + mul_11415);
			double mul_11416 = (mul_11404 * m_tail_32);
			double mul_11414 = (mul_11402 * m_tail_32);
			double add_11400 = (mul_11416 + mul_11414);
			double sub_11409 = (add_11401 - add_11400);
			double mul_11413 = (mul_11460 * m_early_27);
			double mul_11411 = (mul_11456 * m_early_27);
			double add_11399 = (mul_11413 + mul_11411);
			double mul_11412 = (mul_11458 * m_early_27);
			double mul_11410 = (mul_11454 * m_early_27);
			double add_11398 = (mul_11412 + mul_11410);
			double sub_11408 = (add_11399 - add_11398);
			double add_11395 = (sub_11409 + sub_11408);
			double add_11407 = (add_11395 + mix_11323);
			double sub_11520 = (add_11407 - mul_11521);
			double mul_11519 = (sub_11520 * 0.75);
			double add_11518 = (mul_11519 + tap_11523);
			double sub_11511 = (add_11518 - mul_11512);
			double mul_11510 = (sub_11511 * 0.625);
			double add_11509 = (mul_11510 + tap_11514);
			double sub_11504 = (add_11509 - mul_11505);
			double mul_11503 = (sub_11504 * 0.625);
			double add_11502 = (mul_11503 + tap_11507);
			double mul_11406 = (add_11502 * m_mix_34);
			double out1 = (mul_11406 + in1);
			double add_11397 = (add_11395 + mix_11323);
			double sub_11492 = (add_11397 - mul_11493);
			double mul_11491 = (sub_11492 * 0.75);
			double add_11490 = (mul_11491 + tap_11495);
			double sub_11485 = (add_11490 - mul_11486);
			double mul_11484 = (sub_11485 * 0.625);
			double add_11483 = (mul_11484 + tap_11488);
			double sub_11478 = (add_11483 - mul_11479);
			double mul_11477 = (sub_11478 * 0.625);
			double add_11476 = (mul_11477 + tap_11481);
			double mul_11394 = (add_11476 * m_mix_34);
			double out2 = (mul_11394 + in1);
			double y2_next_11701 = m_y_2;
			double history_11541_next_11702 = mix_11542;
			double history_11439_next_11703 = mix_11440;
			double history_11445_next_11704 = mix_11446;
			double history_11433_next_11705 = mix_11434;
			double history_11315_next_11706 = sah_11314;
			double history_11317_next_11707 = sah_11316;
			double history_11322_next_11708 = sah_11320;
			double history_11319_next_11709 = sah_11318;
			double y1_next_11710 = sub_11382;
			double history_11545_next_11711 = mix_11546;
			m_delay_24.write(add_11430);
			m_delay_23.write(add_11428);
			m_delay_22.write(add_11429);
			m_delay_21.write(add_11427);
			m_delay_20.write(sub_11504);
			m_delay_19.write(sub_11478);
			m_delay_18.write(add_11525);
			m_delay_17.write(in1);
			m_delay_16.write(sub_11527);
			m_delay_15.write(sub_11511);
			m_delay_14.write(sub_11485);
			m_delay_13.write(sub_11520);
			m_delay_12.write(sub_11492);
			m_y_11 = y2_next_11701;
			m_history_10 = history_11541_next_11702;
			m_history_9 = history_11439_next_11703;
			m_history_8 = history_11445_next_11704;
			m_history_7 = history_11433_next_11705;
			m_history_6 = history_11315_next_11706;
			m_history_5 = history_11317_next_11707;
			m_history_4 = history_11322_next_11708;
			m_history_3 = history_11319_next_11709;
			m_y_2 = y1_next_11710;
			m_history_1 = history_11545_next_11711;
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
	inline void set_ratio(double _value) {
		m_ratio_25 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_tone(double _value) {
		m_tone_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_early(double _value) {
		m_early_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_roomsize(double _value) {
		m_roomsize_28 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_decay(double _value) {
		m_decay_29 = (_value < 0.1 ? 0.1 : (_value > 360 ? 360 : _value));
	};
	inline void set_damping(double _value) {
		m_damping_30 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_spread(double _value) {
		m_spread_31 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_tail(double _value) {
		m_tail_32 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_blur(double _value) {
		m_blur_33 = (_value < 0 ? 0 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_34 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_resonance(double _value) {
		m_resonance_35 = (_value < 0 ? 0 : (_value > 0.5 ? 0.5 : _value));
	};
	inline void set_cutoff(double _value) {
		m_cutoff_36 = (_value < 0 ? 0 : (_value > 8000 ? 8000 : _value));
	};
	inline void set_shift(double _value) {
		m_shift_37 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_window(double _value) {
		m_window_38 = (_value < 0.1 ? 0.1 : (_value > 1000 ? 1000 : _value));
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
		case 0: self->set_ratio(value); break;
		case 1: self->set_tone(value); break;
		case 2: self->set_early(value); break;
		case 3: self->set_roomsize(value); break;
		case 4: self->set_decay(value); break;
		case 5: self->set_damping(value); break;
		case 6: self->set_spread(value); break;
		case 7: self->set_tail(value); break;
		case 8: self->set_blur(value); break;
		case 9: self->set_mix(value); break;
		case 10: self->set_resonance(value); break;
		case 11: self->set_cutoff(value); break;
		case 12: self->set_shift(value); break;
		case 13: self->set_window(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_ratio_25; break;
		case 1: *value = self->m_tone_26; break;
		case 2: *value = self->m_early_27; break;
		case 3: *value = self->m_roomsize_28; break;
		case 4: *value = self->m_decay_29; break;
		case 5: *value = self->m_damping_30; break;
		case 6: *value = self->m_spread_31; break;
		case 7: *value = self->m_tail_32; break;
		case 8: *value = self->m_blur_33; break;
		case 9: *value = self->m_mix_34; break;
		case 10: *value = self->m_resonance_35; break;
		case 11: *value = self->m_cutoff_36; break;
		case 12: *value = self->m_shift_37; break;
		case 13: *value = self->m_window_38; break;
		
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
	// initialize parameter 0 ("m_ratio_25")
	pi = self->__commonstate.params + 0;
	pi->name = "ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_tone_26")
	pi = self->__commonstate.params + 1;
	pi->name = "tone";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tone_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_early_27")
	pi = self->__commonstate.params + 2;
	pi->name = "early";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_early_27;
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
	// initialize parameter 4 ("m_decay_29")
	pi = self->__commonstate.params + 4;
	pi->name = "decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decay_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 360;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_damping_30")
	pi = self->__commonstate.params + 5;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
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
	// initialize parameter 8 ("m_blur_33")
	pi = self->__commonstate.params + 8;
	pi->name = "blur";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_blur_33;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_mix_34")
	pi = self->__commonstate.params + 9;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_34;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_resonance_35")
	pi = self->__commonstate.params + 10;
	pi->name = "resonance";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_resonance_35;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_cutoff_36")
	pi = self->__commonstate.params + 11;
	pi->name = "cutoff";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cutoff_36;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 8000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_shift_37")
	pi = self->__commonstate.params + 12;
	pi->name = "shift";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_shift_37;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_window_38")
	pi = self->__commonstate.params + 13;
	pi->name = "window";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_window_38;
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
