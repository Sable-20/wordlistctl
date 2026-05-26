#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include <cjson/cJSON.h>
#include <uthash.h>

/**
 * Structure representing a wordlist entry
 * 
 * This structure holds the name, URL, size, and group of a wordlist entry. It is used to store and manage the wordlist entries loaded from the repository JSON file. The `UT_hash_handle` is included to allow this structure to be used with the `uthash` library for efficient hash table management.
 */
typedef struct wordlist
{
    char name[256]; /**< Name of the wordlist entry */

    char url[1024]; /**< URL of the file to download */
    char size[64]; /**< Size of the file */
    char group[64]; /**< Group to which the wordlist entry belongs */

    UT_hash_handle hh; /**< Hash handle for uthash */
} wordlist_t;

char *read_file(const char *path);

wordlist_t *load_repo(const char *path);

wordlist_t *find_by_name(wordlist_t *table,
                         const char *name);

void find_by_group(wordlist_t *table,
                   const char *group);

void free_table(wordlist_t *table);

#endif // FILE_H_