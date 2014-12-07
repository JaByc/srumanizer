#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iterator>
#include <cmath>
#include <algorithm>

using namespace std;


int whichSR(string v1, vector <string> & v2); //szuka gdzie elementy z v1 są w v2 (na ktorym miejscu)
void szybkiSORT(vector <int> &d , int lewy, int prawy);
int sumVec(vector <int> v1);
#include "filtrCL.h"
#include "fspellCL.h"
#include "srumanizerFlagsCl.h"
#include "Srumanizer.h"
 


int main(int argc, char *argv[]){

//cout << "=============================================================================" << endl;
char* source_file = argv[1];

if(argc < 4){

	humanizerLINE header;

	//seperator jako drugi argument programu
	stringstream sep_str;
	string tmpSEP =string(argv[2]);
	sep_str << tmpSEP;
	int sep;
	sep_str >> sep;
	sep_str.clear();

	fstream tmp;
	tmp.open(source_file,ios::in);
	string STRtmp;
		while(true){//ta petla jest potrzebna bo warunek !file.eof() wczytuje i jeden znka za duzo i nalicza sie dodatkowy wiersz
		getline(tmp,STRtmp,'\n');
			humanizerLINE tmp(STRtmp,sep);
			header = tmp;
			break;
		}
	tmp.close();


int ncol = -1;

fstream file;
file.open(source_file,ios::in);
string lineF;
	while(!file.eof()){			
		getline(file,lineF,'\n');
		humanizerLINE varZM(lineF, sep );
		varZM.ShowVarKS();
	}
file.close();
return 0;
}

else{
	
	

	/*
	========================================================================
	========================================================================
	Druga czesc programu do podmiany slow  w kolumnach
	(zadziala jak dodamy plik z slownikiem)
	========================================================================
	========================================================================
	*/

	string Narg;
	vector <srumanizerFlagsCl> answer;
	vector <string> FlagOn;
	for( int i = 3; i < argc; i++ ){
		Narg = string( argv[ i ] );
		srumanizerFlagsCl tmp( Narg );
		answer.push_back( tmp );
		FlagOn.push_back( tmp.flag );
	}

	int optRM    = whichSR("-rm"   , FlagOn);
	int optSpell = whichSR("-spell", FlagOn);
	int optFiltr = whichSR("-filtr", FlagOn);

//	for(int i = 0; i < answer[optRM].getSize() ; i++) cout << answer[optRM].getArg(i) <<" ";

// ============= Modul obslugi usuwania kolumn z wierszy

	vector <int> RM_Args;

	stringstream RM_ArgsSTR;	
	if( optRM >= 0 ){
		int RM_ArgsTMP;
		for( int i = 0 ; i < answer[optRM].getSize(); i++){
			RM_ArgsSTR << string(answer[optRM].getArg(i));
			RM_ArgsSTR >> RM_ArgsTMP;
			RM_Args.push_back( RM_ArgsTMP );
			RM_ArgsSTR.clear();
		}
		szybkiSORT(RM_Args, 0 , RM_Args.size() -1 );
	}
//	for(int i = 0; i < RM_Args.size() ; i++) cout << RM_Args[i] <<" ";
	RM_ArgsSTR.clear();

// ==============================================================================
// ============= Modul obslugi usuwania wirszy ktore nie spelniaja zalozen filtru

	vector <filtrCL> filtrIN; 
	fstream filtr_str;
	string filtrWord;

	if( optFiltr >= 0){
		filtrCL filtr_clTMP;
		string filtr_fileTMP;
		for( int i = 0; i < answer[optFiltr].getSize(); i++){
			filtr_fileTMP = answer[ optFiltr ].getArg( i );
			filtr_clTMP.FiltrName_file = filtr_fileTMP;
			filtr_str.open( filtr_fileTMP.c_str() , ios::in );
			vector <string> filtrWords;
			while( true ){
				getline( filtr_str , filtrWord ,'\n');
				if( filtr_str.eof() ) break;
				if( filtrWord.length() != 0 ){
					filtrWords.push_back( filtrWord );
				}
			}
			if( filtrWords.size() > 0){
				filtr_clTMP.filtrArg = filtrWords;
				filtrIN.push_back(filtr_clTMP);
			}
			filtr_str.clear();
			filtr_str.close();
		}
	}

// ==============================================================================
// ============= Modul obslugi slownikow


	vector <fspellCL> spellIN; 
	fstream spell_str;
	string spellWord;
	const char * spell_idx;

	if( optSpell >= 0){
		fspellCL spell_clTMP;
		string spell_fileTMP;
		string spellWord;
		for( int i = 0; i < answer[optSpell].getSize(); i++){
			spell_fileTMP = answer[ optSpell ].getArg( i );
			spell_clTMP.SpellName_file = spell_fileTMP;
			spell_str.open( spell_fileTMP.c_str() , ios::in );
			vector <string> spellFrom;
			vector <string> spellOn;

			string tmpFrom;
			string tmpOn;
			while( true ){
				getline( spell_str , spellWord ,'\n');
				if( spell_str.eof() ) break;
				if( spellWord.length() > 3 ){
					spell_idx = spellWord.c_str();
					for(int j = 0; j <= spellWord.length(); j++){
						if( spell_idx[j] == ';' ){			
							tmpFrom = spellWord.substr(0, j);
							tmpOn = spellWord.substr(j+1, spellWord.length());
							spellFrom.push_back( tmpFrom );
							spellOn.push_back( tmpOn );

						}
					}					
				}
			}
			spell_clTMP.forArg = spellFrom;
			spell_clTMP.onArg  = spellOn;
			spellIN.push_back(spell_clTMP);
			spell_str.clear();
			spell_str.close();
		}
	}


// ==============================================================================
	humanizerLINE header;

	//seperator jako drugi argument programu
	stringstream sep_str;
	string tmpSEP =string(argv[2]);
	sep_str << tmpSEP;
	int sep;
	sep_str >> sep;
	sep_str.clear();

	fstream tmp;
	tmp.open(source_file,ios::in);
	string STRtmp;
		while(true){//ta petla jest potrzebna bo warunek !file.eof() wczytuje i jeden znka za duzo i nalicza sie dodatkowy wiersz
		getline(tmp,STRtmp,'\n');
			humanizerLINE tmp(STRtmp,sep);
			header = tmp;
			break;
		}
	tmp.close();

	fstream file;
	file.open(source_file,ios::in);
	string lineF;
	vector <string> header_spell = header.line;

	if( optSpell >= 0 ){
		vector <string> headerForSpell = header.line;
		for(int i = 0; i < headerForSpell.size() ; i++ ){
			header_spell[i] += ".spell" ;
			//header_spell.push_back(header.line[i]);
		}
	}

	while(true){
		getline(file,lineF, '\n');
		if( file.eof()) break;
		if( lineF.length() != 0){
//			cout << lineF << endl;
			humanizerLINE varZM(lineF, sep );
			if( optFiltr >= 0 && varZM.VarKSfiltr( filtrIN, header.line) == 1 ){
				if( varZM.VarKSfiltr( filtrIN, header.line) == 1 ) break;
				if( optSpell >= 0 ) varZM.VarKSspell( spellIN, header_spell );
				if( optRM >= 0) varZM.VarKSrm( RM_Args );
				varZM.ShowVarKS();
			}else{
				if( optSpell >= 0 ) varZM.VarKSspell( spellIN, header_spell );
				if( optRM >= 0) varZM.VarKSrm( RM_Args );				
				varZM.ShowVarKS();
			}
		}
	}
	file.close();

	return 0;
}


}


int whichSR(string v1, vector <string> &v2){
	int k; 
	for( k =0 ; k < v2.size(); k++){
		if( v1 == v2[k] ) break;		
	}
	if(k == v2.size() ) return -1;
return k;
}

void szybkiSORT(vector <int> &d , int lewy, int prawy) 		//int prawy - to nieliczba elementow w wektorze d
{								
// int prawy to numer ostatniego elementu czyli rozmiar wektora pomniejszony o 1
  int i,j;
  int piwot;

  i = (lewy + prawy) / 2;
  piwot = d[i]; d[i] = d[prawy];
  for(j = i = lewy; i < prawy; i++)
  if(d[i] < piwot)
  {
    swap(d[i], d[j]);
    j++;
  }
  d[prawy] = d[j]; d[j] = piwot;
  if(lewy < j - 1)  szybkiSORT( d , lewy, j - 1);
  if(j + 1 < prawy) szybkiSORT( d , j + 1, prawy);
}

int sumVec(vector <int> v1){
	int sum = 0;
	for(int i = 0; i < v1.size(); i++){
		sum = sum + v1[i];
	}
return sum;
}




