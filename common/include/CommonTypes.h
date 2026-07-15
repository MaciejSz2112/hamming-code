
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H


#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  @brief System status codes for error handling
**/
typedef enum {
  STATUS_SUCCESS = 0,
  STATUS_ERROR_NULL_PTR,
  STATUS_ERROR_FILE_OPEN,
  STATUS_ERROR_FILE_CLOSE,
  STATUS_ERROR_INVALID_PARAM
} Status;

#define PRINT_INFO(f_, ...)       (printf ("[INFO]  %s: " f_, __func__, ##__VA_ARGS__))
#define PRINT_ERROR(f_, ...)      (fprintf (stderr, "[ERROR] %s: " f_, __func__, ##__VA_ARGS__))

#ifdef __cplusplus
}
#endif

#endif    // COMMON_TYPES_H