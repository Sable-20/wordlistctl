#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include <cjson/cJSON.h>
#include <uthash.h>

typedef struct wordlist
{
    char name[256];

    char url[1024];
    char size[64];
    char group[64];

    UT_hash_handle hh;
} wordlist_t;

char *read_file(const char *path);

wordlist_t *load_repo(const char *path);

wordlist_t *find_by_name(wordlist_t *table,
                         const char *name);

void find_by_group(wordlist_t *table,
                   const char *group);

void free_table(wordlist_t *table);

#endif // FILE_H_