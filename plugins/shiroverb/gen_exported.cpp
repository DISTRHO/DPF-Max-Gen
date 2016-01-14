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
	Delay m_delay_21;
	Delay m_delay_13;
	Delay m_delay_14;
	Delay m_delay_12;
	Delay m_delay_11;
	Delay m_delay_23;
	Delay m_delay_15;
	Delay m_delay_17;
	Delay m_delay_16;
	Delay m_delay_19;
	Delay m_delay_18;
	Delay m_delay_20;
	Delay m_delay_22;
	Delta m_delta_39;
	Delta m_delta_36;
	Delta m_delta_42;
	Delta m_delta_33;
	Phasor m_phasor_32;
	Sah m_sah_37;
	Sah m_sah_35;
	Sah m_sah_38;
	Sah m_sah_41;
	Sah m_sah_40;
	Sah m_sah_34;
	Sah m_sah_44;
	Sah m_sah_43;
	double m_history_5;
	double m_history_6;
	double m_history_7;
	double m_history_10;
	double m_history_4;
	double m_y_2;
	double m_history_3;
	double samplerate;
	double m_history_1;
	double m_history_9;
	double m_history_8;
	double m_ratio_31;
	double samples_to_seconds;
	double m_mix_25;
	double m_bandwidth_24;
	double m_roomsize_27;
	double m_shimmer_26;
	double m_damping_29;
	double m_tone_30;
	double m_decay_28;
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
		m_delay_11.reset("m_delay_11", 7000);
		m_delay_12.reset("m_delay_12", 5000);
		m_delay_13.reset("m_delay_13", 6000);
		m_delay_14.reset("m_delay_14", 48000);
		m_delay_15.reset("m_delay_15", 16000);
		m_delay_16.reset("m_delay_16", 15000);
		m_delay_17.reset("m_delay_17", 96000);
		m_delay_18.reset("m_delay_18", 12000);
		m_delay_19.reset("m_delay_19", 10000);
		m_delay_20.reset("m_delay_20", 48000);
		m_delay_21.reset("m_delay_21", 48000);
		m_delay_22.reset("m_delay_22", 48000);
		m_delay_23.reset("m_delay_23", 48000);
		m_bandwidth_24 = 75;
		m_mix_25 = 75;
		m_shimmer_26 = 30;
		m_roomsize_27 = 200;
		m_decay_28 = 50;
		m_damping_29 = 50;
		m_tone_30 = 1500;
		m_ratio_31 = 2;
		samples_to_seconds = (1 / samplerate);
		m_phasor_32.reset(0);
		m_delta_33.reset(0);
		m_sah_34.reset(0);
		m_sah_35.reset(0);
		m_delta_36.reset(0);
		m_sah_37.reset(0);
		m_sah_38.reset(0);
		m_delta_39.reset(0);
		m_sah_40.reset(0);
		m_sah_41.reset(0);
		m_delta_42.reset(0);
		m_sah_43.reset(0);
		m_sah_44.reset(0);
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
		double mul_13301 = (m_damping_29 * 0.01);
		double mul_13302 = (m_mix_25 * 0.01);
		double mul_13300 = (m_bandwidth_24 * 0.01);
		double rsub_13299 = (1 - mul_13300);
		double mul_13303 = (m_shimmer_26 * 0.01);
		double expr_13519 = safediv(((m_tone_30 * 2) * 3.1415926535898), 48000);
		double sin_13307 = sin(expr_13519);
		double clamp_13308 = ((sin_13307 <= 1e-05) ? 1e-05 : ((sin_13307 >= 0.99999) ? 0.99999 : sin_13307));
		double expr_13529 = safediv((m_roomsize_27 * 48000), 340);
		double mul_13509 = (expr_13529 * 1);
		double mul_13508 = (expr_13529 * 0.81649);
		double mul_13507 = (expr_13529 * 0.7071);
		double mul_13506 = (expr_13529 * 0.63245);
		double expr_13518 = safepow(1.0418, m_decay_28);
		double expr_13528 = safepow(0.001, safediv(1, (expr_13518 * 48000)));
		double expr_13527 = (-safepow(expr_13528, mul_13509));
		double expr_13522 = (-safepow(expr_13528, mul_13508));
		double expr_13521 = (-safepow(expr_13528, mul_13507));
		double expr_13520 = (-safepow(expr_13528, mul_13506));
		double mul_13503 = (expr_13529 * 0.000527);
		int int_13502 = int(mul_13503);
		double mul_13480 = (int_13502 * 400.600006);
		double mul_13459 = (int_13502 * 419.5);
		double rsub_13358 = (1 - m_ratio_31);
		double mul_13357 = (rsub_13358 * 10);
		samples_to_seconds = (1 / samplerate);
		double add_13446 = (expr_13529 + 5);
		double expr_13523 = safepow(expr_13528, add_13446);
		double mul_13487 = (int_13502 * 568.299988);
		double mul_13466 = (int_13502 * 566.700012);
		double mul_13452 = (expr_13529 * 0.41);
		double add_13449 = (mul_13452 + 5);
		double expr_13526 = safepow(expr_13528, add_13449);
		double mul_13451 = (expr_13529 * 0.3);
		double add_13448 = (mul_13451 + 5);
		double expr_13525 = safepow(expr_13528, add_13448);
		double mul_13450 = (expr_13529 * 0.155);
		double add_13447 = (mul_13450 + 5);
		double expr_13524 = safepow(expr_13528, add_13447);
		double mul_13501 = (expr_13529 * 0.110732);
		double mul_13494 = (int_13502 * 162.100006);
		double mul_13473 = (int_13502 * 144.800003);
		double mul_13297 = (m_decay_28 * 2);
		double clamp_13292 = ((mul_13297 <= 0) ? 0 : ((mul_13297 >= 100) ? 100 : mul_13297));
		double mul_13296 = (clamp_13292 * 0.01);
		double atodb_13295 = atodb(mul_13296);
		double sub_13294 = (atodb_13295 - 9);
		double dbtoa_13293 = dbtoa(sub_13294);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_13309 = noise();
			double abs_13326 = fabs(noise_13309);
			double mul_13330 = (abs_13326 * 0.25);
			double noise_13310 = noise();
			double abs_13327 = fabs(noise_13310);
			double mul_13333 = (abs_13327 * 0.25);
			double noise_13311 = noise();
			double abs_13328 = fabs(noise_13311);
			double mul_13336 = (abs_13328 * 0.25);
			double noise_13312 = noise();
			double abs_13329 = fabs(noise_13312);
			double mul_13339 = (abs_13329 * 0.25);
			double tap_13514 = m_delay_23.read_cubic(mul_13509);
			double tap_13432 = m_delay_22.read_cubic(mul_13508);
			double tap_13426 = m_delay_21.read_cubic(mul_13507);
			double tap_13420 = m_delay_20.read_cubic(mul_13506);
			double mul_13505 = (tap_13514 * expr_13527);
			double mix_13540 = (mul_13505 + (mul_13301 * (m_history_10 - mul_13505)));
			double mix_13512 = mix_13540;
			double mul_13428 = (tap_13432 * expr_13522);
			double mix_13541 = (mul_13428 + (mul_13301 * (m_history_9 - mul_13428)));
			double mix_13430 = mix_13541;
			double mul_13422 = (tap_13426 * expr_13521);
			double mix_13542 = (mul_13422 + (mul_13301 * (m_history_8 - mul_13422)));
			double mix_13424 = mix_13542;
			double mul_13416 = (tap_13420 * expr_13520);
			double mix_13543 = (mul_13416 + (mul_13301 * (m_history_7 - mul_13416)));
			double mix_13418 = mix_13543;
			double tap_13479 = m_delay_19.read_linear(mul_13480);
			double mul_13477 = (tap_13479 * 0.625);
			double tap_13458 = m_delay_18.read_linear(mul_13459);
			double mul_13456 = (tap_13458 * 0.625);
			double phasor_13376 = m_phasor_32(mul_13357, samples_to_seconds);
			double add_13350 = ((m_history_6 + phasor_13376) + 0.75);
			double mod_13349 = safemod(add_13350, 1);
			double delta_13332 = m_delta_33(mod_13349);
			double sah_13313 = m_sah_34(mul_13330, delta_13332, 0);
			int sah_13331 = m_sah_35(4800, delta_13332, 0);
			double mul_13322 = (sah_13331 * mod_13349);
			double sub_13348 = (mod_13349 - 0.5);
			double mul_13347 = (sub_13348 * 3.1415926535898);
			double cos_13346 = cos(mul_13347);
			double mul_13341 = (cos_13346 * cos_13346);
			double add_13356 = ((m_history_5 + phasor_13376) + 0.5);
			double mod_13355 = safemod(add_13356, 1);
			double delta_13335 = m_delta_36(mod_13355);
			double sah_13315 = m_sah_37(mul_13333, delta_13335, 0);
			int sah_13334 = m_sah_38(4800, delta_13335, 0);
			double mul_13323 = (sah_13334 * mod_13355);
			double sub_13354 = (mod_13355 - 0.5);
			double mul_13353 = (sub_13354 * 3.1415926535898);
			double cos_13352 = cos(mul_13353);
			double mul_13342 = (cos_13352 * cos_13352);
			double add_13370 = ((m_history_4 + phasor_13376) + 0.25);
			double mod_13369 = safemod(add_13370, 1);
			double delta_13338 = m_delta_39(mod_13369);
			double sah_13317 = m_sah_40(mul_13336, delta_13338, 0);
			int sah_13337 = m_sah_41(4800, delta_13338, 0);
			double mul_13324 = (sah_13337 * mod_13369);
			double sub_13368 = (mod_13369 - 0.5);
			double mul_13367 = (sub_13368 * 3.1415926535898);
			double cos_13366 = cos(mul_13367);
			double mul_13343 = (cos_13366 * cos_13366);
			double add_13375 = ((m_history_3 + phasor_13376) + 0);
			double mod_13374 = safemod(add_13375, 1);
			double delta_13320 = m_delta_42(mod_13374);
			double sah_13319 = m_sah_43(mul_13339, delta_13320, 0);
			int sah_13340 = m_sah_44(4800, delta_13320, 0);
			double mul_13325 = (sah_13340 * mod_13374);
			double tap_13362 = m_delay_17.read_linear(mul_13325);
			double tap_13363 = m_delay_17.read_linear(mul_13324);
			double tap_13364 = m_delay_17.read_linear(mul_13323);
			double tap_13365 = m_delay_17.read_linear(mul_13322);
			double mul_13345 = (tap_13365 * mul_13341);
			double mul_13351 = (tap_13364 * mul_13342);
			double mul_13359 = (tap_13363 * mul_13343);
			double sub_13373 = (mod_13374 - 0.5);
			double mul_13372 = (sub_13373 * 3.1415926535898);
			double cos_13371 = cos(mul_13372);
			double mul_13344 = (cos_13371 * cos_13371);
			double mul_13360 = (tap_13362 * mul_13344);
			double add_13545 = (((mul_13360 + mul_13359) + mul_13351) + mul_13345);
			double mix_13544 = (m_y_2 + (clamp_13308 * (add_13545 - m_y_2)));
			double mix_13305 = mix_13544;
			double mix_13546 = (in1 + (mul_13303 * (mix_13305 - in1)));
			double mix_13377 = mix_13546;
			double mul_13380 = (mix_13377 * 0.707);
			double mix_13547 = (mul_13380 + (rsub_13299 * (m_history_1 - mul_13380)));
			double mix_13516 = mix_13547;
			double add_13410 = (mix_13512 + mix_13430);
			double add_13408 = (mix_13424 + mix_13418);
			double sub_13407 = (add_13410 - add_13408);
			double mul_13389 = (sub_13407 * 0.5);
			double add_13403 = (add_13410 + add_13408);
			double mul_13386 = (add_13403 * 0.5);
			double tap_13486 = m_delay_16.read_linear(mul_13487);
			double tap_13465 = m_delay_15.read_linear(mul_13466);
			double sub_13409 = (mix_13512 - mix_13430);
			double sub_13406 = (mix_13424 - mix_13418);
			double sub_13405 = (sub_13409 - sub_13406);
			double mul_13388 = (sub_13405 * 0.5);
			double add_13404 = (sub_13409 + sub_13406);
			double rsub_13402 = (0 - add_13404);
			double mul_13387 = (rsub_13402 * 0.5);
			double tap_13434 = m_delay_14.read_cubic(add_13449);
			double tap_13435 = m_delay_14.read_cubic(add_13448);
			double tap_13436 = m_delay_14.read_cubic(add_13447);
			double tap_13437 = m_delay_14.read_cubic(add_13446);
			double mul_13444 = (tap_13434 * expr_13526);
			double add_13414 = (mul_13389 + mul_13444);
			double mul_13442 = (tap_13435 * expr_13525);
			double add_13413 = (mul_13388 + mul_13442);
			double mul_13438 = (tap_13437 * expr_13523);
			double add_13411 = (mul_13386 + mul_13438);
			double mul_13440 = (tap_13436 * expr_13524);
			double add_13412 = (mul_13387 + mul_13440);
			double mul_13484 = (tap_13486 * 0.625);
			double mul_13463 = (tap_13465 * 0.625);
			double tap_13500 = m_delay_13.read_cubic(mul_13501);
			double mul_13498 = (tap_13500 * 0.75);
			double sub_13497 = (mix_13516 - mul_13498);
			double mul_13496 = (sub_13497 * 0.75);
			double add_13495 = (mul_13496 + tap_13500);
			double tap_13493 = m_delay_12.read_linear(mul_13494);
			double tap_13472 = m_delay_11.read_linear(mul_13473);
			double mul_13491 = (tap_13493 * 0.75);
			double mul_13470 = (tap_13472 * 0.75);
			double mul_13397 = (mul_13444 * mul_13296);
			double mul_13395 = (mul_13440 * mul_13296);
			double add_13383 = (mul_13397 + mul_13395);
			double mul_13396 = (mul_13442 * mul_13296);
			double mul_13394 = (mul_13438 * mul_13296);
			double add_13382 = (mul_13396 + mul_13394);
			double sub_13392 = (add_13383 - add_13382);
			double mul_13401 = (mul_13389 * dbtoa_13293);
			double mul_13399 = (mul_13387 * dbtoa_13293);
			double add_13385 = (mul_13401 + mul_13399);
			double mul_13400 = (mul_13388 * dbtoa_13293);
			double mul_13398 = (mul_13386 * dbtoa_13293);
			double add_13384 = (mul_13400 + mul_13398);
			double sub_13393 = (add_13385 - add_13384);
			double add_13379 = (sub_13393 + sub_13392);
			double add_13391 = (add_13379 + mix_13377);
			double sub_13490 = (add_13391 - mul_13491);
			double mul_13489 = (sub_13490 * 0.75);
			double add_13488 = (mul_13489 + tap_13493);
			double sub_13483 = (add_13488 - mul_13484);
			double mul_13482 = (sub_13483 * 0.625);
			double add_13481 = (mul_13482 + tap_13486);
			double sub_13476 = (add_13481 - mul_13477);
			double mul_13475 = (sub_13476 * 0.625);
			double add_13474 = (mul_13475 + tap_13479);
			double mul_13390 = (add_13474 * mul_13302);
			double out1 = (in1 + mul_13390);
			double add_13381 = (add_13379 + mix_13377);
			double sub_13469 = (add_13381 - mul_13470);
			double mul_13468 = (sub_13469 * 0.75);
			double add_13467 = (mul_13468 + tap_13472);
			double sub_13462 = (add_13467 - mul_13463);
			double mul_13461 = (sub_13462 * 0.625);
			double add_13460 = (mul_13461 + tap_13465);
			double sub_13455 = (add_13460 - mul_13456);
			double mul_13454 = (sub_13455 * 0.625);
			double add_13453 = (mul_13454 + tap_13458);
			double mul_13378 = (add_13453 * mul_13302);
			double out2 = (in1 + mul_13378);
			double history_13511_next_13530 = mix_13512;
			double history_13429_next_13531 = mix_13430;
			double history_13423_next_13532 = mix_13424;
			double history_13417_next_13533 = mix_13418;
			double history_13314_next_13534 = sah_13313;
			double history_13316_next_13535 = sah_13315;
			double history_13318_next_13536 = sah_13317;
			double history_13321_next_13537 = sah_13319;
			double y0_next_13538 = mix_13305;
			double history_13515_next_13539 = mix_13516;
			m_delay_23.write(add_13414);
			m_delay_22.write(add_13413);
			m_delay_21.write(add_13412);
			m_delay_20.write(add_13411);
			m_delay_19.write(sub_13476);
			m_delay_18.write(sub_13455);
			m_delay_17.write(in1);
			m_delay_16.write(sub_13483);
			m_delay_15.write(sub_13462);
			m_delay_14.write(add_13495);
			m_delay_13.write(sub_13497);
			m_delay_12.write(sub_13490);
			m_delay_11.write(sub_13469);
			m_history_10 = history_13511_next_13530;
			m_history_9 = history_13429_next_13531;
			m_history_8 = history_13423_next_13532;
			m_history_7 = history_13417_next_13533;
			m_history_6 = history_13314_next_13534;
			m_history_5 = history_13316_next_13535;
			m_history_4 = history_13318_next_13536;
			m_history_3 = history_13321_next_13537;
			m_y_2 = y0_next_13538;
			m_history_1 = history_13515_next_13539;
			m_delay_11.step();
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
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_bandwidth(double _value) {
		m_bandwidth_24 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_25 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_shimmer(double _value) {
		m_shimmer_26 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_roomsize(double _value) {
		m_roomsize_27 = (_value < 1 ? 1 : (_value > 300 ? 300 : _value));
	};
	inline void set_decay(double _value) {
		m_decay_28 = (_value < 1 ? 1 : (_value > 100 ? 100 : _value));
	};
	inline void set_damping(double _value) {
		m_damping_29 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_tone(double _value) {
		m_tone_30 = (_value < 500 ? 500 : (_value > 6000 ? 6000 : _value));
	};
	inline void set_ratio(double _value) {
		m_ratio_31 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
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
int num_params() { return 8; }

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
		case 0: self->set_bandwidth(value); break;
		case 1: self->set_mix(value); break;
		case 2: self->set_shimmer(value); break;
		case 3: self->set_roomsize(value); break;
		case 4: self->set_decay(value); break;
		case 5: self->set_damping(value); break;
		case 6: self->set_tone(value); break;
		case 7: self->set_ratio(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_bandwidth_24; break;
		case 1: *value = self->m_mix_25; break;
		case 2: *value = self->m_shimmer_26; break;
		case 3: *value = self->m_roomsize_27; break;
		case 4: *value = self->m_decay_28; break;
		case 5: *value = self->m_damping_29; break;
		case 6: *value = self->m_tone_30; break;
		case 7: *value = self->m_ratio_31; break;
		
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
	// initialize parameter 0 ("m_bandwidth_24")
	pi = self->__commonstate.params + 0;
	pi->name = "bandwidth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_bandwidth_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_mix_25")
	pi = self->__commonstate.params + 1;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_shimmer_26")
	pi = self->__commonstate.params + 2;
	pi->name = "shimmer";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_shimmer_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_roomsize_27")
	pi = self->__commonstate.params + 3;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 300;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_decay_28")
	pi = self->__commonstate.params + 4;
	pi->name = "decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decay_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_damping_29")
	pi = self->__commonstate.params + 5;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_tone_30")
	pi = self->__commonstate.params + 6;
	pi->name = "tone";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tone_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 500;
	pi->outputmax = 6000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_ratio_31")
	pi = self->__commonstate.params + 7;
	pi->name = "ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
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
