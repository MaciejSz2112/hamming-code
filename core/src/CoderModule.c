
#include <CommonTypes.h>
#include <FileIo.h>
#include <CoderModuleLib.h>
#include <Size_15.h>



int
main (
  void
  )
{
  CoderModule ();

  return 0;
}


void
CoderModule (
  void
  )
{
  FILE    *ChannelFilePtr;

  PRINT_INFO ("Function starts.\n");

  if (OpenFileStream (&ChannelFilePtr, "files/channel.txt", "w+b") != STATUS_SUCCESS) {
    PRINT_ERROR ("Coder module aborted due to channel file open failure.\n");
    return;
  }

  Coding (ChannelFilePtr);

  fseek (ChannelFilePtr, 0, SEEK_SET);

  Decoding (ChannelFilePtr);

  if (CloseFileStream (ChannelFilePtr, "files/channel.txt") != STATUS_SUCCESS) {
    PRINT_ERROR ("Warning: Failed to close channel file safely.\n");
  }

  PRINT_INFO ("Function ends.\n");
}


void
Coding (
  FILE      *ChannelFilePtr
  )
{
  FILE      *InputFilePtr;
  char      InputBlock[k+1];
  uint8_t   OutputBlock[n];

  PRINT_INFO ("Function starts.\n");

  if (OpenFileStream (&InputFilePtr, "files/input.txt", "rb") != STATUS_SUCCESS) {
    PRINT_ERROR ("Coding aborted due to input file open failure.\n");
    return;
  }

  ClearCharBuffor (InputBlock, k);
  
  while (GetBlockFromFile (InputFilePtr, InputBlock, k+1)) {

    XorMatrixAndDataToBuffor (n, k, InputBlock, G, OutputBlock);

    PrintIntBufforToFile (ChannelFilePtr, OutputBlock, n);
      
    ClearCharBuffor (InputBlock, k);
  }

  if (CloseFileStream (InputFilePtr, "files/input.txt") != STATUS_SUCCESS) {
    PRINT_ERROR ("Warning: Failed to close input file safely.\n");
  }

  PRINT_INFO ("Function ends.\n");
}


void
Decoding (
  FILE      *ChannelFilePtr
  )
{
  FILE      *OutputFilePtr;
  char      InputBlock[n+1];
  uint8_t   OutputBlock[k];

  PRINT_INFO ("Function starts.\n");

  if (OpenFileStream (&OutputFilePtr, "files/output.txt", "wb") != STATUS_SUCCESS) {
    PRINT_ERROR ("Decoding aborted due to output file open failure.\n");
    return;
  }

  ClearCharBuffor (InputBlock, n);
  
  while (GetBlockFromFile (ChannelFilePtr, InputBlock, n+1)) {

    ErrorCorrection (InputBlock);

    XorMatrixAndDataToBuffor (k, n, InputBlock, I, OutputBlock);

    PrintIntBufforToFile (OutputFilePtr, OutputBlock, k);

    ClearCharBuffor (InputBlock, n);
  }

  if (CloseFileStream (OutputFilePtr, "files/output.txt") != STATUS_SUCCESS) {
    PRINT_ERROR ("Warning: Failed to close output file safely.\n");
  }

  PRINT_INFO ("Function ends.\n");
}


bool
GetBlockFromFile (
  FILE        *FilePtr,
  char        Buffor[],
  uint16_t    BufforSize
  )
{
  uint8_t     Counter;

  if (fgets (Buffor, BufforSize, FilePtr) == NULL) {
    return false;
  }

  for (Counter = 0; Counter < (BufforSize - 1); Counter++) {
    if (Buffor[Counter] == '\0') {
      fseek (FilePtr, 0 - Counter, SEEK_CUR);
      return false;
    }
  }

  return true;
}


void
ErrorCorrection (
  char     Buffor[]
  )
{
  uint16_t    Counter;
  uint8_t     ErrorVector[d];
  uint8_t     ErrorPosition;

  XorMatrixAndDataToBuffor (d, n, Buffor, H, ErrorVector);

  ErrorPosition = 0;
  for (Counter = 0; Counter < d; Counter++) {
    ErrorPosition += ErrorVector[Counter] * (1 << Counter);
  }

  if (ErrorPosition > 0) {
    Buffor[ErrorPosition-1] ^= 1;
  }
}


void
PrintIntBufforToFile (
  FILE        *FilePtr,
  uint8_t     InputBuffor[],
  uint16_t    BufforSize
  )
{
  uint16_t    Counter;
  char        OutputBuffor[BufforSize+1];

  for (Counter = 0; Counter < BufforSize; Counter++) {
    OutputBuffor[Counter] = INT_TO_CHAR (InputBuffor[Counter]);
  }
  OutputBuffor[BufforSize] = '\0';

  fputs (OutputBuffor, FilePtr);
}


void
ClearCharBuffor (
  char        Buffor[],
  uint16_t    BufforSize
  )
{
  uint16_t    Counter;

  for (Counter = 0; Counter < BufforSize; Counter++) {
    Buffor[Counter] = '\0';
  }
}


void
XorMatrixAndDataToBuffor (
  uint16_t        SizeOfDimensionN,
  uint16_t        SizeOfDimensionM,
  char            InputBuffor[],
  const uint8_t   Matrix[][SizeOfDimensionM],
  uint8_t         OutputBuffor[]
  )
{
  uint16_t        CounterN;
  uint16_t        CounterM;

  for (CounterN = 0; CounterN < SizeOfDimensionN; CounterN++) {
    OutputBuffor[CounterN] = 0;

    for (CounterM = 0; CounterM < SizeOfDimensionM; CounterM++) {

      OutputBuffor[CounterN] ^= Matrix[CounterN][CounterM] & CHAR_TO_INT (InputBuffor[CounterM]);
    }
  }
}