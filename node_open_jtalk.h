#ifndef NODE_OPEN_JTALK_H
#define NODE_OPEN_JTALK_H

#include <nan.h>

#ifdef __cplusplus
#define OPEN_JTALK_CC_START extern "C" {
#define OPEN_JTALK_CC_END   }
#else
#define OPEN_JTALK_CC_START
#define OPEN_JTALK_CC_END
#endif

#include <sstream>
#include <vector>
#include "open_jtalk_lib.h"
#include "HTS_hidden.h"

#define DN_DICT "./build/Release"

inline static void ensureLittleEndian(const void *buf, size_t size, size_t n);

struct RiffHeader
{
    RiffHeader() {

    };

    RiffHeader(HTS_Engine& engine);

    char data_01_04[4] = { 'R', 'I', 'F', 'F' };
    int data_05_08;
    char data_09_12[4] = { 'W', 'A', 'V', 'E' };
    char data_13_16[4] = { 'f', 'm', 't', ' ' };
    int data_17_20 = 16;
    short data_21_22 = 1;        /* PCM */
    short data_23_24 = 1;        /* monoral */
    int data_25_28;
    int data_29_32;
    short data_33_34 = sizeof(short);
    short data_35_36 = (short) (sizeof(short) * 8);
    char data_37_40[4] = { 'd', 'a', 't', 'a' };
    int data_41_44;

};

class HTSEngineClient {
public:
  HTSEngineClient(HTS_Engine& engine);
  std::vector<short> writeRiffToStream();
  RiffHeader createHeader();
private:
  HTS_Engine& engine;
};


struct OpenJTalkOption {
    size_t sampling_frequency = 0;
    size_t fperiod = 0;
    double alpha = 0.0;
    double beta = 0.0;
    double speed = 1.0;
    double add_half_tone = 0.0;
    double msd_threshold = 0.0;
    double gv_weight_0 = 0.0;
    double gv_weight_1 = 0.0;
    double volume = 1.0;
    size_t audio_buff_size = 0;
    explicit OpenJTalkOption() {};
    explicit OpenJTalkOption(HTS_Engine& engine) {
        sampling_frequency = HTS_Engine_get_sampling_frequency(&engine);
        fperiod = HTS_Engine_get_fperiod(&engine);
        audio_buff_size = HTS_Engine_get_audio_buff_size(&engine);
        volume = HTS_Engine_get_volume(&engine);
        msd_threshold = HTS_Engine_get_msd_threshold(&engine, 0);
        gv_weight_0 = HTS_Engine_get_gv_weight(&engine, 0);
        gv_weight_1 = HTS_Engine_get_gv_weight(&engine, 1);
        alpha = HTS_Engine_get_alpha(&engine);
        beta = HTS_Engine_get_beta(&engine);
        speed = engine.condition.speed;
        add_half_tone = engine.condition.additional_half_tone;
    }
    void ReflectToV8Object(v8::Local<v8::Object>& object);
    void UpdateFromV8Object(v8::Local<v8::Object>& object);
};

class OpenJTalkWrapper {
public:
    explicit OpenJTalkWrapper();
    ~OpenJTalkWrapper();
    void Load(const std::string& dn_dict, const std::string& fn_voice);
    RiffHeader Synthesis(std::vector<short>& vec, const char *txt);
    void Update(const OpenJTalkOption& option);
    OpenJTalkOption GetOption();
private:
    Open_JTalk open_jtalk;
};


class SynthesisWorkerDynamic : public NanAsyncWorker {
public:
    SynthesisWorkerDynamic(NanCallback* callback, OpenJTalkWrapper* open_jtalk, const std::string txt);
    void Execute();
    void HandleOKCallback();
private:
    OpenJTalkWrapper* open_jtalk;
    const std::string text;
    RiffHeader header;
    std::vector<short> data;
};

class SynthesisWorker : public NanAsyncWorker {
public:
    SynthesisWorker(NanCallback* callback, const std::string txt, const std::string fn_voice_);
    void Execute();
    void HandleOKCallback();
private:
    const std::string text;
    std::string fn_voice;
    RiffHeader header;
    std::vector<short> data;
};

class OpenJTalk : public node::ObjectWrap {
public:
  static void Init(v8::Handle<v8::Object> exports);
  static NAN_METHOD(New);
  static NAN_METHOD(Synthesize);
  static NAN_METHOD(SynthesizeSync);

private:
  explicit OpenJTalk();
  ~OpenJTalk();
  static v8::Persistent<v8::FunctionTemplate> constructor;
  std::string fn_voice;
};

#endif
