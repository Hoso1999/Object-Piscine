#ifndef __ICOMMAND_H__
#define __ICOMMAND_H__

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "iContainer.h"
#include "network.h"
#include "include/event.h"
#include "config.h"
#ifndef CONFDIR
	#define CONFDIR "."
#endif

namespace command
{
	enum class command_type
	{
		FILEOPEN,
		RAILLOAD,
		TRAINLOAD,
		NODE,
		RAIL,
		EVENT,
		TRAIN
	};

	using ArgumentList = std::unordered_map<std::string, std::vector<std::string>>;

	class iCommand
	{
		private:
			command_type _type;
		protected:
			std::string	 _cmd;
		public:
			command_type type() const
			{
				return _type;
			}
			const std::string& name() const
			{
				return _cmd;
			}
			iCommand(const std::string& a_name, const std::string& a_extension, command_type a_type) : _type(a_type)
			{
				_cmd = a_name + a_extension;
			};
			virtual ~iCommand() = default;
			virtual bool validate(ArgumentList&& args) = 0;
			virtual bool execute(ArgumentList&& args) = 0;
	};
	template<object::container_type Type>
	class iObjectCreate : public iCommand
	{
		protected:
			using Base = iObjectCreate<Type>;
			network::network* _net;
			object::iContainer<Type>* _cont;
		public:
			iObjectCreate(const std::string& a_objname, command_type type)
				: iCommand("object", a_objname, type)
			{
				_net = config::config::Config().Network();
				_cont = _net->Manager()->get<Type>();
			}
	};
	class iNode : public iObjectCreate<object::container_type::NODE>
	{
		std::string	_node_name;
		bool		_opCity;
		bool		_opRailNode;
		public:
			iNode()
				: Base("Node",command_type::NODE), _opCity{false}, _opRailNode{false}
			{}
			bool validate(ArgumentList&& args) override;
			bool execute(ArgumentList&& args) override;
	};
	class iRail : public iObjectCreate<object::container_type::RAIL>
	{
		std::string	_from;
		std::string	_to;
		double		_distance;
		public:
			iRail() : Base("Rail", command_type::RAIL) {}
			bool validate(ArgumentList&& args) override;
			bool execute(ArgumentList&& args) override;
	};
	class iTrain : public iObjectCreate<object::container_type::TRAIN>
	{
		using duration_type = object::event::duration_type;
		std::string		_train_name;
		std::string 	_from;
		std::string 	_to;
		double			_max_acc_force;
		double			_max_br_force;
		duration_type	_start_time;
		public:
			iTrain()
				: Base("Train", command_type::TRAIN) {}
			bool validate(ArgumentList&& args) override;
			bool execute(ArgumentList&& args) override;
	};
	class iEvent : public iObjectCreate<object::container_type::EVENT>
	{
		using duration_type = object::event::duration_type;
		std::string		_name;
		double			_prob;
		duration_type	_duration;
		std::string		_loc;
		public:
			iEvent() : Base("Event", command_type::EVENT) {}
			bool validate(ArgumentList&& args) override;
			bool execute(ArgumentList&& args) override;
	};
	class iFileOpen : public iCommand
	{
		protected:
			std::string _filename;
		public:
			iFileOpen(const std::string& a_name = "file", const std::string& a_name_prefix = "open")
				: iCommand(a_name, a_name_prefix, command_type::FILEOPEN)
			{}
			virtual bool validate(ArgumentList&& args) override;
			virtual bool execute(ArgumentList&& args) override;
	};
	class iRailLoad : public iFileOpen
	{
		public:
			iRailLoad() : iFileOpen("Rail", "Load") {}
			bool validate(ArgumentList&& args) override;
			bool execute(ArgumentList&& args) override;
	};
	class iTrainLoad : public iFileOpen
	{
		public:
			iTrainLoad() : iFileOpen("Train", "Load") {}
			bool validate(ArgumentList&& args) override;
			bool execute(ArgumentList&& args) override;
	};


	using iCommand_ptr = std::unique_ptr<iCommand>;
	
} // namespace command




#endif