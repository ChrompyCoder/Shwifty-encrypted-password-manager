
//learn and add SHA1

void first_timer(){
	string passkey;
	cout<<"This is your first time! Read README.md for basic instructions and how this password manager works. Let's get started."<<endl<<"Enter common passkey: ";
	cin>>passkey;

	//encrypt and rewrite passkey
	
	passw<<passkey;
	new_app();
}
void new_app(){//add the application letter and add use this
	string username, password;
	char app_nm;
	cout<<endl<<"Which application? (a/d/f/g/i/m/r) "; cin>>app_nm;

	cout<<"Enter new application username: "; cin>>username;
	cout<<"Enter new application password: "; cin>>password;
	passw.seekg(0, ios::end);
	passw<<endl<<app_nm<<encrypt_password(username);
	passw<<endl<<encrypt_password(password);
	display();
}

void checker(string pkey){
	string encheck;
	pkey = encrypt_password(pkey);
	passw.seekg(0, ios::beg);
	getline(opassw, encheck)
	if(strcmp(encheck, pkey){
		return 0;
	}
	cout<<"<verified>"<<endl;
}

string encrypt_password(string epass){}
