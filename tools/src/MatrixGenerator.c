
#include <CommonTypes.h>
#include <MatrixGeneratorLib.h>



int8_t
main (
  void
  )
{
  MatrixGenerator ();

  return 0;
}


void
MatrixGenerator (
  void
  )
{
  FILE        *HeaderFilePtr;
  uint16_t    n;
  uint16_t    k;
  uint8_t     d;
  char        FileName[30];

  PRINT_INFO ("Function starts.\n");

  CountSizeOfMatrix ((int16_t*)&n, &k, &d);

  sprintf (FileName, "core/include/Size_%d.h", n);

  OPEN_FILE_STREAM (HeaderFilePtr, FileName, "w");

  PrintFileHead (HeaderFilePtr, n, k, d);
  
  PrintGeneratorMatrix (HeaderFilePtr, n, k);

  PrintCheckMatrix (HeaderFilePtr, n, d);

  PrintEncodingMatrix (HeaderFilePtr, n, k);
  
  fprintf (HeaderFilePtr, "#endif\n");

  CLOSE_FILE_STREAM (HeaderFilePtr, FileName);

  PRINT_INFO ("Function ends.\n");
}


void
CountSizeOfMatrix (
  int16_t     *n,
  uint16_t    *k,
  uint8_t     *d
  )
{
  PRINT_INFO ("Function starts.\n");

  printf ("\n"
          "        Size of block (>2): "
    );
  scanf ("%d", n); 
  printf ("\n");

  if (*n < 3) {
    PRINT_ERROR ("Block is too small. It has to be bigger than 2.\n");
    exit (0);
  }

  for (*d = 0; (1<<(*d)) <= *n; (*d)++);

  *k = *n - *d;

  PRINT_INFO ("Function ends.\n");
}


void
PrintFileHead (
  FILE        *FilePtr,
  uint16_t    n,
  uint16_t    k,
  uint8_t     d
  )
{
  PRINT_INFO ("Function starts.\n");

  fprintf (FilePtr, "\n"
                    "#ifndef SIZE_H\n"
                    "#define SIZE_H\n"
                    "\n"
                    "\n"
                    "#include <CommonTypes.h>\n"
                    "\n"
    );

  fprintf (FilePtr, "#define n   %d\n"
                    "#define k   %d\n"
                    "#define d   %d\n"
                    "\n"
                    , n, k, d
    );
  
  PRINT_INFO ("Function ends.\n");
}


void
PrintGeneratorMatrix (
  FILE        *FilePtr,
  uint16_t    RowNumber,
  uint16_t    ColumnNumber
  )
{
  uint16_t    Row;
  uint16_t    Column;
  uint8_t     ParityRow;
  uint16_t    NextParityBit;
  uint8_t     Value;

  PRINT_INFO ("Function starts.\n");

  OPEN_MATRIX (FilePtr, "G[n][k]");

  PrintColumnNumbering (FilePtr, ColumnNumber);

  for (Row = 1, ParityRow = 0; Row <= RowNumber; Row++) {
    
    OPEN_ROW (FilePtr);

    if (Row == (1<<ParityRow)) {

      Value = 0;
      
      for (Column = 1, NextParityBit = 0; Column <= RowNumber; Column++) {

        if ((Column % (1<<ParityRow)) == 0) {
          Value ^= 1;
        }

        if (Column == (1<<NextParityBit)) {
          NextParityBit++;
        }
        else {
          if (Column > 3) {
            fprintf (FilePtr, ", ");
          }
          
          fprintf (FilePtr, "%d", Value);
        }
      }

      ParityRow++;
    }
    else {
      for (Column = 1; Column <= ColumnNumber; Column++) {

        if (Column > 1) {
          fprintf (FilePtr, ", ");
        }

        fprintf (FilePtr, Column == (Row - ParityRow) ? "1" : "0");
      }
    }

    CLOSE_ROW (FilePtr, Row, RowNumber);
  }

  CLOSE_MATRIX (FilePtr);

  PRINT_INFO ("Function ends.\n");
}


void
PrintCheckMatrix (
  FILE        *FilePtr,
  uint16_t    ColumnNumber,
  uint8_t     RowNumber
  )
{
  uint16_t    Column;
  uint8_t     Row;
  uint8_t     Value;

  PRINT_INFO ("Function starts.\n");

  OPEN_MATRIX (FilePtr, "H[d][n]");

  PrintColumnNumbering (FilePtr, ColumnNumber);

  for (Row = 1; Row <= RowNumber; Row++) {

    Value = 0;

    OPEN_ROW (FilePtr);
    for (Column = 1; Column <= ColumnNumber; Column++) {

      if ((Column % (1<<(Row-1))) == 0) {
        Value ^= 1;
      }

      if (Column > 1) {
        fprintf (FilePtr, ", ");
      }

      fprintf (FilePtr, "%d", Value);
    }

    CLOSE_ROW (FilePtr, Row, RowNumber);
  }

  CLOSE_MATRIX (FilePtr);

  PRINT_INFO ("Function ends.\n");
}


void
PrintEncodingMatrix (
  FILE        *FilePtr,
  uint16_t    ColumnNumber,
  uint16_t    RowNumber
  )
{
  uint16_t    Row;
  uint16_t    Column;
  uint16_t    ValuePosition;
  uint16_t    NextParityBit;

  PRINT_INFO ("Function starts.\n");

  OPEN_MATRIX (FilePtr, "I[k][n]");

  PrintColumnNumbering (FilePtr, ColumnNumber);

  for (Row = 1, ValuePosition = 3; Row <= RowNumber; Row++) {

    OPEN_ROW (FilePtr);

    for (Column = 1, NextParityBit = 0; Column <= ColumnNumber; Column++) {

      if (Column == (1<<NextParityBit)) {

        NextParityBit++;
        if (Column == ValuePosition) {
          ValuePosition++;
        }
      }

      if (Column > 1) {
        fprintf (FilePtr, ", ");
      }

      fprintf (FilePtr, Column == ValuePosition ? "1" : "0");
    }

    CLOSE_ROW (FilePtr, Row, RowNumber);

    ValuePosition++;
  }

  CLOSE_MATRIX (FilePtr);

  PRINT_INFO ("Function ends.\n");
}


void
PrintColumnNumbering (
  FILE        *FilePtr,
  uint16_t    ColumnAmount
  )
{
  uint16_t    ColumnNumber;
  uint8_t     Space;
  uint16_t    Cap;

  PrintBlankSpaceBeforeString (FilePtr, 17, "//1");

  for (ColumnNumber = 5, Space = 11, Cap = 10; ColumnNumber <= ColumnAmount; ColumnNumber+=5) {
    if (ColumnNumber == 10) {
      Space = 14;
    }

    if (ColumnNumber >= Cap) {
      Space--;
      Cap *= 10;
    }

    PrintBlankSpaceBeforeInt (FilePtr, Space, ColumnNumber);
  }

  fprintf (FilePtr, "\n");
}


void
PrintBlankSpaceBeforeString (
  FILE      *FilePtr,
  uint8_t   Length,
  char      String[10]
  )
{
  uint8_t   Counter;

  for (Counter = 0; Counter < Length; Counter++) {
    fprintf (FilePtr, " ");
  }

  fprintf (FilePtr, String);
}


void
PrintBlankSpaceBeforeInt (
  FILE        *FilePtr,
  uint8_t     Length,
  uint16_t    IntValue
  )
{
  char      String[10];

  sprintf (String, "%d", IntValue);

  PrintBlankSpaceBeforeString (FilePtr, Length, String);
}