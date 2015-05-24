#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <iterator>
#include <string>
#include <algorithm>

using namespace std;

typedef map<char,int> Freq;
typedef pair<bool,char> CodePair;
typedef vector<CodePair> CodeRes;
typedef vector<bool> Code;
typedef map<char, Code> HuffCodeMap;

class INode
{
public:
	const int f;
	virtual ~INode() {}
protected:
	INode(int f) : f(f) {}
};

class InternalNode : public INode
{
public:
	INode *const left;
	INode *const right;

	InternalNode(INode* c0, INode* c1) : INode(c0->f + c1->f), left(c0), right(c1) {}
	~InternalNode(){
		delete left;
		delete right;
	}
};

class LeafNode : public INode
{
public:
	char c;

	LeafNode(int f, char c) : INode(f), c(c) {}
};

struct NodeCmp
{
	bool operator()(const INode* lhs, const INode* rhs) const { return lhs->f > rhs->f; }
};

INode* BuildTree(map<char,int> frequencies)
{
	std::priority_queue<INode*, std::vector<INode*>, NodeCmp> trees;

	for (auto str: frequencies){
		if( str.second != 0 )
			trees.push(new LeafNode(str.second, str.first) );
		}
	
	while (trees.size() > 1){
		INode* childR = trees.top();
		trees.pop();

		INode* childL = trees.top();
		trees.pop();

		INode* parent = new InternalNode(childR, childL);
		trees.push(parent);
		}

	return trees.top();
}
bool isLeaf( INode* node )
{
	return dynamic_cast<const LeafNode*>(node) != NULL;
}

void GenerateCodes(const INode* node, const Code& prefix, HuffCodeMap& outCodes)
{
	if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node)){
		outCodes[lf->c] = prefix;
		}
	else 
		if (const InternalNode* in = dynamic_cast<const InternalNode*>(node)){
		Code leftPrefix = prefix;
		leftPrefix.push_back(false);
		GenerateCodes(in->left, leftPrefix, outCodes);

		Code rightPrefix = prefix;
		rightPrefix.push_back(true);
		GenerateCodes(in->right, rightPrefix, outCodes);
		}
}

string symbols = " !\"'(),.:?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\n";

Code gencode( CodeRes codeRes, HuffCodeMap cMap )
{
	Code res;
	for( int i = 0; i < codeRes.size(); i++ )
		if( codeRes[ i ].first )
			res.push_back( true );
		else
			{
			Code curCode = cMap[ codeRes[ i ].second ];
			res.push_back( false );
			for( int j = 0; j < curCode.size(); j++ )
				res.push_back( curCode[ j ] );
			}

	while( res.size() % 8 != 0 )
		res.push_back( 0 );

	return res;
}

CodeRes getCodeRes( string & str )
{
	CodeRes res;
	map<string,char> xx;
	int pr = 5;
	int ansStat = 0;
	for( int i = 0; i < pr; i++ )
		res.push_back(make_pair(false,str[ i ]) );

	for( int i = pr; i < str.size(); i++ ){
		string sub = str.substr(i-pr,pr);
		if( xx.count(sub) == 0 )
			xx[sub] = ' ';
		if( xx[ sub ] == str[ i ] ){
			res.push_back( make_pair(true,0));
			}
		else{
			xx[ sub ] = str[ i ];	
			res.push_back( make_pair(false, str[i]) );
			}
		}

	return res;
}

void save( string fname, long len, HuffCodeMap hMap, CodeRes code, Freq myFreq )
{
	ofstream f( fname, fstream::binary);
	f.write( (char*)(&len),4);
	for( int i = 0; i < symbols.size(); i++ ){
		char cSym = symbols[ i ];
		unsigned short int cFreq = myFreq[ cSym ];
		f.write( (char*)(&cSym),1);
		f.write( (char*)(&cFreq),2);
		}
	
	Code bits = gencode( code, hMap );
	int bts = bits.size()/8;
	for( int i = 0; i < bts; i++){
		char curByte = 0;
		for( int j = 0; j < 8 ; j++ )  
			if( bits[ i*8 + j ] )
				curByte |= 1 << (7-j);
		f.write( (char*)(&curByte),1);
		}
}

void read( string fname, string outfname )
{
	long len;
	ifstream f( fname, fstream::binary );
	Freq frequencies;
	f.read( (char*)(&len),4);
	for( int i = 0; i < symbols.size(); i++ ){
		char cSym;
		unsigned short int cFreq;
		f.read( (char*)(&cSym),1);
		f.read( (char*)(&cFreq),2);
		
		frequencies[ cSym ] = cFreq;
		}

	vector<char> buffer;
	while( ! f.eof() ){
		char c;
		f.read((char*)(&c),1);
		buffer.push_back( c );
		}
	
	Code bits;
	for( int i = 0; i < buffer.size(); i++ ){
		char cByte = buffer[ i ];
		for( int j = 7; j >=0; j-- )
			bits.push_back( cByte & 1 << j );
		}
	INode* root = BuildTree(frequencies);
	int idx = 0;
	string res;
	map<string,int> xx;
	string subs;
	for( int i = 0; i < len; i++ ){
		if( i >= 5 )
			subs = res.substr(i-5,5);
		if( xx.count(subs) == 0 )
			xx[subs] = ' ';
		bool curBit = bits[ idx ];
		idx++;
		if( curBit )
			res += xx[ subs ];
		else{
			INode *cur = root;
			while( ! isLeaf( cur ) ){
				const InternalNode* in = dynamic_cast<const InternalNode*>(cur);
				bool cbt = bits[ idx++ ];
				if( cbt )
					cur = in->right;
				else
					cur = in->left;
				}
			const LeafNode* lf = dynamic_cast<const LeafNode*>(cur);
			res += string(1,lf->c);
			xx[ subs ] = lf->c;
			}
	}
	freopen( outfname.c_str(), "wt", stdout );
	cout << res;
}

int main()
{
	read( "input.txt", "output.txt" );
	return 0;
}