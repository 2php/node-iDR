{
  "targets": [
    {
      "target_name": "RoutonRead",
      "sources": [ "src/RoutonRead.cc", "src/RoutonRead.cc" ],
      "include_dirs": [
      'tmp/sdtapi/include',
	  'src'
      ],
      'link_settings': {
        'libraries': [
          '-lSdtapi'
        ],
        'library_dirs': [
          'tmp/sdtapi/lib'
        ]
      },
	  "msbuild_settings": {
			"Link": {
				"ImageHasSafeExceptionHandlers": "false"
			}
		}
    }
  ]
}
