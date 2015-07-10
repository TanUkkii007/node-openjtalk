{
  "variables": {
    "DN_DICT": "<!(node -e \"process.stdout.write(process.cwd() + '/build/Release')\")"
  },
  "targets": [
    {
      "target_name": "<(module_name)",
      "sources": [ "addon.cc", "<(module_name).cc"],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
      ],
      "dependencies": [
        "deps/open_jtalk.gyp:open_jtalk_lib"
      ],
      'cflags':[

      ],
      "defines": [
        "DN_DICT=\"<(DN_DICT)\""
      ],
      "conditions": [
        ['OS=="mac"', {
         'cflags':[
           "-stdlib=stdlibc++",
         ],
        'xcode_settings': {
          'OTHER_CFLAGS': [
            "-stdlib=libstdc++",
          ],
          "CLANG_CXX_LIBRARY": "libstdc++",
          "GCC_ENABLE_CPP_RTTI": "YES",
          "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        }
        }],
      ]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)/"
        }
      ]
    },
  ]
}
