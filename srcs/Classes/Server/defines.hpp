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

#define	CONNECTION_FAILED		"[ERROR]: An error occurred during the connection.\n[INFO] DISCONNECT by the server.\n"
#define USERNAME_ALREADY_SET 	"[ERROR] Username already set.\n"
#define EMPTY_USERNAME 			"[ERROR] Empty username.\n"
#define	DISCONNECT				"[INFO] DISCONNECT.\n"

//////PASS COMMANDS////////

#define BAD_PASSWORD 			"[ERROR]: Bad password.\n[INFO]: DISCONNECTED\n"
#define	MSG_ENTER_USRNM			"[INFO]: Good password ✅\n[INFO]: Use /cmd USER <username> to finish the connection.\n"
#define USERNAME_ALREADY_SET 	"[ERROR] Username already set.\n"
#define EMPTY_USERNAME 			"[ERROR] Empty username.\n"
#define	DISCONNECT				"[INFO] DISCONNECT.\n"
#define	PWD_ALREADY_PAST		"[ERROR]: Password has already been transmitted.\n"
#define	USE_USER_CMD			"[INFO]: Use /cmd USER <your username> to finish the connection.\n"
#define	ENTER_PWD_FIRST			"[ERROR]: Enter the password first.\n[INFO]: Use /cmd PASS <password>.\n"
#define	ACCESS_DENIED	 		"[ERROR]: Access denied.\n[INFO]: Use /cmd USER <username> to finish the connection.\n"

///////USE COMMAND///////

#define	UNKNOWN					-1
#define	NO_USERNAME				"[ERROR]: No username.\n[INFO]: Use /cmd USER <username> to finish the connection.\n"
#define	SPACE_IN_USERNAME		"[ERROR]: In the username the spaces are forbidden.\n"
#define	SUCCESS_CONNECTION		"[INFO]: You are now connected ✅\n"

#endif // DEF_HPP