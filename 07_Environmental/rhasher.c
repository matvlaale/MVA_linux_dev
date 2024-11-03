#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rhash.h>

// #define use_rl 0

#ifdef use_rl
#if use_rl == 1
#include <readline/readline.h>
#endif
#endif

#define base_alloc 128

void make_hash(char *algo, int retval, const char *msg) {
    unsigned flags;
    unsigned char digest[64]; 
    char output[130];
    int type = 1, res = 1;
    if (strcmp(algo, "MD5") == 0 || strcmp(algo, "md5") == 0) {
      flags = RHASH_MD5;
      if (strcmp(algo, "MD5") == 0)
        type = 1;
      else
        type = 2;
    } else if (strcmp(algo, "SHA1") == 0 || strcmp(algo, "sha1") == 0) {
      flags = RHASH_SHA1;
      if (strcmp(algo, "SHA1") == 0)
        type = 1;
      else
        type = 2;
    } else if (strcmp(algo, "TTH") == 0 || strcmp(algo, "tth") == 0) {
      flags = RHASH_TTH;
      if (strcmp(algo, "TTH") == 0)
        type = 1;
      else
        type = 2;
    } else {
      printf("Unknown alogithm\n");
      if (!use_rl)
        printf("> ");
      return;
    }
    if (retval == 2) {
      res = rhash_msg(flags, msg, strlen(msg), digest);
      if (res < 0) {
        fprintf(stderr, "Some problem occured while making hash\n");
        if (!use_rl)
          printf("> ");
        return;
      }
    } else {
      res = rhash_file(flags, msg, digest);
      if (res < 0) {
        fprintf(stderr, "Some problem occured while making hash\n");
        if (!use_rl)
          printf("> ");
        return;
      }
    }
    if (type == 1)
      rhash_print_bytes(output, digest, rhash_get_digest_size(flags),
                        (RHPR_HEX /*| RHPR_UPPERCASE*/));
    else
      rhash_print_bytes(output, digest, rhash_get_digest_size(flags),
                        (RHPR_BASE64 /*| RHPR_UPPERCASE*/));
     
    printf("%s\n", output);
    if (!use_rl)
      printf("> ");
}

int ssplit(char *source, size_t size, char **algo, char **src) { // returns type of src or -1
  int algend = 0, aend = -1;
  for (size_t i = 0; i < size; ++i) {
    if (!algend && i >= base_alloc) {
      return -2;
    } else if (!algend && source[i] == ' ') {
      (*algo)[i] = '\0';
      algend = i;
      continue;
    } else if (source[i] == '\0') {
      aend = i;
      break;
    } else if (source[i] == '\"') {
  	  if (i < 2 || !algend)
  	    return -1;
  	  *src = (char *) malloc((size - i + 1) * sizeof(char));
  	  strcpy(*src, source + i + 1);
  	  for (size_t j = 0; j < size - i + 1; ++j)
  	    if ((*src)[j] == '\n')
  	      (*src)[j] = '\0';
  	  return 2;
  	} else if (!algend)
  	  (*algo)[i] = source[i];
  	else
  	  (*src)[i - algend - 1] = source[i];
  }
  if (!algend)
    return -1;
  if (aend != -1) {
    if (!use_rl)
      (*src)[aend - algend - 2] = '\0';
    else
      (*src)[aend - algend - 1] = '\0';
  } else {
    if (!use_rl)
      (*src)[size - algend - 2] = '\0';
    else
      (*src)[aend - algend - 1] = '\0';
  }
  // printf("%d : %d\n", aend, algend);
  return 1;
}

int main(/*int argc, char **argv*/) {
  int retval = 0;
  char *buffer = (char *) malloc(base_alloc * sizeof(char));
  char *algo = (char *) malloc(base_alloc * sizeof(char)), *src = malloc(1);
  const char *msg;
  size_t bsize = 1;
  rhash_library_init();
  #if use_rl == 0
    printf("> ");
    while(getline(&buffer, &bsize, stdin) != -1) {
      retval = ssplit(buffer, bsize, &algo, &src);
      // printf("%lu: %s\n", bsize, buffer);
      switch (retval) {
       case(-2):
        fprintf(stderr, "Too long algorithm name (>128)\n> ");
        continue;
       case(-1):
        fprintf(stderr, "Usage: [algorithm] [file/string]\n> ");
        continue;
       case(1): // File
        msg = src;
        printf("%s hash for content of %s:\n", algo, src);
        break;
       case(2): // String
        msg = src;
        printf("%s hash for \"%s\":\n", algo, src);
        break;
      }
      make_hash(algo, retval, msg);
    }
  #else
    while((buffer = readline("> ")) != NULL) {
      retval = ssplit(buffer, strlen(buffer), &algo, &src);
      // printf("%lu: %s\n", bsize, buffer);
      switch (retval) {
       case(-2):
        fprintf(stderr, "Too long algorithm name (>128)\n");
        continue;
       case(-1):
        fprintf(stderr, "Usage: [algorithm] [file/string]\n");
        continue;
       case(1): // File
        msg = src;
        printf("%s hash for content of %s:\n", algo, src);
        break;
       case(2): // String
        msg = src;
        printf("%s hash for \"%s\":\n", algo, src);
        break;
      }
      make_hash(algo, retval, msg);
    }
  #endif
  free(src);
  free(algo);
  free(buffer);
  printf("\n");
  return 0;
}
