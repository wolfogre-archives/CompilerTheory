#include "Automata.h"



Automata::Automata()
{
}


Automata::~Automata()
{
}

bool Automata::Run(std::string input)
{
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
	if (is_start && _now_status != NULL)
		return false;
	for (std::set<Status*>::iterator it = _status_set.begin(); it != _status_set.end(); ++it)
		if ((*it)->status_name == status_name)
			return false;
	Status* p_status = new Status(status_name);
	_status_set.insert(p_status);
	if (is_start)
		_now_status = p_status;
	if (is_stop)
		_stop_status_set.insert(p_status);
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
	return true;
}

bool Automata::IsStopped()
{
	return (_stop_status_set.find(_now_status) != _stop_status_set.end());
}

std::string Automata::Show()
{
	std::string result;
	result += "Now Status:";
	if (_now_status == NULL)
		result += "NULL";
	else
		result += _now_status->status_name;
	result += "\n";

	for (std::set<Status*>::iterator it = _status_set.begin(); it != _status_set.end(); ++it)
	{
		result += "Status :";
		result += (*it)->status_name + "\n";
		for (std::pair<std::string, std::string> p : (*it)->paths)
			result += "\t input:" + p.first + "\tto" + p.second + "\n";
	}
	return result;
}
