#include "Messages.h"

namespace message
{
	const std::string& NodeUsage = "Node <node_name>";
	const std::string& RailUsage = "Rail <from_node> <to_node> <distance>";
	const std::string& EventUsage = "Event <event_name> <probability> <duration> <location>";
	const std::string& TrainUsage = "Train <node_name> <max_acc_force> <max_br_force> <from_city> <to_city> <duration>";
	const std::string& EmptyNodeName = "Node name is empty";
	const std::string& EmptyRailNodeName = "RailNode name is empty";
	const std::string& NoRailName = "Rail name is empty";
	const std::string& InvalidNodeName = "Node name should start with City or RailNode";
	const std::string& InvalidCityName = "City name should start with City";
	const std::string& InvalidRailNodeName = "RailNode name should start with RailNode";
	const std::string& NonExistsNode = "Node does not exists";
	const std::string& NonExistsRail = "Rail does not exists";
	const std::string& NonExistsTrain = "Train does not exists";
	const std::string& NonExistsEvent = "Event does not exists";
	const std::string& NonExistsFile = "File does not exists";

	const std::string& SameRailStartEnd = "Rail start and end should be different";

	const std::string& NonBalancedQuote = "Quotes should be balanced";

	const std::string& AlreadyExistsNode = "Node with specified name already exists";
	const std::string& AlreadyExistsTrain = "Train with specified name already exists";
	const std::string& AlreadyExistsRail = "Rail with start and end already exists";

	const std::string& unableInsertNode = "Unable insert Node";
	const std::string& unableInsertRail = "Unable insert Rail";
	const std::string& unableInsertEvent = "Unable insert Event";
	const std::string& unableInsertTrain = "Unable insert Train";

	const std::string& AlreadyExistsEvent = "Event already exists";
} // namespace message
