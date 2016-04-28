#pragma once

#include <vector>
#include <string>
#include <iostream>

class LR0_Analyser
{
public:


	LR0_Analyser(std::vector<std::string> inputs)
	{
		this->inputs = inputs;
		this->inputs.push_back(END_OF_INPUT);
	}

	LR0_Analyser()
	{

	}

	void Input(std::vector<std::string> inputs)
	{
		this->inputs = inputs;
		this->inputs.push_back(END_OF_INPUT);
	}

	void AddProduction(std::string left, std::string right1)
	{
		std::vector<std::string> right_list;
		right_list.push_back(right1);
		production_list.push_back(std::pair<std::string, std::vector<std::string>>(left, right_list));
	}

	void AddProduction(std::string left, std::string right1, std::string right2)
	{
		std::vector<std::string> right_list;
		right_list.push_back(right1);
		right_list.push_back(right2);
		production_list.push_back(std::pair<std::string, std::vector<std::string>>(left, right_list));
	}

	void AddProduction(std::string left, std::string right1, std::string right2, std::string right3)
	{
		std::vector<std::string> right_list;
		right_list.push_back(right1);
		right_list.push_back(right2);
		right_list.push_back(right3);
		production_list.push_back(std::pair<std::string, std::vector<std::string>>(left, right_list));
	}

	void AddProduction(std::string left, std::string right1, std::string right2, std::string right3, std::string right4)
	{
		std::vector<std::string> right_list;
		right_list.push_back(right1);
		right_list.push_back(right2);
		right_list.push_back(right3);
		right_list.push_back(right4);
		production_list.push_back(std::pair<std::string, std::vector<std::string>>(left, right_list));
	}

	void AddProduction(std::string left, std::string right1, std::string right2, std::string right3, std::string right4, std::string right5)
	{
		std::vector<std::string> right_list;
		right_list.push_back(right1);
		right_list.push_back(right2);
		right_list.push_back(right3);
		right_list.push_back(right4);
		right_list.push_back(right5);
		production_list.push_back(std::pair<std::string, std::vector<std::string>>(left, right_list));
	}

	void AddAction(int status, std::string input, char type, int value)
	{
		Action new_action;
		new_action.status = status;
		new_action.input = input;
		new_action.type = type;
		new_action.value = value;
		action_list.push_back(new_action);
	}

	void AddGoto(int status, std::string input, int value)
	{
		Goto new_goto;
		new_goto.status = status;
		new_goto.input = input;
		new_goto.value = value;
		goto_list.push_back(new_goto);
	}

	int Analyse()
	{
		std::vector<int> status_stack;
		std::vector<std::string> chars_stack;

		status_stack.push_back(0);
		size_t index = 0;

		for (index = 0; index < inputs.size(); ++index)
		{
			//Show(status_stack);
			//Show(chars_stack);

			char type;
			int value;
			if (!getAction(status_stack.back(), inputs[index], type, value))
				return index;

			if (type == 's' || type == 'S')
			{
				status_stack.push_back(value);
				chars_stack.push_back(inputs[index]);
				continue;
			}

			if (type == 'r' || type == 'R')
			{
				--index;
				std::pair<std::string, std::vector<std::string>> production = production_list[value - 1];
				while (!production.second.empty())
				{
					production.second.pop_back();
					chars_stack.pop_back();
					status_stack.pop_back();
				}
				chars_stack.push_back(production.first);
				int goto_value;
				if (!getGoto(status_stack.back(), production.first, goto_value))
					return index;
				status_stack.push_back(goto_value);
				continue;
			}

			if (type == 'a' || type == 'A')
			{
				return -1;
			}

		}

		return index;
	}

	static const std::string END_OF_INPUT;
	static const std::string ALL_OF_INPUT;

protected:
	struct Action
	{
		int status;
		std::string input;
		char type;
		int value;
	};

	struct Goto
	{
		int status;
		std::string input;
		int value;
	};

	bool getAction(int status, std::string input, char &type, int &value)
	{
		for (Action action : action_list)
		{
			if (action.status == status && (action.input == input || action.input == ALL_OF_INPUT))
			{
				type = action.type;
				value = action.value;
				return true;
			}
		}
		return false;
	}

	bool getGoto(int status, std::string input, int &value)
	{
		for (Goto g : goto_list)
		{
			if (g.status == status && g.input == input)
			{
				value = g.value;
				return true;
			}
		}
		return false;
	}
	void Show(std::vector<int> status_stack)
	{
		for (auto it : status_stack)
			std::cout << it << " ";
		std::cout << std::endl;
	}
	void Show(std::vector<std::string> chars_stack)
	{
		std::cout << "#" << " ";
		for (auto it : chars_stack)
			std::cout << it << " ";
		std::cout << std::endl;
	}
private:

	std::vector<std::string> inputs;
	std::vector<Action> action_list;
	std::vector<Goto> goto_list;
	std::vector<std::pair<std::string, std::vector<std::string>>> production_list;
};

const std::string LR0_Analyser::END_OF_INPUT = "end_of_input_i_love_vivia";
const std::string LR0_Analyser::ALL_OF_INPUT = "all_of_input_i_love_vivia";