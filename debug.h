//so as to not include file twice
#ifndef __dbg_h__ #define __dbg_h__
//Includes needed
#include <stdio.h> #include <errno.h> #include <string.h>
//If compiliation is made with NDEBUG defined no
//debug messages will remain
#ifdef NDEBUG
#define debug(M, ...)
#else
//otherwise print out debug messages
//##_VA_ARGS__ handles the extra arguments
//__LINE__ gives linenumber for debug message
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE __, ##__VA_ARGS__)
#endif
//Gets a safe readable version of errno
//? is an "IF" 
//thus if nothing in errno "None" otherwise give 
//the errormsg as string
#define clean_errno() (errno == 0 ? "None" : strerror(errno))
//The 3 below is for logging messages for end user
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, _ _LINE__, ##__VA_ARGS__)
//Makes sure that condition A is true and if not logs the error M
//with log_err and then jumps to error for cleanup
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }
//Is placed in any parto of a function that shouldnt run
//if it does print err msg and jumps to error
#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__); errno=0; goto error; } 
//Makes sure a pointer is valid
#define check_mem(A) check((A), "Out of memory.")
//
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; go to error; }
#endif