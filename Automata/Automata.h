#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>

class Automata
{
public:
	Automata();
	~Automata();
	bool Run(std::string input);
	bool AddStatus(std::string status_name, bool isStart = false, bool is_stop = false);
	bool AddPath(std::string from_status, std::string to_status, std::string input);
	bool IsStopped();
	std::string Show();

protected:

private:
	struct Status
	{
		Status(std::string new_status_name)
		{
			status_name = new_status_name;
		}
		std::string status_name;
		std::map<std::string, std::string> paths;
	};
	std::set<Status*> _status_set;
	Status* _now_status = NULL;
	std::set<Status*> _stop_status_set;
};

