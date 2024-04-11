#ifndef __HANDLERFACTORY_H__
#define __HANDLERFACTORY_H__

#include <unordered_map>
#include <memory>
#include "iFileHandler.h"

namespace network
{
	class network;
} // namespace network


namespace handler
{
	using handler_ptr = std::unique_ptr<class iFileHandler>;
	class handlerFactory
	{
		network::network* _net;
		public:
			handlerFactory(network::network* a_net = nullptr) : _net{a_net} {};
			handler_ptr createHandler(enum handler_type type) const;
	};
	class handlerManager
	{
		public:
			using cont_type = std::unordered_map<enum handler_type, handler_ptr>;
		private:
			handlerFactory		_factory;
			network::network*	_net;
			cont_type			_handlers;
		public:
			handlerManager(network::network* a_net = nullptr);
			bool insert(handler_type type);
			class iFileHandler* get(enum handler_type type) const;
	};
	
} // namespace handler


#endif