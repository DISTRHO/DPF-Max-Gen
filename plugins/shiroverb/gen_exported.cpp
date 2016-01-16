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
	Delay m_delay_22;
	Delay m_delay_14;
	Delay m_delay_15;
	Delay m_delay_13;
	Delay m_delay_12;
	Delay m_delay_23;
	Delay m_delay_16;
	Delay m_delay_18;
	Delay m_delay_17;
	Delay m_delay_20;
	Delay m_delay_19;
	Delay m_delay_21;
	Delay m_delay_24;
	Delta m_delta_34;
	Delta m_delta_43;
	Delta m_delta_37;
	Delta m_delta_40;
	Phasor m_phasor_33;
	Sah m_sah_42;
	Sah m_sah_41;
	Sah m_sah_39;
	Sah m_sah_36;
	Sah m_sah_38;
	Sah m_sah_35;
	Sah m_sah_44;
	Sah m_sah_45;
	double m_history_10;
	double m_history_5;
	double m_history_6;
	double m_history_7;
	double m_smth_11;
	double m_history_4;
	double m_y_2;
	double m_history_3;
	double samplerate;
	double m_history_1;
	double m_history_9;
	double m_history_8;
	double m_ratio_32;
	double samples_to_seconds;
	double m_mix_26;
	double m_bandwidth_25;
	double m_damping_28;
	double m_decay_27;
	double m_tone_30;
	double m_shimmer_31;
	double m_roomsize_29;
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
		m_smth_11 = 0;
		m_delay_12.reset("m_delay_12", 7000);
		m_delay_13.reset("m_delay_13", 5000);
		m_delay_14.reset("m_delay_14", 6000);
		m_delay_15.reset("m_delay_15", 48000);
		m_delay_16.reset("m_delay_16", 16000);
		m_delay_17.reset("m_delay_17", 96000);
		m_delay_18.reset("m_delay_18", 15000);
		m_delay_19.reset("m_delay_19", 12000);
		m_delay_20.reset("m_delay_20", 10000);
		m_delay_21.reset("m_delay_21", 48000);
		m_delay_22.reset("m_delay_22", 48000);
		m_delay_23.reset("m_delay_23", 48000);
		m_delay_24.reset("m_delay_24", 48000);
		m_bandwidth_25 = 75;
		m_mix_26 = 50;
		m_decay_27 = 50;
		m_damping_28 = 50;
		m_roomsize_29 = 150;
		m_tone_30 = 1500;
		m_shimmer_31 = 50;
		m_ratio_32 = 2;
		samples_to_seconds = (1 / samplerate);
		m_phasor_33.reset(0);
		m_delta_34.reset(0);
		m_sah_35.reset(0);
		m_sah_36.reset(0);
		m_delta_37.reset(0);
		m_sah_38.reset(0);
		m_sah_39.reset(0);
		m_delta_40.reset(0);
		m_sah_41.reset(0);
		m_sah_42.reset(0);
		m_delta_43.reset(0);
		m_sah_44.reset(0);
		m_sah_45.reset(0);
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
		double mul_5308 = (m_mix_26 * 0.01);
		double mul_5307 = (m_damping_28 * 0.01);
		double expr_5535 = safediv((m_roomsize_29 * 48000), 340);
		double mul_5306 = (m_bandwidth_25 * 0.01);
		double rsub_5305 = (1 - mul_5306);
		double mul_5309 = (m_shimmer_31 * 0.01);
		double expr_5525 = safediv(((m_tone_30 * 2) * 3.1415926535898), 48000);
		double sin_5313 = sin(expr_5525);
		double clamp_5314 = ((sin_5313 <= 1e-05) ? 1e-05 : ((sin_5313 >= 0.99999) ? 0.99999 : sin_5313));
		double expr_5524 = safepow(1.0418, m_decay_27);
		double expr_5534 = safepow(0.001, safediv(1, (expr_5524 * 48000)));
		double rsub_5364 = (1 - m_ratio_32);
		double mul_5363 = (rsub_5364 * 10);
		samples_to_seconds = (1 / samplerate);
		double mul_5303 = (m_decay_27 * 2);
		double clamp_5298 = ((mul_5303 <= 0) ? 0 : ((mul_5303 >= 100) ? 100 : mul_5303));
		double mul_5302 = (clamp_5298 * 0.01);
		double atodb_5301 = atodb(mul_5302);
		double sub_5300 = (atodb_5301 - 9);
		double dbtoa_5299 = dbtoa(sub_5300);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double mix_5568 = (expr_5535 + (0.999 * (m_smth_11 - expr_5535)));
			double mix_5297 = mix_5568;
			double noise_5315 = noise();
			double abs_5332 = fabs(noise_5315);
			double mul_5336 = (abs_5332 * 0.25);
			double noise_5316 = noise();
			double abs_5333 = fabs(noise_5316);
			double mul_5339 = (abs_5333 * 0.25);
			double noise_5317 = noise();
			double abs_5334 = fabs(noise_5317);
			double mul_5342 = (abs_5334 * 0.25);
			double mul_5514 = (mix_5297 * 0.81649);
			double tap_5438 = m_delay_24.read_linear(mul_5514);
			double noise_5318 = noise();
			double abs_5335 = fabs(noise_5318);
			double mul_5345 = (abs_5335 * 0.25);
			double mul_5513 = (mix_5297 * 0.7071);
			double tap_5432 = m_delay_23.read_linear(mul_5513);
			double mul_5512 = (mix_5297 * 0.63245);
			double tap_5426 = m_delay_22.read_linear(mul_5512);
			double mul_5515 = (mix_5297 * 1);
			double tap_5520 = m_delay_21.read_linear(mul_5515);
			double expr_5528 = (-safepow(expr_5534, mul_5514));
			double mul_5434 = (tap_5438 * expr_5528);
			double mix_5569 = (mul_5434 + (mul_5307 * (m_history_10 - mul_5434)));
			double mix_5436 = mix_5569;
			double expr_5527 = (-safepow(expr_5534, mul_5513));
			double mul_5428 = (tap_5432 * expr_5527);
			double mix_5570 = (mul_5428 + (mul_5307 * (m_history_9 - mul_5428)));
			double mix_5430 = mix_5570;
			double expr_5526 = (-safepow(expr_5534, mul_5512));
			double mul_5422 = (tap_5426 * expr_5526);
			double mix_5571 = (mul_5422 + (mul_5307 * (m_history_8 - mul_5422)));
			double mix_5424 = mix_5571;
			double expr_5533 = (-safepow(expr_5534, mul_5515));
			double mul_5511 = (tap_5520 * expr_5533);
			double mix_5572 = (mul_5511 + (mul_5307 * (m_history_7 - mul_5511)));
			double mix_5518 = mix_5572;
			double mul_5509 = (mix_5297 * 0.000527);
			int int_5508 = int(mul_5509);
			double mul_5486 = (int_5508 * 400.600006);
			double tap_5485 = m_delay_20.read_linear(mul_5486);
			double mul_5483 = (tap_5485 * 0.625);
			double mul_5465 = (int_5508 * 419.5);
			double tap_5464 = m_delay_19.read_linear(mul_5465);
			double mul_5462 = (tap_5464 * 0.625);
			double mul_5493 = (int_5508 * 568.299988);
			double tap_5492 = m_delay_18.read_linear(mul_5493);
			double phasor_5382 = m_phasor_33(mul_5363, samples_to_seconds);
			double add_5356 = ((m_history_6 + phasor_5382) + 0.75);
			double mod_5355 = safemod(add_5356, 1);
			double delta_5338 = m_delta_34(mod_5355);
			double sah_5319 = m_sah_35(mul_5336, delta_5338, 0);
			int sah_5337 = m_sah_36(4800, delta_5338, 0);
			double mul_5328 = (sah_5337 * mod_5355);
			double sub_5354 = (mod_5355 - 0.5);
			double mul_5353 = (sub_5354 * 3.1415926535898);
			double cos_5352 = cos(mul_5353);
			double mul_5347 = (cos_5352 * cos_5352);
			double add_5362 = ((m_history_5 + phasor_5382) + 0.5);
			double mod_5361 = safemod(add_5362, 1);
			double delta_5341 = m_delta_37(mod_5361);
			double sah_5321 = m_sah_38(mul_5339, delta_5341, 0);
			int sah_5340 = m_sah_39(4800, delta_5341, 0);
			double mul_5329 = (sah_5340 * mod_5361);
			double sub_5360 = (mod_5361 - 0.5);
			double mul_5359 = (sub_5360 * 3.1415926535898);
			double cos_5358 = cos(mul_5359);
			double mul_5348 = (cos_5358 * cos_5358);
			double add_5376 = ((m_history_4 + phasor_5382) + 0.25);
			double mod_5375 = safemod(add_5376, 1);
			double delta_5344 = m_delta_40(mod_5375);
			double sah_5323 = m_sah_41(mul_5342, delta_5344, 0);
			int sah_5343 = m_sah_42(4800, delta_5344, 0);
			double mul_5330 = (sah_5343 * mod_5375);
			double sub_5374 = (mod_5375 - 0.5);
			double mul_5373 = (sub_5374 * 3.1415926535898);
			double cos_5372 = cos(mul_5373);
			double mul_5349 = (cos_5372 * cos_5372);
			double add_5381 = ((m_history_3 + phasor_5382) + 0);
			double mod_5380 = safemod(add_5381, 1);
			double delta_5326 = m_delta_43(mod_5380);
			double sah_5325 = m_sah_44(mul_5345, delta_5326, 0);
			int sah_5346 = m_sah_45(4800, delta_5326, 0);
			double mul_5331 = (sah_5346 * mod_5380);
			double tap_5368 = m_delay_17.read_linear(mul_5331);
			double tap_5369 = m_delay_17.read_linear(mul_5330);
			double tap_5370 = m_delay_17.read_linear(mul_5329);
			double tap_5371 = m_delay_17.read_linear(mul_5328);
			double mul_5351 = (tap_5371 * mul_5347);
			double mul_5357 = (tap_5370 * mul_5348);
			double mul_5365 = (tap_5369 * mul_5349);
			double sub_5379 = (mod_5380 - 0.5);
			double mul_5378 = (sub_5379 * 3.1415926535898);
			double cos_5377 = cos(mul_5378);
			double mul_5350 = (cos_5377 * cos_5377);
			double mul_5366 = (tap_5368 * mul_5350);
			double add_5574 = (((mul_5366 + mul_5365) + mul_5357) + mul_5351);
			double mix_5573 = (m_y_2 + (clamp_5314 * (add_5574 - m_y_2)));
			double mix_5311 = mix_5573;
			double mix_5575 = (in1 + (mul_5309 * (mix_5311 - in1)));
			double mix_5383 = mix_5575;
			double mul_5386 = (mix_5383 * 0.707);
			double mix_5576 = (mul_5386 + (rsub_5305 * (m_history_1 - mul_5386)));
			double mix_5522 = mix_5576;
			double sub_5415 = (mix_5518 - mix_5436);
			double sub_5412 = (mix_5430 - mix_5424);
			double sub_5411 = (sub_5415 - sub_5412);
			double mul_5394 = (sub_5411 * 0.5);
			double add_5452 = (mix_5297 + 5);
			double expr_5529 = safepow(expr_5534, add_5452);
			double add_5410 = (sub_5415 + sub_5412);
			double rsub_5408 = (0 - add_5410);
			double mul_5393 = (rsub_5408 * 0.5);
			double mul_5472 = (int_5508 * 566.700012);
			double tap_5471 = m_delay_16.read_linear(mul_5472);
			double add_5416 = (mix_5518 + mix_5436);
			double add_5414 = (mix_5430 + mix_5424);
			double add_5409 = (add_5416 + add_5414);
			double mul_5392 = (add_5409 * 0.5);
			double sub_5413 = (add_5416 - add_5414);
			double mul_5395 = (sub_5413 * 0.5);
			double mul_5490 = (tap_5492 * 0.625);
			double mul_5458 = (mix_5297 * 0.41);
			double add_5455 = (mul_5458 + 5);
			double expr_5532 = safepow(expr_5534, add_5455);
			double mul_5457 = (mix_5297 * 0.3);
			double add_5454 = (mul_5457 + 5);
			double expr_5531 = safepow(expr_5534, add_5454);
			double mul_5456 = (mix_5297 * 0.155);
			double add_5453 = (mul_5456 + 5);
			double tap_5440 = m_delay_15.read_linear(add_5455);
			double tap_5441 = m_delay_15.read_linear(add_5454);
			double tap_5442 = m_delay_15.read_linear(add_5453);
			double tap_5443 = m_delay_15.read_linear(add_5452);
			double mul_5448 = (tap_5441 * expr_5531);
			double add_5419 = (mul_5394 + mul_5448);
			double mul_5444 = (tap_5443 * expr_5529);
			double add_5417 = (mul_5392 + mul_5444);
			double mul_5450 = (tap_5440 * expr_5532);
			double add_5420 = (mul_5395 + mul_5450);
			double expr_5530 = safepow(expr_5534, add_5453);
			double mul_5446 = (tap_5442 * expr_5530);
			double add_5418 = (mul_5393 + mul_5446);
			double mul_5469 = (tap_5471 * 0.625);
			double mul_5507 = (mix_5297 * 0.110732);
			double tap_5506 = m_delay_14.read_cubic(mul_5507);
			double mul_5500 = (int_5508 * 162.100006);
			double tap_5499 = m_delay_13.read_linear(mul_5500);
			double mul_5504 = (tap_5506 * 0.75);
			double sub_5503 = (mix_5522 - mul_5504);
			double mul_5502 = (sub_5503 * 0.75);
			double add_5501 = (mul_5502 + tap_5506);
			double mul_5479 = (int_5508 * 144.800003);
			double tap_5478 = m_delay_12.read_linear(mul_5479);
			double mul_5497 = (tap_5499 * 0.75);
			double mul_5476 = (tap_5478 * 0.75);
			double mul_5403 = (mul_5450 * mul_5302);
			double mul_5401 = (mul_5446 * mul_5302);
			double add_5389 = (mul_5403 + mul_5401);
			double mul_5402 = (mul_5448 * mul_5302);
			double mul_5400 = (mul_5444 * mul_5302);
			double add_5388 = (mul_5402 + mul_5400);
			double sub_5398 = (add_5389 - add_5388);
			double mul_5407 = (mul_5395 * dbtoa_5299);
			double mul_5405 = (mul_5393 * dbtoa_5299);
			double add_5391 = (mul_5407 + mul_5405);
			double mul_5406 = (mul_5394 * dbtoa_5299);
			double mul_5404 = (mul_5392 * dbtoa_5299);
			double add_5390 = (mul_5406 + mul_5404);
			double sub_5399 = (add_5391 - add_5390);
			double add_5385 = (sub_5399 + sub_5398);
			double add_5397 = (add_5385 + mix_5383);
			double sub_5496 = (add_5397 - mul_5497);
			double mul_5495 = (sub_5496 * 0.75);
			double add_5494 = (mul_5495 + tap_5499);
			double sub_5489 = (add_5494 - mul_5490);
			double mul_5488 = (sub_5489 * 0.625);
			double add_5487 = (mul_5488 + tap_5492);
			double sub_5482 = (add_5487 - mul_5483);
			double mul_5481 = (sub_5482 * 0.625);
			double add_5480 = (mul_5481 + tap_5485);
			double mul_5396 = (add_5480 * mul_5308);
			double out1 = (in1 + mul_5396);
			double add_5387 = (add_5385 + mix_5383);
			double sub_5475 = (add_5387 - mul_5476);
			double mul_5474 = (sub_5475 * 0.75);
			double add_5473 = (mul_5474 + tap_5478);
			double sub_5468 = (add_5473 - mul_5469);
			double mul_5467 = (sub_5468 * 0.625);
			double add_5466 = (mul_5467 + tap_5471);
			double sub_5461 = (add_5466 - mul_5462);
			double mul_5460 = (sub_5461 * 0.625);
			double add_5459 = (mul_5460 + tap_5464);
			double mul_5384 = (add_5459 * mul_5308);
			double out2 = (in1 + mul_5384);
			double smth_next_5536 = mix_5297;
			double history_5435_next_5537 = mix_5436;
			double history_5429_next_5538 = mix_5430;
			double history_5423_next_5539 = mix_5424;
			double history_5517_next_5540 = mix_5518;
			double history_5320_next_5541 = sah_5319;
			double history_5322_next_5542 = sah_5321;
			double history_5324_next_5543 = sah_5323;
			double history_5327_next_5544 = sah_5325;
			double y0_next_5545 = mix_5311;
			double history_5521_next_5546 = mix_5522;
			m_delay_24.write(add_5419);
			m_delay_23.write(add_5418);
			m_delay_22.write(add_5417);
			m_delay_21.write(add_5420);
			m_delay_20.write(sub_5482);
			m_delay_19.write(sub_5461);
			m_delay_18.write(sub_5489);
			m_delay_17.write(in1);
			m_delay_16.write(sub_5468);
			m_delay_15.write(add_5501);
			m_delay_14.write(sub_5503);
			m_delay_13.write(sub_5496);
			m_delay_12.write(sub_5475);
			m_smth_11 = smth_next_5536;
			m_history_10 = history_5435_next_5537;
			m_history_9 = history_5429_next_5538;
			m_history_8 = history_5423_next_5539;
			m_history_7 = history_5517_next_5540;
			m_history_6 = history_5320_next_5541;
			m_history_5 = history_5322_next_5542;
			m_history_4 = history_5324_next_5543;
			m_history_3 = history_5327_next_5544;
			m_y_2 = y0_next_5545;
			m_history_1 = history_5521_next_5546;
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
	inline void set_bandwidth(double _value) {
		m_bandwidth_25 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_26 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_decay(double _value) {
		m_decay_27 = (_value < 1 ? 1 : (_value > 100 ? 100 : _value));
	};
	inline void set_damping(double _value) {
		m_damping_28 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_roomsize(double _value) {
		m_roomsize_29 = (_value < 1 ? 1 : (_value > 300 ? 300 : _value));
	};
	inline void set_tone(double _value) {
		m_tone_30 = (_value < 500 ? 500 : (_value > 6000 ? 6000 : _value));
	};
	inline void set_shimmer(double _value) {
		m_shimmer_31 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_ratio(double _value) {
		m_ratio_32 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
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
		case 2: self->set_decay(value); break;
		case 3: self->set_damping(value); break;
		case 4: self->set_roomsize(value); break;
		case 5: self->set_tone(value); break;
		case 6: self->set_shimmer(value); break;
		case 7: self->set_ratio(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_bandwidth_25; break;
		case 1: *value = self->m_mix_26; break;
		case 2: *value = self->m_decay_27; break;
		case 3: *value = self->m_damping_28; break;
		case 4: *value = self->m_roomsize_29; break;
		case 5: *value = self->m_tone_30; break;
		case 6: *value = self->m_shimmer_31; break;
		case 7: *value = self->m_ratio_32; break;
		
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
	// initialize parameter 0 ("m_bandwidth_25")
	pi = self->__commonstate.params + 0;
	pi->name = "bandwidth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_bandwidth_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_mix_26")
	pi = self->__commonstate.params + 1;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_decay_27")
	pi = self->__commonstate.params + 2;
	pi->name = "decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decay_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_damping_28")
	pi = self->__commonstate.params + 3;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_roomsize_29")
	pi = self->__commonstate.params + 4;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 300;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_tone_30")
	pi = self->__commonstate.params + 5;
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
	// initialize parameter 6 ("m_shimmer_31")
	pi = self->__commonstate.params + 6;
	pi->name = "shimmer";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_shimmer_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_ratio_32")
	pi = self->__commonstate.params + 7;
	pi->name = "ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_32;
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
