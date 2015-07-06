{
  "variables": {
    "hts_engine_dir":"hts_engine_API-1.09",
  },
  "targets": [
    {
      "target_name": "hts_engine_api",
      "product_name": "hts_engine_api",
      "sources": [
        "<(hts_engine_dir)/bin/hts_engine.c",
        "<(hts_engine_dir)/lib/HTS_audio.c",
        "<(hts_engine_dir)/lib/HTS_engine.c",
        "<(hts_engine_dir)/lib/HTS_gstream.c",
        "<(hts_engine_dir)/lib/HTS_label.c",
        "<(hts_engine_dir)/lib/HTS_misc.c",
        "<(hts_engine_dir)/lib/HTS_model.c",
        "<(hts_engine_dir)/lib/HTS_pstream.c",
        "<(hts_engine_dir)/lib/HTS_sstream.c",
        "<(hts_engine_dir)/lib/HTS_vocoder.c",
      ],
      "type": "static_library",
      "include_dirs": [
        "<(hts_engine_dir)/include",
        "<(hts_engine_dir)/lib",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(hts_engine_dir)/include",
          "<(hts_engine_dir)/lib",
        ],
      },
    }
  ]
}
