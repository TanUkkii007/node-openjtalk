#include <nan.h>
#include "node_open_jtalk.h"

using namespace v8;

void Init(Handle<Object> exports) {
  OpenJTalk::Init(exports);
}

NODE_MODULE(node_open_jtalk, Init);
