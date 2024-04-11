#include "iCommand.h"
#include "CliTools.h"
#include "config.h"
#include "iFileHandler.h"
#include "handlerFactory.h"
#include <stdexcept>
#include <unordered_map>
#include "Messages.h"
#include "config.h"
#include "node.h"
#include "rail.h"
#include <iostream>
#include <regex>

namespace command
{

	std::chrono::nanoseconds getDuration(char type, long& number)
	{
		std::chrono::nanoseconds duration{0};
		switch (type)
		{
			case 'Y':
				duration += std::chrono::hours(number * 365 * 24);
				number = 0;
				break;
			case 'M':
				duration += std::chrono::hours(number * 24);
				number = 0;
				break;
			case 'd':
				duration += std::chrono::hours(number * 30 * 24);
				number = 0;
				break;
			case 'h':
				duration += std::chrono::hours(number);
				number = 0;
				break;
			case 'm':
				duration += std::chrono::minutes(number);
				number = 0;
				break;
			case 's':
				duration += std::chrono::seconds(number);
				number = 0;
				break;
			default:
				throw std::runtime_error("Invalid Date format");
		}
		return duration;
	}
	std::chrono::nanoseconds parseDuration(const std::string& durationStr)
	{
		std::chrono::nanoseconds duration(0);

		std::unordered_map<char, char> map = {
			{'Y', 'M'},
			{'M', 'd'},
			{'d', 'h'},
			{'h', 'm'},
			{'m', 's'},
			{'s', 's'},
			{ 0 , 'm'}
		};
		long number = 0;
		char type = 0;
		for (size_t i = 0; i < durationStr.size(); ++i)
		{
			if (!isdigit(durationStr[i]))
			{
				type = durationStr[i];
				duration += getDuration(type, number);
			}
			else
				number = number * 10 + durationStr[i] - '0';
		}
		duration += getDuration(map[type], number);
		return duration;
	}
	bool iNode::validate(ArgumentList&& args)
	{
		_opCity = false;
		_opRailNode = false;
		_node_name = "";

		if (args.size() > 1 || args[_cmd].size() > 1)
			throw std::runtime_error(message::NodeUsage);
		_node_name = args[_cmd][0];
		if (_node_name.empty())
			throw std::runtime_error(message::EmptyNodeName);
		if (_node_name.find("City") == 0)
			_opCity = true;
		else if (_node_name.find("RailNode") == 0)
			_opRailNode = true;
		if (!_opCity && !_opRailNode)
			throw std::runtime_error(message::InvalidNodeName);
		return true;
		
	}
	bool iRail::validate(ArgumentList&& args)
	{
		_from = "";
		_to = "";
		_distance = 0;
		if (args.size() > 1 || args[_cmd].size() > 3)
			throw std::runtime_error(message::RailUsage);
		auto* manager = _net->Manager()->get<object::container_type::NODE>();
		auto find_node = [&](const std::string& a_name) -> void
		{
			auto* node_ptr = manager->get(
			[&](object::node* node) -> bool
			{
				return node->name() == a_name;
			});
			if (!node_ptr)
				throw std::runtime_error(message::NonExistsNode);
		};
		_from = args[_cmd][0];
		if (_from.empty())
			throw std::runtime_error(message::EmptyNodeName);
		find_node(_from);
		_to = args[_cmd][1];
		if (_from.empty())
			throw std::runtime_error(message::EmptyNodeName);
		find_node(_to);
		if (_from == _to)
			throw std::runtime_error(message::SameRailStartEnd);
		try
		{
			_distance = std::stod(args[_cmd][2]);
		}
		catch(...)
		{
			throw std::runtime_error("Invalid distance");
		}
		return true;
	}
	bool iTrain::validate(ArgumentList&& args)
	{
		if (args.size() > 1 || args[_cmd].size() > 6)
			throw std::range_error(message::TrainUsage);
		_train_name = args[_cmd][0];
		try
		{
			_max_acc_force = std::stod(args[_cmd][1]);
		}
		catch(const std::exception& e)
		{
			throw std::runtime_error("invalid argument");
		}
		try
		{
			_max_br_force = std::stod(args[_cmd][2]);
		}
		catch(const std::exception& e)
		{
			throw std::runtime_error("invalid argument");
		}
		_from = args[_cmd][3];
		if (_from.empty())
			throw std::runtime_error(message::EmptyNodeName);
		
		_to = args[_cmd][4];
		if (_to.empty())
			throw std::runtime_error(message::EmptyNodeName);
		_start_time = parseDuration(args[_cmd][5]);
		return true;
	}
	bool iEvent::validate(ArgumentList&& args)
	{
		_name = "";
		_prob = 0;
		_duration = duration_type();
		_loc = "";
		if (args.size() > 1 || args[_cmd].size() > 4)
			throw std::runtime_error(message::EventUsage);
		_name = args[_cmd][0];
		if (_name.empty())
			throw std::runtime_error("Event name is empty");
		try
		{
			_prob = std::stod(args[_cmd][1]);
		}
		catch(const std::exception& e)
		{
			throw std::runtime_error("Event probability should be a number");
		}
		_duration = parseDuration(args[_cmd][2]);
		_loc = args[_cmd][3];
		if (_loc.empty())
			std::runtime_error(message::EmptyNodeName);
		auto loc = _net->Manager()->get<object::container_type::NODE>()->get(
		[&](object::node* n)
		{
			return n->name() == _loc;
		});
		if (!loc)
			throw std::runtime_error(message::NonExistsNode);
		return true;
	}
	bool iNode::execute(ArgumentList&& args)
	{
		if (_opCity)
		{
			if (!_net->insert(_node_name, object::node_type::CITY))
				std::runtime_error("Cannot create Node " + _node_name);
		}
		else if (_opRailNode)
		{
			if (!_net->insert(_node_name, object::node_type::RAIL))
				std::runtime_error("Cannot create Node " + _node_name);
		}
		auto find_node = [&](const std::string& a_name) -> void
		{
			auto* node_ptr = _cont->get(
			[&](object::node* node) -> bool
			{
				return node->name() == a_name;
			});
			if (!node_ptr)
				throw std::runtime_error(_node_name + " " + message::NonExistsNode);
		};
		find_node(_node_name);
		return true;
	}
	bool iRail::execute(ArgumentList&& args)
	{
		if(!_net->insert(_from, _to, _distance))
			throw std::runtime_error("Cannot create Rail");

		return true;
	}
	bool iTrain::execute(ArgumentList&& args)
	{
		if (!_net->insert(_train_name, _max_acc_force, _max_br_force, _from, _to, _start_time))
			throw std::runtime_error("Cannot create Train");
		return true;
	}
	bool iEvent::execute(ArgumentList&& args)
	{
		if(!_net->insert(_name, _prob, _duration, _loc))
			throw std::runtime_error("Cannot create event");
		return true;
	}
} // namespace command
