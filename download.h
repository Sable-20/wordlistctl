#ifndef DOWNLOAD_H_
#define DOWNLOAD_H_

#include <stdio.h>
#include <curl/curl.h>

int download_file(const char* url,
                  const char* output_path,
                  const char* user_agent);

#endif // DOWNLOAD_H_