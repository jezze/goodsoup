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

#define GS_FILE_NAME "gsv_encoder"

#include "forward.h"
#include "file.h"
#include "video/video_frame.h"
#include "video/video_api.h"

#define GSV_HEADER_BIG "GSVb"
#define GSV_HEADER_LITTLE "GSVl"

namespace gs
{

	static WriteFile* sFile;

	/*
 		General Format of a GSV video file

 			"GSVb"	- 4	- File Header and Version
 			0		- 4	- Offset from beginning to the string table
 			...		- sizeof(VideoEncoderParams) - Video Encoding Params
 			FRME	- 4
			0		- 2 - numAudioSamples
			0		- 2 - numSubtitles
			0		- 1	- hasImageChange
			0		- 1	- hasPaletteChange
			...		- sizeof(VideoTiming) - Timing
			...		- n - 0+ AudioSampleFrame_S16MSB
			...		- n - 0+ SubtitleFrame
			...		- 0 or 307200 - Image Data
			...		- 0 or 768 - Palette Data
			FRME
			...
			FRME
			...
			FRME
 			...
 			STOP
 			<eof>
 	*/

	bool gsv_encoder_initialize(WriteFile* file, const VideoEncoderParams& params) {
		sFile = file;
		sFile->writeTag(GSV_HEADER_BIG);
		sFile->writeBytes(&params, sizeof(VideoEncoderParams));

		return true;
	}

	void gsv_encoder_teardown() {
		sFile->writeTag("STOP");
		/* TODO: STBL - String table */
	}

	static int16 audio_temp[2048];

	static void write_audio_full_rate(AudioSampleFrame_S16MSB* audioSampleFrame) {
		sFile->writeUInt32BE(sizeof(AudioSampleFrame_S16MSB::data));
		sFile->writeBytes(&audioSampleFrame->data[0], sizeof(AudioSampleFrame_S16MSB::data));
	}

	static void write_audio_half_rate(AudioSampleFrame_S16MSB* audioSampleFrame) {
		uint32 length = sizeof(AudioSampleFrame_S16MSB::data) / 2;
		sFile->writeUInt32BE(length);

		int16* src = &audioSampleFrame->data[0];
		int16* dst = &audio_temp[0];
		uint32 count = length;
		while(count--) {
			*dst++ = *src++;
			*dst++ = *src++;
			src += 2;
		}
		sFile->writeBytes(&audio_temp[0], length);
	}

	uint8  gsv_encoder_processFrame(VideoFrame* frame) {
		sFile->writeTag("FRME");
		sFile->writeUInt16BE(frame->_audio.count());
		sFile->writeUInt16BE(frame->_subtitles.count());

		if (frame->_image != NULL) {
			sFile->writeByte(frame->_image->format);
		}
		else {
			sFile->writeByte(IFF_CopyLast);
		}

		sFile->writeByte(frame->_palette != NULL);

		sFile->writeUInt16BE(frame->_timing.num);
		sFile->writeUInt16BE(frame->_timing.length_msec);
		sFile->writeByte(frame->_timing.action);
		sFile->writeByte(frame->_timing.clearFlags);
		sFile->writeByte(frame->_timing.keepSubtitles);
		sFile->writeByte(frame->_timing.reserved);

		AudioSampleFrame_S16MSB* audioSampleFrame = frame->_audio.peekFront();
		while(audioSampleFrame != NULL) {
#if GS_AUDIO_FREQUENCY_HZ == 22050
			write_audio_full_rate(audioSampleFrame);
#else
			write_audio_half_rate(audioSampleFrame);
#endif
			audioSampleFrame = audioSampleFrame->next;
		}

		SubtitleFrame* subtitleFrame = frame->_subtitles.peekFront();
		while(subtitleFrame != NULL) {
			sFile->writeUInt32BE(subtitleFrame->hash);
			sFile->writeUInt16BE(subtitleFrame->length);
			sFile->writeByte(subtitleFrame->flags);
			sFile->writeByte(subtitleFrame->font);
			sFile->writeByte(subtitleFrame->colour);
			sFile->writeByte(subtitleFrame->kind);
			sFile->writeInt16LE(subtitleFrame->x);
			sFile->writeInt16LE(subtitleFrame->y);
			sFile->writeBytes(&subtitleFrame->text[0], subtitleFrame->length + 1);
			subtitleFrame = subtitleFrame->next;
		}

		if (frame->_image != NULL) {
			ImageFrame* image = frame->_image;
			sFile->writeUInt32BE(image->size);
			sFile->writeBytes(image->getData(), image->size);
		}

		if (frame->_palette != NULL) {
			sFile->writeBytes(&frame->_palette->palette[0], sizeof(PaletteFrame::palette));
		}

		return 1;
	}
}

gs::VideoEncoder GSV_ENCODER = {
		&gs::gsv_encoder_initialize,
		&gs::gsv_encoder_teardown,
		&gs::gsv_encoder_processFrame
};