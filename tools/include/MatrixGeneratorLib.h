
#ifndef MATRIX_GENERATOR_LIB_H
#define MATRIX_GENERATOR_LIB_H


#include <stdint.h>
#include <stdio.h>

#include "CommonTypes.h"

#define OPEN_ROW(FilePtr)                   (PrintBlankSpaceBeforeString (FilePtr, 18, "{"))
#define CLOSE_ROW(FilePtr, Row, MaxRow)     (fprintf (FilePtr, Row == MaxRow ? "}\n" : "},\n"))
#define OPEN_MATRIX(FilePtr, MatrixDef)     (fprintf (FilePtr, "const uint8_t   %s = {\n", MatrixDef))
#define CLOSE_MATRIX(FilePtr)               (PrintBlankSpaceBeforeString (FilePtr, 16, "};\n\n"))



/**
  Main function

  @retval   STATUS_SUCCESS    - if matrix generation succeed
  @retval   STATUS_ERROR_     - in case of failure
**/
STATUS
MatrixGenerator (
  void
  );


/**
  Count all dimentions of needed matrix
  
  @param[out] n   Size of data block
  @param[out] k   Number of information bits in block
  @param[out] d   Number of parity bits in block

  @retval   STATUS_SUCCESS                - size configured and validated successfully
  @retval   STATUS_ERROR_INVALID_PARAM    - invalid inputs
**/
STATUS
CountSizeOfMatrix (
  int16_t     *n,
  uint16_t    *k,
  uint8_t     *d
  );


/**
  Prints head of the header file
  
  @param[in]  FilePtr   Pointer to file
  @param[in]  n         Size of data block
  @param[in]  k         Number of information bits in block
  @param[in]  d         Number of parity bits in block
**/
void
PrintFileHead (
  FILE        *HeaderFilePtr,
  uint16_t    n,
  uint16_t    k,
  uint8_t     d
  );


/**
  Generates and prints G matrix
  
  @param[in]  FilePtr   Pointer to file
  @param[in]  n         Size of data block
  @param[in]  k         Number of information bits in block
**/
void
PrintGeneratorMatrix (
  FILE        *FilePtr,
  uint16_t    n,
  uint16_t    k
  );


/**
  Generates and prints H matrix
  
  @param[in]  FilePtr   Pointer to file
  @param[in]  n         Size of data block
  @param[in]  d         Number of parity bits in block
**/
void
PrintCheckMatrix (
  FILE        *FilePtr,
  uint16_t    n,
  uint8_t     d
  );


/**
  Generates and prints I matrix
  
  @param[in]  FilePtr   Pointer to file
  @param[in]  n         Size of data block
  @param[in]  k         Number of information bits in block
**/
void
PrintEncodingMatrix (
  FILE        *FilePtr,
  uint16_t    n,
  uint16_t    k
  );


/**
  Prints numbers of columns
  
  @param[in]  FilePtr         Pointer to file
  @param[in]  ColumnAmount    Column amount in matrix
**/
void
PrintColumnNumbering (
  FILE        *FilePtr,
  uint16_t    ColumnAmount
  );


/**
  Prints blank space fo given size before text
  
  @param[in]  FilePtr   Pointer to file
  @param[in]  Length    Length of blank space
  @param[in]  String    Pointer to text after blank space
**/
void
PrintBlankSpaceBeforeString (
  FILE          *FilePtr,
  uint8_t       Length,
  const char    *StringPtr
  );


/**
  Prints blank space of given size before number
  
  @param[in]  FilePtr     Pointer to file
  @param[in]  Length      Length of blank space
  @param[in]  IntValue    Number after blank space
**/
void
PrintBlankSpaceBeforeInt (
  FILE        *FilePtr,
  uint8_t     Length,
  uint16_t    IntValue
  );


#endif