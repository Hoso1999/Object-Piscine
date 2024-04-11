#include "iCommand.h"
#include "commandInterpreter.h"
#include <iostream>

namespace command
{
	iCommand_ptr commandFactory::createCommand(command_type type) const
	{
		switch (type)
		{
			case command_type::NODE:
				return std::make_unique<iNode>();
			case command_type::RAIL:
				return std::make_unique<iRail>();
			case command_type::EVENT:
				return std::make_unique<iEvent>();
			case command_type::TRAIN:
				return std::make_unique<iTrain>();
			case command_type::FILEOPEN:
				return std::make_unique<iFileOpen>();
			case command_type::RAILLOAD:
				return std::make_unique<iRailLoad>();
			case command_type::TRAINLOAD:
				return std::make_unique<iTrainLoad>();
			default:
				throw std::runtime_error("Not Implemented");
		}
		return {};
	}
	bool commandInterpreter::createCommand(command_type type)
	{
		auto cmd_ptr = _factory.createCommand(type);
		// std::cout << "name: " << cmd_ptr->name() << "\n";
		return _commands.insert(std::make_pair(cmd_ptr->name(), std::move(cmd_ptr))).second;
	}
	commandInterpreter::commandInterpreter()
	{
		createCommand(command_type::NODE);
		createCommand(command_type::RAIL);
		createCommand(command_type::EVENT);
		createCommand(command_type::TRAIN);
		createCommand(command_type::FILEOPEN);
		createCommand(command_type::TRAINLOAD);
		createCommand(command_type::RAILLOAD);
	}
	void commandInterpreter::execute(const std::string& command_name, ArgumentList&& args)
	{
		auto it = _commands.find(command_name);
		if (it == _commands.end())
			throw std::runtime_error("Command not found " + command_name);
		ArgumentList validateArgs{args};
		if (it->second->validate(std::move(validateArgs)))
			it->second->execute(std::move(args));
		
	}


} // namespace command
