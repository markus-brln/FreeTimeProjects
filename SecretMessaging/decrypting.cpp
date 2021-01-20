#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main() {
	
	vector<int> key { 1, 20};

	string message;
	//cin >> message;
	
	ifstream file;
    file.open("message.txt");
	
	
	
	while(getline(file, message)) {
		for(int i = 0; i < message.size(); ++i) {
			message[i] -= key[i%key.size()];
		}
	}
	
	cout << "The message is:\n" << message << "\nPress Enter to exit the program.\n";
	cin.ignore();
	
	
	
	file.close();
}