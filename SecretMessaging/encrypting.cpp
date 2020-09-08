#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main() {
	
	vector<int> key { 1, 20};

	//string message = "hello world";
	cout << "Please type in a message to encrypt:\n";
	string message;
	getline(cin, message);
	
	//cout << key.size() << "\n";
	
	for(size_t i = 0; i< message.size(); ++i) {
		//cout << message[i];
		message[i] += key[i%key.size()];
	}
	
	//cout << message;
	
	ofstream file;
    file.open("message.txt");
	
	file << message;
	
	file.close();
}