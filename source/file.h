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

#ifndef GS_FILE_H
#define GS_FILE_H

#include "types.h"

#if defined(GS_AMIGA)
#define GS_FILE_HANDLE gs::int32
#else
typedef struct SDL_RWops SDL_RWops;
#define GS_FILE_HANDLE SDL_RWops*
#endif

namespace gs
{

	class ReadFile
	{
	public:

		static ReadFile NullFile;

		ReadFile();
		~ReadFile();

		void open(const char* path, bool throwErrorIsNotOpen = true);
		void close();

		bool isOpen() const;
		bool isEof() const;

		uint32 pos() const;
		uint32 length() const;

		void seek(uint32 position);
		uint32 skip(int32 offset);

		uint32 readFixedStringAsHash(uint8 fixedLength);
		byte readByte();
		uint32 readBytes(void* dst, uint32 length);
		uint16 readUInt16LE();
		uint16 readUInt16BE();
		uint32 readUInt32LE();
		uint32 readUInt32BE();

		int16 readInt16LE();
		int16 readInt16BE();
		int32 readInt32LE();
		int32 readInt32BE();

		void readTag(char* tag);

	protected:
		GS_FILE_HANDLE	_file;
		uint32			_length, _pos;
	};

	class WriteFile
	{
	public:

		WriteFile();
		~WriteFile();

		void open(const char* path);
		void close();

		bool isOpen();

		void writeByte(byte byte);
		void writeBytes(const void* data, uint32 length);

		void writeUInt16LE(uint16 value);
		void writeUInt16BE(uint16 value);
		void writeUInt32LE(uint32 value);
		void writeUInt32BE(uint32 value);

		void writeInt16LE(int16 value);
		void writeInt16BE(int16 value);
		void writeInt32LE(int32 value);
		void writeInt32BE(int32 value);

	protected:
		GS_FILE_HANDLE	_file;
	};

#if !defined(GS_AMIGA)
	class StringAppendFile {

    public:

        StringAppendFile();
        ~StringAppendFile();

        void open(const char* path);
        void close();

        bool isOpen() const;
        bool isEof() const;

        void writeChar(char ch);
        void writeString(const char* str);
        void writeFormat(const char* fmt, ...);
        void writeBytes(const void* dst, uint16 length);

    protected:
        SDL_RWops* _file;
    };
#endif

	bool fileExists(const char* path);

	byte* readFileIntoMemory(const char* path, uint32& length, uint32 comment);

	bool writeFileFromMemory(const char* path, uint32 length, const void* data);

}


#endif
