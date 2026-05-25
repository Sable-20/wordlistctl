#ifndef CONFIG_H_
#define CONFIG_H_

typedef struct config {
    char useragent[256];
    char download_path[512];
} config_t;

#endif // CONFIG_H_