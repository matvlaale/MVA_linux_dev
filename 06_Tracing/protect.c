#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef int (*origUnlink)(const char *pathname);

int unlink(const char *pathname) {
  origUnlink oUnlink;
  oUnlink = (origUnlink)dlsym(RTLD_NEXT, "unlink");

  if (strstr(pathname, "PROTECT") != NULL)
    return 0;

  return oUnlink(pathname);
}
