class srumanizerFlagsCl{
	public:
		string flag;
		vector <string> ArgFlag;
		srumanizerFlagsCl(string ProgArgs);
		srumanizerFlagsCl(): flag(""), ArgFlag(0){}
		string getArg(int n);
		int getSize(); 

		srumanizerFlagsCl(const srumanizerFlagsCl &copi){
			flag = copi.flag;
			ArgFlag = copi.ArgFlag;

		}
};

srumanizerFlagsCl::srumanizerFlagsCl(string ProgArgs){
	string answer;
	char sep = '_';
	int size = 0;
	int start = 0, end = 0 ;
	const char *liniaWSK = ProgArgs.c_str();
	for(int i = 0; i < ProgArgs.length(); i++ ){
		if( liniaWSK[i] == sep ){
			end=i;
			size++;
			if (size == 1){
				answer = ProgArgs.substr(start, end - start);
				flag = answer;
			}
			if (size > 1){
				answer = ProgArgs.substr(start, end - start);
				ArgFlag.push_back(answer);
			}
			start = end + 1;
		}
	}	
}

string srumanizerFlagsCl::getArg(int n){
	string answerTMP = ArgFlag[n];
	return answerTMP;
}
int srumanizerFlagsCl::getSize(){
	int tmp = ArgFlag.size();
	return tmp;
}

