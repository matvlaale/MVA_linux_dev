#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main() {
  setlocale(LC_ALL, "");
  bindtextdomain("guess", "./po");
  textdomain("guess");
  const char* greet = _("Guess a number from 1 to 100. If it is more than specified one - answer \"%s\", if less than or equal to - answer \"%s\".\n");
  const char* ask_mes = _("Is is greater than %d?\n");
  const char* inval_ans = _("Incorrect answer \"%s\"\n");
  const char* end_mes = _("Your number: %d\n");
  const char* answers[2] = {_("No"), _("Yes")};

  char ans[128];
  int prev = 50, base = 25, last_no = 0, next_stop = 0;
  printf(greet, answers[1], answers[0]);
  for (;1;) {
    printf(ask_mes, prev);
    scanf("%128s", ans);
    if (!strcmp(ans, answers[0])) {
      prev = prev - base;
      last_no = 1;
    } else if (!strcmp(ans, answers[1])) {
      prev = prev + base;
      last_no = 0;
    } else {
      printf(inval_ans, ans);
      continue;
    }
    if (next_stop && base == 1) {
      prev += last_no;
      break;
      // next_stop = 1;
    } else if (prev < 0) {
      prev = 1;
      break;
    } else if (prev > 100) {
      prev = 100;
      break;
    } else if (base == 1) {
      next_stop = 1;
    }
    base = base / 2 + base % 2;
  }
  printf(end_mes, prev);

  return 0;
}
