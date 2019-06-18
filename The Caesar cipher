#include <iostream>
#include <string>

using namespace std;
char caesar(char c, int key);
string caesar1(string message, int key);

int main()
{
	int key;
	string input;
	cout << "enter capital string only \n";
	cin >> input;
	cout << "enter the encryption key \n";
	cin >> key;
	 cout<<"output= "<<caesar1(input, key);
	
	return 0;
}
char caesar(char c, int key)
{
	char c2;
	c2 = c + key;
	if (c2 > 'Z')
		c2 -= 26;
	if (c2 < 'A')
		c2 += 26;
	return c2;
}
string caesar1(string message, int key)
{
	string output= message;
	for (int i = 0; i < message.length(); i++)
	{
		output[i] = caesar(message[i], key);
	}
	return output;
}
