#include <iostream>
#include <chrono>
#include <unistd.h>
#include "iCommand.h"
#include "commandInterpreter.h"
#include <filesystem>
#include <cmath>
// #include "iContainer.h"
#include "node.h"
#include "train.h"
#include "rail.h"
// #include "iManager.h"
// #include "config.h"
// #include "CliTools.h"
void move(double& position, double& total_pos, double& velocity, \
		double max_acceleration, double max_braking,\
		double max_speed_limit, double time_step, \
		double total_distance, double max_time)
{
    // Simulate acceleration
    if (velocity < max_speed_limit) {
        // Increase velocity up to maximum speed limit
        double potential_velocity = velocity + max_acceleration * time_step;
        velocity = std::min(potential_velocity, max_speed_limit);
    }

    // Simulate braking
    if (velocity > 0) {
        // Calculate the distance required to stop at max braking force
        double stopping_distance = (velocity * velocity) / (2 * max_braking);

        // If the stopping distance is greater than the distance to the next position, brake
        if (stopping_distance >= position) {
            velocity -= max_braking * time_step;
            // Ensure velocity does not go negative
            velocity = std::max(0.0, velocity);
        }
    }
	double step = velocity * time_step;
	if (position + step - total_distance >= 1e-6)
	{
		position = total_distance;
		// if ()
		total_pos += total_distance;
		velocity = 0.0;
	}
	else
	{
		total_pos += step;
    	position += step;
	}
	

    // Update position based on velocity and time step
    // Check if the train has reached the specified distance or time limit
    // if (position >= total_distance) {
	// 	position = total_distance;
    //     // Stop the train (set velocity to zero)
    //     velocity = 0.0;
    // }
}

int main(int argc, char const *argv[]) try
{
	// command::ArgumentList lst;
	// lst.insert(std::make_pair(std::string()))
	// config::config::Config().Manager();
	std::filesystem::path path{std::string(CONFDIR)};

	std::filesystem::path full = path / "RailNetwork.conf";

	std::filesystem::path fullTrain = path / "TrainNetwork.conf";
	
	command::commandInterpreter::Interpreter().execute("RailLoad", {{std::string("--rail"), {full.string()}}});
	command::commandInterpreter::Interpreter().execute("TrainLoad", {{std::string("--train"), {fullTrain.string()}}});
	auto* net = config::config::Config().Network();
	auto* nodeCont = net->Manager()->get<object::container_type::NODE>();
	auto* railCont = net->Manager()->get<object::container_type::RAIL>();
	auto* node = nodeCont->get([&](object::node* n){
		return n->name() == "CityA";
	});
	if (!node)
		throw std::runtime_error(message::NonExistsNode);
	auto* train = net->Manager()->get<object::container_type::TRAIN>()->get([&](object::train* t)
	{
		return t->name() == "TrainAB1";
	});
	if (!train)
		throw std::runtime_error(message::NonExistsTrain);
	
	// node = nodeCont->get(train->startPoint());
	// if (!node)
	// 	throw std::runtime_error(message::NonExistsNode);
	// std::cout << "start: " << node->name() << "\n";
	// node = nodeCont->get(train->endPoint());
	// if (!node)
	// 	throw std::runtime_error(message::NonExistsNode);
	// std::cout << "end: " << node->name() << "\n";
	auto* gr = net->Graph();

	auto res = gr->shortest_path(train->startPoint(), train->endPoint(), train->ID());
	std::cout << "dist: " << res.first << "\n";
	std::cout << "path size: " << res.second.size() << "\n";
	std::cout << "path: \n";
	double total_dist = res.second.back().totalDistance();
	double total_time = 0.0;
	double total_pos = 0.0;
	double position = 0.0; // Initial position
	for (auto i : res.second)
	{
		double velocity = 0.0; // Initial velocity
		double acc = 0.0;
		double br = 0.0;
		double deaccDist = 0;
		// double finalVelocity = 0.0;	
		double max_acceleration = train->maxForce(object::force_type::ACC); // m/s^2
		double max_braking = train->maxForce(object::force_type::BREAK); // m/s^2
		double time_step = 0.5; // Time step (in seconds)
		double distance = i.totalDistance(); // Total distance to cover (in meters)
		double max_speed_limit = sqrt(2 * max_acceleration * distance / 10.0); // m/s
		double dist = i.totalDistance();
		double curr_time = 0.0;
		double max_time = i.time(); // Maximum simulation time (in seconds)
		std::cout << "allTime: " << max_time << "\n";
		std::cout << "allDist: " << dist << "\n";

		std::cout << "pos: " << position << " time: " << total_time << " velociy: " << velocity << "\n";
		while (curr_time < max_time)
		{
			if (velocity < max_speed_limit)
				acc = max_acceleration;
			else
				acc = 0;

			if (velocity > 0)
				br = max_braking;
			else
				br = 0;

			// Update velocity
			velocity += (acc - br) * time_step;
			if (velocity > max_speed_limit)
				velocity = max_speed_limit;

			// Update position
			position += velocity * time_step;

			if (acc == 0 && velocity > 0) { // Deceleration phase
				double decelerationForce = max_braking / 10.0;
    
				// Calculate deceleration rate
				// double decelerationRate = decelerationForce / 10.0;
				
				// Calculate deceleration time
				// double decelerationTime = velocity / decelerationRate;
				std::cout << "t: " << decelerationForce << "\n";
				// double decelerationTime = velocity / max_braking;
				 velocity -= decelerationForce * time_step; // Smoothly decrease velocity
				if (velocity < 0) // Ensure velocity doesn't become negative
					velocity = 0;
			}
			

			if (position >= distance)
			{
				position = distance;
				velocity = 0;
				break;
			}

			// Ensure the train doesn't go backwards
			if (position < 0) {
				position = 0;
				velocity = 0;
			}
			std::cout << "pos: " << position << " time: " << total_time << " velociy: " << velocity << "\n";
			curr_time += time_step;
			total_time += time_step;
		}
		std::cout << "pos: " << position << " time: " << total_time << " velociy: " << velocity << "\n";
	// 		// std::cout << "dist: " << position << " time: " << curr_time << " velocity: " << velocity << "\n"; 
	// 		// if (velocity < max_speed_limit) {
	// 		// 	// Increase velocity up to maximum speed limit
	// 		// 	double potential_velocity = velocity + max_acceleration * curr_time;
	// 		// 	velocity = std::min(potential_velocity, max_speed_limit);
	// 		// }

	// 		// // Simulate braking
	// 		// if (velocity > 0)
	// 		// {
	// 		// 	// Calculate the distance required to stop at max braking force
	// 		// 	double stopping_distance = (velocity * velocity) / (2 * max_braking);

	// 		// 	// If the stopping distance is greater than the distance to the next position, brake
	// 		// 	if (stopping_distance >= position)
	// 		// 	{
	// 		// 		velocity -= max_braking * curr_time;
	// 		// 		// Ensure velocity does not go negative
	// 		// 		velocity = std::max(0.0, velocity);
	// 		// 	}
	// 		// }
	// 		// position += velocity * curr_time;
	// 		// constexpr double maximum_speed = 120.0;
	// 	// Calculate time taken to accelerate and decelerate to maximum speed
	// 		double speed = i.distance() / i.time();
	// 		double acceleration_time =  speed / max_acceleration;
	// 		double braking_time = speed / max_braking;

	// 		// Calculate distance traveled during acceleration and deceleration phases
	// 		double acceleration_distance = 0.5 * max_acceleration * acceleration_time * acceleration_time;
	// 		double braking_distance = 0.5 * max_braking * braking_time * braking_time;
	// 		double remaining_distance = i.distance() - acceleration_distance - braking_distance;

	// 	// Calculate time taken to cover remaining distance at maximum speed
	// 		double remaining_time = remaining_distance / speed;

	// 		// Calculate total time taken for the rail segment
	// 		double total_time = acceleration_time + remaining_time + braking_time;
	// 		std::cout << "t_time: " << acceleration_distance << "\n";
	// 		// position = acceleration_distance + braking_distance;
	// 		curr_time += time_step;
	// 	}
		
	// 	// bool stopping = false;
	// 	// Simulate train movement until either distance or time limit is reached
	// 	// double current_time = 0.0;
	// 	// while (total_pos < total_dist)
	// 	// {
	// 	// 	// Simulate train movement for current time step

	// 	// 	// total_time += current_time;
	// 	// 	// total_position += position;
	// 	// 	std::cout << "Time: " << total_time << " seconds, Position: " << position << " total: " << total_pos << " meters, Velocity: " << velocity << " m/s" << std::endl;
	// 	// 	move(position, total_pos, velocity, max_acceleration, max_braking,\
	// 	// 	 max_speed_limit, time_step, distance, max_time);
			
	// 	// 	// total_position += position;
	// 	// 	// Output current position and velocity

	// 	// 	// Update current time
	// 	// 	current_time += time_step;
	// 	// 	total_time += time_step;
	// 	// }
	// 	// std::cout << "Time: " << total_time << " seconds, Position: " <<  position << " total: " << total_pos << " meters, Velocity: " << velocity << " m/s" << std::endl;
	// 	// total_position += position;
	// 	// total_time += current_time;
	}
	// for (auto i : res.second)
	// {
	// 	std::cout << "distance: " << i.time() << "\n";
	// 	auto* r = railCont->get(i.rail());
	// 	if (!r)
	// 		throw std::runtime_error(message::NonExistsRail);
	// 	auto* start = nodeCont->get(r->startPoint());
	// 	if (!start)
	// 		throw std::runtime_error(message::NonExistsNode);
	// 	auto* end = nodeCont->get(r->endPoint());
	// 	if (!end)
	// 		throw std::runtime_error(message::NonExistsNode);
	// 	std::cout << start->name() << " " << end->name() << "\n";

	// }
	std::cout << std::endl;
	// auto* t = net->Manager()->get<object::container_type::TRAIN>()->get([&](object::train* tr){
	// 	// return tr->name() == "CityA";
	// });
	// std::cout << (node == nullptr) << "\n";
	// std::cout << (train == nullptr) << "\n";
	// net->remove<object::container_type::NODE>(node->ID());
	// config::defaultConfig conf;
	// object::iManager Manager;
	// object::iContainer<object::container_type::NODE>* cont = new object::iContainer<object::container_type::NODE>;
	// cont->insert(std::make_unique<object::node>(std::string("aaa")));
	// auto x = cont.get([&](object::node* obj)
	// {

	// 	return obj->name() == "aaa";
	// });
	// Manager.insert(std::make_unique<object::iContainer<object::container_type::NODE>>());
	// auto m = Manager.get<object::container_type::NODE>();
	// m->insert(std::make_unique<object::node>("aaa"));
	// auto p = m->get([&](object::node* obj)
	// {

	// 	return obj->name() == "aaa";
	// });

	// std::cout << p->name() << "\n";
	// for (size_t i = 0; i < 1000; i++)
	// {
	// 	// std::cout << UniqueIDGenerator::generateID() << "\n";
	// }
	
	return 0;
}
catch(std::exception& ex)
{
	std::cerr << ex.what() << std::endl;
}
