#include "netwokGraph.h"
#include <limits>
#include "iobj.h"
#include "rail.h"
#include "train.h"
#include "iContainer.h"
#include "iManager.h"
#include <iostream>

namespace network
{

	double calculateTime(object::rail* rail, double acceleration_force, double braking_force)
	{
		constexpr double maximum_speed = 120.0;
		constexpr double mass = 10;
		
		double acc = acceleration_force / mass;
		double br = braking_force / mass;
		// Calculate time taken to accelerate and decelerate to maximum speed
		double acceleration_time = maximum_speed / acc;
		double braking_time = maximum_speed / br;
		// std::cout << "ddd: " << rail->distance() << "\n";
		double const_time = rail->distance() / maximum_speed;
		// Calculate distance traveled during acceleration and deceleration phases
		// double acceleration_distance = 0.5 * acc * acceleration_time * acceleration_time;
		// double braking_distance = 0.5 * br * braking_time * braking_time;

		// Calculate remaining distance after acceleration and before deceleration
		// double remaining_distance = rail->distance() - acceleration_distance - braking_distance;

		// std::cout << "rem: " << remaining_distance << "\n";
		// Calculate time taken to cover remaining distance at maximum speed
		// double remaining_time = remaining_distance / maximum_speed;

		// Calculate total time taken for the rail segment
		double total_time = acceleration_time + const_time + braking_time;

		return total_time;
	}

	std::pair<double, std::vector<NodeMapping>> networkGraph::shortest_path(size_t srcID, size_t dstID, size_t trainID) const
	{
		const double INFINITY = std::numeric_limits<double>::max();
		std::unordered_map<size_t, NodeMapping> mappings;
		std::priority_queue<vertex, std::vector<vertex>, std::greater<vertex>> pq;
		std::vector<NodeMapping> path;
		mappings[srcID].setTime(0);
		pq.push({srcID});
		while (!pq.empty())
		{
			auto* cont = _manager->get<object::container_type::RAIL>();
			size_t u = pq.top().vertexID();
			size_t ru = pq.top().railID();
			double time_u = pq.top().time();
			double dist_u = pq.top().distance();
			pq.pop();
			if (u == dstID)
			{
				size_t curr = ru;
				while (curr != object::npos)
				{
					path.push_back(mappings[curr]);
					curr =  mappings[curr].parentRail();
				}
				std::reverse(path.begin(), path.end());
				return std::make_pair(mappings[u].distance(), path);
			}
			auto it = _graph.find(u);
			if (it == _graph.end())
				continue;
			for (auto& railID: it->second)
			{
				
				auto* trainCont = _manager->get<object::container_type::TRAIN>();
				auto* rail = cont->get(railID);
				if (!rail)
					throw std::runtime_error(message::NonExistsRail);
				size_t v = rail->endPoint();
				auto* tr = trainCont->get(trainID);
				if (!tr)
					throw std::runtime_error(message::NonExistsTrain);
				double acc = tr->maxForce(object::force_type::ACC);
				double bracc = tr->maxForce(object::force_type::BREAK);
				double dist_v = rail->distance();
				double time_uv = calculateTime(rail, acc, bracc);
				if (time_u + time_uv < mappings[v].time())
				{
					mappings[v].setTime(time_u + time_uv);
					mappings[v].setDistance(dist_u + dist_v);
					mappings[railID].setTotalDistance(dist_u + dist_v);
					mappings[railID].setTime(time_uv);
					mappings[railID].setDistance(dist_v);
					mappings[railID].setRail(railID);
					mappings[railID].setParentRail(ru);
					pq.push({v, mappings[v].time(), mappings[v].distance(), railID});
				}
			}
		}
		throw std::runtime_error(message::NonExistsRail);
		return {INFINITY, {}};
	}
	
} // namespace network

