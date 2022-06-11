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

#ifndef COMI_INDEX_H
#define COMI_INDEX_H

#include "common/types.h"
#include "common/buffer.h"
#include "common/file.h"

#include "resource.h"
#include "constants.h"
#include "common/string.h"

using namespace common;

namespace comi
{
	class Index;

	extern Index* INDEX;

	template<int Kind, uint16 Capacity>
	class ResourceIndexTable {
	public:

		void reset() {
			clearMemoryNonAllocated(_roomNum, sizeof(_roomNum));
			clearMemoryNonAllocated(_offset, sizeof(_offset));
		}

		const char* _name;
		uint8  _roomNum[Capacity];
		uint32 _offset[Capacity];
	};


	struct ObjectLocation
	{
		String  _name;
		byte   _state;
		byte   _room;
		byte   _owner;
		byte   _padding;
		uint32 _class;
	};

	class ObjectLocationTable
	{
	public:
		void reset();

		ObjectLocation	_objects[NUM_OBJECT_GLOBALS];
	};


	class Index
	{
	public:

		Index();
		~Index();

		bool readFromFile(const char* path);

	private:

		struct ArraySpec
		{
			uint16 num, a, b;
		};

		String					    _roomNames[NUM_ROOMS + 1];
		ResourceIndexTable<RK_ROOM, NUM_ROOMS>		_roomsResources;
		ResourceIndexTable<RK_SCRIPT, NUM_ROOMS>		_roomsScriptsResources;
		ResourceIndexTable<RK_SCRIPT, NUM_SCRIPTS>	_scriptsResources;
		ResourceIndexTable<RK_SOUND, NUM_SOUNDS>	_soundsResources;
		ResourceIndexTable<RK_COSTUME, NUM_COSTUMES>	_costumesResources;
		ResourceIndexTable<RK_CHARSET, NUM_CHARSETS>	_charsetResources;
		ObjectLocationTable					_objectTable;
		ArraySpec					_arraySpec[NUM_AARY];

	};
}

#endif