
#ifndef DEFINES_LIB_H
#define DEFINES_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PRINT_INFO(f_, ...)       (printf ("[INFO]  %s: " f_, __func__, ##__VA_ARGS__))
#define PRINT_ERROR(f_, ...)      (printf ("[ERROR] %s: " f_, __func__, ##__VA_ARGS__))

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