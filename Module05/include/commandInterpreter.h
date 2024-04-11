#ifndef __COMMANDINTERPRETER_H__
#define __COMMANDINTERPRETER_H__

#include <unordered_map>
#include <memory>
#include "iCommand.h"

namespace command
{
	class commandFactory
	{
		public:
			commandFactory() = default;
			iCommand_ptr createCommand(command_type type) const;
	};
	class commandInterpreter
	{
		public:
			using cont_type = std::unordered_map<std::string, iCommand_ptr>;

		private:
			cont_type		_commands;
			commandFactory	_factory;
			bool createCommand(command_type type);
			commandInterpreter();
		public:
			static commandInterpreter& Interpreter()
			{
				static commandInterpreter interpreter;
				return interpreter;
			}
			void execute(const std::string& command_name, ArgumentList&& args);
	};
} // namespace command



#endif