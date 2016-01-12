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
	double m_roomsize_25;
	double m_shimmer_24;
	double m_ratio_27;
	double m_decay_26;
	double m_damping_29;
	double m_mix_30;
	double m_tone_28;
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
		m_shimmer_24 = 50;
		m_roomsize_25 = 200;
		m_decay_26 = 50;
		m_ratio_27 = 2;
		m_tone_28 = 1500;
		m_damping_29 = 90;
		m_mix_30 = 100;
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
		double mul_13 = (m_mix_30 * 0.01);
		double mul_1 = (m_damping_29 * 100);
		double sqrt_2 = sqrt(mul_1);
		double mul_7 = (sqrt_2 * 0.01);
		double mul_14 = (m_shimmer_24 * 0.01);
		double expr_232 = safediv(((m_tone_28 * 2) * 3.1415926535898), 48000);
		double sin_20 = sin(expr_232);
		double clamp_21 = ((sin_20 <= 1e-05) ? 1e-05 : ((sin_20 >= 0.99999) ? 0.99999 : sin_20));
		double expr_242 = safediv((m_roomsize_25 * 48000), 340);
		double mul_221 = (expr_242 * 0.81649);
		double mul_222 = (expr_242 * 1);
		double mul_219 = (expr_242 * 0.63245);
		double mul_220 = (expr_242 * 0.7071);
		double mul_216 = (expr_242 * 0.000527);
		int int_215 = int(mul_216);
		double mul_193 = (int_215 * 400.600006);
		double mul_172 = (int_215 * 419.5);
		double add_159 = (expr_242 + 5);
		double mul_8 = (m_decay_26 * 2);
		double clamp_9 = ((mul_8 <= 0.1) ? 0.1 : ((mul_8 >= 100) ? 100 : mul_8));
		double mul_17 = (clamp_9 * 3.6);
		double expr_241 = safepow(0.001, safediv(1, (mul_17 * 48000)));
		double expr_235 = (-safepow(expr_241, mul_221));
		double expr_240 = (-safepow(expr_241, mul_222));
		double expr_233 = (-safepow(expr_241, mul_219));
		double expr_234 = (-safepow(expr_241, mul_220));
		double expr_236 = safepow(expr_241, add_159);
		double rsub_71 = (1 - m_ratio_27);
		double mul_70 = (rsub_71 * 10);
		samples_to_seconds = (1 / samplerate);
		double mul_200 = (int_215 * 568.299988);
		double mul_179 = (int_215 * 566.700012);
		double mul_165 = (expr_242 * 0.41);
		double add_162 = (mul_165 + 5);
		double expr_239 = safepow(expr_241, add_162);
		double mul_164 = (expr_242 * 0.3);
		double add_161 = (mul_164 + 5);
		double expr_238 = safepow(expr_241, add_161);
		double mul_163 = (expr_242 * 0.155);
		double add_160 = (mul_163 + 5);
		double expr_237 = safepow(expr_241, add_160);
		double mul_214 = (expr_242 * 0.110732);
		double mul_207 = (int_215 * 162.100006);
		double mul_186 = (int_215 * 144.800003);
		double mul_12 = (m_decay_26 * 0.01);
		int gt_6 = (m_decay_26 > 25);
		double mul_5 = (gt_6 * m_decay_26);
		double sub_3 = (mul_5 - 25);
		double expr_231 = safepow(1.06347, sub_3);
		double sub_10 = (expr_231 - 1);
		double clamp_4 = ((sub_10 <= 0) ? 0 : ((sub_10 >= 100) ? 100 : sub_10));
		double mul_16 = (clamp_4 * 0.01);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double noise_25 = noise();
			double abs_42 = fabs(noise_25);
			double mul_52 = (abs_42 * 0.25);
			double noise_24 = noise();
			double abs_41 = fabs(noise_24);
			double mul_49 = (abs_41 * 0.25);
			double noise_23 = noise();
			double abs_40 = fabs(noise_23);
			double mul_46 = (abs_40 * 0.25);
			double noise_22 = noise();
			double abs_39 = fabs(noise_22);
			double mul_43 = (abs_39 * 0.25);
			double tap_145 = m_delay_23.read_cubic(mul_221);
			double tap_227 = m_delay_22.read_cubic(mul_222);
			double tap_133 = m_delay_21.read_cubic(mul_219);
			double tap_139 = m_delay_20.read_cubic(mul_220);
			double tap_192 = m_delay_19.read_linear(mul_193);
			double mul_190 = (tap_192 * 0.625);
			double tap_171 = m_delay_18.read_linear(mul_172);
			double mul_169 = (tap_171 * 0.625);
			double mul_141 = (tap_145 * expr_235);
			double mix_253 = (mul_141 + (mul_7 * (m_history_10 - mul_141)));
			double mix_143 = mix_253;
			double mul_218 = (tap_227 * expr_240);
			double mix_254 = (mul_218 + (mul_7 * (m_history_9 - mul_218)));
			double mix_225 = mix_254;
			double sub_122 = (mix_225 - mix_143);
			double mul_129 = (tap_133 * expr_233);
			double mix_255 = (mul_129 + (mul_7 * (m_history_8 - mul_129)));
			double mix_131 = mix_255;
			double mul_135 = (tap_139 * expr_234);
			double mix_256 = (mul_135 + (mul_7 * (m_history_7 - mul_135)));
			double mix_137 = mix_256;
			double sub_119 = (mix_137 - mix_131);
			double sub_118 = (sub_122 - sub_119);
			double mul_101 = (sub_118 * 0.5);
			double add_123 = (mix_225 + mix_143);
			double add_121 = (mix_137 + mix_131);
			double sub_120 = (add_123 - add_121);
			double mul_102 = (sub_120 * 0.5);
			double add_116 = (add_123 + add_121);
			double mul_99 = (add_116 * 0.5);
			double phasor_89 = m_phasor_31(mul_70, samples_to_seconds);
			double add_88 = ((m_history_6 + phasor_89) + 0);
			double mod_87 = safemod(add_88, 1);
			double delta_33 = m_delta_32(mod_87);
			double sah_32 = m_sah_33(mul_52, delta_33, 0);
			int sah_53 = m_sah_34(4800, delta_33, 0);
			double mul_38 = (sah_53 * mod_87);
			double sub_86 = (mod_87 - 0.5);
			double mul_85 = (sub_86 * 3.1415926535898);
			double cos_84 = cos(mul_85);
			double mul_57 = (cos_84 * cos_84);
			double add_83 = ((m_history_5 + phasor_89) + 0.25);
			double mod_82 = safemod(add_83, 1);
			double delta_51 = m_delta_35(mod_82);
			double sah_30 = m_sah_36(mul_49, delta_51, 0);
			int sah_50 = m_sah_37(4800, delta_51, 0);
			double mul_37 = (sah_50 * mod_82);
			double sub_81 = (mod_82 - 0.5);
			double mul_80 = (sub_81 * 3.1415926535898);
			double cos_79 = cos(mul_80);
			double mul_56 = (cos_79 * cos_79);
			double add_69 = ((m_history_4 + phasor_89) + 0.5);
			double mod_68 = safemod(add_69, 1);
			double delta_48 = m_delta_38(mod_68);
			double sah_28 = m_sah_39(mul_46, delta_48, 0);
			int sah_47 = m_sah_40(4800, delta_48, 0);
			double mul_36 = (sah_47 * mod_68);
			double sub_67 = (mod_68 - 0.5);
			double mul_66 = (sub_67 * 3.1415926535898);
			double cos_65 = cos(mul_66);
			double mul_55 = (cos_65 * cos_65);
			double add_63 = ((m_history_3 + phasor_89) + 0.75);
			double mod_62 = safemod(add_63, 1);
			double delta_45 = m_delta_41(mod_62);
			double sah_26 = m_sah_42(mul_43, delta_45, 0);
			int sah_44 = m_sah_43(4800, delta_45, 0);
			double mul_35 = (sah_44 * mod_62);
			double tap_75 = m_delay_17.read_linear(mul_38);
			double tap_76 = m_delay_17.read_linear(mul_37);
			double tap_77 = m_delay_17.read_linear(mul_36);
			double tap_78 = m_delay_17.read_linear(mul_35);
			double mul_64 = (tap_77 * mul_55);
			double mul_72 = (tap_76 * mul_56);
			double mul_73 = (tap_75 * mul_57);
			double sub_61 = (mod_62 - 0.5);
			double mul_60 = (sub_61 * 3.1415926535898);
			double cos_59 = cos(mul_60);
			double mul_54 = (cos_59 * cos_59);
			double mul_58 = (tap_78 * mul_54);
			double add_258 = (((mul_73 + mul_72) + mul_64) + mul_58);
			double mix_257 = (m_y_2 + (clamp_21 * (add_258 - m_y_2)));
			double mix_18 = mix_257;
			double mix_259 = (in1 + (mul_14 * (mix_18 - in1)));
			double mix_90 = mix_259;
			double mul_93 = (mix_90 * 0.707);
			double mix_260 = (mul_93 + (0.5 * (m_history_1 - mul_93)));
			double mix_229 = mix_260;
			double tap_199 = m_delay_16.read_linear(mul_200);
			double tap_178 = m_delay_15.read_linear(mul_179);
			double add_117 = (sub_122 + sub_119);
			double rsub_115 = (0 - add_117);
			double mul_100 = (rsub_115 * 0.5);
			double tap_147 = m_delay_14.read_cubic(add_162);
			double tap_148 = m_delay_14.read_cubic(add_161);
			double tap_149 = m_delay_14.read_cubic(add_160);
			double tap_150 = m_delay_14.read_cubic(add_159);
			double mul_155 = (tap_148 * expr_238);
			double add_126 = (mul_101 + mul_155);
			double mul_157 = (tap_147 * expr_239);
			double add_127 = (mul_102 + mul_157);
			double mul_151 = (tap_150 * expr_236);
			double add_124 = (mul_99 + mul_151);
			double mul_153 = (tap_149 * expr_237);
			double add_125 = (mul_100 + mul_153);
			double mul_197 = (tap_199 * 0.625);
			double mul_176 = (tap_178 * 0.625);
			double tap_213 = m_delay_13.read_cubic(mul_214);
			double mul_211 = (tap_213 * 0.75);
			double sub_210 = (mix_229 - mul_211);
			double mul_209 = (sub_210 * 0.75);
			double add_208 = (mul_209 + tap_213);
			double tap_206 = m_delay_12.read_linear(mul_207);
			double tap_185 = m_delay_11.read_linear(mul_186);
			double mul_204 = (tap_206 * 0.75);
			double mul_183 = (tap_185 * 0.75);
			double mul_110 = (mul_157 * mul_12);
			double mul_108 = (mul_153 * mul_12);
			double add_96 = (mul_110 + mul_108);
			double mul_109 = (mul_155 * mul_12);
			double mul_107 = (mul_151 * mul_12);
			double add_95 = (mul_109 + mul_107);
			double sub_105 = (add_96 - add_95);
			double mul_114 = (mul_102 * mul_16);
			double mul_112 = (mul_100 * mul_16);
			double add_98 = (mul_114 + mul_112);
			double mul_113 = (mul_101 * mul_16);
			double mul_111 = (mul_99 * mul_16);
			double add_97 = (mul_113 + mul_111);
			double sub_106 = (add_98 - add_97);
			double add_92 = (sub_106 + sub_105);
			double add_104 = (add_92 + mix_90);
			double sub_203 = (add_104 - mul_204);
			double mul_202 = (sub_203 * 0.75);
			double add_201 = (mul_202 + tap_206);
			double sub_196 = (add_201 - mul_197);
			double mul_195 = (sub_196 * 0.625);
			double add_194 = (mul_195 + tap_199);
			double sub_189 = (add_194 - mul_190);
			double mul_188 = (sub_189 * 0.625);
			double add_187 = (mul_188 + tap_192);
			double mul_103 = (add_187 * mul_13);
			double out1 = (in1 + mul_103);
			double add_94 = (add_92 + mix_90);
			double sub_182 = (add_94 - mul_183);
			double mul_181 = (sub_182 * 0.75);
			double add_180 = (mul_181 + tap_185);
			double sub_175 = (add_180 - mul_176);
			double mul_174 = (sub_175 * 0.625);
			double add_173 = (mul_174 + tap_178);
			double sub_168 = (add_173 - mul_169);
			double mul_167 = (sub_168 * 0.625);
			double add_166 = (mul_167 + tap_171);
			double mul_91 = (add_166 * mul_13);
			double out2 = (in1 + mul_91);
			double history_142_next_243 = mix_143;
			double history_224_next_244 = mix_225;
			double history_130_next_245 = mix_131;
			double history_136_next_246 = mix_137;
			double history_34_next_247 = sah_32;
			double history_31_next_248 = sah_30;
			double history_29_next_249 = sah_28;
			double history_27_next_250 = sah_26;
			double y0_next_251 = mix_18;
			double history_228_next_252 = mix_229;
			m_delay_23.write(add_126);
			m_delay_22.write(add_127);
			m_delay_21.write(add_124);
			m_delay_20.write(add_125);
			m_delay_19.write(sub_189);
			m_delay_18.write(sub_168);
			m_delay_17.write(in1);
			m_delay_16.write(sub_196);
			m_delay_15.write(sub_175);
			m_delay_14.write(add_208);
			m_delay_13.write(sub_210);
			m_delay_12.write(sub_203);
			m_delay_11.write(sub_182);
			m_history_10 = history_142_next_243;
			m_history_9 = history_224_next_244;
			m_history_8 = history_130_next_245;
			m_history_7 = history_136_next_246;
			m_history_6 = history_34_next_247;
			m_history_5 = history_31_next_248;
			m_history_4 = history_29_next_249;
			m_history_3 = history_27_next_250;
			m_y_2 = y0_next_251;
			m_history_1 = history_228_next_252;
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
	inline void set_shimmer(double _value) {
		m_shimmer_24 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_roomsize(double _value) {
		m_roomsize_25 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_decay(double _value) {
		m_decay_26 = (_value < 0.1 ? 0.1 : (_value > 100 ? 100 : _value));
	};
	inline void set_ratio(double _value) {
		m_ratio_27 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_tone(double _value) {
		m_tone_28 = (_value < 500 ? 500 : (_value > 6000 ? 6000 : _value));
	};
	inline void set_damping(double _value) {
		m_damping_29 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
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
		case 0: self->set_shimmer(value); break;
		case 1: self->set_roomsize(value); break;
		case 2: self->set_decay(value); break;
		case 3: self->set_ratio(value); break;
		case 4: self->set_tone(value); break;
		case 5: self->set_damping(value); break;
		case 6: self->set_mix(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_shimmer_24; break;
		case 1: *value = self->m_roomsize_25; break;
		case 2: *value = self->m_decay_26; break;
		case 3: *value = self->m_ratio_27; break;
		case 4: *value = self->m_tone_28; break;
		case 5: *value = self->m_damping_29; break;
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
	// initialize parameter 0 ("m_shimmer_24")
	pi = self->__commonstate.params + 0;
	pi->name = "shimmer";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_shimmer_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_roomsize_25")
	pi = self->__commonstate.params + 1;
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
	// initialize parameter 2 ("m_decay_26")
	pi = self->__commonstate.params + 2;
	pi->name = "decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decay_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 100;
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
	// initialize parameter 4 ("m_tone_28")
	pi = self->__commonstate.params + 4;
	pi->name = "tone";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tone_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 500;
	pi->outputmax = 6000;
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
