
#ifndef FILE_IO_H
#define FILE_IO_H


#include <stdlib.h>

#include "CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif



/**
  Opens a file stream

  @param[out] FilePtr     Pointer to the FILE pointer to be populated.
  @param[in]  FileName    Path to the file.
  @param[in]  Mode        Access mode.

  @retval   STATUS_SUCCESS    - if managed to open file stream
  @retval   STATUS_ERROR_     - in case of failure
**/
STATUS
OpenFileStream (
  FILE          **FilePtr,
  const char    *FileName,
  const char    *Mode
  );


/**
  Closes an open file stream

  @param[in]  FilePtr     Pointer to the open FILE stream.
  @param[in]  FileName    Path to the file.

  @retval   STATUS_SUCCESS    - if managed to close file stream
  @retval   STATUS_ERROR_     - in case of failure
**/
STATUS
CloseFileStream (
  FILE          *FilePtr,
  const char    *FileName
  );


#ifdef __cplusplus
}
#endif

#endif    //  FILE_IO_H