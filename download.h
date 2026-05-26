#ifndef DOWNLOAD_H_
#define DOWNLOAD_H_

#include <stdio.h>
#include <curl/curl.h>
#include <pthread.h>
#include <stdlib.h>

/**
 * Structure representing a download job
 * 
 * This structure holds the URL, output path, and user agent for individual download tasks. It is used to pass information to worker threads that perform the downloads concurrently.
 */
typedef struct download_job {
    char url[1024]; /**< URL of the file to download */
    char output_path[512]; /**< Path where the downloaded file will be saved */
    char user_agent[256]; /**< User agent string for the HTTP request */
} download_job_t;

/**
 * Downloads a file from the specified URL and saves it to the given output path using the specified user agent. This function uses `libcurl` to perform the downloads.
 * 
 * @param url The URL of the file to download
 * @param output_path The path where the downloaded file will be saved
 * @param user_agent The user agent string to use for the HTTP request
 * @return 0 on success, -1 on failure
 */
int download_file(const char* url,
                  const char* output_path,
                  const char* user_agent);

/**
 * Worker function for downloading files concurrently. This function is intended to be run in multiple threads, where each thread wil pick a download job from the shared job list and execute it using the `download_file` function. The function uses mutexes to synchronize access to the shared job list and ensure that each job is processed by only one thread.
 * 
 * @param jobs An array of download jobs to be processed
 * @param total_jobs The total number of download jobs in the array
 * @param workers The number of worker threads to create for processing the download jobs
 */
void download_workers(download_job_t* jobs, int total_jobs, int workers);

#endif // DOWNLOAD_H_