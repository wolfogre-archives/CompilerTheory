#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

class Recognizer
{
public:

	Recognizer(){
		basic_words[0] = "begin";
		basic_words[1] = "call";
		basic_words[2] = "const";
		basic_words[3] = "do";
		basic_words[4] = "end";
		basic_words[5] = "if";
		basic_words[6] = "odd";
		basic_words[7] = "procedure";
		basic_words[8] = "read";
		basic_words[9] = "then";
		basic_words[10] = "var";
		basic_words[11] = "while";
		basic_words[12] = "write";
	}

	~Recognizer(){};

	std::map<std::string, int> RecognizeIdentifier(std::string codeFilePath){
		std::ifstream fin;
		fin.open(codeFilePath);
		std::stringstream buffer;
		buffer << fin.rdbuf();
		std::string inputString(buffer.str());
		fin.close();

		std::vector<std::string> temp_string_list;
		unsigned int start = -1;

		for (unsigned int end = 0; end < inputString.length(); ++end){
			if (IsSeparator(inputString[end]))
			{
				temp_string_list.push_back(inputString.substr(start + 1, end - (start + 1)));
				start = end;
			}
		}
		
		std::vector<std::string> string_list;
		for (std::string str : temp_string_list){
			transform(str.begin(), str.end(), str.begin(), tolower);
			if (str.length() > 0 && !IsBasicWord(str) && !IsNumber(str[0]))
				string_list.push_back(str);
		}

		std::map<std::string, int> result;
		for (std::string str : string_list){
			std::map<std::string,int>::iterator it = result.find(str);
			if (it == result.end())
				result.insert(std::pair<std::string, int>(str, 1));
			else
				++it->second;
		}
		return result;
	}

protected:

	bool IsSeparator(char ch){
		return !(
			IsNumber(ch)
			|| ch >= 'a' && ch <= 'z'
			|| ch >= 'A' && ch <= 'Z');
	}

	bool IsNumber(char ch){
		return ch >= '0' && ch <= '9';
	}

	bool IsBasicWord(std::string str){
		for (int i = 0; i < 13; ++i){
			if (str == basic_words[i])
				return true;
		}
		return false;
	}

private:

	std::string basic_words[13];
};