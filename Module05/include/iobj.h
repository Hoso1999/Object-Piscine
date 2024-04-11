#ifndef __IOBJ_H__
#define __IOBJ_H__

#include <memory>
#include <string>
#include "uniqueIDGenerator.h"

namespace object
{
	enum class object_type
	{
		NODE,
		RAIL,
		TRAIN,
		EVENT
	};
	extern const size_t npos;
	class iobj
	{
		public:
			using Base = iobj;
		private:
			object_type _type;
			size_t		_id;
		
		public:
			object_type type() const
			{
				return _type;
			}
			size_t ID()
			{
				return _id;
			}
			size_t ID() const
			{
				return _id;
			}
			iobj(object_type a_type) : _type(a_type), _id(generator::UniqueIDGenerator::generateID()) {};
	};
	using iobj_ptr = std::unique_ptr<iobj>;
} // namespace object


#endif