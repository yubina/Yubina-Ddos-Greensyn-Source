#pragma once
#ifndef __CAPTCHA_H__
#define __CAPTCHA_H__

#include "Common.h"

class Captcha
{
public:
	static bool VerifyInput()
	{			
		string response;
	

		int a = MyRandom() % 10;
		int b = MyRandom() % 10;
		
		cout << endl << endl << "For security purposes please answer the following:" << endl << endl;
		cout << "What does " << a << " + " << b << " equal? " ;	
			
		getline (cin,response);

		if (atoi(response.c_str())!=a+b || response.empty())
		{		
			MySleep(5000);			
			cout << endl << "Answer is incorrect!" << endl << endl;
			return false;
		}

		MySleep(1500);
			
		return true;
	}
};

#endif
