/***************************************************************************
 * Functions for generalized, in-place byte swapping between LSBF and
 * MSBF byte orders.
 *
 * Some standard C99 integer types are needed, namely uint8_t and
 * uint32_t.  Each function expects its input to be a void pointer to
 * a quantity of the appropriate size.
 *
 * There are two versions of most routines.  The memory aligned versions
 * (gswapXa) are aliases of the other versions (gswapX) provided for backwards
 * compatibility.  There is no difference between them.
 *
 * This file is part of the miniSEED Library.
 *
 * Copyright (c) 2020 Chad Trabant, IRIS Data Management Center
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ***************************************************************************/

#include "libmseed.h"

/* Swap routines that work on any (aligned or not) quantities */

void
ms_gswap2 (void *data2)
{
  uint16_t dat;

  memcpy (&dat, data2, 2);

  dat = ((dat & 0xff00) >> 8) | ((dat & 0x00ff) << 8);

  memcpy (data2, &dat, 2);
}

void
ms_gswap4 (void *data4)
{
  uint32_t dat;

  memcpy (&dat, data4, 4);

  dat = ((dat & 0xff000000) >> 24) | ((dat & 0x000000ff) << 24) |
        ((dat & 0x00ff0000) >>  8) | ((dat & 0x0000ff00) <<  8);

  memcpy (data4, &dat, 4);
}

void
ms_gswap8 (void *data8)
{
  uint64_t dat;

  memcpy (&dat, data8, sizeof(uint64_t));

  dat = ((dat & 0xff00000000000000) >> 56) | ((dat & 0x00000000000000ff) << 56) |
        ((dat & 0x00ff000000000000) >> 40) | ((dat & 0x000000000000ff00) << 40) |
        ((dat & 0x0000ff0000000000) >> 24) | ((dat & 0x0000000000ff0000) << 24) |
        ((dat & 0x000000ff00000000) >>  8) | ((dat & 0x00000000ff000000) <<  8);

  memcpy (data8, &dat, sizeof(uint64_t));
}

/* Swap routines that work on memory aligned quantities are the same as the
 * generic routines. The symbols below exist for backwards compatibility. */

void
ms_gswap2a (void *data2)
{
  ms_gswap2 (data2);
}

void
ms_gswap4a (void *data4)
{
  ms_gswap4 (data4);
}

void
ms_gswap8a (void *data8)
{
  ms_gswap8 (data8);
}
