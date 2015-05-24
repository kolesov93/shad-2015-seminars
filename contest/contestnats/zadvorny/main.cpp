#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Barrows_Wiler_Class{
private:
	string Text;
	vector<int> IntText;
	vector<int> ForText;
	vector<int> SufArr;
	vector<int> SufArrBack;
	vector<int> Barrows_Wiler;
	string Barrows_Wiler_String;
	vector<vector<int> > RLE;
	string SifrText;
	
public:
	string Barrows_Wiler_Transform_Back(string S);
};

string Barrows_Wiler_Class::Barrows_Wiler_Transform_Back(string S){
	Barrows_Wiler.resize(S.size());
	for (int i=0; i<S.size(); i++){
		Barrows_Wiler[i] = (int)S[i] - 32;}

	vector<int> C(92);
	for (int i=0; i<Barrows_Wiler.size(); i++){
		C[Barrows_Wiler[i]]++;}

	vector<int> D(92);
	D[0] = 0;
	for (int i=1; i<D.size(); i++){
		D[i] = D[i-1] + C[i-1];}

	vector<int> Letters(92);

	vector<int> T(Barrows_Wiler.size());
	for (int i=0; i<Barrows_Wiler.size(); i++){
		T[i] = D[Barrows_Wiler[i]] + Letters[Barrows_Wiler[i]];
		Letters[Barrows_Wiler[i]]++;}

	ForText.resize(Barrows_Wiler.size());
	ForText[ForText.size()-1] = 91;

	int place = 0;
	while (Barrows_Wiler[place] != 91){
		place++;}

	for (int i = ForText.size()-2; i>=0; i--){
		ForText[i] = Barrows_Wiler[T[place]];
		place = T[place];
	}

	string Answer;
	Answer.resize(ForText.size());
	for (int i=0; i<Answer.size(); i++){
	Answer[i] = (char)(ForText[i]+32);}

	Answer = Answer.substr(0, Answer.size()-1);
	return Answer;
}

class MTF{
private:
	string Alphabet;
	vector<int> make_mtf;
	string str_mtf;
public:
	void mtf_to_int();
	string MTF_Back();
	string All_MTF_Back(string S);
};

string MTF::All_MTF_Back(string S){
	str_mtf = S;

	Alphabet = "s.,EOMTeat:ng";
	Alphabet = Alphabet + '"';
	Alphabet = Alphabet + "ydrf!?kwomIl'NKHYGSUuV)hxcAWDiFRp(LXCbP QB{JzvjZq";

	mtf_to_int();
	string Answer = MTF_Back();
	return Answer;
}

void MTF::mtf_to_int(){
	make_mtf.resize(str_mtf.size());
	for (int i=0; i<make_mtf.size(); i++){
		for (int j=0; j<Alphabet.size(); j++){
			if (Alphabet[j] == str_mtf[i])
				make_mtf[i] = j;
		}
	}
}

string MTF::MTF_Back(){
	char c;
	string Answer;
	Answer.resize(make_mtf.size());
	string Token;
	string Alphabet_Copy = Alphabet;

	for (int i=0; i<make_mtf.size(); i++){
		Answer[i] = Alphabet_Copy[make_mtf[i]];
		if (make_mtf[i] > 0){
			Token = Alphabet_Copy.substr(0, make_mtf[i]);
			c = Alphabet_Copy[make_mtf[i]];
			Alphabet_Copy[0] = c;
			for (int k=0; k<Token.size(); k++){
				Alphabet_Copy[k+1] = Token[k];
			}
		}
	}
	return Answer;
}

class Compressor{
private:
	string Text;
	vector<int> IntText;
	vector<int> ForText;

	vector<int> Uncode_Left;
	vector<int> Uncode_Right;
	vector<int> Uncode_Father;
	vector<int> Tree_Letter;

public:
	string Huffman_Back();
};

string Compressor::Huffman_Back(){
	ifstream huf("input.txt");
	int size;
	huf >> size;
	string For_Uncode;
	vector<int> Uncode_Letter(size);
	vector<string> Uncode_Code(size);
	getline(huf, For_Uncode);
	for (int i=0; i<size; i++){
		getline(huf, For_Uncode);
		if (For_Uncode[0] != ' '){
			Uncode_Letter[i] = (int)For_Uncode[0];
			Uncode_Code[i] = For_Uncode.substr(2, For_Uncode.size());
		}
		else{
			Uncode_Letter[i] = 32;
			Uncode_Code[i] = For_Uncode.substr(2, For_Uncode.size());
		}
	}

	int size_code;
	string Code_Text;
	huf >> size_code;
	huf >> Code_Text;

	int Int_Uncode;
	string BitCode;

	for (int i=0; i<Code_Text.size(); i++){

		Int_Uncode = (int)Code_Text[i];
		if (Int_Uncode < 0)
			Int_Uncode = Int_Uncode + 256;
		Int_Uncode = Int_Uncode - 33;
		string Little;
		Little.resize(7);
		for (int j=0; j<7; j++){
			if (Int_Uncode % 2 == 1){
				Little[6-j] = '1';
			}
			else
				Little[6-j] = '0';
			Int_Uncode = (Int_Uncode - (Int_Uncode % 2))/2;
		}
		BitCode = BitCode+Little;
	}

	if (size_code < BitCode.size()){
		int r = size_code % 7;
		int q = size_code - r;
		string Real = BitCode.substr(q, BitCode.size());
		BitCode = BitCode.substr(0, q);

		Real = Real.substr(7-r, Real.size());
		BitCode = BitCode + Real;
	}

	Uncode_Left.resize(1);
	Uncode_Right.resize(1);
	Uncode_Father.resize(1);
	Uncode_Left[0] = -1;
	Uncode_Right[0] = -1;
	Uncode_Father[0] = -1;
	int Vertex;
	for (int i=0; i<Uncode_Letter.size(); i++){
		Vertex = 0;
		for (int j=0; j<Uncode_Code[i].size(); j++){
			if (Uncode_Code[i][j] == '0'){
				if (Uncode_Left[Vertex]!=-1)
					Vertex = Uncode_Left[Vertex];
				else{
					Uncode_Left.resize(Uncode_Left.size()+1);
					Uncode_Right.resize(Uncode_Right.size()+1);
					Uncode_Father.resize(Uncode_Father.size()+1);
					Uncode_Left[Vertex] = Uncode_Left.size()-1;
					Uncode_Father[Uncode_Father.size() - 1] = Vertex;
					Uncode_Left[Uncode_Father.size() - 1] = -1;
					Uncode_Right[Uncode_Father.size() - 1] = -1;
					Vertex = Uncode_Left[Vertex];
				}}
			if (Uncode_Code[i][j] == '1'){
				if (Uncode_Right[Vertex]!=-1)
					Vertex = Uncode_Right[Vertex];
				else{
					Uncode_Left.resize(Uncode_Left.size()+1);
					Uncode_Right.resize(Uncode_Right.size()+1);
					Uncode_Father.resize(Uncode_Father.size()+1);
					Uncode_Right[Vertex] = Uncode_Left.size()-1;
					Uncode_Father[Uncode_Father.size() - 1] = Vertex;
					Uncode_Left[Uncode_Father.size() - 1] = -1;
					Uncode_Right[Uncode_Father.size() - 1] = -1;
					Vertex = Uncode_Right[Vertex];
				}
			}
		}
	}

	Tree_Letter.resize(Uncode_Left.size());
	for (int i=0; i<Tree_Letter.size(); i++){
		Tree_Letter[i] = -1;}

	for (int i=0; i<Uncode_Code.size(); i++){
		Vertex = 0;
		for (int j=0; j<Uncode_Code[i].size(); j++){
			if (Uncode_Code[i][j] == '1')
				Vertex = Uncode_Right[Vertex];
			else
				Vertex = Uncode_Left[Vertex];
		}
		Tree_Letter[Vertex] = Uncode_Letter[i];
	}

	string New_Text;
	string Token;
	Vertex = 0;
	for (int i=0; i<BitCode.size(); i++){
		if (Tree_Letter[Vertex] == -1){
			if (BitCode[i] == '1')
				Vertex = Uncode_Right[Vertex];
			else
				Vertex = Uncode_Left[Vertex];
		}
		else{
			Token.resize(1);
			Token[0] = (char)Tree_Letter[Vertex];
			New_Text = New_Text + Token;
			Vertex = 0;

			if (BitCode[i] == '1')
				Vertex = Uncode_Right[Vertex];
			else
				Vertex = Uncode_Left[Vertex];

		}
	}
	Token.resize(1);
	Token[0] = (char)Tree_Letter[Vertex];
	New_Text = New_Text + Token;
	Vertex = 0;

	for (int i=0; i<New_Text.size(); i++){
		if ((int)New_Text[i] == 12)
			New_Text[i] = ' ';
	}

	return New_Text;
}

int main(){
	Compressor C;
	Barrows_Wiler_Class BWC;
	MTF mtf;
	string B = C.Huffman_Back();
	string A = mtf.All_MTF_Back(B);
	string Answer = BWC.Barrows_Wiler_Transform_Back(A);

	cout << Answer;

	ofstream out("my_output.txt");
	out << Answer;
	out.close();
	
	return 0;
}