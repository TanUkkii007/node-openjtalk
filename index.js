var binary = require('node-pre-gyp');
var path = require('path');
var binding_path = binary.find(path.resolve(path.join(__dirname,'./package.json')));
var binding = require(binding_path);

module.exports = binding;

module.exports.OpenJTalk.voices = {
  m001: __dirname + '/voice/hts_voice_nitech_jp_atr503_m001-1.05 2/nitech_jp_atr503_m001.htsvoice',
  mei_angry: __dirname + '/voice/mei/mei_angry.htsvoice',
  mei_bashful: __dirname + '/voice/mei/mei_bashful.htsvoice',
  mei_happy: __dirname + '/voice/mei/mei_happy.htsvoice',
  mei_normal: __dirname + '/voice/mei/mei_normal.htsvoice',
  mei_sad  : __dirname + '/voice/mei/mei_sad.htsvoice',
};
