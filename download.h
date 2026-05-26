#ifndef DOWNLOAD_H_
#define DOWNLOAD_H_

#include <stdio.h>
#include <curl/curl.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct download_job {
    char url[1024];
    char output_path[512];
    char user_agent[256];
} download_job_t;

int download_file(const char* url,
                  const char* output_path,
                  const char* user_agent);

void download_workers(download_job_t* jobs, int total_jobs, int workers);

#endif // DOWNLOAD_H_