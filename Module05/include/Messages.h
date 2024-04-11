#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string>

namespace message
{
	extern const std::string& NodeUsage;
	extern const std::string& RailUsage;
	extern const std::string& EventUsage;
	extern const std::string& TrainUsage;

	extern const std::string& EmptyNodeName;
	extern const std::string& EmptyRailNodeName;
	extern const std::string& InvalidNodeName;
	extern const std::string& InvalidRailName;
	extern const std::string& NonExistsNode;
	extern const std::string& NonExistsRail;
	extern const std::string& NonExistsTrain;
	extern const std::string& NonExistsEvent;
	extern const std::string& NonExistsFile;
	extern const std::string& SameRailStartEnd;

	extern const std::string& unableInsertNode;
	extern const std::string& unableInsertRail;
	extern const std::string& unableInsertEvent;
	extern const std::string& unableInsertTrain;
	extern const std::string& AlreadyExistsNode;
	extern const std::string& AlreadyExistsTrain;
	extern const std::string& AlreadyExistsEvent;
	extern const std::string& AlreadyExistsRail;

	extern const std::string& NonBalancedQuote;
} // namespace message


#endif