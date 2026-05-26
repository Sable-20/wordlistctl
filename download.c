#include "download.h"

static size_t write_data(void *ptr,
                         size_t size, size_t nmemb, void *stream)
{
    FILE *fp = (FILE *)stream;

    return fwrite(ptr, size, nmemb, fp);
}

static int current_job = 0;
static int total = 0;
static download_job_t *job_list = NULL;
static pthread_mutex_t job_mutex = PTHREAD_MUTEX_INITIALIZER;

int download_file(const char *url,
                  const char *output_path,
                  const char *user_agent)
{
    CURL *curl;
    CURLcode res;

    FILE *fp = fopen(output_path, "wb");

    if (!fp)
    {
        perror("fopen");
        return -1;
    }

    curl = curl_easy_init();

    if (!curl)
    {
        fprintf(stderr, "curl_easy_init() failed\n");
        fclose(fp);
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
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

static void *worker_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&job_mutex);

        int idx = current_job++;
        pthread_mutex_unlock(&job_mutex);

        if (idx >= total) {
            break;
        }

        download_job_t *job = &job_list[idx];
        printf("[*] Downloading %s\n", job->output_path);

        int r = download_file(job->url, job->output_path, job->user_agent);

        if (r == 0)
            printf("[+] Downloaded %s successfully\n", job->output_path);
        else
            printf("[-] Failed to download %s\n", job->output_path);
    }

    return NULL;
}

void download_workers(download_job_t *jobs, int total_jobs, int workers) {
    job_list = jobs;
    total = total_jobs;

    pthread_t *threads = malloc(sizeof(pthread_t) * workers);

    curl_global_init(CURL_GLOBAL_ALL);

    for (int i = 0; i < workers; i++) {
        pthread_create(&threads[i], NULL, worker_thread, NULL);
    }

    curl_global_cleanup();

    free(threads);
}