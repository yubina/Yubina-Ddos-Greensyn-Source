#pragma once
#ifndef __SETTINGS_H__
#define __SETTINGS_H__


/* un-comment the following options to enable them */

#define USE_STACK
#define HEADER_CHECKSUM	
//#define SINGLE_THREADED
//#define SHOW_CAPTCHA	
	


/* adjust the following settings accordingly */

#define MAX_PACKETS					100000     //requires atleast 1.5 GB of ram at 10M
#define MAX_THREADS					32
#define DEFAULT_THREADS				1	
#define DEFAULT_SPORT_MIN			30000
#define DEFAULT_TTL_MIN				20




#endif /*__SETTINGS_H__*/

