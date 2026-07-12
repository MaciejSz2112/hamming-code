
#ifndef DEFINES_LIB_H
#define DEFINES_LIB_H

#include <stdio.h>
#include <stdlib.h>

// 64-bit unsigned integer type
typedef unsigned long long int    UINT64;
// 64-bit signed integer type
typedef signed long long int      INT64;
// 32-bit unsigned integer type
typedef unsigned long int         UINT32;
// 32-bit signed integer type
typedef signed long int           INT32;
// 16-bit unsigned integer type
typedef unsigned short int        UINT16;
// 16 bit signed integer type
typedef signed short int          INT16;
// 8-bit unsigned integer type
typedef unsigned char             UINT8;
// 8-bit signed integer type
typedef signed char               INT8;
// 8-bit char type
typedef char                      CHAR;
// void type
typedef void                      VOID;
// Takes the value FALSE or TRUE
typedef UINT8                     BOOLEAN;

#define TRUE                      1
#define FALSE                     0

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

#endif