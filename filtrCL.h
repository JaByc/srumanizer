class filtrCL
{
	public:
		string FiltrName_file;
		vector <string> filtrArg;
		filtrCL(string FiltrName, vector <string> from);
		filtrCL(): FiltrName_file(""), filtrArg(0){}
		filtrCL(const filtrCL & copi){
			FiltrName_file = copi.FiltrName_file;
			filtrArg       = copi.filtrArg;

		}

		int getSize();
		string getVar( int j);
};

filtrCL::filtrCL(string  FiltrName, vector <string> from){
	FiltrName_file = FiltrName;
	filtrArg  = from;
}

int filtrCL::getSize(){
	int answer = filtrArg.size();
	return answer;
}

string filtrCL::getVar( int j){
	string ans;
	ans = filtrArg[j];
	return ans;
}

