#include<iostrem>
#include<encrypter.cpp>
#include<decrypter.cpp>
#include<string.h>
#include<fstream>
using namespace std;

int main(){
	cout<<"Welcome!"<<endl<<"[add new: a, discord: d, facebook: f, github: g, insta: i, mail:m, raddit: r]"<<endl;
	fstream passw("lockhead.txt", ios::app | ios::out | ios::in);
	if (is_empty(file)){
		first_timer();
	}
	else{
		display();
	}
	return 0;
}


