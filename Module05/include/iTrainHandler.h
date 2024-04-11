#ifndef __ITRAINHANDLER_H__
#define __IRAILHANDLER_H__

#include "iFileHandler.h"
#include <iostream>

namespace handler
{
	class iTrainHandler : public iFileHandler
	{
		bool load(const std::string& a_filename) const override;
		public:
			iTrainHandler(network::network* net = nullptr) : iFileHandler{net, handler_type::TRAIN} {}
	};
	
} // namespace handler

#endif