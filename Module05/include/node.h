#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <unordered_set>
#include "iobj.h"

namespace object
{
	enum class node_type
	{
		RAIL,
		CITY
	};
	class node : public iobj
	{
		private:
			node_type					_node_type;
			std::string 				_name;
			std::unordered_set<size_t>	_trains;
		public:
			node(const std::string& a_name, node_type a_type = node_type::CITY) :  Base(object_type::NODE) , _name{a_name}, _node_type{a_type} {};

			bool attachTrain(size_t trainID) {}

			inline const std::string& name() const
			{
				return _name;
			}
			inline node_type nodeType() const
			{
				return _node_type;
			}
	};
	
} // namespace network



#endif