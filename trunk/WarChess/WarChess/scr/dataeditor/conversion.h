#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>


void ANSIToUnicode( const std::string &instr, std::wstring &outstr);

void UnicodeToANSI( const std::wstring &instr, std::string &outstr );

void UTF8ToUnicode( const std::string &instr, std::wstring &outstr );

void UnicodeToUTF8( const std::wstring &instr, std::string &outstr );

#endif 