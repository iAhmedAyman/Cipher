//Purpose: This is a program featuring 4 different encryption methods and their decryption. 1) Baconian Cipher, 2) Polybius Square Cipher,
//                                                                                          3) Morse code and 4) XOR Cipher

//Author: Ahmed Ayman Saeed Bakry

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void baconian_cipher();
bool bocanian_ciphered_check(string ciphered_text);
void baconian_decipher();
bool ishexa(string num);
bool morse_check(string morse);
void morse_cipher();
void morse_decipher();
bool polybius_ciphered_input(string ciphered, string &ciphered_nospaces);
void polybius_square_cipher();
void polybuis_square_decipher();
bool polybius_square_key(string key, string &key_nospaces);
bool str_isalpha(string text);
void xor_cipher();
void xor_decipher();

int main(){
	while (true){
		string options1 = "123", options2 = "12345";
		string first_choice;
		cout << "===============Ahlan ya user ya habibi===============" << endl;	
		cout << "Which would you like to do today?" << endl;
		cout << "1) Cipher a message" << endl << "2) Decipher a message" << endl << "3) Exit" << endl;
		getline(cin, first_choice);
		if (options1.find(first_choice) == string::npos){
			cout << "Invalid input, please chose one of the three options" << endl;
			continue;
		}
		if (first_choice[0] == options1[2]){
			break;
		}

		while (true){
		
			cout << "Which ciper do you want?" << endl;
			cout << "1) Baconian Cipher" << endl << "2) Polybius Square Cipher" << endl
				 << "3) Morse code" << endl << "4) XOR Cipher" << endl << "5) Return" << endl;;
            string second_choice;
            getline(cin, second_choice);
			if (options2.find(second_choice) == string::npos){
				cout << "Invalid input, please chose one of the four options" << endl;
				continue;
			}
			
			if (second_choice[0] == options2[4]){
				break;
				}
			else if (second_choice[0] == options2[0] && first_choice[0] == options1[0]){
				baconian_cipher();
				}
			else if (second_choice[0] == options2[0] && first_choice[0] == options1[1]){
				baconian_decipher();
				}
			else if (second_choice[0] == options2[1] && first_choice[0] == options1[0]){
				polybius_square_cipher();
				}
			else if (second_choice[0] == options2[1] && first_choice[0] == options1[1]){
				polybuis_square_decipher();
			}
			else if (second_choice[0] == options2[2] && first_choice[0] == options1[0]){
				morse_cipher();
				}
			else if (second_choice[0] == options2[2] && first_choice[0] == options1[1]){
				morse_decipher();
				}
			else if (second_choice[0] == options2[3] && first_choice[0] == options1[0]){
				xor_cipher();
				}
			else if (second_choice[0] == options2[3] && first_choice[0] == options1[1]){
				xor_decipher();
				}
		}
		
	}
}


//a function to check if the cipherd input is valid.
bool bocanian_ciphered_check(string ciphered_text) {
    for (int i = 0; i < ciphered_text.size(); i += 6) {
        for (int j = i; j < i + 5; j++) {
            if (ciphered_text[j] != 'a' && ciphered_text[j] != 'b') {
                return false;
            }
            else if (j == i + 4 && ciphered_text[j + 1] != ' ' && j < ciphered_text.size() - 1) {
                return false;
            }
        }

    }
    return true;
}

void baconian_cipher() {
    string text;
	cout << "Enter Text you want to cipher: ";
    getline(cin, text);

    //loop on every char in the text
    for (char letter : text) {
        if (isalpha(letter)) {     
            bitset<5> binary(letter - 'a'); //a binary representation for the letter
            string binary_letter = binary.to_string();
            for (char bit : binary_letter) {
                if (bit == '0') {
                    cout << 'a';
                }
                else {
                    cout << 'b';
                }
            }
            cout << ' ';
        }
    }
    cout << endl;
}

void baconian_decipher() {
    string ciphered_text;
    cout << "ciphered text: ";
    getline(cin, ciphered_text);
    //ciphered text has to be a string with 5-letter strings with only 'a' and 'b'.
    while (!bocanian_ciphered_check(ciphered_text)) {
		cout << "Invalid input, please make sure you enter only five of the letters 'a' and 'b' for each ciphered character." << endl;
        cout << "ciphered text: ";
        getline(cin, ciphered_text);
    }

    string text = "";
    //turn the binary repersentations of the letters back to chars
    for (int i = 0; i < ciphered_text.size(); i += 6) {
        string binary = "";
        for (int j = i; j < i + 5; j++) {
            if (ciphered_text[j] == 'a') {
                binary += '0';
            }
            else {
                binary += '1';
            }
        }
        text += stoi(binary, 0, 2) + 'a';
    }
    cout << text << endl;
}

bool polybius_square_key(string key, string &key_nospaces) {
    string key_elements = "12345"; //all possible numbers that can be in key
    bool isvalid = true;
    key_nospaces = "";
    while (key_nospaces.length() < 5) { 
        cout << "enter key as all the numbers from 1 to 5 in any order: ";
        getline(cin, key);
        key_nospaces = "";
        //ignore spaces
        for (int i = 0; i < key.size(); i++) {
            while (key[i] == ' ' && i < key.size()) {
                i++;
            }
            //if the current number can be in key and it wasn't seen before, continue.
            if (key_elements.find(key[i]) != string::npos && key_nospaces.find(key[i]) == string::npos) {
                key_nospaces += key[i];
            }
            else {
                isvalid = false;
                break;
            }
        }
    }
    return isvalid;
}

bool polybius_ciphered_input(string ciphered, string &ciphered_nospaces) {
    ciphered_nospaces = "";
    for (char num : ciphered) {
        if (num >= '1' && num <= '5') {
            ciphered_nospaces += num;
        }
        else if (num == ' ') {
            continue;
        }
        else {
            return false;
        }
    }
    if (ciphered_nospaces.size() & 2 != 0) {
        return false;
    }
    return true;
}

void polybius_square_cipher() {
    string table[5][5] = {{"A", "B", "C", "D", "E"},
                    {"F", "G", "H", "IJ", "K"},
                    {"L", "M", "N", "O", "P"},
                    {"Q", "R", "S", "T", "U"},
                    {"V", "W", "X", "Y", "Z"}};
    string text;
    cout << "Enter Text you want to cipher: ";
    getline(cin, text);
    string key, key_nospaces = "";
    bool isvalid = false;
    while (!isvalid) {
        isvalid = (polybius_square_key(key, key_nospaces));
    }
    //print the space if found
    for (int i = 0; i < text.size(); i++) {
        if (isspace(text[i])) {
            cout << ' ';
            continue;
        }
        //ignore any other alphabetic chars
        else if (!isalpha(text[i])) {
            continue;
        }
        //check the index of each digit in the number, and print it's letter.
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (table[j][k].find(toupper(text[i])) != string::npos) {
                    cout << key_nospaces[j] << key_nospaces[k];
                }
            }
        }
    }
    cout << endl;
}

void polybuis_square_decipher() {
    string table[5][5] = {{"A", "B", "C", "D", "E"},
                          {"F", "G", "H", "IJ", "K"},
                          {"L", "M", "N", "O", "P"},
                          {"Q", "R", "S", "T", "U"},
                          {"V", "W", "X", "Y", "Z"}};
    string ciphered, ciphered_nospaces = "";
    bool isInputValid = false;
    while (!isInputValid) { 
        cout << "Enter ciphered text: ";
        getline(cin, ciphered);
        isInputValid = polybius_ciphered_input(ciphered, ciphered_nospaces);
    }
    string key, key_nospaces = "";
    bool isKeyValid = false;
    while (!isKeyValid) {
        isKeyValid = polybius_square_key(key, key_nospaces);
    }
    //print spaces if found
    for (int i = 0; i < ciphered.size(); i += 2) {
        if (isspace(ciphered[i])) {
            cout << ' ';
            i--;
            continue;
        }
        //find the original letter by using the location of the key number in a list.
        string letter = table[key_nospaces.find(ciphered[i])][key_nospaces.find(ciphered[i+1])];
        if (letter == "IJ") {
            cout << 'I';
            continue;
        }
        cout << letter;
    }
    cout << endl;
}

bool morse_check(string morse) {
    string morse_code = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --..   ";
    int index = 0;
    while (index < morse.size() - 1){
        string token = "";
        while (morse[index] != ' ' && index < morse.size()) {
            token += morse[index];
            index++;
        }
        if (morse_code.find(token) == string::npos) {
            return false;
        }
        index++;
    }
    return true;
}

void morse_cipher() {
    string morse_code[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
                           "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    string text;
    cout << "Enter Text you want to cipher: ";
    getline(cin, text);
    for (char letter : text) {
        if (isspace(letter)) {
            cout << "   ";
            continue;
        }
        else if (!isalpha(letter)) {
            continue;
        }
        cout << morse_code[tolower(letter) - 'a'] << ' '; //get the rank of the letter using ascii and use that to print the correct morse code form the array
    }
    cout << endl;
}

void morse_decipher() {
    string morse_code[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
                           "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    string morse;
    cout << "Enter morse code to decipher: ";
    getline(cin, morse);
    bool isvalid = morse_check(morse);
    while (!isvalid) {
        cout << "Invalid input, please enter valid morse code to decipher." << endl;
        getline(cin, morse);
        isvalid = morse_check(morse);
    }

    int index = 0;
    while (index < morse.size() - 1){
        string token = "";
        while (morse[index] != ' ' && index < morse.size()) {
            token += morse[index];
            index++;
        }
        for (int i = 0; i < 26; i++) {
            if (token == morse_code[i]) {
                cout << (char) (i + 'a');
            }
        }
        if (isspace(morse[index]) && isspace(morse[index+1]) && isspace(morse[index+2])) {
            cout << ' ';
            index += 3; continue;
        } 
        index++;
    }
    cout << endl;
}

void xor_cipher(){
	string text;
	cout << "Please enter the message to cipher: ";
	getline(cin, text);
	//if the text is empty ask the user again
	while (text.size() == 0){
		cout << "Please enter the message to cipher: ";
		getline(cin, text);
	}

	string key;
	cout << "Key (a sequence of letters): ";
	getline(cin, key);
	//the key has to be a letter or more
	while (key.empty() || !str_isalpha(key)){
		cout << "Invalid input, the key can only contain letters: ";
		getline(cin, key);
	}
	
	//the XOR operation
	string cipher_text = "";
	for (int i = 0; i < text.length(); i++){
        char result = text[i] ^ key[i % key.length()]; //i % key.length() loops from 0 to key.length() - 1 depending on the value of i
		//don't print unprintable values
        if (result > 32){ 
		    cipher_text += result;
		}

	}
	//print ciphered text
	cout << cipher_text << endl;
	
	//print ciphered hexa
	for (int i = 0; i < text.length(); i++){
        char result = text[i] ^ key[i % key.length()];
        cout << hex << (int) result << " ";

	}
	cout << endl;
	
	}

void xor_decipher(){
	cout << "Key: ";
	string key;
	int keyCounter = 0;
	getline(cin, key);
	cout << endl;
	cout << "Cipher hexa: ";
	string hexa, hexaNoSpac;
	getline(cin, hexa);

	//hexa has to be a string containig pairs of hexadecimal numbers without spaces between them
	while (!ishexa(hexa) || hexa.size() % 2 != 0)
	{
		cout << "Invalid input, please make sure to insert hexadecimal values in the form XX, for example 0f, and with no spaces." << endl;
		cout << "Cipher hexa: ";
		getline(cin, hexa);
	}


	//iterate on hexa and get each hexadecimal pair and decipher it and print it
	for (int i = 0; i < hexa.size(); i += 2){
		string token = string(1, hexa[i]) + hexa[i + 1];
		int num_hexa = stoi(token, nullptr, 16);
        cout << (char) (num_hexa ^ key[keyCounter % key.length()]);
		keyCounter++;
	}
	cout << endl;
}

//checks if all chars in a string are letter
bool str_isalpha(string text){
	for (int i = 0; i < text.size(); i++){
		if (!isalpha(text[i])){
			return false;
		}
	}
	return true;
}

//checks if a string is a hexadecimal number
bool ishexa(string num){
	bool hexa;
	for (int i = 0; i < num.size(); i++){
		if (num[i] >= 'a' && num[i] <= 'f' || num[i] >= '0' && num[i] <= '9'){
			hexa =  true;
		}
		else {
			return false;
		}
	}
	return hexa;
}
