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

#define GS_FILE_NAME "common/main"

#include "types.h"

extern const char GOODSOUP_VERSION_STR[] = "$VER: goodsoup 0.1 (" __AMIGADATE__ ")";

namespace common
{
	void beginDebug();
	void endDebug();
	void checkMem();

	void test_array();
}

namespace comi
{
	int start();
}

int main(int argc, char** argv)
{
	int rc = 0;
	common::beginDebug();

#if 1
	common::test_array();
#else

	rc = comi::start();
#endif


	common::endDebug();
	common::checkMem();
	return rc;
}