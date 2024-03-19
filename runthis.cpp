#include<iostream>
#include<string.h>
#include<string>
#include<fstream>
#include "sha3.cpp" // This is the external library used.
using namespace std;
// List of all the user-defined functions used:
void first_timer(fstream&);
void new_app(string, fstream& );
void checker(string, fstream& );
string encrypt_password(string, string, fstream& );
void display(fstream& );
void parse(char, string,fstream& );
string decrypt_password(string, string, fstream& );

int main(){
	cout<<"Welcome!"<<endl<<"[add new: a, discord: d, facebook: f, github: g, insta: i, mail:m, reddit: r]"<<endl;
	fstream passw("lockhead.txt", ios::app | ios::out | ios::in); // Opens the file which stores the password in encrypted format.

	if (passw.peek() == EOF) { 
    	first_timer(passw); // Run this if the file is empty, that is if you have run runthis.cpp for the first time.
  	} 
  	else {
    	display(passw); // Usual display if data inside lockhead.txt exists
  	}
	return 0;
}
// Common misinterpretation: You need to pass the file object to the functions as you cannot use it as a global variable.
void first_timer(fstream& passw){
	string passkey, pkey;
	cout<<"This is your first time! Read README.md for basic instructions and how this password manager works. Let's get started."<<endl<<"Enter common passkey( minimum 2 charecters and do not use ~, caret): ";
	cin>>pkey; // This is the common passkey which is used to encrypt/decrypt data.
	passkey = pkey;
	SHA3 sha3;
	pkey= sha3(pkey);
	passw.seekg(0, ios::beg);
	passw<<pkey;
	// Produce a SHA3 of the common passkey and store it in the file.
	// Now everytime runthis.cpp is run, it asks for the common passkey and verifies it with the stored SHA before proceeding.
	new_app(passkey, passw);
}
void new_app(string pkey, fstream& passw){
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
	passw.seekg(0, ios::end); // Go to the end of the file to write data of new application.
	// Encrypt and add the username and password to the lockhead.txt file.
	passw<<endl<<app_nm<<encrypt_password(username, pkey, passw); 
	passw<<endl<<encrypt_password(password, pkey, passw);
	display(passw);
}

void checker(string pkey, fstream& passw){ // This function verifies the common passkey entered to the stored hash of actual common passkey.
	string encheck;
	SHA3 sha3;
	pkey = sha3(pkey); // Hash the entered passkey for verification. 
	passw.seekg(0, ios::beg);
	passw>>encheck; // Retrieve hash value of the actual common passkey.
	if(encheck != pkey){ // Verificaton
		cout<<"<Password rejected!>";
		display(passw);
	}
	cout<<"<verified>"<<endl;
}

void display(fstream& passw){ // This is the common interface. That is the following is displayed everytime you run the runthis.cpp file after setting the common passkey.
	char app_nm; string pkey;
	cout<<"Common passkey: ";cin>>pkey;
	checker(pkey, passw); // Check if the entered passkey is correct or not.

	cout<<endl<<"Which application( for new press a)? (a/d/f/g/i/m/r) ";
	cin>>app_nm;
	if (app_nm == 'a'){ // If you want to add a new application data then it takes you to that interface.
		new_app(pkey, passw);
	}
	else{ // Normal retrieval of data.
		passw.seekg(0, ios::beg);
		parse(app_nm, pkey, passw);
	}
}

void parse(char app_nm, string pkey, fstream& passw){ // Paser for the lockhead.txt to retrieve the data.
	
	passw.seekg(64, ios::beg);
	char checknm;
	string usernm, pw;
	while(true){
		// Retrieve the encrypted data and store it in a specific variable.
		passw>>checknm;
		passw>>usernm;	
		passw>>pw;
		if(checknm == app_nm){
			// Decrypt the encrypted data and display it.
			cout<<"Username: "<<decrypt_password(usernm, pkey, passw)<<endl;
			cout<<"Password: "<<decrypt_password(pw, pkey, passw)<<endl;
			exit(1);
		}	
		if (passw.peek() == EOF) { // If data does not exists: 
    			cout<<"The appllication data you are seeking for, does not exist yet or the service for that app is not available yet"<<endl;
			exit(1);
  		} 
	}
}

string encrypt_password(string epass, string pkey, fstream& passw){ // Encrypts the username and password of a application using the common passkey.
	int ascii1, ascii2, maxk=pkey.length();
	// The following block of code encrypts username and password. How?
	// Encryption is done by taking the average of ASCII values of a character of username/password and a character of the common passkey.
	// Try runing the following code seperately with your own values of username/password( here, epass) and the common passkey( here, pkey).
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
	return epass; // The encrypted string is returned.
}

string decrypt_password(string dpass, string pkey, fstream& passw){ // Reverses the encryption and returns the decrypted string.
	int ascii1, ascii2, maxk=pkey.length();
	// The following block decrypts the string passed though the argument by reversing what is used in for encryption.
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
