#include <cstdio>
#include "BaseException.h"

using namespace std;

BaseException::BaseException(const char *time, const char *filename,
                            const size_t line, const char *class_name,
                            const char *method_name, const char *info) noexcept
{
    size_t ind = 0;
    ErrorInfo[0] = '\0';

    if (info)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "ERROR_Matrix: Info: %s, ", info);

    if (filename)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "File: %s, ", filename);

    ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "Line: %ld, ", line);

    if (class_name)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "Class: %s, ", class_name);

    if (method_name)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "Method: %s, ", method_name);

    if (time)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "Time: %s, ", time);
}

const char *BaseException::what() const noexcept
{
    return ErrorInfo;
}


// BaseIteratorException::BaseIteratorException(const char *time, const char *filename,
//                             const size_t line, const char *class_name,
//                             const char *method_name, const char *info) noexcept
// {
//     size_t ind = 0;
//     ErrorInfo[0] = '\0';

//     if (info)
//         ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "ERROR_Iterator: Info: %s, ", info);

//     if (filename)
//         ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "File: %s, ", filename);

//     ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "Line: %ld, ", line);

//     if (class_name)
//         ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "Class: %s, ", class_name);

//     if (method_name)
//         ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "Method: %s, ", method_name);

//     if (time)
//         ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - ind, "Time: %s, ", time);
// }

// const char *BaseIteratorException::what() const noexcept
// {
//     return ErrorInfo;
// }