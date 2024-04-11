#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <unordered_map>
#include <string>
#include <memory>
#include <chrono>
#include "iManager.h"
#include "netwokGraph.h"

namespace object
{
	enum class node_type;
// 	class iManager;
} // namespace object


namespace network
{
	class networkGraph;
	class network
	{
		public:
			using manager_ptr = std::unique_ptr<class object::iManager>;
			using duration_type = std::chrono::nanoseconds;
			using graph_ptr = std::unique_ptr<class networkGraph>;
		private:
			manager_ptr _manager;
			graph_ptr	_graph;
		public:
			network();
			/*
			 * insert node to network
			*/
			bool insert(const std::string& a_name, object::node_type type);
			/*
			 * insert rail to network
			*/
			bool insert(const std::string& a_src, const std::string& a_dst, double a_distance);
			/*
			 * insert event to network
			*/
			bool insert(const std::string& a_name, double probability, duration_type duration, const std::string& location);
			/*
			 * insert train to network
			*/
			bool insert(const std::string& a_name, double maxAccForce, double maxBrForce, const std::string& a_src, const std::string& a_dst, duration_type duration);
			/*
			 * remove object by ID
			*/
			template<object::container_type Type>
			bool remove(size_t ID)
			{
				auto* cont =  _manager->template get<Type>();
				return cont->remove(ID);
			}
			object::iManager* Manager() const;
			networkGraph* Graph() const
			{
				return _graph.get();
			}
	};
} // namespace network


#endif