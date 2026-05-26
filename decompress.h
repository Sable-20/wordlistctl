#ifndef DECOMPRESS_H_
#define DECOMPRESS_H_

/**
 * Decompresses a tar archive to the specified destination directory
 * 
 * This function uses the `libarchive` library to read a tar archive and extract its contents to the specified destination directory. It handles various archive formats and filters, and ensures that the extracted files are saved with their original timestamps and permissions.
 * 
 * @param archive_path The path to the tar archive to be decompressed
 * @param destination The directory where the contents of the archive will be extracted
 * @return 0 on success, 1 on failure
 */
int decompress_file(const char* archive_path, const char* destination);

#endif // DECOMPRESS_H_