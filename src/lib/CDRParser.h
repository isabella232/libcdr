/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* libcdr
 * Version: MPL 1.1 / GPLv2+ / LGPLv2+
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License or as specified alternatively below. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * Major Contributor(s):
 * Copyright (C) 2011 Fridrich Strba <fridrich.strba@bluewin.ch>
 *
 *
 * All Rights Reserved.
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPLv2+"), or
 * the GNU Lesser General Public License Version 2 or later (the "LGPLv2+"),
 * in which case the provisions of the GPLv2+ or the LGPLv2+ are applicable
 * instead of those above.
 */

#ifndef __CDRPARSER_H__
#define __CDRPARSER_H__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <libwpd/libwpd.h>
#include <libwpd-stream/libwpd-stream.h>
#include <libwpg/libwpg.h>

namespace libcdr
{

class CDRCollector;

class CDRParser
{
public:
  explicit CDRParser(WPXInputStream *input, libwpg::WPGPaintInterface *painter);
  virtual ~CDRParser();
  bool parseRecords(WPXInputStream *input, unsigned *blockLengths = 0, unsigned level = 0);

private:
  CDRParser();
  CDRParser(const CDRParser &);
  CDRParser &operator=(const CDRParser &);
  bool parseRecord(WPXInputStream *input, unsigned *blockLengths = 0, unsigned level = 0);
  void readRecord(WPXString fourCC, unsigned length, WPXInputStream *input);

  void readRectangle(WPXInputStream *input);
  void readEllipse(WPXInputStream *input);
  void readLineAndCurve(WPXInputStream *input);
  void readText(WPXInputStream *input);
  void readBitmap(WPXInputStream *input);
  void readTransform(WPXInputStream *input);
  void readFill(WPXInputStream *input);
  void readLine(WPXInputStream *input);

  void _closePage();
  WPXInputStream *m_input;
  libwpg::WPGPaintInterface *m_painter;

  bool m_isListTypePage;
  bool m_isPageOpened;
  unsigned m_version;

};
} // namespace libcdr

#endif // __CDRPARSER_H__
/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
