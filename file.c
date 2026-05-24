#include "file.h"

char *read_file(const char *path) {
    FILE *fp = fopen(path, "rb");

    if (!fp) {
        perror("fopen");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    rewind(fp);

    char *buf = malloc(len + 1);

    if (!buf) {
        fclose(fp);
        return NULL;
    }

    fread(buf, 1, len, fp);
    buf[len] = '\0';

    fclose(fp);

    return buf;
}

wordlist_t *load_repo(const char *path) {
    char *json_data = read_file(path);

    if (!json_data)
        return NULL;

    cJSON *root = cJSON_Parse(json_data);

    if (!root) {
        fprintf(stderr, "json parse error\n");
        free(json_data);
        return NULL;
    }

    wordlist_t *table = NULL;

    cJSON *item = NULL;

    cJSON_ArrayForEach(item, root) {

        const char *name = item->string;

        cJSON *url =
            cJSON_GetObjectItem(item, "url");

        cJSON *size =
            cJSON_GetObjectItem(item, "size");

        cJSON *group =
            cJSON_GetObjectItem(item, "group");

        if (!cJSON_IsString(url) ||
            !cJSON_IsString(size) ||
            !cJSON_IsString(group)) {
            continue;
        }

        wordlist_t *wl =
            calloc(1, sizeof(*wl));

        snprintf(wl->name,
                 sizeof(wl->name),
                 "%s",
                 name);

        snprintf(wl->url,
                 sizeof(wl->url),
                 "%s",
                 url->valuestring);

        snprintf(wl->size,
                 sizeof(wl->size),
                 "%s",
                 size->valuestring);

        snprintf(wl->group,
                 sizeof(wl->group),
                 "%s",
                 group->valuestring);

        HASH_ADD_STR(table, name, wl);
    }

    cJSON_Delete(root);
    free(json_data);

    return table;
}

wordlist_t *find_by_name(wordlist_t *table,
                         const char *name) {
    wordlist_t *result = NULL;

    HASH_FIND_STR(table, name, result);

    return result;
}

void find_by_group(wordlist_t *table,
                   const char *group) {
    wordlist_t *wl;
    int found = 0;

    for (wl = table; wl != NULL; wl = wl->hh.next) {

        if (strcmp(wl->group, group) == 0) {

            printf("name  : %s\n", wl->name);
            printf("group : %s\n", wl->group);
            printf("size  : %s\n", wl->size);
            printf("url   : %s\n\n", wl->url);

            found = 1;
        }
    }

    if (!found) {
        printf("group not found\n");
    }
}

void free_table(wordlist_t *table) {
    wordlist_t *cur, *tmp;

    HASH_ITER(hh, table, cur, tmp) {
        HASH_DEL(table, cur);
        free(cur);
    }
}