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

/*
	SendClientMessage
*/

stock ZMsg_SendClientMessage(playerid, color, message[])
{
	new
		length,
		shifts_count;

	length = strlen(message);
	shifts_count = length / ZMSG_MAX_CHAT_LENGTH;

	if (shifts_count == 0) {
		return SendClientMessage(playerid, color, message);
	}

	new
		result,
		temp,
		start_pos,
		end_pos;

	for (new i = 0; i < shifts_count; i++) {
		start_pos = i * ZMSG_MAX_CHAT_LENGTH;
		end_pos = (i + 1) * ZMSG_MAX_CHAT_LENGTH;

		temp = message[end_pos];
		message[end_pos] = '\0';

		result = SendClientMessage(playerid, color, message[start_pos]);

		message[end_pos] = temp;
	}

	if (length % ZMSG_MAX_CHAT_LENGTH != 0) {
		SendClientMessage(playerid, color, message[end_pos]);
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
	new
		length,
		shifts_count;

	length = strlen(message);
	shifts_count = length / ZMSG_MAX_CHAT_LENGTH;

	if (shifts_count == 0) {
		return SendClientMessageToAll(color, message);
	}

	new
		result,
		temp,
		start_pos,
		end_pos;

	for (new i = 0; i < shifts_count; i++) {
		start_pos = i * ZMSG_MAX_CHAT_LENGTH;
		end_pos = (i + 1) * ZMSG_MAX_CHAT_LENGTH;

		temp = message[end_pos];
		message[end_pos] = '\0';

		result = SendClientMessageToAll(color, message[start_pos]);

		message[end_pos] = temp;
	}

	if (length % ZMSG_MAX_CHAT_LENGTH != 0) {
		SendClientMessageToAll(color, message[end_pos]);
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
	new
		length,
		shifts_count;

	length = strlen(message);
	shifts_count = length / ZMSG_MAX_PLAYER_CHAT_LENGTH;

	if (shifts_count == 0) {
		return SendPlayerMessageToPlayer(playerid, senderid, message);
	}

	new
		result,
		temp,
		start_pos,
		end_pos;

	for (new i = 0; i < shifts_count; i++) {
		start_pos = i * ZMSG_MAX_PLAYER_CHAT_LENGTH;
		end_pos = (i + 1) * ZMSG_MAX_PLAYER_CHAT_LENGTH;

		temp = message[end_pos];
		message[end_pos] = '\0';

		if (i == 0) {
			result = SendPlayerMessageToPlayer(playerid, senderid, message[start_pos]);
		} else {
			SendClientMessage(playerid, -1, message[start_pos]);
		}

		message[end_pos] = temp;
	}

	if (length % ZMSG_MAX_PLAYER_CHAT_LENGTH != 0) {
		SendClientMessage(playerid, -1, message[end_pos]);
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
	new
		length,
		shifts_count;

	length = strlen(message);
	shifts_count = length / ZMSG_MAX_PLAYER_CHAT_LENGTH;

	if (shifts_count == 0) {
		return SendPlayerMessageToAll(senderid, message);
	}

	new
		result,
		temp,
		start_pos,
		end_pos;

	for (new i = 0; i < shifts_count; i++) {
		start_pos = i * ZMSG_MAX_PLAYER_CHAT_LENGTH;
		end_pos = (i + 1) * ZMSG_MAX_PLAYER_CHAT_LENGTH;

		temp = message[end_pos];
		message[end_pos] = '\0';

		if (i == 0) {
			result = SendPlayerMessageToAll(senderid, message[start_pos]);
		} else {
			SendClientMessageToAll(-1, message[start_pos]);
		}

		message[end_pos] = temp;
	}

	if (length % ZMSG_MAX_PLAYER_CHAT_LENGTH != 0) {
		SendClientMessageToAll(-1, message[end_pos]);
	}
	return result;
}
#if defined _ALS_SendPlayerMessageToAll
	#undef SendPlayerMessageToAll
#else
	#define _ALS_SendPlayerMessageToAll
#endif

#define SendPlayerMessageToAll ZMsg_SendPlayerMessageToAll
