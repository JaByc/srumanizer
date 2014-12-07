
//zbiór funkcji do zarządzania flagami

string getflags(string argN){
	string answer;
	sep = ' ';
	int start = 0, end = 0 ;
	const char *liniaWSK = argN.c_str();
	for(int i = 0; i < linia.length(); i++ ){
		if( liniaWSK[i] == separator ){
			answer = argcN.substr(start, end - start);
			break;
		}
	}
return answer;
}

void SetFlagArg(string argN, vector <string> &Args){
	string answer;
	sep = ' ';
	int size = 0;
	int start = 0, end = 0 ;
	const char *liniaWSK = argN.c_str();
	for(int i = 0; i < linia.length(); i++ ){
		if( liniaWSK[i] == separator ){
		start=i
		size++;
			if(size > 1){
				answer = argcN.substr(start, end - start);
				flags.push_back(answer)
			}
		start = end+1;
		}
	}	
}
