project('wordlistctl', 'c')

cc = meson.get_compiler('c')
cc.has_header('uthash.h', required : true)

cjson = dependency('libcjson')
libcurl = dependency('libcurl')
libargtable3 = dependency('argtable3')
libncurses = dependency('ncurses')
# uthash = dependency('uthash')

src = ['main.c', 'file.c', 'download.c', 'tui.c']

executable('wordlistctl', 
            src, 
            dependencies : [
                cjson, 
                libcurl, 
                libncurses,
                libargtable3
            ], 
            link_args : [ 
                '-lform'
            ]
        )
