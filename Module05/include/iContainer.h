#ifndef __ICONTAINER_H__
#define __ICONTAINER_H__

#include <unordered_map>
#include <memory>
#include <functional>
#include "iobj.h"

namespace object
{
	enum class container_type
	{
		OBJECT,
		RAIL,
		TRAIN,
		NODE,
		EVENT
	};
	class iCont
	{
		container_type _type;
		public:
			iCont(container_type a_type) : _type(a_type) {}
			container_type type() const
			{
				return _type;
			}
			virtual ~iCont() = default;
	};
	template<container_type Type>
	struct object
	{
		using type = iobj;
	};
	template<>
	struct object<container_type::EVENT>
	{
		using type = class event;
	};
	template<>
	struct object<container_type::NODE>
	{
		using type = class node;
	};
	template<>
	struct object<container_type::TRAIN>
	{
		using type = class train;
	};
	template<>
	struct object<container_type::RAIL>
	{
		using type = class rail;
	};
	template<container_type Type>
	using object_t = typename object<Type>::type;

	template<container_type Type, typename ObjType = object_t<Type>, typename ObjPtr = std::unique_ptr<ObjType>>
	class iContainer : public iCont
	{
		public:
			using obj_ptr = ObjPtr;
			using cont_type = std::unordered_map<size_t, ObjPtr>;
		private:
			cont_type _objs;
		public:
			iContainer() : iCont(Type) {}
			bool insert(ObjPtr obj)
			{
				return _objs.insert(std::make_pair(obj->ID(), std::move(obj))).second;
			}
			bool remove(size_t ID)
			{
				return _objs.erase(ID);
			}
			const ObjType* get(size_t ID) const
			{
				return _objs.at(ID).get();
			}
			ObjType* get(size_t ID)
			{
				return _objs.at(ID).get();
			}
			ObjType* get(std::function<bool(ObjType*)> callback)
			{
				for (auto &pair : _objs)
				{
					if (callback(pair.second.get()))
						return pair.second.get();
				}
				return nullptr;
			}
			size_t size() const
			{
				// size_t count = 0;
				// for (auto &pair : _objs)
				// {
				// 	if (pair.second.get())
				// 		++count;
				// }
				return _objs.size();
				// return _objs.size();
			}
			const ObjType* get(std::function<bool(ObjType*)> callback) const
			{
				for (auto &pair : _objs)
				{
					if (callback(pair.second.get()))
						return pair.second.get();
				}
				return nullptr;
			}
			void for_each(std::function<bool(ObjType*)> callback) const
			{
				for (auto &pair : _objs)
				{
					if(!callback(pair.second.get()))
						break;
				}
			}
	};
	
} // namespace object


#endif