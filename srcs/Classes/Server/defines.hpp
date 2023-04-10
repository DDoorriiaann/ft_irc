#ifndef DEFINES_HPP
#define DEFINES_HPP

#define CONTINUE 1
#define	STOP 0
#define SUCCESS 1
#define	FAILURE 0

#define	PWD_ENTRY_STATUS		0
#define USERNAME_ENTRY_STATUS	1
#define	CONNECTED				2

#define UNKNOWN -1

#define HEADER_INFO						"[INFO]: "
#define	HEADER_ERROR					"[ERROR]: "
#define	HEADER_HXCHAT					"CAP LS 302"
#define	MSG_CREATION_SUCCESS			"[INFO]: The server as been created succesfully ✅"
#define	MSG_ENTER_PASSWORD				"[INFO]: Please enter the password.\n "
#define	NEW_USER_MSG 					"[INFO]: New user on DG-Chat 🎉"
#define	MSG_SENT_SUCCESS				"[INFO]: Your message has been send.\n"
#define	MSG_WRONG_PWD					"[ERROR]: Wrong Password.\n"
#define	WELCOME							"[INFO]: Connected. Now logging in. \n"


/////RUN//////

#define	IS_CMD						'/'
#define	PASS_COMMAND				"PASS"
#define	USER_COMMAND				"USER"
#define	JOIN_COMMAND				"JOIN"
#define	MSG_COMMAND					"MSG"
#define	BOT_COMMAND 				"BOT"
#define	NICK_COMMAND 				"NICK"
#define KICK_COMMAND				"KICK"
#define MODE_COMMAND 				"MODE"
#define PART_COMMAND 				"PART"
#define BOT_COMMAND					 "BOT"
#define QUIT_COMMAND_HEXCHAT		"QUIT"
#define	CMD_NOT_FOUND 				"[ERROR]: Command not found\n"
#define	CONNECTION_FAILED			"[ERROR]: An error occurred during the connection.\n[INFO] DISCONNECT by the server.\n"
#define	CHANNEL_NOT_FOUND 			"[ERROR]: Channel not found\n"
#define	CHANNEL_LIST 				"No channel specified, active channels are : "
#define CHANNEL_REQUIRES_HASHTAG	"[ERROR]: A channel name must start with '#'\n"


/////CHECK CLIENT STATUS///////

#define BAD_PASSWORD 			"Bad password.\n"
#define	CONNECTION_FAILED		"[ERROR]: An error occurred during the connection.\n[INFO] DISCONNECT by the server.\n"
#define USERNAME_ALREADY_SET 	"[ERROR] Username already set.\n"
#define SPACE_IN_USERNAME 		"[ERROR] Space in username.\n"
#define EMPTY_USERNAME 			"[ERROR] Empty username.\n"
#define	DISCONNECT				"[INFO] DISCONNECT.\n"

#endif // DEF_HPP