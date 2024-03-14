#include<iostream>
#include<encrypter.cpp>
#include<decrypter.cpp>
#include<string.h>
#include<string>
#include<fstream>
#include<hashpp.h>
using namespace hashpp;
using namespace std;

int main(){
	cout<<"Welcome!"<<endl<<"[add new: a, discord: d, facebook: f, github: g, insta: i, mail:m, reddit: r]"<<endl;
	fstream passw("lockhead.txt", ios::app | ios::out | ios::in);
	if (is_empty(file)){
		first_timer();
	}
	else{
		display();
	}
	return 0;
}
