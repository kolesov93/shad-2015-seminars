#include <iostream>
#include <string>
#include <algorithm>

#include <vector>
#include <iosfwd>
#include <fstream>
#include <assert.h>


using namespace std;

string initText;
int lenText;
string allowed = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM()':,.!?\" ";
string fullAllowed = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM()':,.!?\" 0123456789";
int * cnt;
int * p;
int * c;
int * pn;
int * cn;
string answer;

char * buffer;
char * bufferComp;

int modulo = 96;
int startModulo = 160;

int buffersize = 0;
int bufferCompsize = 0;

int headerStartLine = 0;
int headerBody = 0;

string StartLine;
string Body;

int alphabet = 256;
int * sufArray;

string beta;

void buildSufArray(string & s)
{
	int n = s.size();
	p = new int [n];
	c = new int [n];
	pn = new int [n];
	cn = new int [n];
	cnt = new int [max(n, alphabet)];
	for(int i = 0; i< max(n, alphabet); i++){
		cnt[i] = 0;
	}
	for(int i = 0; i< n; i++){
		c[i] = 0;
		p[i] = 0;
		cn[i] = 0;
		pn[i] = 0;
	}
	for (int i=0; i<n; ++i)
		++cnt[s[i]];
	for (int i=1; i<alphabet; ++i)
		cnt[i] += cnt[i-1];
	for (int i=0; i<n; ++i)
		p[--cnt[s[i]]] = i;
	c[p[0]] = 0;
	int classes = 1;
	for (int i=1; i<n; ++i) {
		if (s[p[i]] != s[p[i-1]]) ++classes;
		c[p[i]] = classes-1;
	}

	for (int h=0; (1<<h)<n; ++h) {
		for (int i=0; i<n; ++i) {
			pn[i] = p[i] - (1<<h);
			if (pn[i] < 0) pn[i] += n;
		}
		for (int j = 0; j < classes; j++) cnt[j] = 0;
		for (int i=0; i<n; ++i)
			++cnt[c[pn[i]]];
		for (int i=1; i<classes; ++i)
			cnt[i] += cnt[i-1];
		for (int i=n-1; i>=0; --i)
			p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0;
		classes = 1;
		for (int i=1; i<n; ++i) {
			int mid1 = (p[i] + (1<<h)) % n, mid2 = (p[i-1] + (1<<h)) % n;
			if (c[p[i]] != c[p[i-1]] || c[mid1] != c[mid2])
				++classes;
			cn[p[i]] = classes-1;
		}
		for (int i =0; i< n; i++)
			c[i] = cn[i];
	}
	sufArray = p;
}

void buildBeta(string & s, int * sufArray)
{
	int n = 2 * s.size() + 2;
	for (int i = 0; i< n; i++){
		if (sufArray[i] <= s.size() && sufArray[i] != 0)
			beta.append(1, s[sufArray[i] - 1]);
		if (sufArray[i] == 0)
			beta.append(1, char(1));
		}

}

int b[10];
void addToBufferComp(int numb)
{
	bufferComp[bufferCompsize] = char(numb);
	bufferCompsize++;
}

int indexAllow(char symb)
{
	for (int i = 0; i< fullAllowed.size(); i++)
		if (int(fullAllowed[i]) == int(symb)) return i;
	assert(1 < 0);
	return 1;
}

void addSymbComp(char symb, int cnt)
{
	if (cnt == 0)
		return;
	if (cnt == 1)
	{
		int ind = indexAllow(symb) + 1 + fullAllowed.size();
		addToBufferComp(ind);
		return;
	}
	int ind = 0;
	while (cnt != 0)
	{
		b[ind] = cnt % modulo + startModulo;
		ind++;
		cnt /= modulo;
	}
	addToBufferComp(indexAllow(symb) + 1);
	for (int j = ind-1; j >=0 ; j--)
	{
		addToBufferComp(b[j]);
	}

}


void buildCompress(string & s)
{
	char curChar = s[0];
	int cnt = 1;
	for (int i = 1; i< s.size(); i++)
		if (s[i] != s[i-1]) {
			addSymbComp(curChar, cnt);
			curChar = s[i];
			cnt = 1;
		}
		else{
			cnt++;
		}
	addSymbComp(curChar, cnt);
}




void addToBuffer(int numb)
{
	buffer[buffersize] = char(numb);
	buffersize++;
}
void writeStart()
{
	headerStartLine = StartLine.size();
	addToBuffer(int(headerStartLine / 256));
	addToBuffer(int(headerStartLine % 256));

	for (int i = 0; i< StartLine.size(); i++)
		addToBuffer(int(StartLine[i]));
}
void writeCompress()
{
	int c[3];
	int cursize = bufferCompsize;
	for (int i = 0; i< 3; i++)
	{
		c[i] = cursize % 256;
		cursize /= 256;
	}
	for (int i = 2; i>=0; i--)
		addToBuffer(c[i]);
	for (int i = 0; i< bufferCompsize; i++)
		addToBuffer(bufferComp[i]);
}

void buildStart(string & s, int *sufArray){
	int n = 2 * s.size() + 2;
	int cnt = 1;
	int startPos[256];

	for (int i = 0; i< 256; i++)
		startPos[i] = -1;
	startPos[1] = 0;

	for (int i = 0; i< n; i++) {
		if (sufArray[i] < s.size() && startPos[int(s[sufArray[i]])] == -1)
			startPos[int(s[sufArray[i]])] = cnt;
		if (sufArray[i] < s.size())
			cnt++;
	}
	vector <int> numb;
	for (int i =0; i< allowed.size(); i++)
		numb.push_back(int(allowed[i]));
	numb.push_back(1);
	sort(numb.begin(), numb.end());
	for (int i = 0; i< numb.size(); i++)
		if (startPos[numb[i]] != -1){
			StartLine += char(numb[i]);
			StartLine += to_string(static_cast<long long>(startPos[numb[i]]));
		}
}

int main(int argc, char * argv[])
{
	freopen (argv[1], "r", stdin);
	std::ofstream outfile (argv[2], std::ofstream::binary);
	fullAllowed.append(1, char(1));
	getline(cin, initText);
	lenText = initText.size();
	buffer = new char [2*lenText];
	bufferComp = new char [2*lenText];

    string tmpBuffer = initText;
    tmpBuffer += char(1);
    tmpBuffer += initText;
    tmpBuffer += char(1);
	buildSufArray(tmpBuffer);
	buildBeta(initText, sufArray);
	buildStart(initText, sufArray);
	writeStart();

	buildCompress(beta);
	writeCompress();

	outfile.write(buffer, buffersize);
	return 0;
}
