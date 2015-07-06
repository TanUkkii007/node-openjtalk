# node-openjtalk
[OpenJTalk](http://open-jtalk.sourceforge.net/), Japanese text-to-speech engine binding for NodeJS.

## Requirements

+ [libiconv](http://www.gnu.org/software/libiconv/)

MacOSX users do not need to install libiconv because OSX already includes it.

## Usage
```js
var fs = require('fs');
var Speaker = require('speaker');
var OpenJTalk = require('node-openjtalk').OpenJTalk;

//pre-included HTS voice file
var fn_voice = OpenJTalk.voices.mei_normal;
// instantiate OpenJTalk with an HTS voice
var open_jtalk = new OpenJTalk({voice: fn_voice});

// synthesize a voice buffer from a text
open_jtalk.synthesize("すもももももももものうち", function(error, buffer) {
  if (!error) {
    // save as sound file
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

## Supported platforms
node-openjtalk currently supports following platforms.
+ MacOSX/x64
+ linux/ia32
+ linux/x64
