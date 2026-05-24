#include "file.h"
#include "download.h"

int main()
{
  wordlist_t *table =
      load_repo("repo.json");

  if (!table)
  {
    fprintf(stderr,
            "failed to load repo\n");
    return 1;
  }

  /*
      search by name
  */

  wordlist_t *wl =
      find_by_name(table,
                   "deepmagic");

  if (wl)
  {

    printf("FOUND BY NAME\n\n");

    printf("name  : %s\n", wl->name);
    printf("group : %s\n", wl->group);
    printf("size  : %s\n", wl->size);
    printf("url   : %s\n\n", wl->url);

    const char* url = wl->url;
    const char* output_path = "/tmp/deepmagic.txt";

    if (download_file(url, output_path) == 0) {
        printf("File downloaded successfully to %s\n", output_path);
    } else {
        fprintf(stderr, "Failed to download file from %s\n", url);
    }
  }

  /*
      search by group
  */

  // printf("FOUND BY GROUP\n\n");

  // find_by_group(table,
  //               "passwords");

  // free_table(table);

  return 0;
}
