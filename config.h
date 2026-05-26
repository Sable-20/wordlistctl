#ifndef CONFIG_H_
#define CONFIG_H_

/**
 * Configuration structure for wordlistctl
 * 
 * This structure holds the user agent string, the default download path and the number of workers used to download the files.
 */
typedef struct config {
    char useragent[256]; /**< User agent string */
    char download_path[512]; /**< Default download path */
    int workers; /**< Number of workers used to download the files */
    char decompress[5]; /**< Whether to decompress downloaded files (true/false) */
} config_t;

#endif // CONFIG_H_