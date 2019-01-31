#pragma once
#ifndef __synflood_H__
#define __synflood_H__

#include "Common.h"
#include "Networking.h"
#include "Sort.h"

struct SYNFLOOD_OPTIONS
{
	int thread_count;			
	
	/* ranges */

	uint32_t target_low;		
	uint32_t target_high;		
	uint32_t source_low;		
	uint32_t source_high;	
	int sport_low;
	int sport_high;
	int dport_low;
	int dport_high;	
	int id_low;
	int id_high;
	int wnd_low;
	int wnd_high;
	int ttl_low;
	int ttl_high;
	int mss_low;
	int mss_high;	

#ifdef WIN32
	N_DEVICE dev;
#endif

};

struct TIMESTAMP
{
	int index;
	int position;
};


class SYNFlood
{
public:
	SYNFlood(void);
	~SYNFlood(void);

	void Start(SYNFLOOD_OPTIONS*  );

	void SetTargets(const vector<uint32_t>&);
	void SetSources(const vector<uint32_t>&);	
	void SetTargetPorts(const vector<int>&);
	void SetSourcePorts(const vector<int>&);
	void SetWindowLengths(const vector<int>&);
	void SetIDValues(const vector<int>&);
	void SetTTLValues(const vector<int>&);
	void SetFragmentationOptions(const vector<int>&);
	void SetMSSValues(const vector<int>&);
	void SetMSSOptions(const vector<int>&);	

	void SendPackets();	
	string GetMSSOptions();
	int GetMSSCount();

private:

	void BuildPackets();	
	void LaunchThreads();
	void AnalyzeMSSOptions();	

#ifndef WIN32
	static void ThreadProc(void*);	
#endif	

#ifdef USE_STACK
	uint8_t  _packets[MAX_PACKETS][128];	
	int _lengths[MAX_PACKETS];
	#ifndef WIN32	
		sockaddr_in _sins[MAX_PACKETS];
	#endif
#else
	uint8_t ** _packets;
	int *_lengths;		
	#ifndef WIN32	
		sockaddr_in *_sins;
	#endif
#endif
			
	string _mssoptstr;
	int _optnum;
	
	vector<uint32_t> _targets;
	vector<uint32_t> _sources;	
	vector<int> _sports;
	vector<int> _dports;
	vector<int> _ids;
	vector<int> _ttls;
	vector<int> _frags;	
	vector<int> _wnds;
	vector<int> _mss;
	vector<int> _msslens;
	vector<TIMESTAMP> _timestamps;			
	SYNFLOOD_OPTIONS * _options;

};

#endif /*__synflood_H__*/
