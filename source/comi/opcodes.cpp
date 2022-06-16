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

#define GS_FILE_NAME "opcodes"

#include "opcodes.h"
#include "vm.h"
#include "context.h"
#include "debug.h"
#include "vm_array.h"

namespace comi
{
	static const uint8 NO_CONTEXT = 0xFF;

#define GS_UNHANDLED_OP(NAME)\
	do {\
		_dumpState();\
		_forceQuit();\
		error(COMI_THIS, "Unhandled Opcode! %lx '%s'", _opcode, NAME);\
	} while(0);

	void VirtualMachine::_step() {
		_opcode = _readByte();
		// debug(COMI_THIS, "%ld : %2lx", _pc-1, (uint32) _opcode);

		switch (_opcode) {
			case OP_00:
				GS_UNHANDLED_OP("OP_00!");
			return;
			case OP_pushWord:
				_pushStack(_readUnsignedWord());
			return;
			case OP_pushWordVar:
				_pushStack(readVar(_readUnsignedWord()));
			return;
			case OP_wordArrayRead:
				GS_UNHANDLED_OP("OP_wordArrayRead!");
			return;
			case OP_wordArrayIndexedRead:
				GS_UNHANDLED_OP("OP_wordArrayIndexedRead!");
			return;
			case OP_dup:
				GS_UNHANDLED_OP("OP_dup!");
			return;
			case OP_pop:
				GS_UNHANDLED_OP("OP_pop!");
			return;
			case OP_not:
				GS_UNHANDLED_OP("OP_not!");
			return;
			case OP_eq: {
				int32 left = _popStack();
				int32 right = _popStack();
				_pushStack(left == right ? 1 : 0);
			}
			return;
			case OP_neq:
				GS_UNHANDLED_OP("OP_neq!");
			return;
			case OP_gt:
				GS_UNHANDLED_OP("OP_gt!");
			return;
			case OP_lt:
				GS_UNHANDLED_OP("OP_lt!");
			return;
			case OP_le:
				GS_UNHANDLED_OP("OP_le!");
			return;
			case OP_ge:
				GS_UNHANDLED_OP("OP_ge!");
			return;
			case OP_add:
				GS_UNHANDLED_OP("OP_add!");
			return;
			case OP_sub:
				GS_UNHANDLED_OP("OP_sub!");
			return;
			case OP_mul:
				GS_UNHANDLED_OP("OP_mul!");
			return;
			case OP_div:
				GS_UNHANDLED_OP("OP_div!");
			return;
			case OP_land: {
				int32 a = _popStack();
				int32 b = _popStack();
				_pushStack(a && b);
			}
			return;
			case OP_lor:
				GS_UNHANDLED_OP("OP_lor!");
			return;
			case OP_band:
				GS_UNHANDLED_OP("OP_band!");
			return;
			case OP_bor:
				GS_UNHANDLED_OP("OP_bor!");
			return;
			case OP_mod:
				GS_UNHANDLED_OP("OP_mod!");
			return;
			case OP_17:
				GS_UNHANDLED_OP("OP_17!");
			return;
			case OP_18:
				GS_UNHANDLED_OP("OP_18!");
			return;
			case OP_19:
				GS_UNHANDLED_OP("OP_19!");
			return;
			case OP_1a:
				GS_UNHANDLED_OP("OP_1a!");
			return;
			case OP_1b:
				GS_UNHANDLED_OP("OP_1b!");
			return;
			case OP_1c:
				GS_UNHANDLED_OP("OP_1c!");
			return;
			case OP_1d:
				GS_UNHANDLED_OP("OP_1d!");
			return;
			case OP_1e:
				GS_UNHANDLED_OP("OP_1e!");
			return;
			case OP_1f:
				GS_UNHANDLED_OP("OP_1f!");
			return;
			case OP_20:
				GS_UNHANDLED_OP("OP_20!");
			return;
			case OP_21:
				GS_UNHANDLED_OP("OP_21!");
			return;
			case OP_22:
				GS_UNHANDLED_OP("OP_22!");
			return;
			case OP_23:
				GS_UNHANDLED_OP("OP_23!");
			return;
			case OP_24:
				GS_UNHANDLED_OP("OP_24!");
			return;
			case OP_25:
				GS_UNHANDLED_OP("OP_25!");
			return;
			case OP_26:
				GS_UNHANDLED_OP("OP_26!");
			return;
			case OP_27:
				GS_UNHANDLED_OP("OP_27!");
			return;
			case OP_28:
				GS_UNHANDLED_OP("OP_28!");
			return;
			case OP_29:
				GS_UNHANDLED_OP("OP_29!");
			return;
			case OP_2a:
				GS_UNHANDLED_OP("OP_2a!");
			return;
			case OP_2b:
				GS_UNHANDLED_OP("OP_2b!");
			return;
			case OP_2c:
				GS_UNHANDLED_OP("OP_2c!");
			return;
			case OP_2d:
				GS_UNHANDLED_OP("OP_2d!");
			return;
			case OP_2e:
				GS_UNHANDLED_OP("OP_2e!");
			return;
			case OP_2f:
				GS_UNHANDLED_OP("OP_2f!");
			return;
			case OP_30:
				GS_UNHANDLED_OP("OP_30!");
			return;
			case OP_31:
				GS_UNHANDLED_OP("OP_31!");
			return;
			case OP_32:
				GS_UNHANDLED_OP("OP_32!");
			return;
			case OP_33:
				GS_UNHANDLED_OP("OP_33!");
			return;
			case OP_34:
				GS_UNHANDLED_OP("OP_34!");
			return;
			case OP_35:
				GS_UNHANDLED_OP("OP_35!");
			return;
			case OP_36:
				GS_UNHANDLED_OP("OP_36!");
			return;
			case OP_37:
				GS_UNHANDLED_OP("OP_37!");
			return;
			case OP_38:
				GS_UNHANDLED_OP("OP_38!");
			return;
			case OP_39:
				GS_UNHANDLED_OP("OP_39!");
			return;
			case OP_3a:
				GS_UNHANDLED_OP("OP_3a!");
			return;
			case OP_3b:
				GS_UNHANDLED_OP("OP_3b!");
			return;
			case OP_3c:
				GS_UNHANDLED_OP("OP_3c!");
			return;
			case OP_3d:
				GS_UNHANDLED_OP("OP_3d!");
			return;
			case OP_3e:
				GS_UNHANDLED_OP("OP_3e!");
			return;
			case OP_3f:
				GS_UNHANDLED_OP("OP_3f!");
			return;
			case OP_40:
				GS_UNHANDLED_OP("OP_40!");
			return;
			case OP_41:
				GS_UNHANDLED_OP("OP_41!");
			return;
			case OP_42:
				GS_UNHANDLED_OP("OP_42!");
			return;
			case OP_43:
				GS_UNHANDLED_OP("OP_43!");
			return;
			case OP_44:
				GS_UNHANDLED_OP("OP_44!");
			return;
			case OP_45:
				GS_UNHANDLED_OP("OP_45!");
			return;
			case OP_46:
				GS_UNHANDLED_OP("OP_46!");
			return;
			case OP_47:
				GS_UNHANDLED_OP("OP_47!");
			return;
			case OP_48:
				GS_UNHANDLED_OP("OP_48!");
			return;
			case OP_49:
				GS_UNHANDLED_OP("OP_49!");
			return;
			case OP_4a:
				GS_UNHANDLED_OP("OP_4a!");
			return;
			case OP_4b:
				GS_UNHANDLED_OP("OP_4b!");
			return;
			case OP_4c:
				GS_UNHANDLED_OP("OP_4c!");
			return;
			case OP_4d:
				GS_UNHANDLED_OP("OP_4d!");
			return;
			case OP_4e:
				GS_UNHANDLED_OP("OP_4e!");
			return;
			case OP_4f:
				GS_UNHANDLED_OP("OP_4f!");
			return;
			case OP_50:
				GS_UNHANDLED_OP("OP_50!");
			return;
			case OP_51:
				GS_UNHANDLED_OP("OP_51!");
			return;
			case OP_52:
				GS_UNHANDLED_OP("OP_52!");
			return;
			case OP_53:
				GS_UNHANDLED_OP("OP_53!");
			return;
			case OP_54:
				GS_UNHANDLED_OP("OP_54!");
			return;
			case OP_55:
				GS_UNHANDLED_OP("OP_55!");
			return;
			case OP_56:
				GS_UNHANDLED_OP("OP_56!");
			return;
			case OP_57:
				GS_UNHANDLED_OP("OP_57!");
			return;
			case OP_58:
				GS_UNHANDLED_OP("OP_58!");
			return;
			case OP_59:
				GS_UNHANDLED_OP("OP_59!");
			return;
			case OP_5a:
				GS_UNHANDLED_OP("OP_5a!");
			return;
			case OP_5b:
				GS_UNHANDLED_OP("OP_5b!");
			return;
			case OP_5c:
				GS_UNHANDLED_OP("OP_5c!");
			return;
			case OP_5d:
				GS_UNHANDLED_OP("OP_5d!");
			return;
			case OP_5e:
				GS_UNHANDLED_OP("OP_5e!");
			return;
			case OP_5f:
				GS_UNHANDLED_OP("OP_5f!");
			return;
			case OP_60:
				GS_UNHANDLED_OP("OP_60!");
			return;
			case OP_61:
				GS_UNHANDLED_OP("OP_61!");
			return;
			case OP_62:
				GS_UNHANDLED_OP("OP_62!");
			return;
			case OP_63:
				GS_UNHANDLED_OP("OP_63!");
			return;
			case OP_if: {
				int32 cond = _popStack();
				int32 relOffset = _readWord();
				
				if (cond != 0) {
					_pc += relOffset;
				}
			}
			return;
			case OP_ifNot: {
				int32 cond = _popStack();
				int32 relOffset = _readWord();
				
				if (cond == 0) {
					_pc += relOffset;
				}
			}
			return;
			case OP_jump: {
				int32 relOffset = _readWord();
				_pc += relOffset;
			}
			return;
			case OP_breakHere:
				GS_UNHANDLED_OP("OP_breakHere!");
			return;
			case OP_delayFrames:
				GS_UNHANDLED_OP("OP_delayFrames!");
			return;
			case OP_wait:
				GS_UNHANDLED_OP("OP_wait!");
			return;
			case OP_delay:
				GS_UNHANDLED_OP("OP_delay!");
			return;
			case OP_delaySeconds:
				GS_UNHANDLED_OP("OP_delaySeconds!");
			return;
			case OP_delayMinutes:
				GS_UNHANDLED_OP("OP_delayMinutes!");
			return;
			case OP_writeWordVar: {
				uint32 varWhere = _readUnsignedWord();
				int32 value = _popStack();
				writeVar(varWhere, value);
			}
			return;
			case OP_wordVarInc:
				GS_UNHANDLED_OP("OP_wordVarInc!");
			return;
			case OP_wordVarDec:
				GS_UNHANDLED_OP("OP_wordVarDec!");
			return;
			case OP_dimArray: {
				byte subOp = _readByte();
				int32 arrayNum = _readUnsignedWord();
				int32 size;

				switch (subOp) {
					case DimArrayOp_NewInt:
						size = _popStack();
						_newArray(arrayNum, AK_Int, 0, size);
					break;
					case DimArrayOp_NewString:
						size = _popStack();
						_newArray(arrayNum, AK_String, 0, size);
					break;
					case DimArrayOp_Delete:
						_deleteArray(arrayNum);
					break;
					default:
						error(COMI_THIS, "Unhandled subop for OP_dimArray %ld", subOp);
						_forceQuit();
					break;
				}
			}
			return;
			case OP_wordArrayWrite:
				GS_UNHANDLED_OP("OP_wordArrayWrite!");
			return;
			case OP_wordArrayInc:
				GS_UNHANDLED_OP("OP_wordArrayInc!");
			return;
			case OP_wordArrayDec:
				GS_UNHANDLED_OP("OP_wordArrayDec!");
			return;
			case OP_dim2dimArray:
				GS_UNHANDLED_OP("OP_dim2dimArray!");
			return;
			case OP_wordArrayIndexedWrite:
				GS_UNHANDLED_OP("OP_wordArrayIndexedWrite!");
			return;
			case OP_arrayOps: {
				byte subOp = _readByte();
				uint32 arrayNum = _readUnsignedWord();
				VmArray* array;
				switch (subOp) {
					case ArrayOps_AssignString: {
						uint16 offset = _popStack();
						uint16 from, len;
						_readStringLength(from, len);
						array = _newArray(arrayNum, VAK_String, 0, len);
						array->writeBytes(
							_script->ptr(from),
							offset,
							len
						);
					}
					return;
					case ArrayOps_AssignScummVarList: {
						int32 list[128];
						/* TODO */
						error(COMI_THIS, "not implemented");
					}
					return;
					case ArrayOps_Assign2DimList: {
						int32 list[128];
						/* TODO */
						error(COMI_THIS, "not implemented");
					}
					return;
				}
			}
			return;
			case OP_77:
				GS_UNHANDLED_OP("OP_77!");
			return;
			case OP_78:
				GS_UNHANDLED_OP("OP_78!");
			return;
			case OP_startScript: {
				int32 args[25];
				uint32 script, flags;

				uint8 count = _readStackList(args, 25);
				script = _popStack();
				flags = _popStack();

				runScript(script, (flags & 1) !=0, (flags & 2) !=0, args, count);
			}
			return;
			case OP_startScriptQuick:
				GS_UNHANDLED_OP("OP_startScriptQuick!");
			return;
			case OP_stopObjectCode:
				_stopObjectCode();
			return;
			case OP_stopScript:
				GS_UNHANDLED_OP("OP_stopScript!");
			return;
			case OP_jumpToScript:
				GS_UNHANDLED_OP("OP_jumpToScript!");
			return;
			case OP_dummy:
				GS_UNHANDLED_OP("OP_dummy!");
			return;
			case OP_startObject:
				GS_UNHANDLED_OP("OP_startObject!");
			return;
			case OP_stopObjectScript:
				GS_UNHANDLED_OP("OP_stopObjectScript!");
			return;
			case OP_cutscene:
				GS_UNHANDLED_OP("OP_cutscene!");
			return;
			case OP_endCutscene:
				GS_UNHANDLED_OP("OP_endCutscene!");
			return;
			case OP_freezeUnfreeze:
				GS_UNHANDLED_OP("OP_freezeUnfreeze!");
			return;
			case OP_beginOverride:
				GS_UNHANDLED_OP("OP_beginOverride!");
			return;
			case OP_endOverride:
				GS_UNHANDLED_OP("OP_endOverride!");
			return;
			case OP_stopSentence:
				GS_UNHANDLED_OP("OP_stopSentence!");
			return;
			case OP_87:
				GS_UNHANDLED_OP("OP_87!");
			return;
			case OP_88:
				GS_UNHANDLED_OP("OP_88!");
			return;
			case OP_setClass:
				GS_UNHANDLED_OP("OP_setClass!");
			return;
			case OP_setState:
				GS_UNHANDLED_OP("OP_setState!");
			return;
			case OP_setOwner:
				GS_UNHANDLED_OP("OP_setOwner!");
			return;
			case OP_panCameraTo:
				GS_UNHANDLED_OP("OP_panCameraTo!");
			return;
			case OP_actorFollowCamera:
				GS_UNHANDLED_OP("OP_actorFollowCamera!");
			return;
			case OP_setCameraAt:
				GS_UNHANDLED_OP("OP_setCameraAt!");
			return;
			case OP_printActor:
				_decodeParseString(0, 1);
			return;
			case OP_printEgo:
				_pushStack(readVar(VAR_EGO));
				_decodeParseString(0, 1);
			return;
			case OP_talkActor:
				GS_UNHANDLED_OP("OP_talkActor!");
			return;
			case OP_talkEgo:
				GS_UNHANDLED_OP("OP_talkEgo!");
			return;
			case OP_printLine:
				_decodeParseString(0, 0);
				return;
			case OP_printText:
				_decodeParseString(1, 0);
			return;
			case OP_printDebug:
				_decodeParseString(2, 0);
			return;
			case OP_printSystem:
				_decodeParseString(3, 0);
			return;
			case OP_blastText:
				GS_UNHANDLED_OP("OP_blastText!");
			return;
			case OP_drawObject:
				GS_UNHANDLED_OP("OP_drawObject!");
			return;
			case OP_99:
				GS_UNHANDLED_OP("OP_99!");
			return;
			case OP_9a:
				GS_UNHANDLED_OP("OP_9a!");
			return;
			case OP_9b:
				GS_UNHANDLED_OP("OP_9b!");
			return;
			case OP_cursorCommand: {
				
				/* UNHANDLED */

				byte param = _readByte();
				warn(COMI_THIS, "Not properly implemented OP_cursorCommand(%ld)", (uint32) param);

				switch (param) {
					case 0xDC:
					break;
					case 0xDD:
					break;
					case 0xDE:
					break;
					case 0xDF:
					break;
					case 0xE0:
					break;
					case 0xE1:
					break;
					case 0xE2:
					break;
					case 0xE3:
					break;
					case 0xE4:
						_popStack();
					break;
					case 0xE5:
						_popStack();
						_popStack();
					break;
					case 0xE6:
						_popStack();
					break;
					case 0xE7:
						_popStack();
					break;
					case 0xE8:
					break;
					case 0xE9:
						_popStack();
						_popStack();
					break;
				}
			}
			return;
			case OP_loadRoom:
				GS_UNHANDLED_OP("OP_loadRoom!");
			return;
			case OP_loadRoomWithEgo:
				GS_UNHANDLED_OP("OP_loadRoomWithEgo!");
			return;
			case OP_walkActorToObj:
				GS_UNHANDLED_OP("OP_walkActorToObj!");
			return;
			case OP_walkActorTo:
				GS_UNHANDLED_OP("OP_walkActorTo!");
			return;
			case OP_putActorAtXY:
				GS_UNHANDLED_OP("OP_putActorAtXY!");
			return;
			case OP_putActorAtObject:
				GS_UNHANDLED_OP("OP_putActorAtObject!");
			return;
			case OP_faceActor:
				GS_UNHANDLED_OP("OP_faceActor!");
			return;
			case OP_animateActor:
				GS_UNHANDLED_OP("OP_animateActor!");
			return;
			case OP_doSentence:
				GS_UNHANDLED_OP("OP_doSentence!");
			return;
			case OP_pickupObject:
				GS_UNHANDLED_OP("OP_pickupObject!");
			return;
			case OP_setBoxFlags:
				GS_UNHANDLED_OP("OP_setBoxFlags!");
			return;
			case OP_createBoxMatrix:
				GS_UNHANDLED_OP("OP_createBoxMatrix!");
			return;
			case OP_a9:
				GS_UNHANDLED_OP("OP_a9!");
			return;
			case OP_resourceRoutines: {
				byte  subOp = _readByte();
				int32 resId = _popStack();

				warn(COMI_THIS, "Not properly implemented OP_resourceRoutines(%ld,%ld)", (uint32) subOp, (uint32) resId);

				/* UNHANDLED */
			}
			return;
			case OP_roomOps:
				GS_UNHANDLED_OP("OP_roomOps!");
			return;
			case OP_actorOps:
				GS_UNHANDLED_OP("OP_actorOps!");
			return;
			case OP_cameraOps:
				GS_UNHANDLED_OP("OP_cameraOps!");
			return;
			case OP_verbOps:
				GS_UNHANDLED_OP("OP_verbOps!");
			return;
			case OP_startSound:
				GS_UNHANDLED_OP("OP_startSound!");
			return;
			case OP_startMusic:
				GS_UNHANDLED_OP("OP_startMusic!");
			return;
			case OP_stopSound:
				GS_UNHANDLED_OP("OP_stopSound!");
			return;
			case OP_soundKludge:
				GS_UNHANDLED_OP("OP_soundKludge!");
			return;
			case OP_systemOps: {
				byte param = _readByte();

				if (param == SystemOps_Quit) {
					_forceQuit();
					info(COMI_THIS, "Quit has been called!");
					return;
				}

				warn(COMI_THIS, "Not properly implemented SysCall! %ld", (uint32)param);
				
				/* UNHANDLED */
			}
			return;
			case OP_saveRestoreVerbs:
				GS_UNHANDLED_OP("OP_saveRestoreVerbs!");
			return;
			case OP_setObjectName:
				GS_UNHANDLED_OP("OP_setObjectName!");
			return;
			case OP_getDateTime:
				GS_UNHANDLED_OP("OP_getDateTime!");
			return;
			case OP_drawBox:
				GS_UNHANDLED_OP("OP_drawBox!");
			return;
			case OP_b8:
				GS_UNHANDLED_OP("OP_b8!");
			return;
			case OP_startVideo:
				GS_UNHANDLED_OP("OP_startVideo!");
			return;
			case OP_kernelSetFunctions: {

				int32 args[30];
				uint8 length = _readStackList(args, 30);
				
				warn(COMI_THIS, "Not properly implemented KernelSetFunctions(%ld,%ld)", (uint32) args[0], length);
				
				/* UNHANDLED */
			}
			return;
			case OP_bb:
				GS_UNHANDLED_OP("OP_bb!");
			return;
			case OP_bc:
				GS_UNHANDLED_OP("OP_bc!");
			return;
			case OP_bd:
				GS_UNHANDLED_OP("OP_bd!");
			return;
			case OP_be:
				GS_UNHANDLED_OP("OP_be!");
			return;
			case OP_bf:
				GS_UNHANDLED_OP("OP_bf!");
			return;
			case OP_c0:
				GS_UNHANDLED_OP("OP_c0!");
			return;
			case OP_c1:
				GS_UNHANDLED_OP("OP_c1!");
			return;
			case OP_c2:
				GS_UNHANDLED_OP("OP_c2!");
			return;
			case OP_c3:
				GS_UNHANDLED_OP("OP_c3!");
			return;
			case OP_c4:
				GS_UNHANDLED_OP("OP_c4!");
			return;
			case OP_c5:
				GS_UNHANDLED_OP("OP_c5!");
			return;
			case OP_c6:
				GS_UNHANDLED_OP("OP_c6!");
			return;
			case OP_c7:
				GS_UNHANDLED_OP("OP_c7!");
			return;
			case OP_startScriptQuick2:
				GS_UNHANDLED_OP("OP_startScriptQuick2!");
			return;
			case OP_startObjectQuick:
				GS_UNHANDLED_OP("OP_startObjectQuick!");
			return;
			case OP_pickOneOf:
				GS_UNHANDLED_OP("OP_pickOneOf!");
			return;
			case OP_pickOneOfDefault:
				GS_UNHANDLED_OP("OP_pickOneOfDefault!");
			return;
			case OP_cc:
				GS_UNHANDLED_OP("OP_cc!");
			return;
			case OP_isAnyOf:
				GS_UNHANDLED_OP("OP_isAnyOf!");
			return;
			case OP_getRandomNumber:
				GS_UNHANDLED_OP("OP_getRandomNumber!");
			return;
			case OP_getRandomNumberRange:
				GS_UNHANDLED_OP("OP_getRandomNumberRange!");
			return;
			case OP_ifClassOfIs:
				GS_UNHANDLED_OP("OP_ifClassOfIs!");
			return;
			case OP_getState:
				GS_UNHANDLED_OP("OP_getState!");
			return;
			case OP_getOwner:
				GS_UNHANDLED_OP("OP_getOwner!");
			return;
			case OP_isScriptRunning:
				GS_UNHANDLED_OP("OP_isScriptRunning!");
			return;
			case OP_d4:
				GS_UNHANDLED_OP("OP_d4!");
			return;
			case OP_isSoundRunning:
				GS_UNHANDLED_OP("OP_isSoundRunning!");
			return;
			case OP_abs:
				GS_UNHANDLED_OP("OP_abs!");
			return;
			case OP_d7:
				GS_UNHANDLED_OP("OP_d7!");
			return;
			case OP_kernelGetFunctions:
				GS_UNHANDLED_OP("OP_kernelGetFunctions!");
			return;
			case OP_isActorInBox:
				GS_UNHANDLED_OP("OP_isActorInBox!");
			return;
			case OP_getVerbEntrypoint:
				GS_UNHANDLED_OP("OP_getVerbEntrypoint!");
			return;
			case OP_getActorFromXY:
				GS_UNHANDLED_OP("OP_getActorFromXY!");
			return;
			case OP_findObject:
				GS_UNHANDLED_OP("OP_findObject!");
			return;
			case OP_getVerbFromXY:
				GS_UNHANDLED_OP("OP_getVerbFromXY!");
			return;
			case OP_de:
				GS_UNHANDLED_OP("OP_de!");
			return;
			case OP_findInventory:
				GS_UNHANDLED_OP("OP_findInventory!");
			return;
			case OP_getInventoryCount:
				GS_UNHANDLED_OP("OP_getInventoryCount!");
			return;
			case OP_getAnimateVariable:
				GS_UNHANDLED_OP("OP_getAnimateVariable!");
			return;
			case OP_getActorRoom:
				GS_UNHANDLED_OP("OP_getActorRoom!");
			return;
			case OP_getActorWalkBox:
				GS_UNHANDLED_OP("OP_getActorWalkBox!");
			return;
			case OP_getActorMoving:
				GS_UNHANDLED_OP("OP_getActorMoving!");
			return;
			case OP_getActorCostume:
				GS_UNHANDLED_OP("OP_getActorCostume!");
			return;
			case OP_getActorScaleX:
				GS_UNHANDLED_OP("OP_getActorScaleX!");
			return;
			case OP_getActorLayer:
				GS_UNHANDLED_OP("OP_getActorLayer!");
			return;
			case OP_getActorElevation:
				GS_UNHANDLED_OP("OP_getActorElevation!");
			return;
			case OP_getActorWidth:
				GS_UNHANDLED_OP("OP_getActorWidth!");
			return;
			case OP_getObjectNewDir:
				GS_UNHANDLED_OP("OP_getObjectNewDir!");
			return;
			case OP_getObjectX:
				GS_UNHANDLED_OP("OP_getObjectX!");
			return;
			case OP_getObjectY:
				GS_UNHANDLED_OP("OP_getObjectY!");
			return;
			case OP_getActorChore:
				GS_UNHANDLED_OP("OP_getActorChore!");
			return;
			case OP_distObjectObject:
				GS_UNHANDLED_OP("OP_distObjectObject!");
			return;
			case OP_distPtPt:
				GS_UNHANDLED_OP("OP_distPtPt!");
			return;
			case OP_getObjectImageX:
				GS_UNHANDLED_OP("OP_getObjectImageX!");
			return;
			case OP_getObjectImageY:
				GS_UNHANDLED_OP("OP_getObjectImageY!");
			return;
			case OP_getObjectImageWidth:
				GS_UNHANDLED_OP("OP_getObjectImageWidth!");
			return;
			case OP_getObjectImageHeight:
				GS_UNHANDLED_OP("OP_getObjectImageHeight!");
			return;
			case OP_f4:
				GS_UNHANDLED_OP("OP_f4!");
			return;
			case OP_f5:
				GS_UNHANDLED_OP("OP_f5!");
			return;
			case OP_getStringWidth:
				GS_UNHANDLED_OP("OP_getStringWidth!");
			return;
			case OP_getActorZPlane:
				GS_UNHANDLED_OP("OP_getActorZPlane!");
			return;
			case OP_f8:
				GS_UNHANDLED_OP("OP_f8!");
			return;
			case OP_f9:
				GS_UNHANDLED_OP("OP_f9!");
			return;
			case OP_fa:
				GS_UNHANDLED_OP("OP_fa!");
			return;
			case OP_fb:
				GS_UNHANDLED_OP("OP_fb!");
			return;
			case OP_fc:
				GS_UNHANDLED_OP("OP_fc!");
			return;
			case OP_fd:
				GS_UNHANDLED_OP("OP_fd!");
			return;
			case OP_fe:
				GS_UNHANDLED_OP("OP_fe!");
			return;
			case OP_ff:
				GS_UNHANDLED_OP("OP_ff!");
			return;
		}
	}

}
