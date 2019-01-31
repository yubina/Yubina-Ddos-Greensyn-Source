#pragma once
#ifndef _APPLICATION_H__
#define _APPLICATION_H__

#include "SYNFlood.h"

class Application
{
public:
	Application(void);
	~Application(void);

	int Create();

private:

	void Run();

	void DisplayHeaders();
	void DisplayWelcome();	
	bool GetParameters();		
	bool GetReadyState();
	
	bool GetAdditionalOptions();
#ifdef WIN32
	bool GetNetworkDevice();
#endif
	void GetThreadCount();
	void GetTargets();
	void GetTargetPorts();
	void GetSources();
	void GetSourcePorts();	
	void GetIDValues();	
	void GetTTLValues();
	void GetWindowLengths();	
	void GetFragmentOptions();	
	void GetMSSValues();
	
	bool GetGenericValues(vector<int>&, int, int&,int& );
	
	SYNFLOOD_OPTIONS _options;
	SYNFlood * _synflood;

};



#endif /*_APPLICATION_H__*/

