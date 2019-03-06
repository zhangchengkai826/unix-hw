#include "common.h"
#include <sys/mman.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[]) {
  int fd_s, fd_d;
  struct stat st_s, st_d;
  void *mp_s, *mp_d;

  if(argc != 3)
    err_quit("usage: ./tcp <source> <target>");
  if((fd_s = open(argv[1], O_RDONLY)) < 0)
    err_sys("open error");
  if(fstat(fd_s, &st_s) < 0)
    err_sys("fstat src error");
  if(stat(argv[2], &st_d) < 0) { /* if dest does not exist */
    if((fd_d = creat(argv[2], st_s.st_mode)) < 0) 
      err_sys("can't creat %s", argv[2]);
  } else if(!S_ISDIR(st_d.st_mode)) { /* if dest exist and it's not a dir */
    if(st_s.st_ino == st_d.st_ino) /* if src & dest are hard-linked */
      err_quit("copy between hard links is not allowed");
    if((fd_d = creat(argv[2], st_s.st_mode)) < 0) 
      err_sys("can't creat %s", argv[2]);
  } else { /* if dest exist and it's a dir */
    size_t sizep;
    char *npath = path_alloc(&sizep);
    char *src_no_ext = strrchr(argv[1], '/');
    if(src_no_ext == NULL)
      src_no_ext = argv[1];
    else
      src_no_ext += 1; /* remove leading '/' */
    sprintf(npath, "%s/%s", argv[2], src_no_ext); /* contruct new dest path */
    if((fd_d = creat(npath, st_s.st_mode)) < 0) 
      err_sys("can't creat %s", npath);
    free(npath);
  }

  mp_s = mmap(NULL, st_s.st_size, PROT_READ, MAP_PRIVATE, fd_s, 0); /* copy via mmap(2) & memcpy(3) */
  mp_d = mmap(NULL, st_s.st_size, PROT_WRITE, MAP_PRIVATE, fd_d, 0);
  memcpy(mp_d, mp_s, st_s.st_size);
  /* mem maps are automatically umaped when process terminate, so no need to explicitly munmap(2) them here */
  
  exit(0);
}

