#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::transform;
using std::cin;

string manipulateStrigs(const string text, const string remove);

vector<string> tokenize(const string text, const char delim);

int main(void)
{
	string sentense;

	//get the text
	cout << "Enter text: " << endl;
	cin >> sentense;
	
	cout << endl << endl;

	//get the word to be removed
	cout << "Enter word/character to remove: ";
	string rem;
	cin >> rem;

	//get the result 
	string res = manipulateStrigs(sentense, rem);

	//print original text
	cout << "Original Text: "<< endl << sentense << endl << endl;

	//print resulting text
	cout << "Resulting Text: "<< endl << res << endl;
	
	return 0;
}

string manipulateStrigs(const string text, const string remove)
{
	//chose on what delimiter to brake up the text
	const char delim = ' ';

	//get tokens of the text
	vector<string> tokens = tokenize(text, delim);

	string temp;

	size_t found_pos;

	//go through the tokens
	for (unsigned int i = 0; i < tokens.size(); i++)
	{
		temp = tokens[i];

		//transform the token working at to lower case word
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

		//check if this is the first word of a sentense and if it
		//matches the word that needs to be removed removed
		//and capitalize the next word in the chain
		if(temp == remove && isupper(tokens[i][0]) && i != tokens.size()-1)
		{
			tokens[i + 1][0] = toupper(tokens[i + 1][0]);
			tokens.erase(tokens.begin() + i);
		}

		//if it is not a capital word, just removed from the sentense
		else if(temp == remove)
		{
			tokens.erase(tokens.begin() + i);
		}

		//if no word was found a single character may have been enetered
		//look inside every word
		else if(found_pos = temp.find(remove) != std::string::npos)
		{
			//while a position to remove was found remove it and search again
			while (found_pos != std::string::npos)
			{
				tokens[i].erase(tokens[i].begin() + found_pos);
				temp.erase(temp.begin() + found_pos);

				found_pos = temp.find(remove);
			}
			
		}
	}

	//string stream used to pipe the array into a single string
	std::stringstream ss;

	//construct a new string
	for (unsigned int i = 0; i < tokens.size(); i++)
	{
		ss << tokens[i];
		ss << " ";
	}
	

	//return the new string with all of the instances of the remove string taken out
	return ss.str();

}

vector<string> tokenize(const string text, const char delim)
{
	std::istringstream ss(text);
	string temp;
	vector<string> tokens;

	//separate the text string into delimited words
	//add them to the array tokens which is returned
	while (std::getline(ss, temp, delim))
		tokens.push_back(temp);

	return tokens;
}

