#ifndef TLPI_HDR_H
#define TLPI_HDR_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>  // Prototypes of commonly used library functions
                     // PLUS EXIT_SUCCESS and EXIT_FAILURE constants
#include <unistd.h>  // Prototypes for many system calls
#include <errno.h>   // Declare errno and defines error constants
#include <string.h>

#include "get_num.h" // Declare the functions for handling numeric
                     // arguments (getInt(), getLong())

#include "error_functions.h" // Declare error-handling functions

typedef enum { FLASE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif