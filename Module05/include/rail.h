#ifndef __RAIL_H__
#define __RAIL_H__

#include <string>
#include <unordered_set>
#include "iobj.h"

namespace object
{
	class rail : public iobj
	{
		private:
			size_t 		_srcID;
			size_t		_destID;
			double		_distance;
			size_t		_train;
		public:
			rail(size_t a_srcID, size_t a_dstID, double a_distance)
				: Base(object_type::RAIL), _srcID{a_srcID}, _destID{a_dstID}, _distance{a_distance}
			{}
			bool attachTrain(size_t trainID) {}
			size_t train() const
			{
				return _train;
			}
			size_t	startPoint() const
			{
				return _srcID;
			}
			size_t endPoint() const
			{
				return _destID;
			}
			std::pair<size_t, size_t> direction() const
			{
				return std::make_pair(_srcID, _destID);
			}
			double distance() const
			{
				return _distance;
			}
	};
} // namespace network

#endif