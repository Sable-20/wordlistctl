project('wordlistctl', 'c')

cc = meson.get_compiler('c')
cc.has_header('uthash.h', required : true)

cjson = dependency('libcjson')
libcurl = dependency('libcurl')
libargtable3 = dependency('argtable3')
# uthash = dependency('uthash')

src = ['main.c', 'file.c', 'download.c']

executable('wordlistctl', src, dependencies : [cjson, libcurl, libargtable3])
