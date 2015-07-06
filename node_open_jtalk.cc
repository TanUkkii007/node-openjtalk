#include <nan.h>
#include <node_buffer.h>
#include <sstream>
#include "HTS_engine.h"
#include "node_open_jtalk.h"

using namespace std;
using namespace v8;
using namespace node;



/*HTS_fwrite_little_endian*/
/* HTS_fwrite_little_endian: fwrite with byteswap */
inline void ensureLittleEndian(const void *buf, size_t size, size_t n)
{
#ifdef WORDS_BIGENDIAN
   HTS_byte_swap(buf, size, n * size);
#endif                          /* WORDS_BIGENDIAN */
}

RiffHeader::RiffHeader(HTS_Engine& engine)
{
    data_05_08 = HTS_GStreamSet_get_total_nsamples(&engine.gss) * sizeof(short) + 36;
    data_25_28 = engine.condition.sampling_frequency;
    data_29_32 = engine.condition.sampling_frequency * sizeof(short);
    data_41_44 = HTS_GStreamSet_get_total_nsamples(&engine.gss) * sizeof(short);

    ensureLittleEndian(data_01_04, sizeof(char), 4);
    ensureLittleEndian(&data_05_08, sizeof(int), 1);
    ensureLittleEndian(data_09_12, sizeof(char), 4);
    ensureLittleEndian(data_13_16, sizeof(char), 4);
    ensureLittleEndian(&data_17_20, sizeof(int), 1);
    ensureLittleEndian(&data_21_22, sizeof(short), 1);
    ensureLittleEndian(&data_23_24, sizeof(short), 1);
    ensureLittleEndian(&data_25_28, sizeof(int), 1);
    ensureLittleEndian(&data_29_32, sizeof(int), 1);
    ensureLittleEndian(&data_33_34, sizeof(short), 1);
    ensureLittleEndian(&data_35_36, sizeof(short), 1);
    ensureLittleEndian(data_37_40, sizeof(char), 4);
    ensureLittleEndian(&data_41_44, sizeof(int), 1);

}

RiffHeader HTSEngineClient::createHeader() {
    return RiffHeader(engine);
}

/* HTS_Engine_save_riff */
std::vector<short> HTSEngineClient::writeRiffToStream() {
    size_t i;
    double x;
    short temp;
    std::vector<short> buffer;
    /* write data */
    HTS_GStreamSet gss = engine.gss;
    for (i = 0; i < HTS_GStreamSet_get_total_nsamples(&gss); i++) {
        x = HTS_GStreamSet_get_speech(&gss, i);
        if (x > 32767.0)
            temp = 32767;
        else if (x < -32768.0)
            temp = -32768;
        else
            temp = (short) x;
        ensureLittleEndian(&temp, sizeof(short), 1);
        buffer.push_back(temp);
    }
    return buffer;
}

HTSEngineClient::HTSEngineClient(HTS_Engine& hts_engine): engine(hts_engine) {

}

void OpenJTalkOption::UpdateFromV8Object(v8::Local<v8::Object>& object) {
    Local<String> sampling_frequency_key = NanNew<String>("samplingFrequency");
    Local<String> fperiod_key = NanNew<String>("fPeriod");
    Local<String> audio_buff_size_key = NanNew<String>("audioBuffSize");
    Local<String> volume_key = NanNew<String>("volume");
    Local<String> msd_threshold_key = NanNew<String>("msdThreshold");
    Local<String> gv_weight_0_key = NanNew<String>("gvWeightForSpectrum");
    Local<String> gv_weight_1_key = NanNew<String>("gvWeightForLogF0");
    Local<String> alpha_key = NanNew<String>("alpha");
    Local<String> beta_key = NanNew<String>("beta");
    Local<String> speed_key = NanNew<String>("speed");
    Local<String> add_half_tone_key = NanNew<String>("addHalfTone");
    if (object->Has(sampling_frequency_key)) {
        sampling_frequency = object->Get(sampling_frequency_key).As<Number>()->Value();
    }
    if (object->Has(fperiod_key)) {
        fperiod = object->Get(fperiod_key).As<Number>()->Value();
    }
    if (object->Has(audio_buff_size_key)) {
        audio_buff_size = object->Get(audio_buff_size_key).As<Number>()->Value();
    }
    if (object->Has(volume_key)) {
        volume = object->Get(volume_key).As<Number>()->Value();
    }
    if (object->Has(msd_threshold_key)) {
        msd_threshold = object->Get(msd_threshold_key).As<Number>()->Value();
    }
    if (object->Has(gv_weight_0_key)) {
        gv_weight_0 = object->Get(gv_weight_0_key).As<Number>()->Value();
    }
    if (object->Has(gv_weight_1_key)) {
        gv_weight_0 = object->Get(gv_weight_1_key).As<Number>()->Value();
    }
    if (object->Has(alpha_key)) {
        alpha = object->Get(alpha_key).As<Number>()->Value();
    }
    if (object->Has(beta_key)) {
        beta = object->Get(beta_key).As<Number>()->Value();
    }
    if (object->Has(speed_key)) {
        speed = object->Get(speed_key).As<Number>()->Value();
    }
    if (object->Has(add_half_tone_key)) {
        add_half_tone = object->Get(add_half_tone_key).As<Number>()->Value();
    }
}


void OpenJTalkOption::ReflectToV8Object(v8::Local<v8::Object>& object) {
    object->Set(NanNew<String>("samplingFrequency"), NanNew<Uint32>(static_cast<int>(sampling_frequency)));
    object->Set(NanNew<String>("fPeriod"), NanNew<Uint32>(static_cast<int>(fperiod)));
    object->Set(NanNew<String>("alpha"), NanNew<Number>(alpha));
    object->Set(NanNew<String>("beta"), NanNew<Number>(beta));
    object->Set(NanNew<String>("speed"), NanNew<Number>(speed));
    object->Set(NanNew<String>("addHalfTone"), NanNew<Number>(add_half_tone));
    object->Set(NanNew<String>("msdThreshold"), NanNew<Number>(msd_threshold));
    object->Set(NanNew<String>("gvWeightForSpectrum"), NanNew<Number>(gv_weight_0));
    object->Set(NanNew<String>("gvWeightForLogF0"), NanNew<Number>(gv_weight_1));
    object->Set(NanNew<String>("volume"), NanNew<Number>(volume));
    object->Set(NanNew<String>("audioBuffSize"), NanNew<Uint32>(static_cast<int>(audio_buff_size)));
}

OpenJTalkWrapper::OpenJTalkWrapper() {
    Open_JTalk_initialize(&open_jtalk);
}

OpenJTalkWrapper::~OpenJTalkWrapper() {
    Open_JTalk_clear(&open_jtalk);
}

void OpenJTalkWrapper::Load(const std::string& dn_dict, const std::string& fn_voice) {
    Open_JTalk_load(&open_jtalk, dn_dict.c_str(), fn_voice.c_str());
}

RiffHeader OpenJTalkWrapper::Synthesis(std::vector<short>& vec, const char *txt) {
    int result = 0;
    char buff[MAXBUFLEN];
    RiffHeader header;
    HTSEngineClient htsEngineClient = HTSEngineClient(open_jtalk.engine);
    text2mecab(buff, txt);
    Mecab_analysis(&open_jtalk.mecab, buff);
    mecab2njd(&open_jtalk.njd, Mecab_get_feature(&open_jtalk.mecab),
              Mecab_get_size(&open_jtalk.mecab));
    njd_set_pronunciation(&open_jtalk.njd);
    njd_set_digit(&open_jtalk.njd);
    njd_set_accent_phrase(&open_jtalk.njd);
    njd_set_accent_type(&open_jtalk.njd);
    njd_set_unvoiced_vowel(&open_jtalk.njd);
    njd_set_long_vowel(&open_jtalk.njd);
    njd2jpcommon(&open_jtalk.jpcommon, &open_jtalk.njd);
    JPCommon_make_label(&open_jtalk.jpcommon);
    if (JPCommon_get_label_size(&open_jtalk.jpcommon) > 2) {
        if (HTS_Engine_synthesize_from_strings
            (&open_jtalk.engine, JPCommon_get_label_feature(&open_jtalk.jpcommon),
             JPCommon_get_label_size(&open_jtalk.jpcommon)) == TRUE)
            result = 1;
        vec = htsEngineClient.writeRiffToStream();
        header = htsEngineClient.createHeader();
        HTS_Engine_refresh(&open_jtalk.engine);
    }
    JPCommon_refresh(&open_jtalk.jpcommon);
    NJD_refresh(&open_jtalk.njd);
    Mecab_refresh(&open_jtalk.mecab);
    return header;
}

void OpenJTalkWrapper::Update(const OpenJTalkOption& option) {
    Open_JTalk_set_sampling_frequency(&open_jtalk, option.sampling_frequency);
    Open_JTalk_set_fperiod(&open_jtalk, option.fperiod);
    Open_JTalk_set_alpha(&open_jtalk, option.alpha);
    Open_JTalk_set_beta(&open_jtalk, option.beta);
    Open_JTalk_set_speed(&open_jtalk, option.speed);
    Open_JTalk_add_half_tone(&open_jtalk, option.add_half_tone);
    Open_JTalk_set_msd_threshold(&open_jtalk, 1, option.msd_threshold);
    Open_JTalk_set_gv_weight(&open_jtalk, 0, option.gv_weight_0);
    Open_JTalk_set_gv_weight(&open_jtalk, 1, option.gv_weight_1);
    Open_JTalk_set_volume(&open_jtalk, option.volume);
    Open_JTalk_set_audio_buff_size(&open_jtalk, option.audio_buff_size);
}

OpenJTalkOption OpenJTalkWrapper::GetOption() {
    OpenJTalkOption ojt_option(open_jtalk.engine);
    return ojt_option;
}


SynthesisWorkerDynamic::SynthesisWorkerDynamic(NanCallback* callback, OpenJTalkWrapper* open_jtalk, const std::string txt) : NanAsyncWorker(callback), open_jtalk(open_jtalk), text(txt) {
    
}

void SynthesisWorkerDynamic::Execute() {
    header = open_jtalk->Synthesis(data, text.c_str());
    if (data.size() == 0) {
        SetErrorMessage("Failed to synthesize voice.");
    }
}

void SynthesisWorkerDynamic::HandleOKCallback() {
    NanScope();
    std::stringstream stream;
    stream.write(reinterpret_cast<char*>(&header), sizeof(header));
    stream.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(short));
    Local<Object> jsbuffer = NanNewBufferHandle(stream.str().c_str(), sizeof(header) + data.size() * sizeof(short));
    Local<Value> argv[2] = {NanNull(), jsbuffer};
    callback->Call(2, argv);
    delete open_jtalk;
}

SynthesisWorker::SynthesisWorker(NanCallback* callback, const string txt, const string fn_voice_) : NanAsyncWorker(callback), text(txt), fn_voice(fn_voice_) {

}

void SynthesisWorker::Execute() {
    OpenJTalkWrapper open_jtalk;
    open_jtalk.Load(DN_DICT, fn_voice);
    header = open_jtalk.Synthesis(data, text.c_str());
    if (data.size() == 0) {
        SetErrorMessage("Failed to synthesize voice.");
    }
}

void SynthesisWorker::HandleOKCallback() {
    NanScope();
    std::stringstream stream;
    stream.write(reinterpret_cast<char*>(&header), sizeof(header));
    stream.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(short));
    Local<Object> jsbuffer = NanNewBufferHandle(stream.str().c_str(), sizeof(header) + data.size() * sizeof(short));
    Local<Value> argv[2] = {NanNull(), jsbuffer};
    callback->Call(2, argv);
}


NAN_METHOD(OpenJTalk::Synthesize) {
    NanScope();
    Local<String> buf = args[0].As<String>();
    OpenJTalk* obj = ObjectWrap::Unwrap<OpenJTalk>(args.Holder());
    if (args.Length() == 3) {
        Local<Function> optionHook = args[1].As<Function>();
        Local<Function> callback = args[2].As<Function>();
        Local<Object> arg = NanNew<Object>();
        OpenJTalkWrapper* open_jtalk = new OpenJTalkWrapper();
        open_jtalk->Load(DN_DICT, obj->fn_voice);
        OpenJTalkOption option = open_jtalk->GetOption();
        option.ReflectToV8Object(arg);
        Local<Value> argv[1] = {arg};
        Local<Value> new_option = NanMakeCallback(NanGetCurrentContext()->Global(), optionHook, 1, argv);
        if (new_option->IsObject()) {
            Local<Object> new_option_ = new_option.As<Object>();
            option.UpdateFromV8Object(new_option_);
            open_jtalk->Update(option);
        }
        NanCallback* nanCallback = new NanCallback(callback);
        SynthesisWorkerDynamic* worker = new SynthesisWorkerDynamic(nanCallback, open_jtalk, string(*String::Utf8Value(buf)));
        Local<v8::Object> _this = args.This();
        worker->SaveToPersistent("OpenJTalk", _this);
        NanAsyncQueueWorker(worker);
    } else if (args.Length() == 2) {
        Local<Function> callback = args[1].As<Function>();
        NanCallback* nanCallback = new NanCallback(callback);
        
        SynthesisWorker* worker = new SynthesisWorker(nanCallback, string(*String::Utf8Value(buf)), obj->fn_voice.c_str());
        Local<v8::Object> _this = args.This();
        worker->SaveToPersistent("OpenJTalk", _this);
        NanAsyncQueueWorker(worker);
    }

    NanReturnUndefined();
}

NAN_METHOD(OpenJTalk::SynthesizeSync) {
  NanScope();
  stringstream stream;
  vector<short> data;

  OpenJTalk* obj = ObjectWrap::Unwrap<OpenJTalk>(args.Holder());
  Local<String> buf = args[0].As<String>();

    OpenJTalkWrapper open_jtalk;
    open_jtalk.Load(DN_DICT, obj->fn_voice.c_str());
    if (!args[1].IsEmpty() && args[1]->IsFunction()) {
        Local<Function> callback = args[1].As<Function>();
        Local<Object> arg = NanNew<Object>();
        OpenJTalkOption option = open_jtalk.GetOption();
        option.ReflectToV8Object(arg);
        Local<Value> argv[1] = {arg};
        Local<Value> new_option = NanMakeCallback(NanGetCurrentContext()->Global(), callback, 1, argv);
        if (new_option->IsObject()) {
            Local<Object> new_option_ = new_option.As<Object>();
            option.UpdateFromV8Object(new_option_);
            open_jtalk.Update(option);
        }
    }
    RiffHeader header = open_jtalk.Synthesis(data, *String::Utf8Value(buf));
  stream.write(reinterpret_cast<char*>(&header), sizeof(header));
  stream.write(reinterpret_cast<char*>(data.data()), data.size() * sizeof(short));
  Local<Object> jsbuffer = NanNewBufferHandle(stream.str().c_str(), sizeof(header) + data.size() * sizeof(short));
  NanReturnValue(jsbuffer);
}


Persistent<FunctionTemplate> OpenJTalk::constructor;

OpenJTalk::OpenJTalk() {

}

OpenJTalk::~OpenJTalk() {
  
}

void OpenJTalk::Init(Handle<Object> exports) {
  NanScope();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("OpenJTalk"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "synthesize", OpenJTalk::Synthesize);
  NODE_SET_PROTOTYPE_METHOD(tpl, "synthesizeSync", OpenJTalk::SynthesizeSync);

  NanAssignPersistent(constructor, tpl);
  exports->Set(NanNew("OpenJTalk"), tpl->GetFunction());
}

NAN_METHOD(OpenJTalk::New) {
  NanScope();

  if (args.IsConstructCall()) {
    Local<Object> optionsObj = args[0]->ToObject();
    Local<String> fn_voice_key = NanNew<String>("voice");
    if (optionsObj.IsEmpty() || !optionsObj->Has(fn_voice_key)) {
      return NanThrowError("Please specify a voice to use.");
    }
    Local<String> fn_voice_ = optionsObj->Get(fn_voice_key)->ToString();

    // Invoked as constructor: `new OpenJTalk(...)`
    OpenJTalk* obj = new OpenJTalk();
    obj->fn_voice = *String::Utf8Value(fn_voice_);

    obj->Wrap(args.This());
    NanReturnValue(args.This());
  } else {
    // Invoked as plain function `OpenJTalk(...)`, turn into construct call.
    // const int argc = 1;
    // Local<Value> argv[argc] = { args[0] };
    // Local<FunctionTemplate> cons = NanNew<FunctionTemplate>(constructor);
    // NanReturnValue(cons->NewInstance(argc, argv));
    return NanThrowTypeError("Use the new operator to create new objects");
  }

}
