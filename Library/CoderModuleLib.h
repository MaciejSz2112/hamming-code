
#ifndef CODER_MODULE_LIB_H
#define CODER_MODULE_LIB_H

#include "DefinesLib.h"

#define CHAR_TO_INT(InputChar)    ((InputChar) - (48))
#define INT_TO_CHAR(InputInt)     ((InputInt) + (48))



/**
	Main function
 **/
VOID
CoderModule (
  VOID
  );


/**
  Coding function

  @param  FilePtr   Pointer to file simulating channel
**/
VOID 
Coding (
  FILE              *FilePtr
  );


/**
  Decoding function

  @param  FilePtr   Pointer to file simulating channel
 **/
VOID
Decoding (
  FILE              *FilePtr
  );


/**
	Gets block of data from file. If there is no data
  or block is incomplete, returnes FALSE
	
	@param	FilePtr       Pointer to a file
	@param	Buffor        Pointer to a buffor array
	@param	BufforSize    Size of the buffor
	
	@retval	TRUE          - if function gets full block
  @retval FALSE         - if geting full block was impossible
 **/
BOOLEAN
GetBlockFromFile (
  FILE                  *FilePtr,
  CHAR                  Buffor[],
  UINT16                BufforSize
  );


/**
	Checks parity bits and corrects error if it occurs
	
	@param	Buffor    Pointer to a buffor array
 **/
VOID
ErrorCorrection (
  UINT8             Buffor[]
  );


/**
  Prints to file data from int buffor

  @param  FilePtr       Pointer to a file
  @param  InputBuffor   Pointer to a buffor array
  @param  BufforSize    Size of the buffor
 **/
VOID
PrintIntBufforToFile (
  FILE                  *FilePtr,
  UINT8                 InputBuffor[],
  UINT16                BufforSize
  );


/**
  Fils UCHAR buffor with '\0'

  @param  Buffor        Pointer to a buffor array
  @param  BufforSize    Size of the buffor
 **/
VOID
ClearCharBuffor (
  CHAR                  Buffor[],
  UINT16                BufforSize
  );


/**
	OutputBuffor XOR (Matrix AND (UINT8)InputBuffor)
	
	@param	SizeOfDimensionN    Size of N dimension of the matrix and OutputBuffor
	@param	SizeOfDimensionM    Size of M dimension of the matrix and InputBuffor
	@param	InputBuffor         Pointer to data InputBuffor
	@param	Matrix              Pointer to the matrix
	@param	OutputBuffor        Pointer to OutputBuffor
 **/
VOID
XorMatrixAndDataToBuffor (
  UINT16                      SizeOfDimensionN,
  UINT16                      SizeOfDimensionM,
  CHAR                        InputBuffor[],
  const UINT8                 Matrix[][SizeOfDimensionM],
  UINT8                       OutputBuffor[]
  );


#endif