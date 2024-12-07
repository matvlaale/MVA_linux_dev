#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#include "guess.h"

int run_game(int argc, char* argv[]) {
  setlocale(LC_ALL, "");
  bindtextdomain("guess", "/usr/local/share/locale/");
  textdomain("guess");

  int use_roman = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-r") == 0) {
      use_roman = 1;
    } else if (strcmp(argv[i], "--help") == 0) {
      print_help();
      return 0;
    } else if (strcmp(argv[i], "--help-ru") == 0) {
      print_help();
      return 0;
    }
  }

  const char* greet = _("Guess a number from 1 to 100. If it is more than specified one - answer \"%s\", if less than or equal to - answer \"%s\".\n");
  const char* ask_mes = _("Is it greater than %d?\n");
  const char* inval_ans = _("Incorrect answer \"%s\"\n");
  const char* end_mes = _("Your number: %d\n");
  const char* answers[2] = {_("No"), _("Yes")};

  char ans[128];
  int prev = 50, base = 25, last_no = 0, next_stop = 0;
  printf(greet, answers[1], answers[0]);
  for (; 1;) {
    if (use_roman) {
      char* roman_prev = int_to_roman(prev);
      printf(_("Is it greater than %s?\n"), roman_prev);
      free(roman_prev);
    } else {
      printf(ask_mes, prev);
    }
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
  if (use_roman) {
    char* roman_result = int_to_roman(prev);
    printf(_("Your number: %s\n"), roman_result);
    free(roman_result);
  } else {
    printf(end_mes, prev);
  }

  return 0;
}

char* int_to_roman(int num) {
  char* result = malloc(8 * sizeof(char));
  strcpy(result, roman_table[num - 1]);
  return result;
}

int roman_to_int(const char* roman) {
  for (int i = 0; i < 100; ++i) {
    if (strcmp(roman, roman_table[i]) == 0) {
      return i + 1;
    }
  }
  return -1;
}

void print_help() {
    printf(_("Usage: guess [params]\n"));
    printf(_("Parameters:\n"));
    printf(_("  -r          Use Roman numbers\n"));
    printf(_("  --help      Show this help message\n"));
}
