
#ifndef FILE_IO_H
#define FILE_IO_H


#include <stdlib.h>

#include "CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif



/**
  @brief Opens a file stream

  @param[out]   FilePtr     Pointer to the FILE pointer to be populated.
  @param[in]    FileName    Path to the file.
  @param[in]    Mode        Access mode.

  @return   STATUS_SUCCESS, or appropriate error code.
**/
Status OpenFileStream (
  FILE          **FilePtr,
  const char    *FileName,
  const char    *Mode
  );


/**
  @brief Closes an open file stream

  @param[in]    FilePtr     Pointer to the open FILE stream.
  @param[in]    FileName    Path to the file.

  @return   STATUS_SUCCESS, or appropriate error code.
**/
Status CloseFileStream (
  FILE          *FilePtr,
  const char    *FileName
  );


#ifdef __cplusplus
}
#endif

#endif    //  FILE_IO_H