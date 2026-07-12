
#ifndef MATRIX_GENERATOR_LIB_H
#define MATRIX_GENERATOR_LIB_H

#include "DefinesLib.h"

#define OPEN_ROW(FilePtr)                   (PrintBlankSpaceBeforeString (FilePtr, 16, "{"))
#define CLOSE_ROW(FilePtr, Row, MaxRow)     (fprintf (FilePtr, Row == MaxRow ? "}\n" : "},\n"))
#define OPEN_MATRIX(FilePtr, MatrixDef)     (fprintf (FilePtr, "const UINT8   %s = {\n", MatrixDef))
#define CLOSE_MATRIX(FilePtr)               (PrintBlankSpaceBeforeString (FilePtr, 14, "};\n\n"))



/**
	Main function
 **/
VOID
MatrixGenerator (
  VOID
  );


/**
	Count all dimentions of needed matrix
	
	@param	n   Size of data block
	@param	k   Number of information bits in block
	@param	d   Number of parity bits in block
 **/
VOID
CountSizeOfMatrix (
  INT16       *n,
  UINT16      *k,
  UINT8       *d
  );


/**
	Prints head of the header file
	
	@param	FilePtr   Pointer to file
	@param	n         Size of data block
	@param	k         Number of information bits in block
	@param	d         Number of parity bits in block
 **/
VOID
PrintFileHead (
  FILE              *HeaderFilePtr,
  UINT16            n,
  UINT16            k,
  UINT8             d
  );


/**
	Generates and prints G matrix
	
	@param	FilePtr   Pointer to file
	@param	n         Size of data block
	@param	k         Number of information bits in block
 **/
VOID
PrintGeneratorMatrix (
  FILE              *FilePtr,
  UINT16            n,
  UINT16            k
  );


/**
	Generates and prints H matrix
	
	@param	FilePtr   Pointer to file
	@param	n         Size of data block
	@param	d         Number of parity bits in block
 **/
VOID
PrintCheckMatrix (
  FILE              *FilePtr,
  UINT16            n,
  UINT8             d
  );


/**
	Generates and prints I matrix
	
	@param	FilePtr   Pointer to file
	@param	n         Size of data block
	@param	k         Number of information bits in block
 **/
VOID
PrintEncodingMatrix (
  FILE              *FilePtr,
  UINT16            n,
  UINT16            k
  );


/**
	Prints numbers of columns
	
	@param	FilePtr         Pointer to file
	@param	ColumnAmount    Column amount in matrix
 **/
VOID
PrintColumnNumbering (
  FILE                    *FilePtr,
  UINT16                  ColumnAmount
  );


/**
	Prints blank space fo given size before text
	
	@param	FilePtr   Pointer to file
	@param	Length    Length of blank space
	@param	String    Text after blank space
 **/
VOID
PrintBlankSpaceBeforeString (
  FILE              *FilePtr,
  UINT8             Length,
  CHAR              String[]
  );


/**
	Prints blank space of given size before number
	
	@param	FilePtr     Pointer to file
	@param	Length      Length of blank space
	@param	IntValue    Number after blank space
 **/
VOID
PrintBlankSpaceBeforeInt (
  FILE                *FilePtr,
  UINT8               Length,
  UINT16              IntValue
  );


#endif