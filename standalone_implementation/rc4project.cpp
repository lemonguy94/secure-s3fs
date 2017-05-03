//Anthony Lemmon - eu6623
//CSC4420
//RC4 standalone implementation
#include <iostream>
#include <string>
#include <fstream>
#include "rc4_enc.c"
#include "rc4_skey.c"
using namespace std;

//Used a predefined key for testing, but decided to also create a local 
//password file for this purpose
#define KEY "testkeylol"
#define KEY_LENGTH (sizeof(KEY)-1)

//Prototype for crypt function
void decodeAndEncode(int argc, char *argv[]); 

//Main
int main(int argc, char *argv[]){
	if(argc < 2){
		cerr << "Error: File name not specified.";
		return 0;}
	else if(argc > 3){
		cerr << "Error: Too many arguments.";
		return 0;}
	else{
		decodeAndEncode(argc, argv);
		return 0;}}

void decodeAndEncode(int argc, char* argv[]){
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Password block
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	printf("Args: %d\n", argc);
	ifstream pass;
	pass.open("/home/stickshift/.pass.txt");
	if(pass.good()){ //Password file located
		printf("Pass: yes\n");
		string password;
		getline(pass,password);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	        //Input and output filestreams
	        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ifstream ifs(argv[1]);
	       	string data((istreambuf_iterator<char>(ifs)),
	               	(istreambuf_iterator<char>()));
	       	ofstream ouf;
		if(argc == 2){ //Single file for encrypt/decrypt
			ouf.open(argv[1], ios::binary);}
		else{ //Separate file to encrypt/decrypt to
			ouf.open(argv[2], ios::binary);}
	       	RC4_KEY key;
	       	int datalen = data.size();
	       	unsigned char *buffer = (unsigned char*)malloc(datalen + 1);
	       	memset(buffer, 0, datalen + 1);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	        //Encryption
	        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	       	RC4_set_key(&key, password.length(), (const unsigned char*)password.c_str());
	       	RC4(&key, datalen, (const unsigned char*)data.c_str(), buffer);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	        //Write to file
	        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	       	string ret((char*)buffer, datalen);
	       	free(buffer);
	       	ouf.clear(); 
	       	ouf << ret;
	       	ouf.close();}
	else{ //No password file
		printf("Error: password file not found. Continuing with default key.\n");
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	        //Input and output filestreams
	        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	        ifstream ifs(argv[1]);
	        string data((istreambuf_iterator<char>(ifs)),
	                (istreambuf_iterator<char>()));
	        ofstream ouf;
	        if(argc == 2){ //Single file for encrypt/decrypt
	                ouf.open(argv[1], ios::binary);}
	        else{ //Separate file to encrypt/decrypt to
	                ouf.open(argv[2], ios::binary);}
	        RC4_KEY key;
	        int datalen = data.size();
	        unsigned char *buffer = (unsigned char*)malloc(datalen + 1);
	        memset(buffer, 0, datalen + 1);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //Encryption
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                RC4_set_key(&key, KEY_LENGTH, (const unsigned char*)KEY);
                RC4(&key, datalen, (const unsigned char*)data.c_str(), buffer);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //Write to file
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                string ret((char*)buffer, datalen);
                free(buffer);
                ouf.clear();
                ouf << ret;
                ouf.close();}}

