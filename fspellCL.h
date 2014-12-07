class fspellCL
{
	public:
		string SpellName_file;
		vector <string> forArg;
		vector <string> onArg;
		fspellCL(string SpellName, vector <string> from , vector <string> on);
		fspellCL(): SpellName_file(""), forArg(0), onArg(0){}
		fspellCL(const fspellCL & copi){
			SpellName_file = copi.SpellName_file;
			forArg	       = copi.forArg;
			onArg	       = copi.onArg;
		}

		int getSize();
		string getVar_For( int j);
		string getVar_On( int j);
};

fspellCL::fspellCL(string SpellName, vector <string> from , vector <string> on){
	SpellName_file = SpellName;
	onArg 	 = on;
	forArg	 = from;
}

int fspellCL::getSize(){
	int answer = forArg.size();
	return answer;
}


string fspellCL::getVar_For( int j){
	string ans;
	ans = forArg[j];
	return ans;
}

string fspellCL::getVar_On( int j){
	string ans;
	ans = onArg[j];
	return ans;
}

