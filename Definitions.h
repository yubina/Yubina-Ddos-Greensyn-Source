#pragma once
#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#define VERSION		"0.6.2"
#define APP_NAME	"SYNFlood"

#ifdef WIN32 
	#define TH_SYN 0x02
	#define IP_DF 0x4000 
	#define IP_MF 0x2000
	#define MyRandom()  (( rand() << 16) + rand())
#define MySleep(a) this_thread::sleep_for(chrono::milliseconds(a))
	#define MyClear() system("cls")
	#define MyStrTok(a,b,c) strtok_s(a,b,c)
#else
	#define MAX_PATH 260
	#define MyRandom() random()
	#define MySleep(a) usleep(a * 1000)
	#define MyClear() system("clear")
	#define MyStrTok(a,b,c) strtok_r(a,b,c)
#endif


#endif /*__DEFINITIONS_H__*/
