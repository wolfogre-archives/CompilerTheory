#include "Automata.h"

Automata::Automata()
{
	_start_status = NULL;
	_now_status = _start_status;
}

Automata::~Automata()
{
	for (Status *p_status : _status_set)
		delete p_status;
}

void Automata::Restart()
{
	_now_status = _start_status;
}

bool Automata::Run(std::string input)
{
	if (_now_status == NULL)
		return false;
	std::map<std::string, std::string>::const_iterator path = (_now_status->paths).find(input);
	if (path == (_now_status->paths).end())
		return false;
	for (std::set<Status*>::iterator it = _status_set.begin(); it != _status_set.end(); ++it)
	{
		if ((*it)->status_name == path->second)
		{
			_now_status = (*it);
			return true;
		}
	}
	return false;
}

bool Automata::AddStatus(std::string status_name, bool is_start, bool is_stop)
{
	if (is_start && _start_status != NULL)
		return false;

	for (std::set<Status*>::iterator it = _status_set.begin(); it != _status_set.end(); ++it)
		if ((*it)->status_name == status_name)
			return false;

	Status* p_status = new Status(status_name);
	if (is_stop)
		p_status->isStopStatus = true;
	_status_set.insert(p_status);
	if (is_start)
		_start_status = p_status;

	Restart();
	return true;
}

bool Automata::AddPath(std::string from_status, std::string to_status, std::string input)
{
	std::set<Status*>::iterator it;
	for (it = _status_set.begin(); it != _status_set.end(); ++it)
		if ((*it)->status_name == from_status)
			break;

	if (it == _status_set.end())
		return false;

	if ((*it)->paths.find(input) != (*it)->paths.end())
		return false;

	(*it)->paths.insert(std::pair<std::string, std::string>(input, to_status));
	Restart();
	return true;
}

bool Automata::IsStopped()
{
	return _now_status->isStopStatus;
}

std::string Automata::NowStatus()
{
	std::string result;
	result += _now_status->status_name;
	if (_now_status->isStopStatus)
		result += "\tStop";
	return result;
}

std::string Automata::AllStatus()
{
	std::string result;
	for (Status *p_status : _status_set)
	{
		result += p_status->status_name;
		if (p_status->isStopStatus)
			result += "\tStop";
		result += "\n";
	}
	return result;
}

std::string Automata::AllPaths()
{
	std::string result;
	for (Automata::Status *p_status : _status_set)
		for (std::pair<std::string, std::string> pr : p_status->paths)
			result += p_status->status_name + "\t-- " + pr.first + " -->\t" + pr.second + "\n";
	return result;
}

