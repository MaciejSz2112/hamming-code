
#ifndef CODER_MODULE_LIB_H
#define CODER_MODULE_LIB_H


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "CommonTypes.h"

#define CHAR_TO_INT(InputChar)    ((InputChar) - (48))
#define INT_TO_CHAR(InputInt)     ((InputInt) + (48))



/**
	Main function
 **/
void
CoderModule (
  void
  );


/**
  Coding function

  @param  FilePtr   Pointer to file simulating channel
**/
void 
Coding (
  FILE              *FilePtr
  );


/**
  Decoding function

  @param  FilePtr   Pointer to file simulating channel
 **/
void
Decoding (
  FILE              *FilePtr
  );


/**
	Gets block of data from file. If there is no data
  or block is incomplete, returnes false
	
	@param	FilePtr       Pointer to a file
	@param	Buffor        Pointer to a buffor array
	@param	BufforSize    Size of the buffor
	
	@retval	true          - if function gets full block
  @retval false         - if geting full block was impossible
 **/
bool
GetBlockFromFile (
  FILE                  *FilePtr,
  char                  Buffor[],
  uint16_t              BufforSize
  );


/**
	Checks parity bits and corrects error if it occurs
	
	@param	Buffor    Pointer to a buffor array
 **/
void
ErrorCorrection (
  char              Buffor[]
  );


/**
  Prints to file data from int buffor

  @param  FilePtr       Pointer to a file
  @param  InputBuffor   Pointer to a buffor array
  @param  BufforSize    Size of the buffor
 **/
void
PrintIntBufforToFile (
  FILE                  *FilePtr,
  uint8_t               InputBuffor[],
  uint16_t              BufforSize
  );


/**
  Fils char buffor with '\0'

  @param  Buffor        Pointer to a buffor array
  @param  BufforSize    Size of the buffor
 **/
void
ClearCharBuffor (
  char                  Buffor[],
  uint16_t              BufforSize
  );


/**
	OutputBuffor XOR (Matrix AND (uint8_t)InputBuffor)
	
	@param	SizeOfDimensionN    Size of N dimension of the matrix and OutputBuffor
	@param	SizeOfDimensionM    Size of M dimension of the matrix and InputBuffor
	@param	InputBuffor         Pointer to data InputBuffor
	@param	Matrix              Pointer to the matrix
	@param	OutputBuffor        Pointer to OutputBuffor
 **/
void
XorMatrixAndDataToBuffor (
  uint16_t                    SizeOfDimensionN,
  uint16_t                    SizeOfDimensionM,
  char                        InputBuffor[],
  const uint8_t               Matrix[][SizeOfDimensionM],
  uint8_t                     OutputBuffor[]
  );


#endif