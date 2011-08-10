#include "conversion.h"
#include <Windows.h>

void ANSIToUnicode( const std::string &instr, std::wstring &outstr)
{
	wchar_t* tempstr = NULL;
	int len = 0;
	len = MultiByteToWideChar( CP_ACP, 0, instr.c_str(),-1, NULL,0 );  
	tempstr = new  wchar_t[len];
	memset(tempstr,0,len*sizeof(wchar_t));  
	MultiByteToWideChar( CP_ACP, 0, instr.c_str(),-1,tempstr,len );
	outstr = tempstr;
	delete[] tempstr;
}

void UnicodeToANSI( const std::wstring &instr, std::string &outstr )
{
	char* tempstr = NULL;
	int len = 0;
	len = WideCharToMultiByte( CP_ACP, 0, instr.c_str(), -1, NULL, 0, NULL, NULL );
	tempstr = new char[len];
	memset(tempstr, 0, len * sizeof(char));
	WideCharToMultiByte( CP_ACP, 0, instr.c_str(), -1, tempstr, len, NULL, NULL );
	outstr = tempstr;
	delete[] tempstr;
}

void UTF8ToUnicode( const std::string &instr, std::wstring &outstr )
{
	wchar_t * tempstr = NULL;
	int len = 0;
	len = MultiByteToWideChar( CP_UTF8, 0, instr.c_str(),-1,  NULL,0 );  
	tempstr = new  wchar_t[len];
	memset(tempstr,0,len*sizeof(wchar_t));  
	MultiByteToWideChar( CP_UTF8, 0,instr.c_str(),-1,tempstr,len );
	outstr = tempstr;
	delete[] tempstr;
}

void UnicodeToUTF8( const std::wstring &instr, std::string &outstr )
{
	char* tempstr = NULL;
	int len = 0;
	len = WideCharToMultiByte( CP_UTF8, 0, instr.c_str(), -1, NULL, 0, NULL, NULL );
	tempstr = new char[len];
	memset(tempstr, 0, len * sizeof(char));
	WideCharToMultiByte( CP_UTF8, 0, instr.c_str(), -1, tempstr, len, NULL, NULL );
	outstr = tempstr;
	delete[] tempstr;
}