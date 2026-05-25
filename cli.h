#ifndef CLI_H_
#define CLI_H_

#include "argtable3.h"

#define REG_EXTENDED 1
#define REG_ICASE (REG_EXTENDED << 1)

/* wordlistctl fetch [-h] [-l WORDLIST [WORDLIST ...]]
    -g {usernames,passwords,discovery,fuzzing,misc} [{usernames,passwords,discovery,fuzzing,misc} ...]]
    [-d] [-w WORKERS] [-u USERAGENT] [-b BASEDIR] fetch_term
*/

int cli_fetch(const char* wordlist,
              const char* group,
              int decompress,
              int workers,
              const char* user_agent,
              const char* base_dir);

// wordlistctl search  [-h] [-l] [-b BASEDIR] search_term
int cli_search(int local,
               const char* base_dir,
               const char* search_term);

// wordlistctl list [-h] [-g {usernames,passwords,discovery,fuzzing,misc}]
int cli_list(const char* group);

#endif // CLI_H_