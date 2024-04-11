#include "iManager.h"
#include <stdexcept>
#include "train.h"
#include "rail.h"
#include "node.h"
#include "event.h"

namespace object
{
	iCont_ptr iManager::createContainer(container_type type) const
	{
		switch (type)
		{
			case container_type::NODE:
				return std::make_unique<iContainer<container_type::NODE>>();
			case container_type::EVENT:
				return std::make_unique<iContainer<container_type::EVENT>>();
			case container_type::RAIL:
				return std::make_unique<iContainer<container_type::RAIL>>();
			case container_type::TRAIN:
				return std::make_unique<iContainer<container_type::TRAIN>>();
			default:
				throw std::runtime_error("Not Implemented");
		}
		return {};
	}
	bool iManager::insert(iCont_ptr container)
	{
		return _containers.insert(std::make_pair(container->type(), std::move(container))).second;
	}
} // namespace object
