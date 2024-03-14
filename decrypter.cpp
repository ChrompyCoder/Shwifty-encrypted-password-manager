void display(){
	char app_nm; string pkey;
	cout<<"Common passkey: ";cin>>pkey;
	checker(pkey);
	cout<<endl<<"Which application( for new press a)? (a/d/f/g/i/m/r) ";
	cin>>app_nm;
	//parse the file and retrieve data
	if (app_nm == a){
		new_app(pkey);
	}
	else{
		passw.seekg(0, ios::beg);
		parse(app_nm, pkey);
	}
}

void parse(char app_nm, string pkey){
	passw.seekg(96, ios::beg);
	char checknm;
	string usernm, pw;
	while(true){
		passw>>checknm;
		passw>>usernm;	
		passw>>pw;
		if(checknm == app_nm){
			cout<<"Username: "<<decrypt_password(usernm, pkey)<<endl;
			cout<<"Password: "<<decrypt_password(pw, pkey)<<endl;
			return 0;
	}	
}}
string decrypt_password(string dpass, string pkey){
	int ascii1, ascii2;
	for(int i=0, k=0; dpass[i]!='\0'; i++,k++){
		if( pkey[k] == '\0'){ k=0;}
		ascii1 = dpass[i];
		ascii2 = pkey[k];
		if( ascii1 == ascii2){continue;}
		else if(dpass[i+1] == '^'){
			dpass.erase(i+1, 1);
			dpass[i]= char((ascii1*2)+1 - ascii2);
		}
		else{
			dpass[i]=char((ascii1*2) - ascii2);
		}
	}
	return dpass;
}
