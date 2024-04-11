#ifndef __IRAILHANDLER_H__
#define __IRAILHANDLER_H__


#include "iFileHandler.h"
#include <string>

namespace handler
{
	class iRailHandler : public	iFileHandler
	{
		bool load(const std::string& a_filename) const override;
		public:
			iRailHandler(network::network* net = nullptr) : iFileHandler{net} {}
	};
	
} // namespace handler

#endif