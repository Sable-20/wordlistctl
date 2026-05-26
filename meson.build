project('wordlistctl', 'c')

cc = meson.get_compiler('c')
cc.has_header('uthash.h', required : true)

cjson = dependency('libcjson')
libcurl = dependency('libcurl')
libncurses = dependency('ncurses')
libarchive = dependency('libarchive')

# uthash = dependency('uthash')

src = ['main.c', 'file.c', 'download.c', 'tui.c', 'decompress.c']

executable('wordlistctl', 
            src, 
            dependencies : [
                cjson, 
                libcurl, 
                libncurses,
                libarchive,
            ], 
            link_args : [ 
                '-lform',
                '-pthread'
            ]
        )
