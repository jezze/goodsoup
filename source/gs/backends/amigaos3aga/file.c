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

#include "shared/forward.h"
#include "shared/memory.h"

#include <proto/dos.h>

typedef struct gs_File {
	BPTR handle;
	uint32 pos;
	uint32 length;
} gs_File;

GS_EXPORT gs_File* gs_OpenRead(const char* path) {
	return NULL;
}

GS_EXPORT gs_File* gs_OpenWrite(const char* path) {
	return NULL;
}

GS_EXPORT void gs_Close(gs_File* file) {
	if (file != NULL) {
		Close(file->handle);
		file->handle = 0;
		file->pos = 0;
		file->length = 0;
		gs_Deallocate(file);
	}
}

GS_EXPORT uint32 gs_ReadBytes(gs_File* file, void* data, uint32 length) {
	return 0;	/* TODO */
}

GS_EXPORT byte gs_ReadByte(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT int8 gs_ReadInt8(gs_File* file) {
	return 0;	/* TODO */
}
GS_EXPORT uint8 gs_ReadUInt8(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT int16 gs_ReadInt16_BE(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT uint16 gs_ReadUInt16_BE(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT int16 gs_ReadInt16_LE(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT uint16 gs_ReadUInt16_LE(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT int16 gs_ReadInt16_Native(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT uint16 gs_ReadUInt16_Native(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT int32 gs_ReadInt32_BE(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT uint32 gs_ReadUInt32_BE(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT int32 gs_ReadInt32_LE(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT uint32 gs_ReadUInt32_LE(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT int32 gs_ReadInt32_Native(gs_File* file) {
	return 0;	/* TODO */
}

GS_EXPORT uint32 gs_ReadUInt32_Native(gs_File* file) {
	return 0;	/* TODO */
}
