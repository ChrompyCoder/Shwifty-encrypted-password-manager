#include<iostream>
#include<string.h>
#include<string>
#include<fstream>
#include "sha3.cpp"
using namespace std;
void first_timer(fstream&);
void new_app(string, fstream& );
void checker(string, fstream& );
string encrypt_password(string, string, fstream& );
void display(fstream& );
void parse(char, string,fstream& );
string decrypt_password(string, string, fstream& );

int main(){
	cout<<"Welcome!"<<endl<<"[add new: a, discord: d, facebook: f, github: g, insta: i, mail:m, reddit: r]"<<endl;
	fstream passw("lockhead.txt", ios::app | ios::out | ios::in);

	if (passw.peek() == EOF) {
    	first_timer(passw);
  	} 
  	else {
    	display(passw);
  	}
	return 0;
}

void first_timer(fstream& passw){
	string passkey, pkey;
	cout<<"This is your first time! Read README.md for basic instructions and how this password manager works. Let's get started."<<endl<<"Enter common passkey( minimum 2 charecters and do not use ~, caret): ";
	cin>>pkey;
	passkey = pkey;
	SHA3 sha3;
	pkey= sha3(pkey);
	passw.seekg(0, ios::beg);
	passw<<pkey;
	new_app(passkey, passw);
}
void new_app(string pkey, fstream& passw){//add the application letter and add use this
	string username, password;
	char app_nm;
	cout<<endl<<"Which application? (d/f/g/i/m/r) "; cin>>app_nm;
	if(app_nm == 'a'){new_app(pkey, passw);}
	if(app_nm != 'd' && app_nm != 'f' && app_nm != 'g' && app_nm != 'i' && app_nm != 'm' && app_nm != 'r'){
		cout<<"This application is not available yet. Try another.";
		new_app(pkey, passw);
	}
	
	cout<<"Enter new application username: "; cin>>username;
	cout<<"Enter new application password: "; cin>>password;
	passw.seekg(0, ios::end);
	passw<<endl<<app_nm<<encrypt_password(username, pkey, passw);
	passw<<endl<<encrypt_password(password, pkey, passw);
	display(passw);
}

void checker(string pkey, fstream& passw){
	string encheck;
	SHA3 sha3;
	pkey = sha3(pkey);
	passw.seekg(0, ios::beg);
	passw>>encheck;
	if(encheck != pkey){
		cout<<"<Password rejected!>";
		display(passw);
	}
	cout<<"<verified>"<<endl;
}

string encrypt_password(string epass, string pkey, fstream& passw){
	int ascii1, ascii2, maxk=pkey.length();
	for(int i =0, k=0; epass[i]!='\0'; i++, k++){
		if( k>maxk){ k=0;} 
		ascii1 = epass[i];
		ascii2 = pkey[k];
		if( ascii1 == ascii2){continue;}
		else if(((ascii1%2!=0) && (ascii2%2==0)) || ((ascii1%2==0) && (ascii2%2!=0))) {
			ascii1=(ascii1+ascii2)/2;
			epass[i] = char(ascii1);
			i = i+1;
			epass.insert( i, "~");			
		}
		else{
			epass[i] = char((ascii1+ascii2)/2);
		}

	}
	return epass;
}
void display(fstream& passw){
	char app_nm; string pkey;
	cout<<"Common passkey: ";cin>>pkey;
	checker(pkey, passw);

	cout<<endl<<"Which application( for new press a)? (a/d/f/g/i/m/r) ";
	cin>>app_nm;
	//parse the file and retrieve data
	if (app_nm == 'a'){
		new_app(pkey, passw);
	}
	else{
		passw.seekg(0, ios::beg);
		parse(app_nm, pkey, passw);
	}
}

void parse(char app_nm, string pkey, fstream& passw){
	
	passw.seekg(64, ios::beg);
	char checknm;
	string usernm, pw;
	while(true){
		passw>>checknm;
		passw>>usernm;	
		passw>>pw;
		if(checknm == app_nm){
			cout<<"Username: "<<decrypt_password(usernm, pkey, passw)<<endl;
			cout<<"Password: "<<decrypt_password(pw, pkey, passw)<<endl;
			exit(1);
		}	
		if (passw.peek() == EOF) {
    			cout<<"The appllication data you are seeking for, does not exist yet or the service for that app is not available yet"<<endl;
			exit(1);
  		} 
	}
}
string decrypt_password(string dpass, string pkey, fstream& passw){
	int ascii1, ascii2, maxk=pkey.length();
	for(int i=0, k=0; dpass[i]!='\0'; i++,k++){
		if( k>maxk){ k=0;}
		ascii1 = dpass[i];
		ascii2 = pkey[k];
		if(dpass[i+1] == '~'){
			dpass.erase(i+1, 1);
			dpass[i]= char((ascii1*2)+1 - ascii2);
		}
		else if( ascii1 == ascii2){continue;} 
		else{
			dpass[i]=char((ascii1*2)- ascii2);
		}
	}
	return dpass;
}
