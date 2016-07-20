/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libcdr project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <librevenge/librevenge.h>
#include <librevenge-generators/librevenge-generators.h>
#include <librevenge-stream/librevenge-stream.h>
#include <libcdr/libcdr.h>

#ifndef VERSION
#define VERSION "UNKNOWN VERSION"
#endif

namespace
{

int printUsage()
{
  printf("`cdr2raw' is used to test import of CorelDRAW documents in libcdr.\n");
  printf("\n");
  printf("Usage: cdr2raw [OPTION] FILE\n");
  printf("\n");
  printf("Options:\n");
  printf("\t--callgraph           display the call graph nesting level\n");
  printf("\t--help                show this help message\n");
  printf("\t--version             show version information and exit\n");
  printf("\n");
  printf("Report bugs to <https://bugs.documentfoundation.org/>.\n");
  return -1;
}

int printVersion()
{
  printf("cdr2raw " VERSION "\n");
  return 0;
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  bool printIndentLevel = false;
  char *file = 0;

  if (argc < 2)
    return printUsage();

  for (int i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "--callgraph"))
      printIndentLevel = true;
    else if (!strcmp(argv[i], "--version"))
      return printVersion();
    else if (!file && strncmp(argv[i], "--", 2))
      file = argv[i];
    else
      return printUsage();
  }

  if (!file)
    return printUsage();

  librevenge::RVNGFileStream input(file);
  librevenge::RVNGRawDrawingGenerator painter(printIndentLevel);

  if (!libcdr::CDRDocument::isSupported(&input))
  {
    if (!libcdr::CMXDocument::isSupported(&input))
    {
      fprintf(stderr, "ERROR: Unsupported file format!\n");
      return 1;
    }

    libcdr::CMXDocument::parse(&input, &painter);

    return 0;
  }

  libcdr::CDRDocument::parse(&input, &painter);

  return 0;
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
