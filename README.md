# node-openjtalk
[OpenJTalk](http://open-jtalk.sourceforge.net/), Japanese text-to-speech engine binding for NodeJS.

## Requirements

+ NodeJS 0.12 (caution: NodeJS >= 4.0 is not supported)
+ [libiconv](http://www.gnu.org/software/libiconv/)

MacOSX users do not need to install libiconv because OSX already includes it.

## Installation

```sh
$ npm install node-openjtalk
```

## Usage
```js
var fs = require('fs');
var Speaker = require('speaker');
var OpenJTalk = require('node-openjtalk').OpenJTalk;

// pre-included HTS voice file
var fn_voice = OpenJTalk.voices.mei_normal;
// instantiate OpenJTalk with an HTS voice
var open_jtalk = new OpenJTalk({voice: fn_voice});

// synthesize a voice buffer from a text
open_jtalk.synthesize("すもももももももものうち", function(error, buffer) {
  if (!error) {
    // save as audio file
    var fd = fs.openSync(__dirname + '/test.wav', 'w');
    fs.write(fd, buffer, 0, buffer.length, null, function(err, written, buffer) {
      fs.closeSync(fd);
    });
  }
});

// synthesize a voice synchronously
var buffer = open_jtalk.synthesizeSync("すもももももももものうち");

// flush to node-speaker
var speaker = new Speaker({
  channels: 1,
  bitDepth: 16,
  sampleRate: 48000
});
speaker.end(buffer);

```

## API

### new OpenJTalk(option)
Instantiates OpenJTalk object.

You must specify HTS voice file path with an option argument.
```js
var OpenJTalk = require('node-openjtalk').OpenJTalk;
var open_jtalk = new OpenJTalk({voice: "/path/to/HTS voice file"});
```

You can use pre-included voice files.

```js
var OpenJTalk = require('node-openjtalk').OpenJTalk;
var open_jtalk = new OpenJTalk({voice: OpenJTalk.voices.m001});
```

The pre-included voice files are:
+ m001
+ mei_angry
+ mei_bashful
+ mei_happy
+ mei_normal
+ mei_sad

### OpenJTalk#synthesize(text, [optionHook], callback)
Synthesizes voice audio asynchronously from a text. The callback takes two arguments, error and buffer object.

```js
open_jtalk.synthesize("音声合成するテキスト", function(error, buffer) {
  if (!error) {
    // do something with buffer
  }
});
```
The "optionHook" function lets you modify synthesis parameters. For example, following code makes speech speed double.

```js
open_jtalk.synthesize(text, function(option) {
  return {
    speed: option.speed * 2
  };
}, function(error, buffer) {

});
```

The available parameters are:
+ samplingFrequency
+ fPeriod
+ alpha
+ beta
+ speed
+ addHalfTone
+ msdThreshold
+ gvWeightForSpectrum
+ gvWeightForLogF0
+ volume
+ audioBuffSize

### OpenJTalk#synthesizeSync(text, [optionHook])

Synthesizes voice audio synchronously from a text. This function returns buffer object.

## Supported platforms
node-openjtalk currently supports following platforms.
+ MacOSX/x64
+ linux/ia32
+ linux/x64

## License
node-openjtalk is licensed under the MIT license. See [LICENSE](https://github.com/TanUkkii007/node-openjtalk/blob/master/LICENSE) for more details.

node-openjtalk builds on [OpenJTalk](http://open-jtalk.sourceforge.net/) and [hts_engine API](http://hts-engine.sourceforge.net/), and is shiped with HTS Voice ["NIT ATR503 M001"](http://open-jtalk.sourceforge.net/) and ["Mei"](http://www.mmdagent.jp/). Thanks for their works.

Both OpenJTalk and hts_engine API are issued under the Modified BSD license.

HTS Voice "NIT ATR503 M001" and "Mei" are both issued under the Creative Commons Attribution 3.0 license.
