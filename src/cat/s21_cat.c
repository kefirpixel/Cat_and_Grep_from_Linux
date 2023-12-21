#include "s21_cat.h"

int cat_parser(int argc, char *argv[], cat_options *flag) {
  int error = 0;
  int options = 0;
  int option_index = 0;
  while ((options = getopt_long(argc, argv, "+bevnstET", long_option,
                                &option_index)) != -1) {
    switch (options) {
      case 'E':
        flag->e = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->v = 1;
        flag->t = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      default: /* '?' */
        error = 1;
        break;
      case '?':
        printf("usage: s21_cat [-benstvTE?] [file ...]\n");
        error = 1;
    }
  }
  return error;
}

int cat_read(char **argv, cat_options *flag) {
  int error = 0;
  FILE *file = fopen(argv[optind], "rb");
  if (file != NULL) {
    int emp_str_cnt = 0;
    int str_cnt = 0;
    int previous_symbol = '\n';
    while (true) {
      int current_symbol = fgetc(file);
      if (current_symbol == EOF) break;
      if (flag->s && current_symbol == '\n' && previous_symbol == '\n') {
        emp_str_cnt++;
        if (emp_str_cnt > 1) continue;
      } else {
        emp_str_cnt = 0;
      }
      if (previous_symbol == '\n' &&
          ((flag->b && current_symbol != '\n') || flag->n)) {
        str_cnt++;
        printf("%6d\t", str_cnt);
      }
      if (flag->e && current_symbol == '\n') printf("$");
      if (flag->t && current_symbol == '\t') {
        printf("^");
        current_symbol = 'I';
      }
      if (flag->v) {
        if ((current_symbol >= 0 && current_symbol <= 8) ||
            (current_symbol >= 11 && current_symbol <= 31)) {
          printf("^");
          current_symbol = current_symbol + 64;
        }
        if (current_symbol == 127) {
          printf("^");
          current_symbol = current_symbol - 64;
        }
      }
      printf("%c", current_symbol);
      previous_symbol = current_symbol;
    }
    fclose(file);
  } else {
    error = 2;
  }
  return error;
}

int main(int argc, char *argv[]) {
  int error;
  cat_options flag = {0};
  error = cat_parser(argc, argv, &flag);
  if (error != 1) {
    if (flag.b) flag.n = 0;
    while (optind < argc) {
      if ((error = cat_read(argv, &flag)) == 2)
        fprintf(stderr, "%s: %s: %s\n", argv[0], argv[optind], strerror(error));
      optind++;
    }
  }
  return error;
}