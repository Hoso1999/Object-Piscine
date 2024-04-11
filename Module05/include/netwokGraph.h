#ifndef __NETWORKGRAPH_H__
#define __NETWORKGRAPH_H__

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <stack>
#include <limits>
#include <stdexcept>
#include "Messages.h"

namespace object
{
	class iManager;
	extern const size_t npos;
}

namespace network
{
	class vertex
	{
		size_t	_vertexID;
		size_t	_railID;
		double	_time;
		double	_distance;
		public:
			vertex(size_t a_vertexID, double a_time = 0, double a_dist = 0, size_t a_railID = object::npos)
				: _vertexID(a_vertexID), _railID(a_railID), _time(a_time), _distance(a_dist)
			{}
			double time() const
			{
				return _time;
			}

			double distance() const
			{
				return _distance;
			}
			size_t vertexID() const
			{
				return _vertexID;
			}
			size_t railID() const
			{
				return _railID;
			}

			bool operator>(const vertex &other) const
			{
				return _time > other._time;
			}
	};
	class NodeMapping
	{
		double INFINITY{std::numeric_limits<double>::max()};
		double	_time;
		double	_distance;
		double	_totalDistance;
		size_t	_parentRail;
		size_t	_rail;
		public:
			NodeMapping()
				:	_time(INFINITY),
					_distance(INFINITY),
					_totalDistance(INFINITY),
					_parentRail(object::npos),
					_rail(object::npos)
			{}
			double time() const
			{
				return _time;
			}

			size_t rail() const
			{
				return _rail;
			}

			void setRail(size_t a_rail)
			{
				_rail = a_rail;
			}
			void setTime(double a_time)
			{
				_time = a_time;
			}
			size_t parentRail() const
			{
				return _parentRail;
			}
			void setParentRail(size_t a_parent)
			{
				_parentRail = a_parent;
			}
			double distance() const
			{
				return _distance;
			}
			void setDistance(double a_distance)
			{
				_distance = a_distance;
			}

			double totalDistance() const
			{
				return _totalDistance;
			}
			void setTotalDistance(double a_totalDist)
			{
				_totalDistance = a_totalDist;
			}
	};
	class networkGraph
	{
		public:
			// using order_type = std::unordered_set<size_t>;
			// using degree_type = std::unordered_map<size_t, long>;
			using container_type = std::unordered_map<size_t, std::unordered_set<size_t>>;
		private:
			object::iManager* _manager;
			container_type	_graph;
			// std::unordered_map<size_t, long> inDegree; // Keeps track of in-degrees of vertices
			// order_type topologicalOrder;
			void doOrder() {}
		public:
			networkGraph(object::iManager* manager = nullptr) : _manager{manager} {};
			bool insert(size_t nodeID, size_t railID)
			{
				return _graph[nodeID].insert(railID).second;
			}
			bool remove(size_t ID)
			{
				auto it = _graph.find(ID);
				if (it != _graph.end())
				{
					for (auto& node : _graph)
					{
						if (!node.second.erase(ID))
							throw std::runtime_error(message::NonExistsRail);
					}
				}
				return true;
			}
			std::pair<double, std::vector<NodeMapping>> shortest_path(size_t srcID, size_t dstID, size_t trainID) const;
			// size_t get(const std::string& a_name);
			// const size_t get(const std::string& a_name) const;
			// size_t get(std::function<bool(size_t)> callback);
			// const size_t get(std::function<bool(size_t)> callback) const;
			// void for_each(std::function<bool(size_t)> callback);
	};
} // namespace network

#endif