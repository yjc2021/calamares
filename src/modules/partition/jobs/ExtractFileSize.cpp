#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <string>
#include "ExtractFileSize.h"
using namespace std;

// local file size KB
int get_du_size(const char* str)
{
	int size = 100;
	char Bufor[100];
	int du_size = 0;
	char *next_ptr;
	
	std::ostringstream oss;
	string path = str;

	oss << "du -sk "+ path;
	FILE* stream = popen(oss.str().c_str() , "r");
	
	fgets(Bufor, size, stream);
	
	vector<string> vec;

	char *ptr = strtok(Bufor, " ");
	vec.push_back(ptr);
	
	fclose(stream);
	
	du_size = stoi(vec[0]);
	return du_size;
}

// usb usable storage size KB
int get_df_size(const char* str)
{
	int size = 100;
	char Bufor[100];
	int df_size = 0;
	
	std::ostringstream oss;
	string path = str;

	oss << "df "+ path;
	FILE* stream = popen(oss.str().c_str() , "r");

	fgets(Bufor, size, stream);
	fgets(Bufor, size, stream);
	
	vector<string> vec;
	
	char *ptr = strtok(Bufor, " ");
	vec.push_back(ptr);
	
	for(int i=0; i<3; i++)
	{
		ptr = strtok(NULL, " ");
		vec.push_back(ptr);
	}
	
	fclose(stream);
	
	df_size = stoi(vec[3]);
	return df_size;
}



bool isManageable(int from, int to) 
{
	int gap = to - from;
	if (gap < 0) return false;
	else return true;
}

