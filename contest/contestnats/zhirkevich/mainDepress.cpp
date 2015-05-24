#include <iostream>
#include <string>
#include <algorithm>

#include <vector>
#include <iosfwd>
#include <fstream>
#include <assert.h>


using namespace std;

string startLine;
int start;
string textPress;
string text;
int startPoint[256];
int *cnt;
int lastCnt[256];
string answer = "";
char * inbuffer;
int bufferSize = 0;

int modulo = 96;
int startModulo = 160;

string fullAllowed = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM()':,.!?\" 0123456789";

int ch(char c)
{
	if (int(c) < 0) return (int(c) + 256);
	return (int (c));
}

void getStartLine()
{
	int curSize = ch(inbuffer[0]);
	curSize *= 256;
	curSize += ch(inbuffer[1]);
	bufferSize = 2;
	for (int i =0; i< curSize; i++)
	{
		startLine.append(1, inbuffer[bufferSize]);
		bufferSize++;
	}
}

void parseStartLine(string & s){
	for (int i = 0; i < 256; i++) 
		startPoint[i] = 0;
	string st = "";
	char symb = char(1);
	for (int i = 0; i < s.size(); i++)
	{
		if (int(s[i]) - int('0')<= 9 && int(s[i]) - int('0') >= 0){
			st.append(1, s[i]);
			continue;
		}
		startPoint[int(symb)] = atoi(st.c_str());
		st = "";
		symb = s[i];
	}
	startPoint[int(symb)] = atoi(st.c_str());
}

bool isLetter(int numb)
{
	if (numb >= 1 && numb <= fullAllowed.size())
		return true;
	assert(numb != 0);
	return false;
}
bool isLetterWith1(int numb)
{
	if (numb < startModulo && !isLetter(numb)) 
		return true;
	return false;
}

bool isNumb(int numb)
{
	if (numb >= startModulo)
		return true;
	return false;
}
char inAllow(int numb)
{
	return fullAllowed[numb-1];
}

char getInAllowWith1(int numb)
{
	return fullAllowed[numb - fullAllowed.size() - 1];
}


void getBody()
{
	int curSize = 0;
	for (int i =0; i< 3; i++)
	{
		curSize *= 256;
		curSize += ch(inbuffer[bufferSize]);
		bufferSize++;
	}
	bool state = true;
	int cnt = 0;
	int curChar;
	char symb = 'a';
	for (int i = 0; i<curSize; i++)
	{
		curChar = ch(inbuffer[bufferSize]);
		bufferSize++;

		if (isLetter(curChar))
		{
			text.append(cnt, symb);
			symb = inAllow(curChar);
			cnt = 0;
			continue;
		}
		if (isLetterWith1(curChar))
		{
			text.append(cnt, symb);
			text.append(1, getInAllowWith1(curChar));
			cnt = 0;
			continue;
		}
		if (isNumb(curChar))
		{
			cnt *= modulo;
			cnt += curChar - startModulo;
		}
	}
	text.append(cnt, symb);
}

void countText(string & s)
{
	for (int i =0; i< 256; i++)
		lastCnt[i] = -1;
	cnt = new int [s.size()];
	for (int i = 0; i< s.size(); i++){
		cnt[i] = lastCnt[int(s[i])] + 1;
		lastCnt[int(s[i])]++;
	}
}


void findAnswer(string & s, int start)
{
	answer = "";
	answer.append(1, text[start]);
	int j = 0;
	for (int i = 0; i< s.size() - 1; i++)
	{
		j = startPoint[int(s[start])] + cnt[start];
		start = j;
		answer.append(1, s[start]);
	}
}

int main(int argc, char * argv[])
{
	std::ifstream infile (argv[1], std::ofstream::binary);
	fullAllowed.append(1, char(1));
	inbuffer = new char [2111111];

	infile.seekg (0,infile.end);
	long size = infile.tellg();
	infile.seekg (0);
	infile.read (inbuffer, size);

	getStartLine();
	parseStartLine(startLine);
	
	getBody();
	countText(text);
	findAnswer(text, start);
	
	char* buffer = new char[answer.size() - 1];
	int j = 0;
	for (int i = answer.size() - 2; i >= 0; i--)
	{
		buffer[j] = answer[i];
		j++;
	}
	buffer[j] = char(10);
	std::ofstream outfile (argv[2], std::ofstream::binary);
	outfile.write(buffer, answer.size());
	
	return 0;
}