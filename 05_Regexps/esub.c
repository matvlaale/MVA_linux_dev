#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAXGR 10
#define MAXSUBST 100

void handle_regex_error(int errcode, regex_t *regex) {
  char buffer[256];
  regerror(errcode, regex, buffer, sizeof(buffer));
  printf("Regex error: %s\n", buffer);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: %s <regexp> <substitution> <string>\n", argv[0]);
    return EXIT_FAILURE;
  }
  const char *pattern = argv[1];
  const char *subs = argv[2];
  const char *string = argv[3];
  regex_t regex;
  regmatch_t matches[MAXGR];

  int ret = regcomp(&regex, pattern, REG_EXTENDED);
  if (ret)
    handle_regex_error(ret, &regex);

  ret = regexec(&regex, string, MAXGR, matches, 0);
  if (ret == REG_NOMATCH) {
    printf("%s\n", string);
    regfree(&regex);
    return 0;
  } else if (ret) {
    handle_regex_error(ret, &regex);
  }

  char result[1024] = {0};
  char *r = result;

  size_t prefix_len = matches[0].rm_so;
  strncat(r, string, prefix_len);
  r += prefix_len;
  const char *p = subs;
  while (*p) {
    if (*p == '\\' && *(p + 1) >= '0' && *(p + 1) <= '9') {
      int group = *(p + 1) - '0';
      if (matches[group].rm_so == -1) {
        printf("Invalid group: \\%d\n", group);
        regfree(&regex);
        return EXIT_FAILURE;
      }
      size_t len = matches[group].rm_eo - matches[group].rm_so;
      strncat(r, string + matches[group].rm_so, len);
      r += len;
      p += 2;
    } else if (*p == '\\' && *(p + 1) == '\\') {
      *r++ = '\\';
      p += 2;
    } else {
      *r++ = *p++;
    }
  }
  size_t suffix_len = strlen(string) - matches[0].rm_eo;
  strncat(r, string + matches[0].rm_eo, suffix_len);

  printf("%s\n", result);
  regfree(&regex);
  return 0;
}
