void first_timer(){
	string passkey;
	cout<<"This is your first time! Read README.md for basic instructions and how this password manager works. Let's get started."<<endl<<"Enter common passkey( minimum 2 charecters and do not use ^, caret): ";
	cin>>passkey;

	//encrypt and rewrite passkey
	passkey = get::getHash(ALGORITHMS::SHA2_384, passkey);
	passw<<passkey;
	new_app();
}
void new_app(string pkey){//add the application letter and add use this
	string username, password;
	char app_nm;
	cout<<endl<<"Which application? (d/f/g/i/m/r) "; cin>>app_nm;
	if(app_nm == 'a'){new_app(pkey);}
	if(app_nm != 'd' && app_nm != 'f' && app_nm != 'g' && app_nm == 'i' && app_nm != 'm' && app_nm != 'r'){
		cout<<"This application is not available yet. Try another.";
		new_app();
	}
	
	cout<<"Enter new application username: "; cin>>username;
	cout<<"Enter new application password: "; cin>>password;
	passw.seekg(0, ios::end);
	passw<<endl<<app_nm<<encrypt_password(username, pkey);
	passw<<endl<<encrypt_password(password, pkey);
	display();
}

void checker(string pkey){
	string encheck;
	pkey = get::getHash(ALGORITHMS::SHA2_384, pkey);
	passw.seekg(0, ios::beg);
	getline(passw, encheck);
	if(strcmp(encheck, pkey)){
		return 0;
	}
	cout<<"<verified>"<<endl;
}

string encrypt_password(string epass, string pkey){
	int ascii1, ascii2;
	for(int i =0, k=0; epass[i]!='\0'; i++, k++){
		if( pkey[k] == '\0'){ k=0;} 
		ascii1 = epass[i];
		ascii2 = pkey[k];
		if( ascii1 == ascii2){continue;}
		else if((ascii1%2!=0) && (ascii2%2!=0)){
			ascii1=(ascii1+ascii2)/2;
			epass[i] = char(ascii1);
			i = i+1;
			epass.insert( i, '^');			
		}
		else{
			epass[i] = char((ascii1+ascii2)/2);
		}

	}
	return epass;
}
