
#include "Library/DefinesLib.h"
#include "Library/CoderModuleLib.h"
#include "Library/Size_15.h"



VOID
main (
  VOID
  )
{
  CoderModule ();
}


VOID
CoderModule (
  VOID
  )
{
  FILE    *ChannelFilePtr;

  PRINT_INFO ("Function starts.\n");

  OPEN_FILE_STREAM (ChannelFilePtr, "Files/channel.txt", "w+b");

  Coding (ChannelFilePtr);

  fseek (ChannelFilePtr, 0, SEEK_SET);

  Decoding (ChannelFilePtr);

  CLOSE_FILE_STREAM (ChannelFilePtr, "Files/channel.txt")

  PRINT_INFO ("Function ends.\n");
}


VOID
Coding (
  FILE    *ChannelFilePtr
  )
{
  FILE    *InputFilePtr;
  CHAR    InputBlock[k+1];
  UINT8   OutputBlock[n];

  PRINT_INFO ("Function starts.\n");

  OPEN_FILE_STREAM (InputFilePtr, "Files/input.txt", "rb");

  ClearCharBuffor (InputBlock, k);
  
  while (GetBlockFromFile (InputFilePtr, InputBlock, k+1)) {

    XorMatrixAndDataToBuffor (n, k, InputBlock, G, OutputBlock);

    PrintIntBufforToFile (ChannelFilePtr, OutputBlock, n);
      
    ClearCharBuffor (InputBlock, k);
  }

  CLOSE_FILE_STREAM (InputFilePtr, "Files/input.txt");

  PRINT_INFO ("Function ends.\n");
}


VOID
Decoding (
  FILE    *ChannelFilePtr
  )
{
  FILE    *OutputFilePtr;
  CHAR    InputBlock[n+1];
  UINT8   OutputBlock[k];

  PRINT_INFO ("Function starts.\n");

  OPEN_FILE_STREAM (OutputFilePtr, "Files/output.txt", "wb");

  ClearCharBuffor (InputBlock, n);
  
  while (GetBlockFromFile (ChannelFilePtr, InputBlock, n+1)) {

    ErrorCorrection (InputBlock);

    XorMatrixAndDataToBuffor (k, n, InputBlock, I, OutputBlock);

    PrintIntBufforToFile (OutputFilePtr, OutputBlock, k);

    ClearCharBuffor (InputBlock, n);
  }

  CLOSE_FILE_STREAM (OutputFilePtr, "Files/output.txt");

  PRINT_INFO ("Function ends.\n");
}


BOOLEAN
GetBlockFromFile (
  FILE      *FilePtr,
  CHAR      Buffor[],
  UINT16    BufforSize
  )
{
  UINT8     Counter;

  if (fgets (Buffor, BufforSize, FilePtr) == NULL) {
    return FALSE;
  }

  for (Counter = 0; Counter < (BufforSize - 1); Counter++) {
    if (Buffor[Counter] == '\0') {
      fseek (FilePtr, 0 - Counter, SEEK_CUR);
      return FALSE;
    }
  }

  return TRUE;
}


VOID
ErrorCorrection (
  UINT8     Buffor[]
  )
{
  UINT16    Counter;
  UINT8     ErrorVector[d];
  UINT8     ErrorPosition;

  XorMatrixAndDataToBuffor (d, n, Buffor, H, ErrorVector);

  ErrorPosition = 0;
  for (Counter = 0; Counter < d; Counter++) {
    ErrorPosition += ErrorVector[Counter] * (1 << Counter);
  }

  if (ErrorPosition > 0) {
    Buffor[ErrorPosition-1] ^= 1;
  }
}


VOID
PrintIntBufforToFile (
  FILE      *FilePtr,
  UINT8     InputBuffor[],
  UINT16    BufforSize
  )
{
  UINT16    Counter;
  CHAR      OutputBuffor[BufforSize+1];

  for (Counter = 0; Counter < BufforSize; Counter++) {
    OutputBuffor[Counter] = INT_TO_CHAR (InputBuffor[Counter]);
  }
  OutputBuffor[BufforSize] = '\0';

  fputs (OutputBuffor, FilePtr);
}


VOID
ClearCharBuffor (
  CHAR      Buffor[],
  UINT16    BufforSize
  )
{
  UINT16    Counter;

  for (Counter = 0; Counter < BufforSize; Counter++) {
    Buffor[Counter] = '\0';
  }
}


VOID
XorMatrixAndDataToBuffor (
  UINT16        SizeOfDimensionN,
  UINT16        SizeOfDimensionM,
  CHAR          InputBuffor[],
  const UINT8   Matrix[][SizeOfDimensionM],
  UINT8         OutputBuffor[]
  )
{
  UINT16        CounterN;
  UINT16        CounterM;

  for (CounterN = 0; CounterN < SizeOfDimensionN; CounterN++) {
    OutputBuffor[CounterN] = 0;

    for (CounterM = 0; CounterM < SizeOfDimensionM; CounterM++) {

      OutputBuffor[CounterN] ^= Matrix[CounterN][CounterM] & CHAR_TO_INT (InputBuffor[CounterM]);
    }
  }
}