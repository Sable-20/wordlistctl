#include <archive.h>
#include <archive_entry.h>

#include <stdio.h>
#include <stdlib.h>

#include "decompress.h"

static int copy_data(struct archive *ar, struct archive *aw)
{
    int r;

    const void *buf;
    size_t size;
    la_int64_t offset;

    while (1)
    {
        r = archive_read_data_block(ar, &buf, &size, &offset);

        if (r == ARCHIVE_EOF)
            return ARCHIVE_OK;
        if (r != ARCHIVE_OK)
            return r;

        r = archive_write_data_block(aw, buf, size, offset);

        if (r != ARCHIVE_OK)
        {
            fprintf(
                stderr,
                "%s\n",
                archive_error_string(aw));

            return r;
        }
    }
}

int decompress_file(const char *archive_path, const char *destination)
{
   struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;

    int flags;
    int r;

    flags =
        ARCHIVE_EXTRACT_TIME;

    a = archive_read_new();

    archive_read_support_format_tar(a);

    archive_read_support_filter_all(a);

    ext = archive_write_disk_new();

    archive_write_disk_set_options(
        ext,
        flags
    );

    archive_write_disk_set_standard_lookup(
        ext
    );

    if ((r = archive_read_open_filename(
             a,
             archive_path,
             10240)))
    {
        fprintf(
            stderr,
            "Could not open archive\n"
        );

        return 1;
    }

    while (1)
    {
        r = archive_read_next_header(
            a,
            &entry
        );

        if (r == ARCHIVE_EOF)
            break;

        if (r != ARCHIVE_OK)
        {
            fprintf(
                stderr,
                "%s\n",
                archive_error_string(a)
            );

            return 1;
        }

        const char *current =
            archive_entry_pathname(entry);

        char fullpath[1024];

        snprintf(
            fullpath,
            sizeof(fullpath),
            "%s/%s",
            destination,
            current
        );

        archive_entry_set_pathname(
            entry,
            fullpath
        );

        r = archive_write_header(
            ext,
            entry
        );

        if (r != ARCHIVE_OK)
        {
            fprintf(
                stderr,
                "%s\n",
                archive_error_string(ext)
            );
        }
        else
        {
            copy_data(a, ext);
        }

        archive_write_finish_entry(ext);
    }

    archive_read_close(a);
    archive_read_free(a);

    archive_write_close(ext);
    archive_write_free(ext);

    return 0;
}