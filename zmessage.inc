/*

	About: Multi-line message system
	Author: ziggi

*/

#if !defined _samp_included
	#error Please include a_samp or a_npc before zlang
#endif

#if defined _zmsg_included
	#endinput
#endif

#define _zmsg_included

/*
	Defines
*/

#if !defined ZMSG_MAX_CHAT_LENGTH
	#define ZMSG_MAX_CHAT_LENGTH MAX_CHATBUBBLE_LENGTH
#endif

#if !defined ZMSG_MAX_PLAYER_CHAT_LENGTH
	#define ZMSG_MAX_PLAYER_CHAT_LENGTH (MAX_CHATBUBBLE_LENGTH / 2)
#endif

#if !defined ZMSG_SEPARATORS_LIST
	#define ZMSG_SEPARATORS_LIST ' '
#endif

/*
	Functions
*/

static stock Zmsg_ShiftStartPos(const message[], const pos, const bool:is_packed, const size = sizeof(message))
{
	new result_pos = pos;

	if (is_packed) {
		while (result_pos < size) {
			switch (message{result_pos}) {
				case ZMSG_SEPARATORS_LIST: {
					result_pos++;
				}
				default: {
					break;
				}
			}
		}
	} else {
		while (result_pos < size) {
			switch (message[result_pos]) {
				case ZMSG_SEPARATORS_LIST: {
					result_pos++;
				}
				default: {
					break;
				}
			}
		}
	}
	return result_pos;
}

static stock Zmsg_ShiftEndPos(const message[], const pos, const bool:is_packed)
{
	new result_pos = pos;

	if (is_packed) {
		while (result_pos > 0) {
			switch (message{result_pos}) {
				case ZMSG_SEPARATORS_LIST: {
					break;
				}
				default: {
					result_pos--;
				}
			}
		}
	} else {
		while (result_pos > 0) {
			switch (message[result_pos]) {
				case ZMSG_SEPARATORS_LIST: {
					break;
				}
				default: {
					result_pos--;
				}
			}
		}
	}
	return result_pos;
}

/*
	SendClientMessage
*/

stock ZMsg_SendClientMessage(playerid, color, message[])
{
	new length = strlen(message);

	// shouldn't be shifted
	if (length <= ZMSG_MAX_CHAT_LENGTH) {
		return SendClientMessage(playerid, color, message);
	}

	new
		bool:is_packed,
		result,
		temp,
		temp_string[(ZMSG_MAX_CHAT_LENGTH + 1) char],
		start_pos,
		end_pos;

	is_packed = message{0} != 0;

	while (end_pos <= length) {
		// get pos
		start_pos = Zmsg_ShiftStartPos(message, end_pos, is_packed, length);
		end_pos = start_pos + ZMSG_MAX_CHAT_LENGTH;

		if (is_packed) {
			if (end_pos >= length) {
				strmid(temp_string, message, start_pos, length);
				return SendClientMessage(playerid, color, temp_string);
			}

			end_pos = Zmsg_ShiftEndPos(message, end_pos, is_packed);

			// prepare string and print
			strmid(temp_string, message, start_pos, end_pos);
			temp_string{end_pos - start_pos} = '\0';
			result = SendClientMessage(playerid, color, temp_string);
		} else {
			if (end_pos >= length) {
				return SendClientMessage(playerid, color, message[start_pos]);
			}

			end_pos = Zmsg_ShiftEndPos(message, end_pos, is_packed);

			// prepare string and print
			temp = message[end_pos];
			message[end_pos] = '\0';

			result = SendClientMessage(playerid, color, message[start_pos]);

			message[end_pos] = temp;
		}
	}
	return result;
}
#if defined _ALS_SendClientMessage
	#undef SendClientMessage
#else
	#define _ALS_SendClientMessage
#endif

#define SendClientMessage ZMsg_SendClientMessage

/*
	SendClientMessageToAll
*/

stock ZMsg_SendClientMessageToAll(color, message[])
{
	new length = strlen(message);

	// shouldn't be shifted
	if (length <= ZMSG_MAX_CHAT_LENGTH) {
		return SendClientMessageToAll(color, message);
	}

	new
		bool:is_packed,
		result,
		temp,
		temp_string[(ZMSG_MAX_CHAT_LENGTH + 1) char],
		start_pos,
		end_pos;

	is_packed = message{0} != 0;

	while (end_pos <= length) {
		// get pos
		start_pos = Zmsg_ShiftStartPos(message, end_pos, is_packed, length);
		end_pos = start_pos + ZMSG_MAX_CHAT_LENGTH;

		if (is_packed) {
			if (end_pos >= length) {
				strmid(temp_string, message, start_pos, length);
				return SendClientMessageToAll(color, temp_string);
			}

			end_pos = Zmsg_ShiftEndPos(message, end_pos, is_packed);

			// prepare string and print
			strmid(temp_string, message, start_pos, end_pos);
			temp_string{end_pos - start_pos} = '\0';
			result = SendClientMessageToAll(color, temp_string);
		} else {
			if (end_pos >= length) {
				return SendClientMessageToAll(color, message[start_pos]);
			}

			end_pos = Zmsg_ShiftEndPos(message, end_pos, is_packed);

			// prepare string and print
			temp = message[end_pos];
			message[end_pos] = '\0';

			result = SendClientMessageToAll(color, message[start_pos]);

			message[end_pos] = temp;
		}
	}
	return result;
}
#if defined _ALS_SendClientMessageToAll
	#undef SendClientMessageToAll
#else
	#define _ALS_SendClientMessageToAll
#endif

#define SendClientMessageToAll ZMsg_SendClientMessageToAll

/*
	SendPlayerMessageToPlayer
*/

stock ZMsg_SendPlayerMessageToPlayer(playerid, senderid, message[])
{
	new length = strlen(message);

	// shouldn't be shifted
	if (length <= ZMSG_MAX_PLAYER_CHAT_LENGTH) {
		return SendPlayerMessageToPlayer(playerid, senderid, message);
	}

	new
		bool:is_packed,
		result,
		temp,
		temp_string[(ZMSG_MAX_PLAYER_CHAT_LENGTH + 1) char],
		start_pos,
		end_pos,
		line;

	is_packed = message{0} != 0;

	while (end_pos <= length) {
		// get pos
		start_pos = Zmsg_ShiftStartPos(message, end_pos, is_packed, length);
		end_pos = start_pos + ZMSG_MAX_PLAYER_CHAT_LENGTH;

		if (is_packed) {
			if (end_pos >= length) {
				strmid(temp_string, message, start_pos, length);
				return SendClientMessage(playerid, -1, temp_string);
			}

			end_pos = Zmsg_ShiftEndPos(message, end_pos, is_packed);

			// prepare string and print
			strmid(temp_string, message, start_pos, end_pos);
			temp_string{end_pos - start_pos} = '\0';

			if (line == 0) {
				result = SendPlayerMessageToPlayer(playerid, senderid, temp_string);
			} else {
				SendClientMessage(playerid, -1, temp_string);
			}
		} else {
			if (end_pos >= length) {
				return SendClientMessage(playerid, -1, message[start_pos]);
			}

			end_pos = Zmsg_ShiftEndPos(message, end_pos, is_packed);

			// prepare string and print
			temp = message[end_pos];
			message[end_pos] = '\0';

			if (line == 0) {
				result = SendPlayerMessageToPlayer(playerid, senderid, message[start_pos]);
			} else {
				SendClientMessage(playerid, -1, message[start_pos]);
			}

			message[end_pos] = temp;
		}
		line++;
	}
	return result;
}
#if defined _ALS_SendPlayerMessageToPlayer
	#undef SendPlayerMessageToPlayer
#else
	#define _ALS_SendPlayerMessageToPlayer
#endif

#define SendPlayerMessageToPlayer ZMsg_SendPlayerMessageToPlayer

/*
	SendPlayerMessageToAll
*/

stock ZMsg_SendPlayerMessageToAll(senderid, message[])
{
	new length = strlen(message);

	// shouldn't be shifted
	if (length <= ZMSG_MAX_PLAYER_CHAT_LENGTH) {
		return SendPlayerMessageToAll(senderid, message);
	}

	new
		bool:is_packed,
		result,
		temp,
		temp_string[(ZMSG_MAX_PLAYER_CHAT_LENGTH + 1) char],
		start_pos,
		end_pos,
		line;

	is_packed = message{0} != 0;

	while (end_pos <= length) {
		// get pos
		start_pos = Zmsg_ShiftStartPos(message, end_pos, is_packed, length);
		end_pos = start_pos + ZMSG_MAX_PLAYER_CHAT_LENGTH;

		if (is_packed) {
			if (end_pos >= length) {
				strmid(temp_string, message, start_pos, length);
				return SendClientMessageToAll(senderid, temp_string);
			}

			end_pos = Zmsg_ShiftEndPos(message, end_pos, is_packed);

			// prepare string and print
			strmid(temp_string, message, start_pos, end_pos);
			temp_string{end_pos - start_pos} = '\0';

			if (line == 0) {
				result = SendPlayerMessageToAll(senderid, temp_string);
			} else {
				SendClientMessageToAll(senderid, temp_string);
			}
		} else {
			if (end_pos >= length) {
				return SendClientMessageToAll(senderid, message[start_pos]);
			}

			end_pos = Zmsg_ShiftEndPos(message, end_pos, is_packed);

			// prepare string and print
			temp = message[end_pos];
			message[end_pos] = '\0';

			if (line == 0) {
				result = SendPlayerMessageToAll(senderid, message[start_pos]);
			} else {
				SendClientMessageToAll(senderid, message[start_pos]);
			}

			message[end_pos] = temp;
		}
		line++;
	}
	return result;
}
#if defined _ALS_SendPlayerMessageToAll
	#undef SendPlayerMessageToAll
#else
	#define _ALS_SendPlayerMessageToAll
#endif

#define SendPlayerMessageToAll ZMsg_SendPlayerMessageToAll
