#ifndef __IMANAGER_H__
#define __IMANAGER_H__

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include "iContainer.h"

// #include "iContainer.h"
// namespace object
// {
// 	template<
// } // namespace object


namespace object
{
	enum class manager_type
	{
		NODE,
		RAIL,
		TRAIN,
		EVENT
	};
	using iCont_ptr = std::unique_ptr<iCont>;
	class iManager
	{
		public:
			using cont_type = std::unordered_map<container_type, iCont_ptr>;
		private:
			cont_type _containers;
			iCont_ptr	createContainer(container_type type) const;
			bool insert(iCont_ptr container);
		public:
			iManager()
			{
				insert(std::move(createContainer(container_type::NODE)));
				insert(std::move(createContainer(container_type::RAIL)));
				insert(std::move(createContainer(container_type::TRAIN)));
				insert(std::move(createContainer(container_type::EVENT)));
			};
			template<container_type Type>
			iContainer<Type>* get() const
			{
				return dynamic_cast<iContainer<Type>*>(_containers.at(Type).get());
			}
	};
} // namespace network





#endif