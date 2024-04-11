#include "handlerFactory.h"
#include "iRailHandler.h"
#include "iTrainHandler.h"
#include "network.h"

namespace handler
{
	handler_ptr handlerFactory::createHandler(handler_type type) const
	{
		switch (type)
		{
			case handler_type::RAIL:
				return std::make_unique<iRailHandler>(_net);
			case handler_type::TRAIN:
				return std::make_unique<iTrainHandler>(_net);
			default:
				throw std::runtime_error("Handler Not Implemented");
		}
		return {};
	}

	bool handlerManager::insert(handler_type type)
	{
		auto handler = _factory.createHandler(type);
		return _handlers.insert(std::make_pair(handler->type(), std::move(handler))).second;
	}
	handlerManager::handlerManager(network::network* a_net)
		: _factory{a_net}, _net{a_net}
	{
		insert(handler_type::RAIL);
		insert(handler_type::TRAIN);
	}
	iFileHandler* handlerManager::get(handler_type type) const
	{
		return _handlers.at(type).get();
	}

} // namespace handler

