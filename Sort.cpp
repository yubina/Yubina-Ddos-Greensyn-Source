#include "Sort.h"

string  ReplaceAll(string  input, const string find, const string replace )
{
	size_t size ;
	while ((size = input.find(find)) != string::npos)
	{
		input.erase(size, find.size());
		input.insert(size, replace);
	}
	return input;
}

void SplitString(const string &s, char delim, vector<string> &elems) 
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) 
	{
        elems.push_back(item);
    }
}

int CountSubstring(const char *str, const char *sub)
{
    int length = strlen(sub);
    if (length == 0) return 0;
    int count = 0;
    for (str = strstr(str, sub); str; str = strstr(str + length, sub))
        ++count;
    return count;
}


bool ReadFileIntoArray(string file, vector<string> &list)
{	
	ifstream ifile(file);
	string line;	
	list.clear();

	if (!ifile)
	{		
		return false;
	}
    while (getline(ifile, line))
    {
			
		line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        list.push_back(line);    
	}	
	return true;
}

bool SortInputAddresses(string input, vector<uint32_t> &output)
{
		
	input = ReplaceAll(input, " ", ",");
	
	vector<string> arr;
	output.clear();

	SplitString(input, ',', arr);

	for(unsigned int i = 0 ; i < arr.size(); ++i)
	{		
		
		if (!arr[i].empty())
		{
			
			uint32_t address = inet_addr(arr[i].c_str());
			
			if (address != INADDR_NONE)
			{
				output.push_back(address);
			}
			else
			{
				cout << endl << "Problem parsing input!" <<endl;
				return false;
			}
		}
	}

	return true;
}


bool SortAddressList(vector<string> &lines, vector<uint32_t> &output)
{

	for(unsigned int i = 0 ; i < lines.size(); ++i)
	{
		if (!lines[i].empty())
		{
			uint32_t address = inet_addr(lines[i].c_str());
			
			if (address != INADDR_NONE)
			{
				output.push_back(address);
			}
			else
			{
				cout << "Problem parsing list on line " << i << "!" << endl;
				return false;
			}
		}
	}

}



bool SortInputValues(string input, vector<int> &output, int max, int range_min, int range_max)
{
		
	
	input = ReplaceAll(input, "to", "-");   
	size_t pos;

	if ((pos = input.find("-")) != string::npos)
	{
		
		//check if theres more than one dash

		if (CountSubstring(input.c_str(), "-" ) != 1)
		{
			cout << "Invalid range specified!" <<endl;			
		}
		else
		{
			
			int left, right;

			left = atoi(input.substr(0, pos).c_str());
			right = atoi(input.substr(pos+1, input.length() - 1).c_str());

			if (left > right || left < 0 || right > max || left == right)
			{
				cout << "Invalid values specified!" <<endl;				
			}
			else
			{
				range_min = left;
				range_max = right;

				return true;
			}

		}
		
		return false;
	
	}
	else
	{

		input = ReplaceAll(input, " ", ",");
	
		vector<string> arr;
		output.clear();

		SplitString(input, ',', arr);

		for(unsigned  int i = 0 ; i < arr.size(); ++i)
		{
			if (!arr[i].empty())
			{

				int val = atoi(arr[i].c_str());
			
				if (val < 0 || val > max)
				{
					cout << "Problem parsing input!" <<endl;
					return false;
				}
				else
				{
					output.push_back(val);				
				}
			}
		}

	}

	return true;
}


bool SortValueList(vector<string> &lines, vector<int> &output, int max)
{

	output.clear();

	for(unsigned int i = 0 ; i < lines.size(); ++i)
	{
		if (!lines[i].empty())
		{
	
			int val = atoi(lines[i].c_str());
			
			if (val < 0 || val > max)
			{
				cout << "Problem parsing list on line " << i << "!" << endl;
				return false;
			}
			else
			{
				output.push_back(val);				
			}

		}
	}

}

