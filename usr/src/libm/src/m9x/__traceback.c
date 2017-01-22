/*
 * This file is covered by the Internet Software Consortium (ISC) License
 * Copyright (C) 2017 by John R. Marino <draco@marino.st>
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sysctl.h>

#define ADDR2LINE_PROG        "/usr/bin/addr2line"
#define MAXIMUM_PATH_LEN      1024
#define MAXIMUM_OUTPUT_LEN    512
#define MAXIMUM_COMMAND_SIZE 1120

char full_path [MAXIMUM_PATH_LEN];
char addr2line_output [MAXIMUM_OUTPUT_LEN];
int  self_path_known = 0;

void
determine_full_path () {
  size_t len = MAXIMUM_PATH_LEN - 1;
  int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };

  if (sysctl(mib, 4, full_path, &len, NULL, 0) == 0) {
    self_path_known = 1;
  }
}

char *
convert_address_to_symbol (char *address) {
  const char *popen_failed = "Failed to popen addr2line";
  char  command[MAXIMUM_COMMAND_SIZE];
  FILE *pipein_fp;
  size_t result_len;

  if (!self_path_known) { determine_full_path(); }
  snprintf(command, sizeof(command),"%s --functions --basenames --pretty-print -e %s 0x%016lx",
           ADDR2LINE_PROG, full_path, (long)address);

  if ((pipein_fp = popen((const char*)command, "re")) == NULL)
  {
    return (char *)popen_failed;
  }
  fgets (addr2line_output, MAXIMUM_OUTPUT_LEN, pipein_fp);
  pclose(pipein_fp);

  /* truncate the line feed that addr2line generates */
  result_len = strlen(addr2line_output);
  if (result_len > 0)
    addr2line_output[result_len - 1] = 0;

  return addr2line_output;
}
