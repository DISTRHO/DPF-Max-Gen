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
	double m_shimmer_35;
	double m_blur_36;
	double m_ratio_38;
	double m_cutoff_33;
	double m_window_37;
	double samples_to_seconds;
	double m_resonance_32;
	double m_roomsize_25;
	double m_damping_30;
	double m_history_4;
	double m_history_5;
	double m_history_6;
	double m_history_3;
	double m_history_1;
	double m_y_2;
	double samplerate;
	double m_mix_31;
	double m_history_7;
	double m_history_9;
	double m_tail_28;
	double m_tone_29;
	double m_history_8;
	double m_spread_27;
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
		m_delay_12.reset("m_delay_12", 5000);
		m_delay_13.reset("m_delay_13", 7000);
		m_delay_14.reset("m_delay_14", 15000);
		m_delay_15.reset("m_delay_15", 16000);
		m_delay_16.reset("m_delay_16", 6000);
		m_delay_17.reset("m_delay_17", 48000);
		m_delay_18.reset("m_delay_18", 96000);
		m_delay_19.reset("m_delay_19", 10000);
		m_delay_20.reset("m_delay_20", 12000);
		m_delay_21.reset("m_delay_21", 48000);
		m_delay_22.reset("m_delay_22", 48000);
		m_delay_23.reset("m_delay_23", 48000);
		m_delay_24.reset("m_delay_24", 48000);
		m_roomsize_25 = 150;
		m_decay_26 = 180;
		m_spread_27 = 25;
		m_tail_28 = 0.25;
		m_tone_29 = 0.5;
		m_damping_30 = 0.75;
		m_mix_31 = 0.5;
		m_resonance_32 = 0;
		m_cutoff_33 = 3000;
		m_early_34 = 0.25;
		m_shimmer_35 = 0.5;
		m_blur_36 = 0.25;
		m_window_37 = 100;
		m_ratio_38 = 2;
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
		double rsub_238 = (1 - m_tone_29);
		double expr_271 = safepow(0.001, safediv(1, (m_decay_26 * 44100)));
		double expr_272 = safediv((m_roomsize_25 * 44100), 340);
		double mul_230 = (expr_272 * 1);
		double expr_270 = (-safepow(expr_271, mul_230));
		double mul_229 = (expr_272 * 0.81649);
		double expr_265 = (-safepow(expr_271, mul_229));
		double mul_228 = (expr_272 * 0.7071);
		double expr_264 = (-safepow(expr_271, mul_228));
		double mul_227 = (expr_272 * 0.63245);
		double expr_263 = (-safepow(expr_271, mul_227));
		double mul_12 = (m_resonance_32 * 0.125);
		double exp_13 = exp(mul_12);
		double mul_11 = (exp_13 * 0.882497);
		double mul_7 = (mul_11 * mul_11);
		double expr_262 = safediv(((m_cutoff_33 * 2) * 3.1415926535898), 44100);
		double cos_10 = cos(expr_262);
		double mul_9 = (cos_10 * mul_11);
		double mul_8 = (mul_9 * -2);
		double add_6 = ((mul_8 + mul_7) + 1);
		double mul_224 = (expr_272 * 0.000527);
		int int_223 = int(mul_224);
		double add_153 = (expr_272 + 5);
		double expr_266 = safepow(expr_271, add_153);
		double mstosamps_78 = (m_window_37 * (samplerate * 0.001));
		double mul_164 = (m_spread_27 * -0.380445);
		double add_163 = (mul_164 + 931);
		double rsub_160 = (1341 - add_163);
		double mul_173 = (int_223 * rsub_160);
		double mul_192 = (m_spread_27 * 0.376623);
		double add_191 = (mul_192 + 931);
		double rsub_188 = (1341 - add_191);
		double mul_199 = (int_223 * rsub_188);
		double rsub_65 = (1 - m_ratio_38);
		double mul_64 = (rsub_65 * 1000);
		double div_63 = safediv(mul_64, m_window_37);
		samples_to_seconds = (1 / samplerate);
		double mul_159 = (expr_272 * 0.41);
		double add_156 = (mul_159 + 5);
		double expr_269 = safepow(expr_271, add_156);
		double mul_158 = (expr_272 * 0.3);
		double add_155 = (mul_158 + 5);
		double expr_268 = safepow(expr_271, add_155);
		double mul_157 = (expr_272 * 0.155);
		double add_154 = (mul_157 + 5);
		double expr_267 = safepow(expr_271, add_154);
		double mul_222 = (expr_272 * 0.110732);
		double mul_166 = (m_spread_27 * -0.568366);
		double add_162 = (mul_166 + 369);
		double rsub_161 = (add_163 - add_162);
		double mul_180 = (int_223 * rsub_161);
		double mul_208 = (m_spread_27 * 0.125541);
		double add_190 = (mul_208 + 369);
		double rsub_189 = (add_191 - add_190);
		double mul_206 = (int_223 * rsub_189);
		double add_165 = (mul_166 + 159);
		double mul_187 = (int_223 * add_165);
		double add_207 = (mul_208 + 159);
		double mul_215 = (int_223 * add_207);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_14 = noise();
			double abs_32 = fabs(noise_14);
			double mul_36 = (abs_32 * m_blur_36);
			double noise_16 = noise();
			double abs_34 = fabs(noise_16);
			double mul_42 = (abs_34 * m_blur_36);
			double noise_17 = noise();
			double abs_35 = fabs(noise_17);
			double mul_45 = (abs_35 * m_blur_36);
			double noise_15 = noise();
			double abs_33 = fabs(noise_15);
			double mul_39 = (abs_33 * m_blur_36);
			double tap_235 = m_delay_24.read_linear(mul_230);
			double mul_226 = (tap_235 * expr_270);
			double mix_297 = (mul_226 + (m_damping_30 * (m_history_10 - mul_226)));
			double mix_233 = mix_297;
			double tap_139 = m_delay_23.read_linear(mul_229);
			double mul_135 = (tap_139 * expr_265);
			double mix_298 = (mul_135 + (m_damping_30 * (m_history_9 - mul_135)));
			double mix_137 = mix_298;
			double tap_133 = m_delay_22.read_linear(mul_228);
			double mul_129 = (tap_133 * expr_264);
			double mix_299 = (mul_129 + (m_damping_30 * (m_history_8 - mul_129)));
			double mix_131 = mix_299;
			double tap_127 = m_delay_21.read_linear(mul_227);
			double mul_123 = (tap_127 * expr_263);
			double mix_300 = (mul_123 + (m_damping_30 * (m_history_7 - mul_123)));
			double mix_125 = mix_300;
			double mul_3 = (mul_7 * m_y_11);
			double mul_4 = (mul_8 * m_y_2);
			double add_117 = (mix_233 + mix_137);
			double add_115 = (mix_131 + mix_125);
			double sub_114 = (add_117 - add_115);
			double mul_96 = (sub_114 * 0.5);
			double add_110 = (add_117 + add_115);
			double mul_93 = (add_110 * 0.5);
			double tap_172 = m_delay_20.read_linear(mul_173);
			double mul_170 = (tap_172 * 0.625);
			double sub_116 = (mix_233 - mix_137);
			double sub_113 = (mix_131 - mix_125);
			double sub_112 = (sub_116 - sub_113);
			double mul_95 = (sub_112 * 0.5);
			double add_111 = (sub_116 + sub_113);
			double rsub_109 = (0 - add_111);
			double mul_94 = (rsub_109 * 0.5);
			double tap_198 = m_delay_19.read_linear(mul_199);
			double mul_196 = (tap_198 * 0.625);
			double phasor_84 = m_phasor_39(div_63, samples_to_seconds);
			double add_56 = ((m_history_6 + phasor_84) + 0.75);
			double mod_55 = safemod(add_56, 1);
			double delta_38 = m_delta_40(mod_55);
			double sah_18 = m_sah_41(mul_36, delta_38, 0);
			double sah_37 = m_sah_42(mstosamps_78, delta_38, 0);
			double mul_28 = (sah_37 * mod_55);
			double sub_54 = (mod_55 - 0.5);
			double mul_53 = (sub_54 * 3.1415926535898);
			double cos_52 = cos(mul_53);
			double mul_47 = (cos_52 * cos_52);
			double add_77 = ((m_history_5 + phasor_84) + 0.25);
			double mod_76 = safemod(add_77, 1);
			double delta_44 = m_delta_43(mod_76);
			double sah_22 = m_sah_44(mul_42, delta_44, 0);
			double sah_43 = m_sah_45(mstosamps_78, delta_44, 0);
			double mul_30 = (sah_43 * mod_76);
			double sub_75 = (mod_76 - 0.5);
			double mul_74 = (sub_75 * 3.1415926535898);
			double cos_73 = cos(mul_74);
			double mul_49 = (cos_73 * cos_73);
			double add_83 = ((m_history_4 + phasor_84) + 0);
			double mod_82 = safemod(add_83, 1);
			double delta_25 = m_delta_46(mod_82);
			double sah_24 = m_sah_47(mul_45, delta_25, 0);
			double sah_46 = m_sah_48(mstosamps_78, delta_25, 0);
			double mul_31 = (sah_46 * mod_82);
			double sub_81 = (mod_82 - 0.5);
			double mul_80 = (sub_81 * 3.1415926535898);
			double cos_79 = cos(mul_80);
			double mul_50 = (cos_79 * cos_79);
			double add_62 = ((m_history_3 + phasor_84) + 0.5);
			double mod_61 = safemod(add_62, 1);
			double delta_41 = m_delta_49(mod_61);
			double sah_20 = m_sah_50(mul_39, delta_41, 0);
			double sah_40 = m_sah_51(mstosamps_78, delta_41, 0);
			double mul_29 = (sah_40 * mod_61);
			double tap_69 = m_delay_18.read_linear(mul_31);
			double tap_70 = m_delay_18.read_linear(mul_30);
			double tap_71 = m_delay_18.read_linear(mul_29);
			double tap_72 = m_delay_18.read_linear(mul_28);
			double mul_51 = (tap_72 * mul_47);
			double mul_66 = (tap_70 * mul_49);
			double mul_67 = (tap_69 * mul_50);
			double sub_60 = (mod_61 - 0.5);
			double mul_59 = (sub_60 * 3.1415926535898);
			double cos_58 = cos(mul_59);
			double mul_48 = (cos_58 * cos_58);
			double mul_57 = (tap_71 * mul_48);
			double mul_5 = ((((mul_67 + mul_66) + mul_57) + mul_51) * add_6);
			double sub_2 = (mul_5 - (mul_4 + mul_3));
			double mix_301 = (in1 + (m_shimmer_35 * (sub_2 - in1)));
			double mix_27 = mix_301;
			double mul_87 = (mix_27 * 0.707);
			double mix_302 = (mul_87 + (rsub_238 * (m_history_1 - mul_87)));
			double mix_237 = mix_302;
			double tap_141 = m_delay_17.read_linear(add_156);
			double tap_142 = m_delay_17.read_linear(add_155);
			double tap_143 = m_delay_17.read_linear(add_154);
			double tap_144 = m_delay_17.read_linear(add_153);
			double mul_151 = (tap_141 * expr_269);
			double add_121 = (mul_96 + mul_151);
			double mul_149 = (tap_142 * expr_268);
			double add_120 = (mul_95 + mul_149);
			double mul_145 = (tap_144 * expr_266);
			double add_118 = (mul_93 + mul_145);
			double mul_147 = (tap_143 * expr_267);
			double add_119 = (mul_94 + mul_147);
			double tap_221 = m_delay_16.read_linear(mul_222);
			double mul_219 = (tap_221 * 0.75);
			double sub_218 = (mix_237 - mul_219);
			double mul_217 = (sub_218 * 0.75);
			double add_216 = (mul_217 + tap_221);
			double tap_179 = m_delay_15.read_linear(mul_180);
			double mul_177 = (tap_179 * 0.625);
			double tap_205 = m_delay_14.read_linear(mul_206);
			double mul_203 = (tap_205 * 0.625);
			double tap_186 = m_delay_13.read_linear(mul_187);
			double mul_184 = (tap_186 * 0.75);
			double tap_214 = m_delay_12.read_linear(mul_215);
			double mul_212 = (tap_214 * 0.75);
			double mul_108 = (mul_96 * m_tail_28);
			double mul_106 = (mul_94 * m_tail_28);
			double add_92 = (mul_108 + mul_106);
			double mul_107 = (mul_95 * m_tail_28);
			double mul_105 = (mul_93 * m_tail_28);
			double add_91 = (mul_107 + mul_105);
			double sub_100 = (add_92 - add_91);
			double mul_104 = (mul_151 * m_early_34);
			double mul_102 = (mul_147 * m_early_34);
			double add_90 = (mul_104 + mul_102);
			double mul_103 = (mul_149 * m_early_34);
			double mul_101 = (mul_145 * m_early_34);
			double add_89 = (mul_103 + mul_101);
			double sub_99 = (add_90 - add_89);
			double add_86 = (sub_100 + sub_99);
			double add_88 = (add_86 + mix_27);
			double sub_183 = (add_88 - mul_184);
			double mul_182 = (sub_183 * 0.75);
			double add_181 = (mul_182 + tap_186);
			double sub_176 = (add_181 - mul_177);
			double mul_175 = (sub_176 * 0.625);
			double add_174 = (mul_175 + tap_179);
			double sub_169 = (add_174 - mul_170);
			double mul_168 = (sub_169 * 0.625);
			double add_167 = (mul_168 + tap_172);
			double mul_85 = (add_167 * m_mix_31);
			double out2 = (mul_85 + in1);
			double add_98 = (add_86 + mix_27);
			double sub_211 = (add_98 - mul_212);
			double mul_210 = (sub_211 * 0.75);
			double add_209 = (mul_210 + tap_214);
			double sub_202 = (add_209 - mul_203);
			double mul_201 = (sub_202 * 0.625);
			double add_200 = (mul_201 + tap_205);
			double sub_195 = (add_200 - mul_196);
			double mul_194 = (sub_195 * 0.625);
			double add_193 = (mul_194 + tap_198);
			double mul_97 = (add_193 * m_mix_31);
			double out1 = (mul_97 + in1);
			double y2_next_286 = m_y_2;
			double history_232_next_287 = mix_233;
			double history_136_next_288 = mix_137;
			double history_130_next_289 = mix_131;
			double history_124_next_290 = mix_125;
			double history_19_next_291 = sah_18;
			double history_23_next_292 = sah_22;
			double history_26_next_293 = sah_24;
			double history_21_next_294 = sah_20;
			double y1_next_295 = sub_2;
			double history_236_next_296 = mix_237;
			m_delay_24.write(add_121);
			m_delay_23.write(add_120);
			m_delay_22.write(add_119);
			m_delay_21.write(add_118);
			m_delay_20.write(sub_169);
			m_delay_19.write(sub_195);
			m_delay_18.write(in1);
			m_delay_17.write(add_216);
			m_delay_16.write(sub_218);
			m_delay_15.write(sub_176);
			m_delay_14.write(sub_202);
			m_delay_13.write(sub_183);
			m_delay_12.write(sub_211);
			m_y_11 = y2_next_286;
			m_history_10 = history_232_next_287;
			m_history_9 = history_136_next_288;
			m_history_8 = history_130_next_289;
			m_history_7 = history_124_next_290;
			m_history_6 = history_19_next_291;
			m_history_5 = history_23_next_292;
			m_history_4 = history_26_next_293;
			m_history_3 = history_21_next_294;
			m_y_2 = y1_next_295;
			m_history_1 = history_236_next_296;
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
	inline void set_roomsize(double _value) {
		m_roomsize_25 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_decay(double _value) {
		m_decay_26 = (_value < 0.1 ? 0.1 : (_value > 360 ? 360 : _value));
	};
	inline void set_spread(double _value) {
		m_spread_27 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_tail(double _value) {
		m_tail_28 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_tone(double _value) {
		m_tone_29 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_damping(double _value) {
		m_damping_30 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_31 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_resonance(double _value) {
		m_resonance_32 = (_value < 0 ? 0 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_cutoff(double _value) {
		m_cutoff_33 = (_value < 0 ? 0 : (_value > 6000 ? 6000 : _value));
	};
	inline void set_early(double _value) {
		m_early_34 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_shimmer(double _value) {
		m_shimmer_35 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_blur(double _value) {
		m_blur_36 = (_value < 0.01 ? 0.01 : (_value > 0.25 ? 0.25 : _value));
	};
	inline void set_window(double _value) {
		m_window_37 = (_value < 0.1 ? 0.1 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_ratio(double _value) {
		m_ratio_38 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
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
		case 0: self->set_roomsize(value); break;
		case 1: self->set_decay(value); break;
		case 2: self->set_spread(value); break;
		case 3: self->set_tail(value); break;
		case 4: self->set_tone(value); break;
		case 5: self->set_damping(value); break;
		case 6: self->set_mix(value); break;
		case 7: self->set_resonance(value); break;
		case 8: self->set_cutoff(value); break;
		case 9: self->set_early(value); break;
		case 10: self->set_shimmer(value); break;
		case 11: self->set_blur(value); break;
		case 12: self->set_window(value); break;
		case 13: self->set_ratio(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_roomsize_25; break;
		case 1: *value = self->m_decay_26; break;
		case 2: *value = self->m_spread_27; break;
		case 3: *value = self->m_tail_28; break;
		case 4: *value = self->m_tone_29; break;
		case 5: *value = self->m_damping_30; break;
		case 6: *value = self->m_mix_31; break;
		case 7: *value = self->m_resonance_32; break;
		case 8: *value = self->m_cutoff_33; break;
		case 9: *value = self->m_early_34; break;
		case 10: *value = self->m_shimmer_35; break;
		case 11: *value = self->m_blur_36; break;
		case 12: *value = self->m_window_37; break;
		case 13: *value = self->m_ratio_38; break;
		
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
	// initialize parameter 0 ("m_roomsize_25")
	pi = self->__commonstate.params + 0;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 300;
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
	// initialize parameter 2 ("m_spread_27")
	pi = self->__commonstate.params + 2;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_tail_28")
	pi = self->__commonstate.params + 3;
	pi->name = "tail";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tail_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_tone_29")
	pi = self->__commonstate.params + 4;
	pi->name = "tone";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tone_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
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
	// initialize parameter 6 ("m_mix_31")
	pi = self->__commonstate.params + 6;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_resonance_32")
	pi = self->__commonstate.params + 7;
	pi->name = "resonance";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_resonance_32;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_cutoff_33")
	pi = self->__commonstate.params + 8;
	pi->name = "cutoff";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cutoff_33;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 6000;
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
	// initialize parameter 10 ("m_shimmer_35")
	pi = self->__commonstate.params + 10;
	pi->name = "shimmer";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_shimmer_35;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_blur_36")
	pi = self->__commonstate.params + 11;
	pi->name = "blur";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_blur_36;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
	pi->outputmax = 0.25;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_window_37")
	pi = self->__commonstate.params + 12;
	pi->name = "window";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_window_37;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_ratio_38")
	pi = self->__commonstate.params + 13;
	pi->name = "ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ratio_38;
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
