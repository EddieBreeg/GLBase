#pragma once

#define glClearErrors   while(glGetError());

#if defined(__cplusplus)
extern "C"
#endif // __cplusplus
// prints an error message to the standard output. This function is only there for internal use
int glLogError(const char *funcName, const char *file, int lineNumber);

// Cleans all errors in the queue, evaluates expr and prints the relevant message if an error occured
#define glCheckCall(expr)           \
    glClearErrors;                  \
    expr;                           \
    glLogError(#expr, __FILE__, __LINE__);  \

