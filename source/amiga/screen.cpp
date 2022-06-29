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

#define GS_FILE_NAME "screen"

#include "types_amiga.h"
#include "../debug.h"
#include "../profile.h"
#include "../globals.h"
#include "../functions.h"
#include "../room.h"

#include "timer_amiga.h"
#include "cursor_amiga.h"

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <proto/cybergraphics.h>
#include <proto/graphics.h>
#include <proto/datatypes.h>

#include <intuition/intuition.h>
#include <intuition/screens.h>
#include <cybergraphx/cybergraphics.h>

#include <datatypes/datatypes.h>
#include <datatypes/datatypesclass.h>
#include <datatypes/pictureclass.h>
#include <graphics/gfx.h>
#include <graphics/scale.h>
#include <graphics/displayinfo.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>


#define GS_AMIGA_TEXT(NAME, STR)\
	struct IntuiText NAME = { 0, 1, JAM2, 4, 2, NULL, (UBYTE*) STR, NULL }
#define GS_AMIGA_MENU_ITEM(NAME, TEXT, PREV, Y)\
	struct MenuItem NAME = { PREV, 0, Y, 48, 12, ITEMTEXT|ITEMENABLED|HIGHCOMP, 0, (APTR) TEXT, (APTR) TEXT, NULL, NULL, 0 }
#define GS_AMIGA_MENU(NAME, TEXT, FIRST_CHILD)\
	struct Menu NAME = { NULL, 0, 0, 48, 12, MENUENABLED, (BYTE*) TEXT, FIRST_CHILD, 0, 0, 0, 0 }

namespace gs
{
	typedef VOID(*PUTCHARPROC)();

	struct Screen* sScreen;
	struct Window* sWindow;
	struct ScreenBuffer* sScreenBuffer;
	struct RastPort sRastPort;
	SystemTimer sSystemTimer;

	static const uint32 PutChar = 0x16c04e75;

	struct TextAttr sDefaultFont =
	{
		(STRPTR) "topaz.font", 		/* Name */
		8, 				/* YSize */
		FS_NORMAL,			/* Style */
		FPF_ROMFONT | FPF_DESIGNED,	/* Flags */
	};

	GS_AMIGA_TEXT(TEXT_Unpause, "Resume");
	GS_AMIGA_TEXT(TEXT_Quit, "Quit");
	GS_AMIGA_MENU_ITEM(MENUITEM_Unpause, &TEXT_Unpause, NULL, 0);
	GS_AMIGA_MENU_ITEM(MENUITEM_Quit, &TEXT_Quit, &MENUITEM_Unpause, 12);

	GS_AMIGA_MENU(MENU_Game, GS_GAME_NAME, &MENUITEM_Quit);
	
	void drawSystemText(uint8 colour, uint16 x, uint16 y, const char* text);

	bool openScreen() {

		uint32 modeId = BestCModeIDTags(
			CYBRBIDTG_NominalWidth, GS_SCREEN_WIDTH,
			CYBRBIDTG_NominalHeight, GS_SCREEN_HEIGHT,
			CYBRBIDTG_Depth, GS_SCREEN_DEPTH,
			TAG_DONE
		);

		if (modeId == INVALID_ID) {
			error(GS_THIS, "Could not find suitable screen mode for %ldx%ldx%ld!", GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, GS_SCREEN_DEPTH);
			return false;
		}

		sScreen = OpenScreenTags(NULL,
			SA_DisplayID, modeId,
			SA_Left, 0,
			SA_Top, 0,
			SA_Width, GS_SCREEN_WIDTH,
			SA_Height, GS_SCREEN_HEIGHT,
			SA_Depth, GS_SCREEN_DEPTH,
			SA_Title, (ULONG) GS_GAME_NAME,
			SA_ShowTitle, FALSE,
			SA_Type, CUSTOMSCREEN,
			SA_Font, (ULONG) &sDefaultFont,
			TAG_DONE
		);

		if (sScreen == NULL) {
			error(GS_THIS, "Could open Screen for %ldx%ldx%ld!", GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, GS_SCREEN_DEPTH);
			return false;
		}
		
		sScreenBuffer = AllocScreenBuffer(
			sScreen,
			NULL,
			SB_SCREEN_BITMAP
		);

		if (sScreenBuffer == NULL)
		{
			error(GS_THIS, "Could open ScreenBuffer for %ldx%ldx%ld!", GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, GS_SCREEN_DEPTH);
			return false;
		}

		InitRastPort(&sRastPort);
		sRastPort.BitMap = sScreenBuffer->sb_BitMap;

		sWindow = OpenWindowTags(NULL,
			WA_Left, 0,
			WA_Top, 0,
			WA_Width, GS_SCREEN_WIDTH,
			WA_Height, GS_SCREEN_HEIGHT,
			WA_CustomScreen, (ULONG)sScreen,
			WA_Backdrop, TRUE,
			WA_Borderless, TRUE,
			WA_DragBar, FALSE,
			WA_Activate, TRUE,
			WA_SimpleRefresh, TRUE,
			WA_CloseGadget, FALSE,
			WA_DepthGadget, FALSE,
			WA_IDCMP, IDCMP_CLOSEWINDOW | IDCMP_VANILLAKEY | IDCMP_IDCMPUPDATE | IDCMP_MOUSEBUTTONS,
			TAG_END
		);
		
		if (sWindow == NULL)
		{
			error(GS_THIS, "Could open Window for %ldx%ldx%ld!", GS_SCREEN_WIDTH, GS_SCREEN_HEIGHT, GS_SCREEN_DEPTH);
			return false;
		}
		
		if (sSystemTimer.open() == false) {
			return false;
		}

		openAmigaCursor(sWindow);

		return true;
	}

	bool closeScreen() {

		closeAmigaCursor();
		
		sSystemTimer.close();

		if (sScreenBuffer && sScreen)
		{
			FreeScreenBuffer(sScreen, sScreenBuffer);
			sScreenBuffer = NULL;
		}

		if (sWindow)
		{
			CloseWindow(sWindow);
			sWindow = NULL;
		}

		if (sScreen)
		{
			CloseScreen(sScreen);
			sScreen = NULL;
		}

		return true;
	}

	void screenLoop() {

		uint32 timerBit = sSystemTimer.start(GS_FRAME_DELAY_MSEC); // 1/30 seconds in microseconds.
		uint32 windowBit = (1 << sWindow->UserPort->mp_SigBit);

		debug(GS_THIS, "Signal bit = %lx", timerBit);

		uint32 signalBits = windowBit | timerBit | SIGBREAKF_CTRL_C;

		while (QUIT_NOW == false) {

			ULONG signal = Wait(signalBits);

			if (signal & SIGBREAKF_CTRL_C) {
				QUIT_NOW = true;
				break;
			}
			
			if (signal & windowBit) {

				struct IntuiMessage* msg;
				bool step = false;

				while (true)
				{
					msg = (struct IntuiMessage*)GetMsg(sWindow->UserPort);

					if (msg == NULL)
						break;

					struct TagItem* tstate, * tag, * tags;
					ULONG tiData;

					switch (msg->Class)
					{
						case IDCMP_CLOSEWINDOW: {
							QUIT_NOW = true;
						}
						break;
						case IDCMP_VANILLAKEY: {
							if (msg->Code == 27) {
								QUIT_NOW = true;
							}
							else if (msg->Code == 32) {
								togglePause();
								step = false;
							}
							else if (PAUSED && (msg->Code == 115 || msg->Code == 83)) {
								debug(GS_THIS, "Frame Step");
								runFrame();
							}
						}
						break;
						case IDCMP_MENUPICK: {
						
							uint16 menuNum = MENUNUM((msg->Code));
							uint16 itemNum = ITEMNUM((msg->Code));

							if (menuNum == 0) {
								if (itemNum == 1) {
									togglePause();
									step = false;
								}
								else if (itemNum == 0) {
									QUIT_NOW = true;
								}
							}
						}
						break;
						case IDCMP_MOUSEBUTTONS: {
							MOUSE_X = msg->MouseX;
							MOUSE_Y = msg->MouseY;

							if (msg->Code == SELECTUP) {
								MOUSE_LMB_STATE = 1;
							}
							else {
								MOUSE_LMB_STATE = -1;
							}

							if (msg->Code == MENUUP) {
								MOUSE_RMB_STATE = 1;
							}
							else {
								MOUSE_RMB_STATE = -1;
							}
						}
						break;
					}
					ReplyMsg((struct Message*)msg);
				}
			}
			
			if (signal & timerBit) {

				

				if (sSystemTimer.isReady()) {
					if (PAUSED == false) {
						runFrame();
					}

					sSystemTimer.start(GS_FRAME_DELAY_MSEC);
				}
			}

		}

		sSystemTimer.close();
	}
	
	void clearScreen(uint8 colour) {
		SetRast(&sRastPort, colour);
	}

	void drawSystemText(uint8 colour, uint16 x, uint16 y, const char* text) {
		struct IntuiText  intText;
		intText.FrontPen = 1;
		intText.BackPen = 0;
		intText.DrawMode = JAM2;
		intText.LeftEdge = 0;
		intText.TopEdge = 0;
		intText.ITextFont = &sDefaultFont;
		intText.IText = (UBYTE*) text;
		intText.NextText = NULL;

		
		PrintIText(&sRastPort, &intText, x, y);
	}

	void drawSystemTextF(uint8 colour, uint16 x, uint16 y, const char* fmt, ...) {
		static char sTemp[256] = {};
		const char* arg = (const char*)(&fmt + 1);
		RawDoFmt((CONST_STRPTR)fmt, (APTR)arg, (PUTCHARPROC)&PutChar, &sTemp[0]);

		drawSystemText(colour, x, y, &sTemp[0]);
	}

	void drawBox(uint8 colour, uint16 x, uint16 y, uint16 w, uint16 h) {
		FillPixelArray(&sRastPort, x, y, w, h, colour);
	}
	
	void togglePause() {
		
		PAUSED = !PAUSED;

		if (PAUSED == true) {
			SetMenuStrip (sWindow, &MENU_Game);
			
			ModifyIDCMP(sWindow, IDCMP_IDCMPUPDATE | IDCMP_VANILLAKEY | IDCMP_MENUPICK);

			if (SHOW_OSD) {
				runOSD();
			}

		}
		else {
			ClearMenuStrip(sWindow);
			ModifyIDCMP(sWindow, IDCMP_CLOSEWINDOW | IDCMP_VANILLAKEY | IDCMP_IDCMPUPDATE | IDCMP_MOUSEBUTTONS);
		}

	}
	
	void setCursor(CursorKind type) {

	}
	
	void drawRoomBackground(RoomData* roomData) {

	}
}