#include "download.h"

static size_t write_data(void *ptr,
                         size_t size, size_t nmemb, void *stream)
{
    FILE *fp = (FILE *)stream;

    return fwrite(ptr, size, nmemb, fp);
}

int download_file(const char *url,
                  const char *output_path,
                  const char *user_agent)
{
    CURL *curl;
    CURLcode res;

    FILE *fp = fopen(output_path, "wb");

    if (!fp) {
        perror("fopen");
        return -1;
    }

    curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "curl_easy_init() failed\n");
        fclose(fp);
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        fclose(fp);
        return -1;
    }

    curl_easy_cleanup(curl);
    fclose(fp);

    return 0;
}