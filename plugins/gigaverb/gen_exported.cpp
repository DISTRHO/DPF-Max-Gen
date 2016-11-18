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
	Delay m_delay_11;
	Delay m_delay_10;
	Delay m_delay_12;
	Delay m_delay_6;
	Delay m_delay_7;
	Delay m_delay_8;
	Delay m_delay_13;
	Delay m_delay_15;
	Delay m_delay_14;
	Delay m_delay_17;
	Delay m_delay_16;
	Delay m_delay_9;
	int __exception;
	int vectorsize;
	t_sample m_roomsize_20;
	t_sample m_revtime_19;
	t_sample m_damping_24;
	t_sample m_dry_21;
	t_sample m_bandwidth_23;
	t_sample m_tail_22;
	t_sample m_history_5;
	t_sample m_early_18;
	t_sample m_history_1;
	t_sample m_history_4;
	t_sample samplerate;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample m_spread_25;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = 0;
		m_history_2 = 0;
		m_history_3 = 0;
		m_history_4 = 0;
		m_history_5 = 0;
		m_delay_6.reset("m_delay_6", 7000);
		m_delay_7.reset("m_delay_7", 5000);
		m_delay_8.reset("m_delay_8", 16000);
		m_delay_9.reset("m_delay_9", 6000);
		m_delay_10.reset("m_delay_10", 15000);
		m_delay_11.reset("m_delay_11", 12000);
		m_delay_12.reset("m_delay_12", 48000);
		m_delay_13.reset("m_delay_13", 10000);
		m_delay_14.reset("m_delay_14", 48000);
		m_delay_15.reset("m_delay_15", 48000);
		m_delay_16.reset("m_delay_16", 48000);
		m_delay_17.reset("m_delay_17", 48000);
		m_early_18 = 0.25;
		m_revtime_19 = 11;
		m_roomsize_20 = 75;
		m_dry_21 = 1;
		m_tail_22 = 0.25;
		m_bandwidth_23 = 0.5;
		m_damping_24 = 0.7;
		m_spread_25 = 23;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_317 = ((m_roomsize_20 * samplerate) * 0.0029411764705882);
		t_sample expr_316 = safepow(0.001, safediv(1, (m_revtime_19 * samplerate)));
		t_sample add_221 = (expr_317 + 5);
		t_sample expr_311 = safepow(expr_316, add_221);
		t_sample mul_298 = (expr_317 * 1);
		t_sample expr_315 = (-safepow(expr_316, mul_298));
		t_sample mul_297 = (expr_317 * 0.81649);
		t_sample expr_310 = (-safepow(expr_316, mul_297));
		t_sample mul_295 = (expr_317 * 0.63245);
		t_sample expr_308 = (-safepow(expr_316, mul_295));
		t_sample mul_296 = (expr_317 * 0.7071);
		t_sample expr_309 = (-safepow(expr_316, mul_296));
		t_sample mul_227 = (expr_317 * 0.41);
		t_sample add_224 = (mul_227 + 5);
		t_sample expr_314 = safepow(expr_316, add_224);
		t_sample mul_226 = (expr_317 * 0.3);
		t_sample add_223 = (mul_226 + 5);
		t_sample expr_313 = safepow(expr_316, add_223);
		t_sample mul_225 = (expr_317 * 0.155);
		t_sample add_222 = (mul_225 + 5);
		t_sample expr_312 = safepow(expr_316, add_222);
		t_sample rsub_306 = (1 - m_bandwidth_23);
		t_sample mul_292 = (expr_317 * 0.000527);
		int int_291 = int(mul_292);
		t_sample mul_260 = (m_spread_25 * 0.376623);
		t_sample add_259 = (mul_260 + 931);
		t_sample rsub_256 = (1341 - add_259);
		t_sample mul_267 = (int_291 * rsub_256);
		t_sample mul_232 = (m_spread_25 * (-0.380445));
		t_sample add_231 = (mul_232 + 931);
		t_sample rsub_228 = (1341 - add_231);
		t_sample mul_241 = (int_291 * rsub_228);
		t_sample mul_276 = (m_spread_25 * 0.125541);
		t_sample add_258 = (mul_276 + 369);
		t_sample rsub_257 = (add_259 - add_258);
		t_sample mul_274 = (int_291 * rsub_257);
		t_sample mul_290 = (expr_317 * 0.110732);
		t_sample mul_234 = (m_spread_25 * (-0.568366));
		t_sample add_230 = (mul_234 + 369);
		t_sample rsub_229 = (add_231 - add_230);
		t_sample mul_248 = (int_291 * rsub_229);
		t_sample add_275 = (mul_276 + 159);
		t_sample mul_283 = (int_291 * add_275);
		t_sample add_233 = (mul_234 + 159);
		t_sample mul_255 = (int_291 * add_233);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_165 = (in1 * m_dry_21);
			t_sample mul_153 = (in2 * m_dry_21);
			t_sample mul_155 = ((in1 + in2) * 0.707);
			t_sample mix_323 = (mul_155 + (rsub_306 * (m_history_5 - mul_155)));
			t_sample mix_305 = mix_323;
			t_sample tap_201 = m_delay_17.read_linear(mul_296);
			t_sample mul_197 = (tap_201 * expr_309);
			t_sample mix_324 = (mul_197 + (m_damping_24 * (m_history_4 - mul_197)));
			t_sample mix_199 = mix_324;
			t_sample tap_207 = m_delay_16.read_linear(mul_297);
			t_sample mul_203 = (tap_207 * expr_310);
			t_sample mix_325 = (mul_203 + (m_damping_24 * (m_history_3 - mul_203)));
			t_sample mix_205 = mix_325;
			t_sample tap_303 = m_delay_15.read_linear(mul_298);
			t_sample mul_294 = (tap_303 * expr_315);
			t_sample mix_326 = (mul_294 + (m_damping_24 * (m_history_2 - mul_294)));
			t_sample mix_301 = mix_326;
			t_sample tap_195 = m_delay_14.read_linear(mul_295);
			t_sample mul_191 = (tap_195 * expr_308);
			t_sample mix_327 = (mul_191 + (m_damping_24 * (m_history_1 - mul_191)));
			t_sample mix_193 = mix_327;
			t_sample tap_266 = m_delay_13.read_linear(mul_267);
			t_sample mul_264 = (tap_266 * 0.625);
			t_sample tap_209 = m_delay_12.read_linear(add_224);
			t_sample tap_210 = m_delay_12.read_linear(add_223);
			t_sample tap_211 = m_delay_12.read_linear(add_222);
			t_sample tap_212 = m_delay_12.read_linear(add_221);
			t_sample mul_215 = (tap_211 * expr_312);
			t_sample mul_217 = (tap_210 * expr_313);
			t_sample mul_219 = (tap_209 * expr_314);
			t_sample mul_213 = (tap_212 * expr_311);
			t_sample tap_240 = m_delay_11.read_linear(mul_241);
			t_sample mul_238 = (tap_240 * 0.625);
			t_sample sub_184 = (mix_301 - mix_205);
			t_sample sub_181 = (mix_199 - mix_193);
			t_sample sub_180 = (sub_184 - sub_181);
			t_sample mul_163 = (sub_180 * 0.5);
			t_sample add_188 = (mul_163 + mul_217);
			t_sample add_179 = (sub_184 + sub_181);
			t_sample rsub_177 = (0 - add_179);
			t_sample mul_162 = (rsub_177 * 0.5);
			t_sample add_187 = (mul_162 + mul_215);
			t_sample add_185 = (mix_301 + mix_205);
			t_sample add_183 = (mix_199 + mix_193);
			t_sample sub_182 = (add_185 - add_183);
			t_sample mul_164 = (sub_182 * 0.5);
			t_sample add_189 = (mul_164 + mul_219);
			t_sample add_178 = (add_185 + add_183);
			t_sample mul_161 = (add_178 * 0.5);
			t_sample add_186 = (mul_161 + mul_213);
			t_sample tap_273 = m_delay_10.read_linear(mul_274);
			t_sample mul_271 = (tap_273 * 0.625);
			t_sample tap_289 = m_delay_9.read_linear(mul_290);
			t_sample tap_247 = m_delay_8.read_linear(mul_248);
			t_sample mul_245 = (tap_247 * 0.625);
			t_sample tap_282 = m_delay_7.read_linear(mul_283);
			t_sample mul_280 = (tap_282 * 0.75);
			t_sample mul_287 = (tap_289 * 0.75);
			t_sample sub_286 = (mix_305 - mul_287);
			t_sample mul_285 = (sub_286 * 0.75);
			t_sample add_284 = (mul_285 + tap_289);
			t_sample tap_254 = m_delay_6.read_linear(mul_255);
			t_sample mul_252 = (tap_254 * 0.75);
			t_sample mul_176 = (mul_164 * m_tail_22);
			t_sample mul_174 = (mul_162 * m_tail_22);
			t_sample add_160 = (mul_176 + mul_174);
			t_sample mul_175 = (mul_163 * m_tail_22);
			t_sample mul_173 = (mul_161 * m_tail_22);
			t_sample add_159 = (mul_175 + mul_173);
			t_sample sub_168 = (add_160 - add_159);
			t_sample mul_172 = (mul_219 * m_early_18);
			t_sample mul_170 = (mul_215 * m_early_18);
			t_sample add_158 = (mul_172 + mul_170);
			t_sample mul_171 = (mul_217 * m_early_18);
			t_sample mul_169 = (mul_213 * m_early_18);
			t_sample add_157 = (mul_171 + mul_169);
			t_sample sub_167 = (add_158 - add_157);
			t_sample add_154 = (sub_168 + sub_167);
			t_sample add_166 = (add_154 + in1);
			t_sample sub_279 = (add_166 - mul_280);
			t_sample mul_278 = (sub_279 * 0.75);
			t_sample add_277 = (mul_278 + tap_282);
			t_sample sub_270 = (add_277 - mul_271);
			t_sample mul_269 = (sub_270 * 0.625);
			t_sample add_268 = (mul_269 + tap_273);
			t_sample sub_263 = (add_268 - mul_264);
			t_sample mul_262 = (sub_263 * 0.625);
			t_sample add_261 = (mul_262 + tap_266);
			t_sample out1 = (mul_165 + add_261);
			t_sample add_156 = (add_154 + in2);
			t_sample sub_251 = (add_156 - mul_252);
			t_sample mul_250 = (sub_251 * 0.75);
			t_sample add_249 = (mul_250 + tap_254);
			t_sample sub_244 = (add_249 - mul_245);
			t_sample mul_243 = (sub_244 * 0.625);
			t_sample add_242 = (mul_243 + tap_247);
			t_sample sub_237 = (add_242 - mul_238);
			t_sample mul_236 = (sub_237 * 0.625);
			t_sample add_235 = (mul_236 + tap_240);
			t_sample out2 = (mul_153 + add_235);
			t_sample history_304_next_318 = fixdenorm(mix_305);
			t_sample history_198_next_319 = fixdenorm(mix_199);
			t_sample history_204_next_320 = fixdenorm(mix_205);
			t_sample history_300_next_321 = fixdenorm(mix_301);
			t_sample history_192_next_322 = fixdenorm(mix_193);
			m_delay_17.write(add_187);
			m_delay_16.write(add_188);
			m_delay_15.write(add_189);
			m_delay_14.write(add_186);
			m_delay_13.write(sub_263);
			m_delay_12.write(add_284);
			m_delay_11.write(sub_237);
			m_delay_10.write(sub_270);
			m_delay_9.write(sub_286);
			m_delay_8.write(sub_244);
			m_delay_7.write(sub_279);
			m_delay_6.write(sub_251);
			m_history_5 = history_304_next_318;
			m_history_4 = history_198_next_319;
			m_history_3 = history_204_next_320;
			m_history_2 = history_300_next_321;
			m_history_1 = history_192_next_322;
			m_delay_6.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_9.step();
			m_delay_10.step();
			m_delay_11.step();
			m_delay_12.step();
			m_delay_13.step();
			m_delay_14.step();
			m_delay_15.step();
			m_delay_16.step();
			m_delay_17.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_early(t_param _value) {
		m_early_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_revtime(t_param _value) {
		m_revtime_19 = (_value < 0.1 ? 0.1 : (_value > 360 ? 360 : _value));
	};
	inline void set_roomsize(t_param _value) {
		m_roomsize_20 = (_value < 0.1 ? 0.1 : (_value > 300 ? 300 : _value));
	};
	inline void set_dry(t_param _value) {
		m_dry_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_tail(t_param _value) {
		m_tail_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_bandwidth(t_param _value) {
		m_bandwidth_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_damping(t_param _value) {
		m_damping_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_spread(t_param _value) {
		m_spread_25 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 8; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

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
		case 0: self->set_bandwidth(value); break;
		case 1: self->set_damping(value); break;
		case 2: self->set_dry(value); break;
		case 3: self->set_early(value); break;
		case 4: self->set_revtime(value); break;
		case 5: self->set_roomsize(value); break;
		case 6: self->set_spread(value); break;
		case 7: self->set_tail(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_bandwidth_23; break;
		case 1: *value = self->m_damping_24; break;
		case 2: *value = self->m_dry_21; break;
		case 3: *value = self->m_early_18; break;
		case 4: *value = self->m_revtime_19; break;
		case 5: *value = self->m_roomsize_20; break;
		case 6: *value = self->m_spread_25; break;
		case 7: *value = self->m_tail_22; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(8 * sizeof(ParamInfo));
	self->__commonstate.numparams = 8;
	// initialize parameter 0 ("m_bandwidth_23")
	pi = self->__commonstate.params + 0;
	pi->name = "bandwidth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_bandwidth_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_damping_24")
	pi = self->__commonstate.params + 1;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_dry_21")
	pi = self->__commonstate.params + 2;
	pi->name = "dry";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_dry_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_early_18")
	pi = self->__commonstate.params + 3;
	pi->name = "early";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_early_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_revtime_19")
	pi = self->__commonstate.params + 4;
	pi->name = "revtime";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_revtime_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 360;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_roomsize_20")
	pi = self->__commonstate.params + 5;
	pi->name = "roomsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_roomsize_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 300;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_spread_25")
	pi = self->__commonstate.params + 6;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_tail_22")
	pi = self->__commonstate.params + 7;
	pi->name = "tail";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tail_22;
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
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // gen_exported::
