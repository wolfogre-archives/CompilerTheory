#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>

class Automata
{
public:
	struct Status
	{
		Status(std::string new_status_name)
		{
			status_name = new_status_name;
			isStopStatus = false;
		}
		std::string status_name;
		std::map<std::string, std::string> paths;
		bool isStopStatus;
	};
	Automata();
	~Automata();
	void Automata::Restart();
	bool Run(std::string input);
	bool AddStatus(std::string status_name, bool isStart = false, bool is_stop = false);
	bool AddPath(std::string from_status, std::string to_status, std::string input);
	bool IsStopped();
	std::string NowStatus();
	std::string AllStatus();
	std::string AllPaths();

protected:

private:
	std::set<Status*> _status_set;
	Status* _now_status;
	Status* _start_status;
};

