#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include "Glossary.h"

class Analyser
{
public:

	Analyser(){}
	~Analyser(){}

	std::vector<std::pair<std::string, std::string>> AnalyseLexical(std::string inputString){
		std::vector<std::string> words = RecognizeWord(inputString);
		std::vector<std::pair<std::string, std::string>> result;

		Glossary g;
		for (size_t i = 0; i < words.size(); ++i)
		{
			std::string temp = words[i];
			if (g.GetValue(words[i]) == "number" && i >= 2
				&& (g.GetValue(words[i - 1]) == "plus" || g.GetValue(words[i - 1]) == "minus")
				&& !(g.GetValue(words[i - 2]) == "number" || g.GetValue(words[i - 2]) == "rparen" || g.GetValue(words[i - 2]) == "ident")
				)
			{
				temp = result.back().first + words[i];
				result.pop_back();
			}
			result.push_back(std::pair<std::string, std::string>(temp, g.GetValue(temp)));
		}
			
		return result;
	}

protected:

	std::vector<std::string> RecognizeWord(std::string inputString){
		inputString += "\n";
		std::vector<std::string> result;
		Glossary g;
		unsigned int start = -1;

		for (unsigned int end = 0; end < inputString.length(); ++end){
			if (IsSeparator(inputString[end]))
			{
				std::string sub_string = inputString.substr(start + 1, end - (start + 1));
				if (sub_string.length() > 0)
				{
					transform(sub_string.begin(), sub_string.end(), sub_string.begin(), tolower);
					result.push_back(sub_string);
				}
				if (IsUsefulChar(inputString[end]))
				{
					std::string temp;
					if (!result.empty() && g.IsOperator(temp = result.back() + inputString[end]))
					{
						result.pop_back();
						result.push_back(temp);
					}
					else
					{
						result.push_back(inputString.substr(end, 1));
					}
				}
				start = end;
			}
		}

		return result;
	}

	bool IsSeparator(char ch){
		return std::string("+-*/=#<>:(),;. \n\t").find_first_of(ch) != std::string::npos;;
	}

	bool IsUsefulChar(char ch){
		return std::string("+-*/=#<>:(),;.").find_first_of(ch) != std::string::npos;
	}

private:

};
