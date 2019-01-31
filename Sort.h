#pragma once
#ifndef __SORT_H__
#define __SORT_H__

#include "Common.h"


string  ReplaceAll(string, const string, const string);
void SplitString(const string &, char, vector<string> &) ;
int CountSubstring(const char *str, const char *sub);
bool ReadFileIntoArray(string, vector<string> &);
bool SortInputAddresses(string, vector<uint32_t> &);
bool SortAddressList(vector<string> &, vector<uint32_t> &);
bool SortInputValues(string, vector<int> &, int, int, int);
bool SortValueList(vector<string> &, vector<int> &, int);

#endif /*__SORT_H__*/
