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
	Delta m_delta_38;
	Delta m_delta_35;
	Delta m_delta_41;
	Delta m_delta_32;
	Phasor m_phasor_31;
	Sah m_sah_36;
	Sah m_sah_34;
	Sah m_sah_37;
	Sah m_sah_40;
	Sah m_sah_39;
	Sah m_sah_33;
	Sah m_sah_43;
	Sah m_sah_42;
	double m_history_4;
	double m_history_5;
	double m_history_6;
	double m_history_7;
	double m_history_3;
	double m_history_1;
	double m_y_2;
	double samplerate;
	double m_history_10;
	double m_history_8;
	double samples_to_seconds;
	double m_history_9;
	double m_shimmer_25;
	double m_damping_24;
	double m_ratio_27;
	double m_roomsize_26;
	double m_tone_29;
	double m_mix_30;
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
		m_delay_16.reset("m_delay_16", 96000);
		m_delay_17.reset("m_delay_17", 15000);
		m_delay_18.reset("m_delay_18", 12000);
		m_delay_19.reset("m_delay_19", 10000);
		m_delay_20.reset("m_delay_20", 48000);
		m_delay_21.reset("m_delay_21", 48000);
		m_delay_22.reset("m_delay_22", 48000);
		m_delay_23.reset("m_delay_23", 48000);
		m_damping_24 = 75;
		m_shimmer_25 = 50;
		m_roomsize_26 = 150;
		m_ratio_27 = 2;
		m_decay_28 = 50;
		m_tone_29 = 3000;
		m_mix_30 = 50;
		samples_to_seconds = (1 / samplerate);
		m_phasor_31.reset(0);
		m_delta_32.reset(0);
		m_sah_33.reset(0);
		m_sah_34.reset(0);
		m_delta_35.reset(0);
		m_sah_36.reset(0);
		m_sah_37.reset(0);
		m_delta_38.reset(0);
		m_sah_39.reset(0);
		m_sah_40.reset(0);
		m_delta_41.reset(0);
		m_sah_42.reset(0);
		m_sah_43.reset(0);
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
		double mul_46254 = (m_mix_30 * 0.01);
		double mul_46253 = (m_damping_24 * 0.01);
		double mul_46252 = (m_shimmer_25 * 0.01);
		double expr_46250 = safediv(((m_tone_29 * 2) * 3.1415926535898), 48000);
		double sin_46037 = sin(expr_46250);
		double clamp_46038 = ((sin_46037 <= 1e-05) ? 1e-05 : ((sin_46037 >= 0.99999) ? 0.99999 : sin_46037));
		double expr_46249 = safediv((m_roomsize_26 * 48000), 340);
		double mul_46219 = (expr_46249 * 0.81649);
		double mul_46220 = (expr_46249 * 1);
		double mul_46218 = (expr_46249 * 0.7071);
		double mul_46217 = (expr_46249 * 0.63245);
		double mul_46229 = (m_decay_28 * 3.6);
		double expr_46248 = safepow(0.001, safediv(1, (mul_46229 * 48000)));
		double expr_46145 = (-safepow(expr_46248, mul_46219));
		double expr_46215 = (-safepow(expr_46248, mul_46220));
		double expr_46140 = (-safepow(expr_46248, mul_46218));
		double expr_46135 = (-safepow(expr_46248, mul_46217));
		double mul_46214 = (expr_46249 * 0.000527);
		int int_46213 = int(mul_46214);
		double mul_46238 = (int_46213 * 400.600006);
		double mul_46241 = (int_46213 * 419.5);
		double mul_46237 = (int_46213 * 568.299988);
		double add_46163 = (expr_46249 + 5);
		double expr_46156 = safepow(expr_46248, add_46163);
		double rsub_46079 = (1 - m_ratio_27);
		double mul_46251 = (rsub_46079 * 10);
		samples_to_seconds = (1 / samplerate);
		double mul_46240 = (int_46213 * 566.700012);
		double mul_46169 = (expr_46249 * 0.41);
		double add_46166 = (mul_46169 + 5);
		double expr_46162 = safepow(expr_46248, add_46166);
		double mul_46168 = (expr_46249 * 0.3);
		double add_46165 = (mul_46168 + 5);
		double expr_46160 = safepow(expr_46248, add_46165);
		double mul_46167 = (expr_46249 * 0.155);
		double add_46164 = (mul_46167 + 5);
		double expr_46158 = safepow(expr_46248, add_46164);
		double mul_46212 = (expr_46249 * 0.110732);
		double mul_46236 = (int_46213 * 162.100006);
		double mul_46239 = (int_46213 * 144.800003);
		double mul_46230 = (m_decay_28 * 0.01);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_46040 = noise();
			double abs_46057 = fabs(noise_46040);
			double mul_46227 = (abs_46057 * 0.25);
			double noise_46042 = noise();
			double abs_46059 = fabs(noise_46042);
			double mul_46225 = (abs_46059 * 0.25);
			double noise_46041 = noise();
			double abs_46058 = fabs(noise_46041);
			double mul_46226 = (abs_46058 * 0.25);
			double noise_46039 = noise();
			double abs_46056 = fabs(noise_46039);
			double mul_46228 = (abs_46056 * 0.25);
			double tap_46149 = m_delay_23.read_linear(mul_46219);
			double tap_46223 = m_delay_22.read_linear(mul_46220);
			double tap_46144 = m_delay_21.read_linear(mul_46218);
			double tap_46139 = m_delay_20.read_linear(mul_46217);
			double mul_46146 = (tap_46149 * expr_46145);
			double mix_46475 = (mul_46146 + (mul_46253 * (m_history_10 - mul_46146)));
			double mix_46246 = mix_46475;
			double mul_46216 = (tap_46223 * expr_46215);
			double mix_46476 = (mul_46216 + (mul_46253 * (m_history_9 - mul_46216)));
			double mix_46247 = mix_46476;
			double mul_46141 = (tap_46144 * expr_46140);
			double mix_46477 = (mul_46141 + (mul_46253 * (m_history_8 - mul_46141)));
			double mix_46245 = mix_46477;
			double mul_46136 = (tap_46139 * expr_46135);
			double mix_46478 = (mul_46136 + (mul_46253 * (m_history_7 - mul_46136)));
			double mix_46244 = mix_46478;
			double tap_46193 = m_delay_19.read_linear(mul_46238);
			double mul_46191 = (tap_46193 * 0.625);
			double tap_46175 = m_delay_18.read_linear(mul_46241);
			double mul_46173 = (tap_46175 * 0.625);
			double tap_46199 = m_delay_17.read_linear(mul_46237);
			double sub_46129 = (mix_46247 - mix_46246);
			double sub_46126 = (mix_46245 - mix_46244);
			double sub_46125 = (sub_46129 - sub_46126);
			double mul_46108 = (sub_46125 * 0.5);
			double phasor_46097 = m_phasor_31(mul_46251, samples_to_seconds);
			double add_46078 = ((m_history_6 + phasor_46097) + 0.5);
			double mod_46077 = safemod(add_46078, 1);
			double delta_46061 = m_delta_32(mod_46077);
			double sah_46045 = m_sah_33(mul_46227, delta_46061, 0);
			int sah_46233 = m_sah_34(4800, delta_46061, 0);
			double mul_46053 = (sah_46233 * mod_46077);
			double sub_46076 = (mod_46077 - 0.5);
			double mul_46075 = (sub_46076 * 3.1415926535898);
			double cos_46074 = cos(mul_46075);
			double mul_46064 = (cos_46074 * cos_46074);
			double add_46096 = ((m_history_5 + phasor_46097) + 0);
			double mod_46095 = safemod(add_46096, 1);
			double delta_46050 = m_delta_35(mod_46095);
			double sah_46049 = m_sah_36(mul_46225, delta_46050, 0);
			int sah_46231 = m_sah_37(4800, delta_46050, 0);
			double mul_46055 = (sah_46231 * mod_46095);
			double sub_46094 = (mod_46095 - 0.5);
			double mul_46093 = (sub_46094 * 3.1415926535898);
			double cos_46092 = cos(mul_46093);
			double mul_46066 = (cos_46092 * cos_46092);
			double add_46091 = ((m_history_4 + phasor_46097) + 0.25);
			double mod_46090 = safemod(add_46091, 1);
			double delta_46062 = m_delta_38(mod_46090);
			double sah_46047 = m_sah_39(mul_46226, delta_46062, 0);
			int sah_46232 = m_sah_40(4800, delta_46062, 0);
			double mul_46054 = (sah_46232 * mod_46090);
			double sub_46089 = (mod_46090 - 0.5);
			double mul_46088 = (sub_46089 * 3.1415926535898);
			double cos_46087 = cos(mul_46088);
			double mul_46065 = (cos_46087 * cos_46087);
			double add_46072 = ((m_history_3 + phasor_46097) + 0.75);
			double mod_46071 = safemod(add_46072, 1);
			double delta_46060 = m_delta_41(mod_46071);
			double sah_46043 = m_sah_42(mul_46228, delta_46060, 0);
			int sah_46234 = m_sah_43(4800, delta_46060, 0);
			double mul_46052 = (sah_46234 * mod_46071);
			double tap_46083 = m_delay_16.read_linear(mul_46055);
			double tap_46084 = m_delay_16.read_linear(mul_46054);
			double tap_46085 = m_delay_16.read_linear(mul_46053);
			double tap_46086 = m_delay_16.read_linear(mul_46052);
			double mul_46073 = (tap_46085 * mul_46064);
			double mul_46080 = (tap_46084 * mul_46065);
			double mul_46081 = (tap_46083 * mul_46066);
			double sub_46070 = (mod_46071 - 0.5);
			double mul_46069 = (sub_46070 * 3.1415926535898);
			double cos_46068 = cos(mul_46069);
			double mul_46063 = (cos_46068 * cos_46068);
			double mul_46067 = (tap_46086 * mul_46063);
			double add_46480 = (((mul_46081 + mul_46080) + mul_46073) + mul_46067);
			double mix_46479 = (m_y_2 + (clamp_46038 * (add_46480 - m_y_2)));
			double mix_46036 = mix_46479;
			double mix_46481 = (in1 + (mul_46252 * (mix_46036 - in1)));
			double mix_46243 = mix_46481;
			double mul_46100 = (mix_46243 * 0.707);
			double mix_46482 = (mul_46100 + (0.5 * (m_history_1 - mul_46100)));
			double mix_46235 = mix_46482;
			double tap_46181 = m_delay_15.read_linear(mul_46240);
			double add_46130 = (mix_46247 + mix_46246);
			double add_46128 = (mix_46245 + mix_46244);
			double sub_46127 = (add_46130 - add_46128);
			double mul_46109 = (sub_46127 * 0.5);
			double add_46123 = (add_46130 + add_46128);
			double mul_46106 = (add_46123 * 0.5);
			double add_46124 = (sub_46129 + sub_46126);
			double rsub_46122 = (0 - add_46124);
			double mul_46107 = (rsub_46122 * 0.5);
			double mul_46197 = (tap_46199 * 0.625);
			double tap_46151 = m_delay_14.read_linear(add_46166);
			double tap_46152 = m_delay_14.read_linear(add_46165);
			double tap_46153 = m_delay_14.read_linear(add_46164);
			double tap_46154 = m_delay_14.read_linear(add_46163);
			double mul_46159 = (tap_46152 * expr_46160);
			double add_46133 = (mul_46108 + mul_46159);
			double mul_46161 = (tap_46151 * expr_46162);
			double add_46134 = (mul_46109 + mul_46161);
			double mul_46155 = (tap_46154 * expr_46156);
			double add_46131 = (mul_46106 + mul_46155);
			double mul_46157 = (tap_46153 * expr_46158);
			double add_46132 = (mul_46107 + mul_46157);
			double mul_46179 = (tap_46181 * 0.625);
			double tap_46211 = m_delay_13.read_linear(mul_46212);
			double tap_46205 = m_delay_12.read_linear(mul_46236);
			double mul_46209 = (tap_46211 * 0.75);
			double sub_46208 = (mix_46235 - mul_46209);
			double mul_46207 = (sub_46208 * 0.75);
			double add_46206 = (mul_46207 + tap_46211);
			double tap_46187 = m_delay_11.read_linear(mul_46239);
			double mul_46203 = (tap_46205 * 0.75);
			double mul_46185 = (tap_46187 * 0.75);
			double mul_46121 = (mul_46109 * mul_46230);
			double mul_46119 = (mul_46107 * mul_46230);
			double add_46105 = (mul_46121 + mul_46119);
			double mul_46120 = (mul_46108 * mul_46230);
			double mul_46118 = (mul_46106 * mul_46230);
			double add_46104 = (mul_46120 + mul_46118);
			double sub_46113 = (add_46105 - add_46104);
			double mul_46117 = (mul_46161 * mul_46230);
			double mul_46115 = (mul_46157 * mul_46230);
			double add_46103 = (mul_46117 + mul_46115);
			double mul_46116 = (mul_46159 * mul_46230);
			double mul_46114 = (mul_46155 * mul_46230);
			double add_46102 = (mul_46116 + mul_46114);
			double sub_46112 = (add_46103 - add_46102);
			double add_46099 = (sub_46113 + sub_46112);
			double add_46111 = (add_46099 + mix_46243);
			double sub_46202 = (add_46111 - mul_46203);
			double mul_46201 = (sub_46202 * 0.75);
			double add_46200 = (mul_46201 + tap_46205);
			double sub_46196 = (add_46200 - mul_46197);
			double mul_46195 = (sub_46196 * 0.625);
			double add_46194 = (mul_46195 + tap_46199);
			double sub_46190 = (add_46194 - mul_46191);
			double mul_46189 = (sub_46190 * 0.625);
			double add_46188 = (mul_46189 + tap_46193);
			double mul_46110 = (add_46188 * mul_46254);
			double out1 = (in1 + mul_46110);
			double add_46101 = (add_46099 + mix_46243);
			double sub_46184 = (add_46101 - mul_46185);
			double mul_46183 = (sub_46184 * 0.75);
			double add_46182 = (mul_46183 + tap_46187);
			double sub_46178 = (add_46182 - mul_46179);
			double mul_46177 = (sub_46178 * 0.625);
			double add_46176 = (mul_46177 + tap_46181);
			double sub_46172 = (add_46176 - mul_46173);
			double mul_46171 = (sub_46172 * 0.625);
			double add_46170 = (mul_46171 + tap_46175);
			double mul_46098 = (add_46170 * mul_46254);
			double out2 = (in1 + mul_46098);
			double history_46147_next_46255 = mix_46246;
			double history_46221_next_46256 = mix_46247;
			double history_46142_next_46257 = mix_46245;
			double history_46137_next_46258 = mix_46244;
			double history_46046_next_46259 = sah_46045;
			double history_46051_next_46260 = sah_46049;
			double history_46048_next_46261 = sah_46047;
			double history_46044_next_46262 = sah_46043;
			double y0_next_46263 = mix_46036;
			double history_46224_next_46264 = mix_46235;
			m_delay_23.write(add_46133);
			m_delay_22.write(add_46134);
			m_delay_21.write(add_46132);
			m_delay_20.write(add_46131);
			m_delay_19.write(sub_46190);
			m_delay_18.write(sub_46172);
			m_delay_17.write(sub_46196);
			m_delay_16.write(in1);
			m_delay_15.write(sub_46178);
			m_delay_14.write(add_46206);
			m_delay_13.write(sub_46208);
			m_delay_12.write(sub_46202);
			m_delay_11.write(sub_46184);
			m_history_10 = history_46147_next_46255;
			m_history_9 = history_46221_next_46256;
			m_history_8 = history_46142_next_46257;
			m_history_7 = history_46137_next_46258;
			m_history_6 = history_46046_next_46259;
			m_history_5 = history_46051_next_46260;
			m_history_4 = history_46048_next_46261;
			m_history_3 = history_46044_next_46262;
			m_y_2 = y0_next_46263;
			m_history_1 = history_46224_next_46264;
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
	inline void set_damping(double _value) {
		m_damping_24 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_shimmer(double _value) {
		m_shimmer_25 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_roomsize(double _value) {
		m_roomsize_26 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_ratio(double _value) {
		m_ratio_27 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_decay(double _value) {
		m_decay_28 = (_value < 0.1 ? 0.1 : (_value > 100 ? 100 : _value));
	};
	inline void set_tone(double _value) {
		m_tone_29 = (_value < 500 ? 500 : (_value > 6000 ? 6000 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_30 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
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
int num_params() { return 7; }

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
		case 0: self->set_damping(value); break;
		case 1: self->set_shimmer(value); break;
		case 2: self->set_roomsize(value); break;
		case 3: self->set_ratio(value); break;
		case 4: self->set_decay(value); break;
		case 5: self->set_tone(value); break;
		case 6: self->set_mix(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_damping_24; break;
		case 1: *value = self->m_shimmer_25; break;
		case 2: *value = self->m_roomsize_26; break;
		case 3: *value = self->m_ratio_27; break;
		case 4: *value = self->m_decay_28; break;
		case 5: *value = self->m_tone_29; break;
		case 6: *value = self->m_mix_30; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(7 * sizeof(ParamInfo));
	self->__commonstate.numparams = 7;
	// initialize parameter 0 ("m_damping_24")
	pi = self->__commonstate.params + 0;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_shimmer_25")
	pi = self->__commonstate.params + 1;
	pi->name = "shimmer";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_shimmer_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_roomsize_26")
	pi = self->__commonstate.params + 2;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 300;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ratio_27")
	pi = self->__commonstate.params + 3;
	pi->name = "ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
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
	pi->outputmin = 0.1;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_tone_29")
	pi = self->__commonstate.params + 5;
	pi->name = "tone";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tone_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 500;
	pi->outputmax = 6000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_mix_30")
	pi = self->__commonstate.params + 6;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
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
