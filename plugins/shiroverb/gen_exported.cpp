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
	double m_ratio_35;
	double m_cutoff_36;
	double m_blur_38;
	double m_roomsize_33;
	double m_spread_37;
	double samples_to_seconds;
	double m_tail_32;
	double m_shimmer_25;
	double m_window_30;
	double m_history_4;
	double m_history_5;
	double m_history_6;
	double m_history_3;
	double m_history_1;
	double m_y_2;
	double samplerate;
	double m_damping_31;
	double m_history_7;
	double m_history_9;
	double m_resonance_28;
	double m_mix_29;
	double m_history_8;
	double m_tone_27;
	double m_y_11;
	double m_history_10;
	double m_decay_26;
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
		m_shimmer_25 = 0.5;
		m_decay_26 = 60;
		m_tone_27 = 0.5;
		m_resonance_28 = 0;
		m_mix_29 = 0.5;
		m_window_30 = 100;
		m_damping_31 = 0.75;
		m_tail_32 = 0.25;
		m_roomsize_33 = 75;
		m_early_34 = 0.25;
		m_ratio_35 = 2;
		m_cutoff_36 = 3000;
		m_spread_37 = 25;
		m_blur_38 = 0.25;
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
		double rsub_3603 = (1 - m_tone_27);
		double expr_4406 = safepow(0.001, safediv(1, (m_decay_26 * 44100)));
		double expr_4407 = safediv((m_roomsize_33 * 44100), 340);
		double mul_3592 = (expr_4407 * 0.63245);
		double expr_4398 = (-safepow(expr_4406, mul_3592));
		double mul_3595 = (expr_4407 * 1);
		double expr_4405 = (-safepow(expr_4406, mul_3595));
		double mul_3593 = (expr_4407 * 0.7071);
		double expr_4399 = (-safepow(expr_4406, mul_3593));
		double mul_3594 = (expr_4407 * 0.81649);
		double expr_4400 = (-safepow(expr_4406, mul_3594));
		double mul_3589 = (expr_4407 * 0.000527);
		int int_3588 = int(mul_3589);
		double mul_3377 = (m_resonance_28 * 0.125);
		double exp_3378 = exp(mul_3377);
		double mul_3376 = (exp_3378 * 0.882497);
		double mul_3372 = (mul_3376 * mul_3376);
		double expr_4397 = safediv(((m_cutoff_36 * 2) * 3.1415926535898), 44100);
		double cos_3375 = cos(expr_4397);
		double mul_3374 = (cos_3375 * mul_3376);
		double mul_3373 = (mul_3374 * -2);
		double add_3371 = ((mul_3373 + mul_3372) + 1);
		double mul_3557 = (m_spread_37 * 0.376623);
		double add_3556 = (mul_3557 + 931);
		double rsub_3553 = (1341 - add_3556);
		double mul_3564 = (int_3588 * rsub_3553);
		double add_3518 = (expr_4407 + 5);
		double expr_4401 = safepow(expr_4406, add_3518);
		double mstosamps_3443 = (m_window_30 * (samplerate * 0.001));
		double mul_3529 = (m_spread_37 * -0.380445);
		double add_3528 = (mul_3529 + 931);
		double rsub_3525 = (1341 - add_3528);
		double mul_3538 = (int_3588 * rsub_3525);
		double mul_3524 = (expr_4407 * 0.41);
		double add_3521 = (mul_3524 + 5);
		double expr_4404 = safepow(expr_4406, add_3521);
		double mul_3523 = (expr_4407 * 0.3);
		double add_3520 = (mul_3523 + 5);
		double expr_4403 = safepow(expr_4406, add_3520);
		double mul_3522 = (expr_4407 * 0.155);
		double add_3519 = (mul_3522 + 5);
		double expr_4402 = safepow(expr_4406, add_3519);
		double rsub_3430 = (1 - m_ratio_35);
		double mul_3429 = (rsub_3430 * 1000);
		double div_3428 = safediv(mul_3429, m_window_30);
		samples_to_seconds = (1 / samplerate);
		double mul_3587 = (expr_4407 * 0.110732);
		double mul_3573 = (m_spread_37 * 0.125541);
		double add_3555 = (mul_3573 + 369);
		double rsub_3554 = (add_3556 - add_3555);
		double mul_3571 = (int_3588 * rsub_3554);
		double mul_3531 = (m_spread_37 * -0.568366);
		double add_3527 = (mul_3531 + 369);
		double rsub_3526 = (add_3528 - add_3527);
		double mul_3545 = (int_3588 * rsub_3526);
		double add_3572 = (mul_3573 + 159);
		double mul_3580 = (int_3588 * add_3572);
		double add_3530 = (mul_3531 + 159);
		double mul_3552 = (int_3588 * add_3530);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_3382 = noise();
			double abs_3400 = fabs(noise_3382);
			double mul_3410 = (abs_3400 * m_blur_38);
			double noise_3381 = noise();
			double abs_3399 = fabs(noise_3381);
			double mul_3407 = (abs_3399 * m_blur_38);
			double noise_3379 = noise();
			double abs_3397 = fabs(noise_3379);
			double mul_3401 = (abs_3397 * m_blur_38);
			double noise_3380 = noise();
			double abs_3398 = fabs(noise_3380);
			double mul_3404 = (abs_3398 * m_blur_38);
			double tap_3492 = m_delay_24.read_linear(mul_3592);
			double mul_3488 = (tap_3492 * expr_4398);
			double mix_4450 = (mul_3488 + (m_damping_31 * (m_history_10 - mul_3488)));
			double mix_3490 = mix_4450;
			double tap_3600 = m_delay_23.read_linear(mul_3595);
			double mul_3591 = (tap_3600 * expr_4405);
			double mix_4451 = (mul_3591 + (m_damping_31 * (m_history_9 - mul_3591)));
			double mix_3598 = mix_4451;
			double tap_3498 = m_delay_22.read_linear(mul_3593);
			double mul_3494 = (tap_3498 * expr_4399);
			double mix_4452 = (mul_3494 + (m_damping_31 * (m_history_8 - mul_3494)));
			double mix_3496 = mix_4452;
			double tap_3504 = m_delay_21.read_linear(mul_3594);
			double mul_3500 = (tap_3504 * expr_4400);
			double mix_4453 = (mul_3500 + (m_damping_31 * (m_history_7 - mul_3500)));
			double mix_3502 = mix_4453;
			double mul_3368 = (mul_3372 * m_y_11);
			double mul_3369 = (mul_3373 * m_y_2);
			double tap_3563 = m_delay_20.read_linear(mul_3564);
			double mul_3561 = (tap_3563 * 0.625);
			double add_3482 = (mix_3598 + mix_3502);
			double add_3480 = (mix_3496 + mix_3490);
			double add_3475 = (add_3482 + add_3480);
			double mul_3458 = (add_3475 * 0.5);
			double sub_3479 = (add_3482 - add_3480);
			double mul_3461 = (sub_3479 * 0.5);
			double sub_3481 = (mix_3598 - mix_3502);
			double sub_3478 = (mix_3496 - mix_3490);
			double sub_3477 = (sub_3481 - sub_3478);
			double mul_3460 = (sub_3477 * 0.5);
			double add_3476 = (sub_3481 + sub_3478);
			double rsub_3474 = (0 - add_3476);
			double mul_3459 = (rsub_3474 * 0.5);
			double tap_3537 = m_delay_19.read_linear(mul_3538);
			double mul_3535 = (tap_3537 * 0.625);
			double tap_3506 = m_delay_18.read_linear(add_3521);
			double tap_3507 = m_delay_18.read_linear(add_3520);
			double tap_3508 = m_delay_18.read_linear(add_3519);
			double tap_3509 = m_delay_18.read_linear(add_3518);
			double mul_3510 = (tap_3509 * expr_4401);
			double add_3483 = (mul_3458 + mul_3510);
			double mul_3516 = (tap_3506 * expr_4404);
			double add_3486 = (mul_3461 + mul_3516);
			double mul_3514 = (tap_3507 * expr_4403);
			double add_3485 = (mul_3460 + mul_3514);
			double mul_3512 = (tap_3508 * expr_4402);
			double add_3484 = (mul_3459 + mul_3512);
			double phasor_3449 = m_phasor_39(div_3428, samples_to_seconds);
			double add_3448 = ((m_history_6 + phasor_3449) + 0);
			double mod_3447 = safemod(add_3448, 1);
			double delta_3390 = m_delta_40(mod_3447);
			double sah_3389 = m_sah_41(mul_3410, delta_3390, 0);
			double sah_3411 = m_sah_42(mstosamps_3443, delta_3390, 0);
			double mul_3396 = (sah_3411 * mod_3447);
			double sub_3446 = (mod_3447 - 0.5);
			double mul_3445 = (sub_3446 * 3.1415926535898);
			double cos_3444 = cos(mul_3445);
			double mul_3415 = (cos_3444 * cos_3444);
			double add_3442 = ((m_history_5 + phasor_3449) + 0.25);
			double mod_3441 = safemod(add_3442, 1);
			double delta_3409 = m_delta_43(mod_3441);
			double sah_3387 = m_sah_44(mul_3407, delta_3409, 0);
			double sah_3408 = m_sah_45(mstosamps_3443, delta_3409, 0);
			double mul_3395 = (sah_3408 * mod_3441);
			double sub_3440 = (mod_3441 - 0.5);
			double mul_3439 = (sub_3440 * 3.1415926535898);
			double cos_3438 = cos(mul_3439);
			double mul_3414 = (cos_3438 * cos_3438);
			double add_3421 = ((m_history_4 + phasor_3449) + 0.75);
			double mod_3420 = safemod(add_3421, 1);
			double delta_3403 = m_delta_46(mod_3420);
			double sah_3383 = m_sah_47(mul_3401, delta_3403, 0);
			double sah_3402 = m_sah_48(mstosamps_3443, delta_3403, 0);
			double mul_3393 = (sah_3402 * mod_3420);
			double sub_3419 = (mod_3420 - 0.5);
			double mul_3418 = (sub_3419 * 3.1415926535898);
			double cos_3417 = cos(mul_3418);
			double mul_3412 = (cos_3417 * cos_3417);
			double add_3427 = ((m_history_3 + phasor_3449) + 0.5);
			double mod_3426 = safemod(add_3427, 1);
			double delta_3406 = m_delta_49(mod_3426);
			double sah_3385 = m_sah_50(mul_3404, delta_3406, 0);
			double sah_3405 = m_sah_51(mstosamps_3443, delta_3406, 0);
			double mul_3394 = (sah_3405 * mod_3426);
			double tap_3434 = m_delay_17.read_linear(mul_3396);
			double tap_3435 = m_delay_17.read_linear(mul_3395);
			double tap_3436 = m_delay_17.read_linear(mul_3394);
			double tap_3437 = m_delay_17.read_linear(mul_3393);
			double mul_3416 = (tap_3437 * mul_3412);
			double mul_3431 = (tap_3435 * mul_3414);
			double mul_3432 = (tap_3434 * mul_3415);
			double sub_3425 = (mod_3426 - 0.5);
			double mul_3424 = (sub_3425 * 3.1415926535898);
			double cos_3423 = cos(mul_3424);
			double mul_3413 = (cos_3423 * cos_3423);
			double mul_3422 = (tap_3436 * mul_3413);
			double mul_3370 = ((((mul_3432 + mul_3431) + mul_3422) + mul_3416) * add_3371);
			double sub_3367 = (mul_3370 - (mul_3369 + mul_3368));
			double mix_4454 = (in1 + (m_shimmer_25 * (sub_3367 - in1)));
			double mix_3392 = mix_4454;
			double mul_3452 = (mix_3392 * 0.707);
			double mix_4455 = (mul_3452 + (rsub_3603 * (m_history_1 - mul_3452)));
			double mix_3602 = mix_4455;
			double tap_3586 = m_delay_16.read_linear(mul_3587);
			double tap_3570 = m_delay_15.read_linear(mul_3571);
			double mul_3568 = (tap_3570 * 0.625);
			double mul_3584 = (tap_3586 * 0.75);
			double sub_3583 = (mix_3602 - mul_3584);
			double mul_3582 = (sub_3583 * 0.75);
			double add_3581 = (mul_3582 + tap_3586);
			double tap_3544 = m_delay_14.read_linear(mul_3545);
			double mul_3542 = (tap_3544 * 0.625);
			double tap_3579 = m_delay_13.read_linear(mul_3580);
			double mul_3577 = (tap_3579 * 0.75);
			double tap_3551 = m_delay_12.read_linear(mul_3552);
			double mul_3549 = (tap_3551 * 0.75);
			double mul_3473 = (mul_3461 * m_tail_32);
			double mul_3471 = (mul_3459 * m_tail_32);
			double add_3457 = (mul_3473 + mul_3471);
			double mul_3472 = (mul_3460 * m_tail_32);
			double mul_3470 = (mul_3458 * m_tail_32);
			double add_3456 = (mul_3472 + mul_3470);
			double sub_3465 = (add_3457 - add_3456);
			double mul_3469 = (mul_3516 * m_early_34);
			double mul_3467 = (mul_3512 * m_early_34);
			double add_3455 = (mul_3469 + mul_3467);
			double mul_3468 = (mul_3514 * m_early_34);
			double mul_3466 = (mul_3510 * m_early_34);
			double add_3454 = (mul_3468 + mul_3466);
			double sub_3464 = (add_3455 - add_3454);
			double add_3451 = (sub_3465 + sub_3464);
			double add_3463 = (add_3451 + mix_3392);
			double sub_3576 = (add_3463 - mul_3577);
			double mul_3575 = (sub_3576 * 0.75);
			double add_3574 = (mul_3575 + tap_3579);
			double sub_3567 = (add_3574 - mul_3568);
			double mul_3566 = (sub_3567 * 0.625);
			double add_3565 = (mul_3566 + tap_3570);
			double sub_3560 = (add_3565 - mul_3561);
			double mul_3559 = (sub_3560 * 0.625);
			double add_3558 = (mul_3559 + tap_3563);
			double mul_3462 = (add_3558 * m_mix_29);
			double out1 = (mul_3462 + in1);
			double add_3453 = (add_3451 + mix_3392);
			double sub_3548 = (add_3453 - mul_3549);
			double mul_3547 = (sub_3548 * 0.75);
			double add_3546 = (mul_3547 + tap_3551);
			double sub_3541 = (add_3546 - mul_3542);
			double mul_3540 = (sub_3541 * 0.625);
			double add_3539 = (mul_3540 + tap_3544);
			double sub_3534 = (add_3539 - mul_3535);
			double mul_3533 = (sub_3534 * 0.625);
			double add_3532 = (mul_3533 + tap_3537);
			double mul_3450 = (add_3532 * m_mix_29);
			double out2 = (mul_3450 + in1);
			double y2_next_4421 = m_y_2;
			double history_3489_next_4422 = mix_3490;
			double history_3597_next_4423 = mix_3598;
			double history_3495_next_4424 = mix_3496;
			double history_3501_next_4425 = mix_3502;
			double history_3391_next_4426 = sah_3389;
			double history_3388_next_4427 = sah_3387;
			double history_3384_next_4428 = sah_3383;
			double history_3386_next_4429 = sah_3385;
			double y1_next_4430 = sub_3367;
			double history_3601_next_4431 = mix_3602;
			m_delay_24.write(add_3483);
			m_delay_23.write(add_3486);
			m_delay_22.write(add_3484);
			m_delay_21.write(add_3485);
			m_delay_20.write(sub_3560);
			m_delay_19.write(sub_3534);
			m_delay_18.write(add_3581);
			m_delay_17.write(in1);
			m_delay_16.write(sub_3583);
			m_delay_15.write(sub_3567);
			m_delay_14.write(sub_3541);
			m_delay_13.write(sub_3576);
			m_delay_12.write(sub_3548);
			m_y_11 = y2_next_4421;
			m_history_10 = history_3489_next_4422;
			m_history_9 = history_3597_next_4423;
			m_history_8 = history_3495_next_4424;
			m_history_7 = history_3501_next_4425;
			m_history_6 = history_3391_next_4426;
			m_history_5 = history_3388_next_4427;
			m_history_4 = history_3384_next_4428;
			m_history_3 = history_3386_next_4429;
			m_y_2 = y1_next_4430;
			m_history_1 = history_3601_next_4431;
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
	inline void set_shimmer(double _value) {
		m_shimmer_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_decay(double _value) {
		m_decay_26 = (_value < 0.1 ? 0.1 : (_value > 360 ? 360 : _value));
	};
	inline void set_tone(double _value) {
		m_tone_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_resonance(double _value) {
		m_resonance_28 = (_value < 0 ? 0 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_29 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_window(double _value) {
		m_window_30 = (_value < 0.1 ? 0.1 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_damping(double _value) {
		m_damping_31 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_tail(double _value) {
		m_tail_32 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_roomsize(double _value) {
		m_roomsize_33 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_early(double _value) {
		m_early_34 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ratio(double _value) {
		m_ratio_35 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_cutoff(double _value) {
		m_cutoff_36 = (_value < 0 ? 0 : (_value > 6000 ? 6000 : _value));
	};
	inline void set_spread(double _value) {
		m_spread_37 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_blur(double _value) {
		m_blur_38 = (_value < 0.01 ? 0.01 : (_value > 0.25 ? 0.25 : _value));
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
		case 0: self->set_shimmer(value); break;
		case 1: self->set_decay(value); break;
		case 2: self->set_tone(value); break;
		case 3: self->set_resonance(value); break;
		case 4: self->set_mix(value); break;
		case 5: self->set_window(value); break;
		case 6: self->set_damping(value); break;
		case 7: self->set_tail(value); break;
		case 8: self->set_roomsize(value); break;
		case 9: self->set_early(value); break;
		case 10: self->set_ratio(value); break;
		case 11: self->set_cutoff(value); break;
		case 12: self->set_spread(value); break;
		case 13: self->set_blur(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_shimmer_25; break;
		case 1: *value = self->m_decay_26; break;
		case 2: *value = self->m_tone_27; break;
		case 3: *value = self->m_resonance_28; break;
		case 4: *value = self->m_mix_29; break;
		case 5: *value = self->m_window_30; break;
		case 6: *value = self->m_damping_31; break;
		case 7: *value = self->m_tail_32; break;
		case 8: *value = self->m_roomsize_33; break;
		case 9: *value = self->m_early_34; break;
		case 10: *value = self->m_ratio_35; break;
		case 11: *value = self->m_cutoff_36; break;
		case 12: *value = self->m_spread_37; break;
		case 13: *value = self->m_blur_38; break;
		
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
	// initialize parameter 0 ("m_shimmer_25")
	pi = self->__commonstate.params + 0;
	pi->name = "shimmer";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_shimmer_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_decay_26")
	pi = self->__commonstate.params + 1;
	pi->name = "decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decay_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 360;
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
	// initialize parameter 3 ("m_resonance_28")
	pi = self->__commonstate.params + 3;
	pi->name = "resonance";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_resonance_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_mix_29")
	pi = self->__commonstate.params + 4;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_window_30")
	pi = self->__commonstate.params + 5;
	pi->name = "window";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_window_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_damping_31")
	pi = self->__commonstate.params + 6;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
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
	// initialize parameter 8 ("m_roomsize_33")
	pi = self->__commonstate.params + 8;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_33;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 300;
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
	// initialize parameter 10 ("m_ratio_35")
	pi = self->__commonstate.params + 10;
	pi->name = "ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_35;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
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
	pi->outputmax = 6000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_spread_37")
	pi = self->__commonstate.params + 12;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_37;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_blur_38")
	pi = self->__commonstate.params + 13;
	pi->name = "blur";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_blur_38;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
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
