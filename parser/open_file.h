#ifndef OPEN_FILE_H
# define OPEN_FILE_H

#include <fcntl.h>

#ifndef CREATE_MOD
# define CREATE_MOD 0777
#endif

#ifndef REDIR_APPEND
# define REDIR_APPEND O_CREAT | O_RDWR | O_APPEND 
#endif

#ifndef REDIR_OUT
# define REDIR_OUT O_CREAT | O_RDWR | O_TRUNC
#endif

#ifndef REDIR_IN
# define REDIR_IN O_RDONLY 
#endif

int open_file(char *file_name, int flags);

#endif