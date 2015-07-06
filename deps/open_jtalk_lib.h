/* ----------------------------------------------------------------- */
/*           The Japanese TTS System "Open JTalk"                    */
/*           developed by HTS Working Group                          */
/*           http://open-jtalk.sourceforge.net/                      */
/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2008-2014  Nagoya Institute of Technology          */
/*                           Department of Computer Science          */
/*                                                                   */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/* - Redistributions of source code must retain the above copyright  */
/*   notice, this list of conditions and the following disclaimer.   */
/* - Redistributions in binary form must reproduce the above         */
/*   copyright notice, this list of conditions and the following     */
/*   disclaimer in the documentation and/or other materials provided */
/*   with the distribution.                                          */
/* - Neither the name of the HTS working group nor the names of its  */
/*   contributors may be used to endorse or promote products derived */
/*   from this software without specific prior written permission.   */
/*                                                                   */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND            */
/* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,       */
/* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF          */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS */
/* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY    */
/* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           */
/* POSSIBILITY OF SUCH DAMAGE.                                       */
/* ----------------------------------------------------------------- */

#ifndef OPEN_JTALK_LIB
#define OPEN_JTALK_LIB


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <math.h>

/* Main headers */
#include "mecab.h"
#include "njd.h"
#include "jpcommon.h"
#include "HTS_engine.h"

/* Sub headers */
#include "text2mecab.h"
#include "mecab2njd.h"
#include "njd_set_pronunciation.h"
#include "njd_set_digit.h"
#include "njd_set_accent_phrase.h"
#include "njd_set_accent_type.h"
#include "njd_set_unvoiced_vowel.h"
#include "njd_set_long_vowel.h"
#include "njd2jpcommon.h"

//namespace jtalk {

#define MAXBUFLEN 1024

typedef struct _Open_JTalk {
   Mecab mecab;
   NJD njd;
   JPCommon jpcommon;
   HTS_Engine engine;
} Open_JTalk;

 void Open_JTalk_initialize(Open_JTalk * open_jtalk);

 void Open_JTalk_clear(Open_JTalk * open_jtalk);

 int Open_JTalk_load(Open_JTalk * open_jtalk, const char* dn_mecab, const char *fn_voice);

 void Open_JTalk_set_sampling_frequency(Open_JTalk * open_jtalk, size_t i);

 void Open_JTalk_set_fperiod(Open_JTalk * open_jtalk, size_t i);

 void Open_JTalk_set_alpha(Open_JTalk * open_jtalk, double f);

 void Open_JTalk_set_beta(Open_JTalk * open_jtalk, double f);

 void Open_JTalk_set_speed(Open_JTalk * open_jtalk, double f);

 void Open_JTalk_add_half_tone(Open_JTalk * open_jtalk, double f);

 void Open_JTalk_set_msd_threshold(Open_JTalk * open_jtalk, size_t i, double f);

 void Open_JTalk_set_gv_weight(Open_JTalk * open_jtalk, size_t i, double f);

 void Open_JTalk_set_volume(Open_JTalk * open_jtalk, double f);

 void Open_JTalk_set_audio_buff_size(Open_JTalk * open_jtalk, size_t i);

 int Open_JTalk_synthesis(Open_JTalk * open_jtalk, const char *txt, FILE * wavfp,
                                FILE * logfp);

//OPEN_JTALK_LIB_END;
//}
#endif                          /* !OPEN_JTALK_LIB */
