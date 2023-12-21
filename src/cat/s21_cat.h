#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 4096

typedef struct {
  unsigned int b;  //только неотрцательные целые значения
  unsigned int e;
  unsigned int E;
  unsigned int n;
  unsigned int s;
  unsigned int t;
  unsigned int T;
  unsigned int v;
} cat_options;

static struct option long_option[] = {{"number", 0, 0, 'n'},
                                      {"squeeze-blank", 0, 0, 's'},
                                      {"number-nonblank", 0, 0, 'b'},
                                      {0, 0, 0, 0}};

int cat_read(char **argv, cat_options *flag);
int cat_parser(int argc, char *argv[], cat_options *flag);

#endif  // SRC_CAT_S21_CAT_H_

// Flags = read_flags(argc, argv, short_options, long_options, NULL,
//                      &cat_flag_switch); мой opt