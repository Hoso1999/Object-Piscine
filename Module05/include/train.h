#ifndef __TRAIN_H__
#define __TRAIN_H__

#include <string>
#include <chrono>
#include "iobj.h"
#include <stdexcept>

namespace object
{
	enum class force_type
	{
		ACC,
		BREAK
	};
	class train : public iobj
	{
		public:
			using duration_type = std::chrono::nanoseconds;
		private:
			std::string 	_name;
			double			_max_acc_force;
			double			_max_br_force;
			double			_velocity;
			size_t			_srcID;
			size_t			_destID;
			duration_type	_start_time;
			size_t			_railID = npos;
			size_t			_nodeID = npos;
		public:
			train(const std::string& a_name) :  Base(object_type::TRAIN), _name{a_name} {};
			const std::string& name() const
			{
				return _name;
			}
			double velocity() const
			{
				return _velocity;
			}
			void setVelocity(double a_velocity)
			{
				_velocity = a_velocity;
			}
			double maxForce(force_type type) const
			{
				switch (type)
				{
					case force_type::ACC:
						return _max_acc_force;
					case force_type::BREAK:
						return _max_br_force;
					default:
						throw std::runtime_error("Not Implemented");
				}
			}
			std::pair<size_t, size_t> direction() const
			{
				return std::make_pair(_srcID, _destID);
			}
			void setStartPoint(size_t a_srcID)
			{
				_srcID = a_srcID;
			}
			void setEndPoint(size_t a_endID)
			{
				_destID = a_endID;
			}
			size_t startPoint() const
			{
				return _srcID;
			}
			size_t endPoint() const
			{
				return _destID;
			}
			// const std::string& direction(direction_type dir) const
			// {
			// 	switch (dir)
			// 	{
			// 		case direction_type::START:
			// 			return _src;
			// 			break;
			// 		case direction_type::END:
			// 			return _dest;
			// 			break;
			// 		default:
			// 			throw std::runtime_error("Not Implemented");
			// 	}
			// }
			duration_type startTime() const
			{
				return _start_time;
			}

			void setMaxForce(double force, force_type type)
			{
				switch (type)
				{
					case force_type::ACC:
						_max_acc_force = force;
						break;
					case force_type::BREAK:
						_max_br_force = force;
						break;
					default:
						throw std::runtime_error("Not Implemented");
				}
			}
			// void setDir(const std::string& a_src, direction_type dir)
			// {
			// 	switch (dir)
			// 	{
			// 		case direction_type::START:
			// 			_src = a_src;
			// 			break;
			// 		case direction_type::END:
			// 			_dest = a_src;
			// 			break;
			// 		default:
			// 			throw std::runtime_error("Not Implemented");
			// 	}
			// }
			void setStartTime(duration_type start_time)
			{
				_start_time = start_time;
			}
	};
} // namespace network

#endif