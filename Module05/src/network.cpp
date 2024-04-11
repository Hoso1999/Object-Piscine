#include "network.h"
#include "netwokGraph.h"
#include "node.h"
#include "train.h"
#include "rail.h"
#include "include/event.h"
#include <iostream>
#include "Messages.h"

namespace network
{
	network::network()
	{
		_manager = std::make_unique<object::iManager>();
		_graph = std::make_unique<networkGraph>(_manager.get());
	}
	bool network::insert(const std::string& a_name, object::node_type type)
	{
		// std::cout << "insert node " << a_name << "\n";
		auto* cont = _manager->get<object::container_type::NODE>();
		auto* node = cont->get([&](object::node* n)->bool
		{
			return n->name() == a_name;
		});
		if (node)
			std::runtime_error(message::AlreadyExistsNode);
		return cont->insert(std::make_unique<object::node>(a_name, type));
	}
	bool network::insert(const std::string& a_src, const std::string& a_dst, double a_distance)
	{
		auto* nodeCont = _manager->get<object::container_type::NODE>();
		auto getID = [&](const std::string& name)
		{
			auto* node = nodeCont->get([&](object::node* n)
			{
				return n->name() == name;
			});
			if (!node)
				throw std::runtime_error(message::NonExistsNode);
			return node->ID();
		};
		auto startID = getID(a_src);
		auto endID = getID(a_dst);
		auto* cont = _manager->get<object::container_type::RAIL>();
		auto* rail = cont->get([&](object::rail* r)->bool
		{
			return r->startPoint() == startID && r->endPoint() == endID;
		});
		if (rail)
			throw std::runtime_error(message::AlreadyExistsRail);
		auto railPtr = std::make_unique<object::rail>(startID, endID, a_distance);
		auto railID = railPtr->ID();
		bool res = cont->insert(std::move(railPtr));
		_graph->insert(nodeCont->get(startID)->ID(), railID);
		return res;
	}
	/*
		* insert event to network
	*/
	bool network::insert(const std::string& a_name, double probability, network::duration_type duration, const std::string& location)
	{
		auto* nodeCont = _manager->get<object::container_type::NODE>();
		auto* node = nodeCont->get([&](object::node* n)
		{
			return n->name() == location;
		});
		if (!node)
			throw std::runtime_error(message::NonExistsNode);
		auto locID = node->ID();
		auto* cont = _manager->get<object::container_type::EVENT>();
		auto* event = cont->get([&](object::event* e)->bool
		{
			return e->location() == locID && e->name() == a_name && e->duration() == duration && e->probability() == probability;
		});
		if (event)
			throw std::runtime_error(message::AlreadyExistsEvent);
		return cont->insert(std::make_unique<object::event>(a_name, probability, duration, locID));
	}
	/*
		* insert train to network
	*/
	bool network::insert(const std::string& a_name, double maxAccForce, double maxBrForce, const std::string& a_src, const std::string& a_dst, network::duration_type duration)
	{
		auto* nodeCont = _manager->get<object::container_type::NODE>();
		auto getID = [&](const std::string& name)
		{
			auto* node = nodeCont->get([&](object::node* n)
			{
				return n->name() == name;
			});
			if (!node)
				throw std::runtime_error(message::NonExistsNode);
			return node->ID();
		};
		auto startID = getID(a_src);
		auto endID = getID(a_dst);
		auto* cont = _manager->get<object::container_type::TRAIN>();
		auto* train = cont->get([&](object::train* t)->bool
		{
			return (t->name() == a_name);
		});
		if (train)
			throw std::runtime_error(message::AlreadyExistsTrain);
		auto tr = std::make_unique<object::train>(a_name);
		tr->setStartPoint(startID);
		tr->setEndPoint(endID);
		tr->setStartTime(duration);
		tr->setMaxForce(maxAccForce, object::force_type::ACC);
		tr->setMaxForce(maxBrForce, object::force_type::BREAK);
		return cont->insert(std::move(tr));
	}

	object::iManager* network::Manager() const
	{
		return _manager.get();
	}
	
} // namespace network
