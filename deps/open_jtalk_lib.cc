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

#include "open_jtalk_lib.h"
#include <string.h>

//using namespace jtalk;

 void Open_JTalk_initialize(Open_JTalk * open_jtalk)
{
   Mecab_initialize(&open_jtalk->mecab);
   NJD_initialize(&open_jtalk->njd);
   JPCommon_initialize(&open_jtalk->jpcommon);
   HTS_Engine_initialize(&open_jtalk->engine);
}

 int Open_JTalk_load(Open_JTalk * open_jtalk, const char *dn_mecab, const char *fn_voice)
{
   if (Mecab_load(&open_jtalk->mecab, dn_mecab) != TRUE) {
      Open_JTalk_clear(open_jtalk);
      return 0;
   }
   if (HTS_Engine_load(&open_jtalk->engine, const_cast<char**>(&fn_voice), 1) != TRUE) {
      Open_JTalk_clear(open_jtalk);
      return 0;
   }
   if (strcmp(HTS_Engine_get_fullcontext_label_format(&open_jtalk->engine), "HTS_TTS_JPN") != 0) {
      Open_JTalk_clear(open_jtalk);
      return 0;
   }
   return 1;
}

void Open_JTalk_clear(Open_JTalk * open_jtalk)
{
   Mecab_clear(&open_jtalk->mecab);
   NJD_clear(&open_jtalk->njd);
   JPCommon_clear(&open_jtalk->jpcommon);
   HTS_Engine_clear(&open_jtalk->engine);
}

 void Open_JTalk_set_sampling_frequency(Open_JTalk * open_jtalk, size_t i)
{
   HTS_Engine_set_sampling_frequency(&open_jtalk->engine, i);
}

 void Open_JTalk_set_fperiod(Open_JTalk * open_jtalk, size_t i)
{
   HTS_Engine_set_fperiod(&open_jtalk->engine, i);
}

 void Open_JTalk_set_alpha(Open_JTalk * open_jtalk, double f)
{
   HTS_Engine_set_alpha(&open_jtalk->engine, f);
}

 void Open_JTalk_set_beta(Open_JTalk * open_jtalk, double f)
{
   HTS_Engine_set_beta(&open_jtalk->engine, f);
}

 void Open_JTalk_set_speed(Open_JTalk * open_jtalk, double f)
{
   HTS_Engine_set_speed(&open_jtalk->engine, f);
}

 void Open_JTalk_add_half_tone(Open_JTalk * open_jtalk, double f)
{
   HTS_Engine_add_half_tone(&open_jtalk->engine, f);
}

 void Open_JTalk_set_msd_threshold(Open_JTalk * open_jtalk, size_t i, double f)
{
   HTS_Engine_set_msd_threshold(&open_jtalk->engine, i, f);
}

 void Open_JTalk_set_gv_weight(Open_JTalk * open_jtalk, size_t i, double f)
{
   HTS_Engine_set_gv_weight(&open_jtalk->engine, i, f);
}

 void Open_JTalk_set_volume(Open_JTalk * open_jtalk, double f)
{
   HTS_Engine_set_volume(&open_jtalk->engine, f);
}

 void Open_JTalk_set_audio_buff_size(Open_JTalk * open_jtalk, size_t i)
{
   HTS_Engine_set_audio_buff_size(&open_jtalk->engine, i);
}

 int Open_JTalk_synthesis(Open_JTalk * open_jtalk, const char *txt, FILE * wavfp,
                                FILE * logfp)
{
   int result = 0;
   char buff[MAXBUFLEN];

   text2mecab(buff, txt);
   Mecab_analysis(&open_jtalk->mecab, buff);
   mecab2njd(&open_jtalk->njd, Mecab_get_feature(&open_jtalk->mecab),
             Mecab_get_size(&open_jtalk->mecab));
   njd_set_pronunciation(&open_jtalk->njd);
   njd_set_digit(&open_jtalk->njd);
   njd_set_accent_phrase(&open_jtalk->njd);
   njd_set_accent_type(&open_jtalk->njd);
   njd_set_unvoiced_vowel(&open_jtalk->njd);
   njd_set_long_vowel(&open_jtalk->njd);
   njd2jpcommon(&open_jtalk->jpcommon, &open_jtalk->njd);
   JPCommon_make_label(&open_jtalk->jpcommon);
   if (JPCommon_get_label_size(&open_jtalk->jpcommon) > 2) {
      if (HTS_Engine_synthesize_from_strings
          (&open_jtalk->engine, JPCommon_get_label_feature(&open_jtalk->jpcommon),
           JPCommon_get_label_size(&open_jtalk->jpcommon)) == TRUE)
         result = 1;
      if (wavfp != NULL)
         HTS_Engine_save_riff(&open_jtalk->engine, wavfp);
      if (logfp != NULL) {
         fprintf(logfp, "[Text analysis result]\n");
         NJD_fprint(&open_jtalk->njd, logfp);
         fprintf(logfp, "\n[Output label]\n");
         HTS_Engine_save_label(&open_jtalk->engine, logfp);
         fprintf(logfp, "\n");
         HTS_Engine_save_information(&open_jtalk->engine, logfp);
      }
      HTS_Engine_refresh(&open_jtalk->engine);
   }
   JPCommon_refresh(&open_jtalk->jpcommon);
   NJD_refresh(&open_jtalk->njd);
   Mecab_refresh(&open_jtalk->mecab);

   return result;
}
