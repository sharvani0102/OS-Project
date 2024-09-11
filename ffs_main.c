#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include <fuse.h>
#include "ffs_operations.h"
#include "tree.h"


// macros for backward compatibility
#define openDisk(x) openDisk(x, 0)

char *path_to_mount;
int diskfd;

static struct fuse_operations ffs_operations = {
    .getattr    = ffs_getattr,
    .mknod    = ffs_mknod,
    .mkdir      = ffs_mkdir,
    .unlink     = ffs_unlink,
	.rmdir	    = ffs_rmdir,
	.rename	    = ffs_rename,
	.chmod	    = ffs_chmod,
	.chown	    = ffs_chown,
	.truncate   = ffs_truncate,
	.open	    = ffs_open,
	.read	    = ffs_read,
	.write	    = ffs_write,
	.flush	    = ffs_flush,
	.readdir	= ffs_readdir,
	.utime	= ffs_utimens,
};

int main(int argc, char **argv) {
    diskfd = openDisk(argv[argc-1]);
    //init_fs();
	load_fs(diskfd);
    return fuse_main(argc-1, argv, &ffs_operations);
}