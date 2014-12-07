class humanizerLINE //klasa zarzadzajaca liniami
{
	public:
		vector <string> line;			// stash code
		string lineIN;
		int sep;				// jaki separator ma linia		
		humanizerLINE(string lineIN, int sep);  // konstruktor
		void setVar(string Var, int ncol); 	// ustawia na miejscy ncol wartosc Var (w wektorze) Liczby
		string getVar(int ncol);		// pobiera wartosc z miejsca ncol wektora Liczby
		void ShowVarKS();			// funkcja wypisujaca wszystkie atrybuty naszej zmiennej (base_VAR)
		void ShowVarKS(int withOUT);
		void ShowVarKSrm(vector <int> withOUT);
		void VarKSrm(vector <int> withOUT);

		void ShowVarKSfiltr(vector <filtrCL> filtrALL, vector <string> header);
		int VarKSfiltr(vector <filtrCL> filtrALL, vector <string> header);

		void ShowVarKSspell( vector <fspellCL> SpellALL, vector <string> header );
		void VarKSspell( vector <fspellCL> SpellALL, vector <string> header );

		humanizerLINE( const humanizerLINE & copi){	//Konstruktor kopiujacy chuj wie po co :) - no dobra wiem po co...
			sep  = copi.sep;
			line = copi.line;
			lineIN = copi.lineIN;
		}
		humanizerLINE() : line(20), lineIN("") , sep(-2) {}
};

void humanizerLINE::ShowVarKS(){
	for( int i = 0; i < line.size() -1 ; ++i){
		cout << line[i]<<';';
	}
	cout << line[line.size() -1] << endl;
}

void humanizerLINE::ShowVarKS(int withOUT){
    if( withOUT != line.size() - 1 ){
	for( int i = 0; i < line.size() - 1 ; ++i){
		if( i != withOUT ) cout << line[i] <<';';
	}
	cout << line[line.size() -1] << endl;
    }else{
	for( int i = 0; i < line.size() - 2 ;++i){
		cout << line[i] <<';';	
	}
	cout << line[line.size() - 2] << endl;
    }
}

void humanizerLINE::ShowVarKSrm(vector <int> withOUT){
	vector <string> lineTMP = line;
	int left  = 0;
	int right = withOUT.size() - 1;
	//szybkiSORT(vector <int> & withOUT , left, right);
	
	for(int i = withOUT.size() - 1 ; i >=0  ; i--){
		lineTMP.erase( lineTMP.begin() + withOUT[i] );
	}
	
	for( int i = 0; i < lineTMP.size() -1 ; ++i){
		cout << line[i]<<';';
	}
	cout << line[line.size() -1] << endl;
}

void humanizerLINE::ShowVarKSfiltr(vector <filtrCL> filtrALL, vector <string> header){
	//filtrALL przechowuje nazwy plikow w ktorych sa filtry oraz same filtry
	//nazwy plikow sa takie same jak nazwy kolumn ktorych dotycza
	//int whichSR(string v1, vector <string> v2); //szuka gdzie elementy z v1 są w v2 (na ktorym miejscu)
	vector <int> check;
	check.push_back(0);
	int tmp;
	//vector <int> check;
	for(int i = 0; i < filtrALL.size(); i++){	
		tmp = whichSR( filtrALL[i].FiltrName_file , header );
		//which.push_back(tmp);
		
		for(int j = 0; j < filtrALL[i].getSize(); j++ ){
			if( line[tmp] == filtrALL[i].getVar(j) ) check.push_back(1);
		}
	}

	if( sumVec(check) != 0){
		for( int i = 0; i < line.size() -1 ; ++i){
			cout << line[i]<<';';
		}
		cout << line[line.size() -1] << endl;
	}

}

void humanizerLINE::ShowVarKSspell(vector <fspellCL> SpellALL, vector <string> header){
	vector <int> which;
	int tmp;
	
	for(int i = 0; i < SpellALL.size(); i++ ){
		tmp = whichSR( SpellALL[i].SpellName_file, header );
		for( int j = 0; j < SpellALL[i].getSize(); j++){
			 if( line[tmp] == SpellALL[i].getVar_For(j) ) line[tmp] = SpellALL[i].getVar_On(j);
		}
	}

	for( int i = 0; i < line.size() -1 ; ++i){
		cout << line[i]<<';';
	}
	cout << line[line.size() -1] << endl;
}

void humanizerLINE::setVar(string Var, int ncol){
	line[ncol] = Var;
}

string humanizerLINE::getVar(int ncol){
	string answer;
	answer = line[ncol];
	return answer;
}

humanizerLINE::humanizerLINE (string lineIN, int FS) {
	sep = FS;
	int start = 0, end = 0 ;

	const char *lineWSK = lineIN.c_str();
	string tmp;

	for(int i = 0; i <= lineIN.length(); i++ ){
		if( (int)lineWSK[i] == sep ||  i == lineIN.length() ){			
			end = i;
			tmp = lineIN.substr(start, end - start);
			line.push_back(tmp);
			start = end+1;
		}
	}		
}

//================ Przeladowane Funckje Show zeby bez show ale z dzialaniem
/* */
void humanizerLINE::VarKSrm(vector <int> withOUT){
	vector <string> lineTMP = line;
	int left  = 0;
	int right = withOUT.size() - 1;
	for(int i = withOUT.size() - 1 ; i >=0  ; i--){
		lineTMP.erase( lineTMP.begin() + withOUT[i] );
	}
	line = lineTMP;
}


int humanizerLINE::VarKSfiltr(vector <filtrCL> filtrALL, vector <string> header){
	//filtrALL przechowuje nazwy plikow w ktorych sa filtry oraz same filtry
	//nazwy plikow sa takie same jak nazwy kolumn ktorych dotycza
	//int whichSR(string v1, vector <string> v2); //szuka gdzie elementy z v1 są w v2 (na ktorym miejscu)
	vector <int> check;
	check.push_back(0);

	int tmp;
	for(int i = 0; i < filtrALL.size(); i++){
		tmp = whichSR( filtrALL[i].FiltrName_file , header );	
		for(int j = 0; j < filtrALL[i].getSize(); j++ ){
			if( line[tmp] == filtrALL[i].getVar(j) ) check.push_back(1);
		}
	}
	if( sumVec(check) != 0){
		return 1;
	}else{
		return 0;
	}
}

void humanizerLINE::VarKSspell(vector <fspellCL> SpellALL, vector <string> header){
	vector <int> which;
	int tmp;
	
	for(int i = 0; i < SpellALL.size(); i++ ){
		tmp = whichSR( SpellALL[i].SpellName_file, header );
		for( int j = 0; j < SpellALL[i].getSize(); j++){
			 if( line[tmp] == SpellALL[i].getVar_For(j) ) line[tmp] = SpellALL[i].getVar_On(j);
		}
	}
}



