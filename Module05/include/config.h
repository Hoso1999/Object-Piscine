#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <memory>
#include "handlerFactory.h"
#include "network.h"

namespace network
{
	class network;
} // namespace network

namespace handler
{
	class iFileHandler;
	class handlerManager;
} // namespace network

namespace config
{
	class config
	{
		using handlerManager_ptr = std::unique_ptr<handler::handlerManager>;
		using network_ptr = std::unique_ptr<network::network>;
		private:
			handlerManager_ptr	_manager;
			network_ptr	_net;
			config();
		public:
			static config& Config()
			{
				static config conf;
				return conf;
			}
			network::network*	Network() const;
			handler::handlerManager* Manager() const;
	};
	// class defaultConfig
	// {
	// 	public:
	// 	private:
	// 		config		_config;
	// 	public:
	// 		defaultConfig();
	// };
	
} // namespace config


#endif