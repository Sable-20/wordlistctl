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

/**
 * Reads the contents of a file into a dynamically allocated string. The caller is responsible for freeing the returned string after use.
 * 
 * @param path The path to the file to be read
 * @return A pointer to a dynamically allocated string containing the contents of the file, or NULL
 */
char *read_file(const char *path);

/**
 * Loads the repository JSON file and parses it into a hash table of wordlist entries. Each entry in the JSON file is expected to have a name, URL, size, and group. The function returns a pointer to the hash table containing the loaded wordlist entries, or NULL if there was an error loading or parsing the file.
 * 
 * @param path The path to the repository JSON file
 * @return A pointer to a hash table of wordlist entries, or NULL on failure
 */
wordlist_t *load_repo(const char *path);

/**
 * Finds a wordlist entry in the hash table by its name. The function returns a pointer to the wordlist entry if found, or NULL if no entry with the specified name exists in the table.
 * 
 * @param table The hash table of wordlist entries to search
 * @param name The name of the wordlist entry to find
 * @return A pointer to the wordlist entry if found, or NULL if not found
 */
wordlist_t *find_by_name(wordlist_t *table,
                         const char *name);

/**
 * Finds and prints all wordlist entries in the hash table that belong to the specified group. The function iterates through the hash table and prints the details of each entry that matches the specified group. If no entries are found for the group, a message indicating that the group was not found is printed.
 * 
 * @param table The hash table of wordlist entries to search
 * @param group The group name to filter the wordlist entries by
 */
void find_by_group(wordlist_t *table,
                   const char *group);

/** 
 * Frees the memory allocated for the hash table of wordlist entries. This function iterates through the
 * hash table and frees the memory allocated for each entry.
 * 
 * @param table The hash table of wordlist entries to free
 */
void free_table(wordlist_t *table);

#endif // FILE_H_