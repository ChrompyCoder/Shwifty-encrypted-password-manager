void display(){
	char app_nm; string pkey;
	cout<<"Common passkey: ";cin>>pkey;
	checker(pkey);
	cout<<endl<<"Which application( for new press a)? (a/d/f/g/i/m/r) ";
	cin>>app_nm;
	//parse the file and retrieve data
	if (app_nm == a){
		new_app();
	}
	else{
		passw.seekg(0, ios::beg);
		parse(app_nm);
	}
}

void parse(char app_nm){
	passw.seekg(40, ios::beg);
	char checknm='a';
	string usernm, pw;
	while(true){
		passw>>checknm;
		passw>>usernm;	
		passw>>pw;
		if(checknm == app_nm){
			cout<<"Username: "<<decrypt_password(usernm)<<endl;
			cout<<"Password: "<<decrypt_password(pw)<<endl;
			return 0;
	}	
}
string decrypt_password(string dpass){}


