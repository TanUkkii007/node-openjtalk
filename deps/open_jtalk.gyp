{
  "variables": {
      "PACKAGE": "open_jtalk",
      "VERSION": "1.08",
      "open_jtalk_dir":"open_jtalk-1.08",
      "DIC_VERSION": "102",
      "CHARSET": "CHARSET_UTF_8",
      "MECAB_CHARSET": "utf-8",
      "MECAB_USE_UTF8_ONLY": "MECAB_USE_UTF8_ONLY",
      "MECAB_DEFAULT_RC": "dummy",
  },
  "target_defaults": {
    "conditions": [
      ['OS!="win"', {
        "defines": [
          "PIC",
          "HAVE_CONFIG_H",
        ],
      }]
    ],
  },
  "targets": [
    {
      "target_name": "mecab",
      "product_name": "libmecab",
      "sources": [
        "<(open_jtalk_dir)/mecab/src/char_property.cpp",
        "<(open_jtalk_dir)/mecab/src/connector.cpp",
        "<(open_jtalk_dir)/mecab/src/context_id.cpp",
        "<(open_jtalk_dir)/mecab/src/dictionary.cpp",
        "<(open_jtalk_dir)/mecab/src/dictionary_compiler.cpp",
        "<(open_jtalk_dir)/mecab/src/dictionary_generator.cpp",
        "<(open_jtalk_dir)/mecab/src/dictionary_rewriter.cpp",
        "<(open_jtalk_dir)/mecab/src/eval.cpp",
        "<(open_jtalk_dir)/mecab/src/feature_index.cpp",
        "<(open_jtalk_dir)/mecab/src/iconv_utils.cpp",
        "<(open_jtalk_dir)/mecab/src/lbfgs.cpp",
        "<(open_jtalk_dir)/mecab/src/learner.cpp",
        "<(open_jtalk_dir)/mecab/src/learner_tagger.cpp",
        "<(open_jtalk_dir)/mecab/src/libmecab.cpp",
        "<(open_jtalk_dir)/mecab/src/mecab.cpp",
        "<(open_jtalk_dir)/mecab/src/string_buffer.cpp",
        "<(open_jtalk_dir)/mecab/src/utils.cpp",
        "<(open_jtalk_dir)/mecab/src/eval.cpp",
        "<(open_jtalk_dir)/mecab/src/learner.cpp",
        "<(open_jtalk_dir)/mecab/src/nbest_generator.cpp",
        "<(open_jtalk_dir)/mecab/src/tagger.cpp",
        "<(open_jtalk_dir)/mecab/src/viterbi.cpp",
        "<(open_jtalk_dir)/mecab/src/param.cpp",
        "<(open_jtalk_dir)/mecab/src/tokenizer.cpp",
        "<(open_jtalk_dir)/mecab/src/writer.cpp",
      ],
      "type": "static_library",
      "include_dirs": [
        "<(module_root_dir)/deps/config/open_jtalk/mecab/<(OS)/<(target_arch)",
        "<(open_jtalk_dir)/mecab/src",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/mecab/src",
        ]
      },
      "defines": [
        "DIC_VERSION=<(DIC_VERSION)",
        "<(MECAB_USE_UTF8_ONLY)",
        "MECAB_DEFAULT_RC=<(MECAB_DEFAULT_RC)",
      ],
      "conditions": [
        ['OS=="win"', {
          "defines": [
            "PACKAGE=\"<(PACKAGE)\"",
            "VERSION=\"(VERSION)\"",
          ],
        }],
      ],
      "link_settings": {
        "libraries": [ "-liconv" ],
        "conditions": [
          ['OS=="mac"', {
          'xcode_settings': {
            'OTHER_LDFLAGS': [
              "-liconv",
            ],
          }
          }],
        ]
      },
    },
    {
      "target_name": "mecab-dict-index",
      "product_name": "mecab-dict-index",
      "sources": [
        "<(open_jtalk_dir)/mecab/src/mecab-dict-index.cpp",
      ],
      "type": "executable",
      "defines": [
        "DIC_VERSION=<(DIC_VERSION)",
        "<(MECAB_USE_UTF8_ONLY)",
        "MECAB_DEFAULT_RC=<(MECAB_DEFAULT_RC)",
      ],
      "dependencies": [
        "mecab",
      ],
    },
    {
      "target_name": "mecab-naist-jdic",
      "type": "none",
      "actions": [
        {
          "action_name": "compile_dictionary",
          "inputs": [
            "<(open_jtalk_dir)/mecab-naist-jdic/naist-jdic.csv",
            "<(open_jtalk_dir)/mecab-naist-jdic/matrix.def",
            "<(open_jtalk_dir)/mecab-naist-jdic/left-id.def",
            "<(open_jtalk_dir)/mecab-naist-jdic/rewrite.def",
            "<(open_jtalk_dir)/mecab-naist-jdic/pos-id.def",
            "<(open_jtalk_dir)/mecab-naist-jdic/right-id.def",
            "<(open_jtalk_dir)/mecab-naist-jdic/char.def",
            "<(open_jtalk_dir)/mecab-naist-jdic/unk.def",
            "<(open_jtalk_dir)/mecab-naist-jdic/feature.def",
          ],
          "outputs": [
            "<(open_jtalk_dir)/mecab-naist-jdic/char.bin",
            "<(open_jtalk_dir)/mecab-naist-jdic/matrix.bin",
            "<(open_jtalk_dir)/mecab-naist-jdic/sys.dic",
            "<(open_jtalk_dir)/mecab-naist-jdic/unk.dic",
          ],
          "action": ["<(PRODUCT_DIR)/mecab-dict-index", "-d", "<(open_jtalk_dir)/mecab-naist-jdic", "-o", "<(PRODUCT_DIR)", "-f", "EUC-JP", "-t", "<(MECAB_CHARSET)"]
        }
      ],
      "dependencies": [
        "mecab-dict-index",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/mecab-naist-jdic",
        ],
      },
    },
    {
      "target_name": "text2mecab",
      "product_name": "libtext2mecab",
      "sources": [
        "<(open_jtalk_dir)/text2mecab/text2mecab.c",
      ],
      "type": "static_library",
      "include_dirs": [
        "<(open_jtalk_dir)/text2mecab",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/text2mecab",
        ]
      },
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "njd",
      "product_name": "libnjd",
      "sources": [
        "<(open_jtalk_dir)/njd/njd.c",
        "<(open_jtalk_dir)/njd/njd_node.c",
      ],
      "type": "static_library",
      "include_dirs": [
        "<(open_jtalk_dir)/njd",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/njd",
        ]
      },
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "njd_set_pronunciation",
      "product_name": "libnjd_set_pronunciation",
      "sources": [
        "<(open_jtalk_dir)/njd_set_pronunciation/njd_set_pronunciation.c",
      ],
      "type": "static_library",
      "dependencies": [
        "njd",
      ],
      "include_dirs": [
        "<(open_jtalk_dir)/njd_set_pronunciation",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/njd_set_pronunciation",
        ]
      },
      "export_dependent_settings": [
        "njd",
      ],
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "mecab2njd",
      "product_name": "libmecab2njd",
      "sources": [
        "<(open_jtalk_dir)/mecab2njd/mecab2njd.c",
      ],
      "type": "static_library",
      "dependencies": [
        "njd",
      ],
      "include_dirs": [
        "<(open_jtalk_dir)/mecab2njd",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/mecab2njd",
        ]
      },
      "export_dependent_settings": [
        "njd",
      ],
    },
    {
      "target_name": "njd_set_digit",
      "product_name": "libnjd_set_digit",
      "sources": [
        "<(open_jtalk_dir)/njd_set_digit/njd_set_digit.c",
      ],
      "type": "static_library",
      "dependencies": [
        "njd",
      ],
      "include_dirs": [
        "<(open_jtalk_dir)/njd_set_digit",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/njd_set_digit",
        ]
      },
      "export_dependent_settings": [
        "njd",
      ],
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "njd_set_accent_phrase",
      "product_name": "libnjd_set_accent_phrase",
      "sources": [
        "<(open_jtalk_dir)/njd_set_accent_phrase/njd_set_accent_phrase.c",
      ],
      "type": "static_library",
      "dependencies": [
        "njd",
      ],
      "include_dirs": [
        "<(open_jtalk_dir)/njd_set_accent_phrase",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/njd_set_accent_phrase",
        ]
      },
      "export_dependent_settings": [
        "njd",
      ],
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "njd_set_accent_type",
      "product_name": "libnjd_set_accent_type",
      "sources": [
        "<(open_jtalk_dir)/njd_set_accent_type/njd_set_accent_type.c",
      ],
      "type": "static_library",
      "dependencies": [
        "njd",
      ],
      "include_dirs": [
        "<(open_jtalk_dir)/njd_set_accent_type",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/njd_set_accent_type",
        ]
      },
      "export_dependent_settings": [
        "njd",
      ],
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "njd_set_unvoiced_vowel",
      "product_name": "libnjd_set_unvoiced_vowel",
      "sources": [
        "<(open_jtalk_dir)/njd_set_unvoiced_vowel/njd_set_unvoiced_vowel.c",
      ],
      "type": "static_library",
      "dependencies": [
        "njd",
      ],
      "include_dirs": [
        "<(open_jtalk_dir)/njd_set_unvoiced_vowel",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/njd_set_unvoiced_vowel",
        ]
      },
      "export_dependent_settings": [
        "njd",
      ],
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "njd_set_long_vowel",
      "product_name": "libnjd_set_long_vowel",
      "sources": [
        "<(open_jtalk_dir)/njd_set_long_vowel/njd_set_long_vowel.c",
      ],
      "type": "static_library",
      "dependencies": [
        "njd",
      ],
      "include_dirs": [
        "<(open_jtalk_dir)/njd_set_long_vowel",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/njd_set_long_vowel",
        ]
      },
      "export_dependent_settings": [
        "njd",
      ],
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "jpcommon",
      "product_name": "libjpcommon",
      "sources": [
        "<(open_jtalk_dir)/jpcommon/jpcommon.c",
        "<(open_jtalk_dir)/jpcommon/jpcommon_label.c",
        "<(open_jtalk_dir)/jpcommon/jpcommon_node.c",
      ],
      "type": "static_library",
      "include_dirs": [
        "<(open_jtalk_dir)/jpcommon",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/jpcommon",
        ]
      },
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "njd2jpcommon",
      "product_name": "libnjd2jpcommon",
      "sources": [
        "<(open_jtalk_dir)/njd2jpcommon/njd2jpcommon.c",
      ],
      "type": "static_library",
      "dependencies": [
        "njd",
        "jpcommon",
      ],
      "include_dirs": [
        "<(open_jtalk_dir)/njd2jpcommon",
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "<(open_jtalk_dir)/njd2jpcommon",
        ]
      },
      "export_dependent_settings": [
        "njd",
        "jpcommon",
      ],
      "defines": [
        "<(CHARSET)",
      ],
    },
    {
      "target_name": "open_jtalk_lib",
      "product_name": "open_jtalk_lib",
      "sources": [
        "open_jtalk_lib.cc",
      ],
      "type": "static_library",
      "dependencies": [
        "mecab",
        "text2mecab",
        "njd",
        "njd_set_pronunciation",
        "mecab2njd",
        "njd_set_digit",
        "njd_set_accent_phrase",
        "njd_set_accent_type",
        "njd_set_unvoiced_vowel",
        "njd_set_long_vowel",
        "jpcommon",
        "njd2jpcommon",
        "mecab-naist-jdic",
        "hts_engine_api.gyp:hts_engine_api"
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          ".",
        ],
      },
      "export_dependent_settings": [
        "mecab",
        "text2mecab",
        "njd",
        "njd_set_pronunciation",
        "mecab2njd",
        "njd_set_digit",
        "njd_set_accent_phrase",
        "njd_set_accent_type",
        "njd_set_unvoiced_vowel",
        "njd_set_long_vowel",
        "jpcommon",
        "njd2jpcommon",
        "mecab-naist-jdic",
        "hts_engine_api.gyp:hts_engine_api"
      ]
    },
  ]
}
