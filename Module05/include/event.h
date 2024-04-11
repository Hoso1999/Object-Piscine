#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>
#include <chrono>
#include "iobj.h"

namespace object
{
	class event : public iobj
	{
		public:
			using duration_type = std::chrono::nanoseconds;
		private:
			std::string		_name;
			double			_probability;
			duration_type	_duration;
			size_t			_locationID;
		public:
			event(const std::string& a_name, double a_prob, duration_type a_duration, size_t a_locID)
				:  Base(object_type::EVENT), _name{a_name}, _probability{a_prob}, _duration{a_duration}, _locationID{a_locID}
			{}
			const std::string& name() const
			{
				return _name;
			}
			double probability() const
			{
				return _probability;
			}
			duration_type duration() const
			{
				return _duration;
			}
			size_t location() const
			{
				return _locationID;
			}
	};
	
} // namespace network

#endif