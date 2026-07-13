
#ifndef DEFINES_LIB_H
#define DEFINES_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

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

#define OPEN_FILE_STREAM(FilePtr, FileName, Mode)   do {                                                  \
                                                      FilePtr = fopen (FileName, Mode);                   \
                                                      if (FilePtr == NULL) {                              \
                                                        PRINT_ERROR ("%s opening error.\n", FileName);    \
                                                        exit (0);                                         \
                                                      }                                                   \
                                                      PRINT_INFO ("%s opened succesfully.\n", FileName);  \
                                                    } while (0);
#define CLOSE_FILE_STREAM(FilePtr, FileName)        do {                                                  \
                                                      if(fclose (FilePtr) == EOF) {                       \
                                                        PRINT_ERROR ("%s closing error.\n", FileName);    \
                                                        exit (0);                                         \
                                                      }                                                   \
                                                      PRINT_INFO ("%s closed succesfully.\n", FileName);  \
                                                    } while (0);

#ifdef __cplusplus
}
#endif

#endif