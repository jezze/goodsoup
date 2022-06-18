/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef COMI_UTILS_H
#define COMI_UTILS_H

#include "common/types.h"
#include "debug.h"

namespace comi
{
	inline void checkRange(int max, int min, int no, const char* str) {
		if (no < min || no > max) {
			::common::error(COMI_THIS, "Value %d is out of bounds (%d,%d) (%s)", no, max, min, str);
		}
	}

	inline bool tagEqual(char tagName[5], char a, char b, char c, char d) {
		return (tagName[0] == a && tagName[1] == b && tagName[2] == c && tagName[3] == d);
	}

	uint32 getRandom(uint32 max);

	uint32 getRandomRange(uint32 min, uint32 max);
}

#endif