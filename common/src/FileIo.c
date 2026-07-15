
#include "FileIo.h"



STATUS
OpenFileStream (
  FILE          **FilePtr,
  const char    *FileName,
  const char    *Mode
  )
{
  if (FilePtr == NULL || FileName == NULL || Mode == NULL) {
    return STATUS_ERROR_INVALID_PARAM;
  }

  *FilePtr = fopen (FileName, Mode);
  if (*FilePtr == NULL) {
    PRINT_ERROR ("Failed to open file: %s\n", FileName);
    return STATUS_ERROR_FILE_OPEN;
  }

  PRINT_INFO ("File opened successfully: %s\n", FileName);

  return STATUS_SUCCESS;
}


STATUS
CloseFileStream (
  FILE          *FilePtr,
  const char    *FileName
  )
{
  if (FilePtr == NULL || FileName == NULL) {
    return STATUS_ERROR_INVALID_PARAM;
  }

  if (fclose (FilePtr) == EOF) {
    PRINT_ERROR ("Failed to close file: %s\n", FileName);
    return STATUS_ERROR_FILE_CLOSE;
  }

  PRINT_INFO ("File closed successfully: %s\n", FileName);

  return STATUS_SUCCESS;
}

