#include "iTrainHandler.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iCommand.h>
#include <sstream>
#include "Messages.h"
#include "commandInterpreter.h"


namespace handler
{
	bool iTrainHandler::load(const std::string& a_filename) const
	{
		std::ifstream fs(a_filename);
		if (!fs.is_open()) throw std::runtime_error("Path not exists");
		std::string line;
		while (std::getline(fs, line))
		{
			strip(line);
			if (!isBalancedQuotes(line))
				throw std::runtime_error(message::NonBalancedQuote);
			auto tokenized = tokenize(line, " \n\v\t\f\r\"\'");
			if (tokenized.empty())
				throw std::runtime_error("empty tokens");
			command::ArgumentList args;
			std::string cmd_name;
			if (tokenized.size())
				cmd_name = "objectTrain";
			for (size_t i = 0; i < tokenized.size(); ++i)
			{
				args[cmd_name].emplace_back(tokenized[i]);
			}
			auto& interpreter = command::commandInterpreter::Interpreter();
			interpreter.execute(cmd_name, std::move(args));
		}
		return true;
	}
} // namespace handler
