#include "iCommand.h"
#include "CliTools.h"
#include "config.h"
#include "iFileHandler.h"
#include "handlerFactory.h"
#include <stdexcept>
#include <unordered_map>

namespace command
{
	bool iFileOpen::execute(ArgumentList&& args)
	{
		return true;
	}
	bool iFileOpen::validate(ArgumentList&& args)
	{
		return true;
	}
	bool iRailLoad::execute(ArgumentList&& args)
	{
		if(!iFileOpen::execute(std::move(args))) return false;
		auto& conf = config::config::Config();
		auto* manager = conf.Manager()->get( handler::handler_type::RAIL);
		manager->load(_filename);
		return true;
	}
	bool iRailLoad::validate(ArgumentList&& args)
	{
		// args["sss"];
		ArgumentList lst{args};
		if(!iFileOpen::validate(std::move(lst))) return false;
		if (args.size() > 2)
			throw std::runtime_error("Invalid options");
		if (args.find("--rail") == args.end() || args["--rail"].size() < 1)
			throw std::runtime_error("Invalid options Rail");
		_filename = args["--rail"].at(0);
		return true;
	}
	bool iTrainLoad::validate(ArgumentList&& args)
	{
		ArgumentList lst{args};
		if(!iFileOpen::validate(std::move(lst))) return false;
		if (args.size() > 2)
			throw std::runtime_error("Invalid options");
		if (args.find("--train") == args.end() || args["--train"].size() < 1)
			throw std::runtime_error("Invalid options");
		_filename = args["--train"].at(0);
		return true;
	}
	bool iTrainLoad::execute(ArgumentList&& args)
	{
		if(!iFileOpen::execute(std::move(args))) return false;
	
		auto& conf = config::config::Config();
		auto* manager = conf.Manager()->get( handler::handler_type::TRAIN);
		manager->load(_filename);
		return true;
	}

} // namespace command
