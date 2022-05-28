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

#ifndef COMMON_DEBUG_H
#define COMMON_DEBUG_H

#include "types.h"

namespace common
{
	void verbose(const char* fmt, ...);
	void debug(const char* fmt, ...);
	void info(const char* fmt, ...);
	void warn(const char* fmt, ...);
	void error(const char* fmt, ...);
}

#define assert(X) SDL_assert(X)

#ifndef GS_FILE_NAME
#define GS_FILE_NAME __FILE__
#endif

#define gs_verbose(FMT, ...) ::common::verbose("GS   %s:%i:%s " FMT, GS_FILE_NAME, __LINE__,__FUNCTION__,##__VA_ARGS__)
#define gs_debug(FMT, ...)   ::common::debug("GS   %s:%i:%s " FMT, GS_FILE_NAME, __LINE__,__FUNCTION__,##__VA_ARGS__)
#define gs_info(FMT, ...)    ::common::info("GS   %s:%i:%s " FMT, GS_FILE_NAME, __LINE__, __FUNCTION__,##__VA_ARGS__)
#define gs_warn(FMT, ...)    ::common::warn("GS   %s:%i:%s " FMT, GS_FILE_NAME, __LINE__, __FUNCTION__,##__VA_ARGS__)
#define gs_error(FMT, ...)   ::common::error("GS   %s:%i:%s " FMT, GS_FILE_NAME, __LINE__, __FUNCTION__,##__VA_ARGS__)


#endif
