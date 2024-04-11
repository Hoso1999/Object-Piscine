#include "config.h"
#include "handlerFactory.h"

size_t generator::UniqueIDGenerator::counter = 0;

const size_t object::npos = -1;
namespace config
{
	config::config()
	{
		_net = std::make_unique<network::network>();
		_manager = std::make_unique<handler::handlerManager>(_net.get());
	};
	handler::handlerManager* config::Manager() const
	{
		return _manager.get();
	}
	network::network*	config::Network() const
	{
		return _net.get();
	}
} // namespace config
