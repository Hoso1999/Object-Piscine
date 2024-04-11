#ifndef __NETWORKMANAGER_H__
#define __NETWORKMANAGER_H__

#include <memory>
#include <unordered_map>

namespace network
{
	// using manager_ptr = std::unique_ptr<class iManager_base>;

	// class ManagerFactory
	// {
	// 	public:
	// 		ManagerFactory() = default;
	// 		manager_ptr createManager(enum class manager_type type);
	// };
	// class NetworkManager : private ManagerFactory
	// {
	// 	public:
	// 		using manager_cont_type = std::unordered_map<enum class manager_type, manager_ptr>;
	// 	private:
	// 		manager_cont_type	_managers;
	// 	public:
	// 		NetworkManager() = default;
	// 		bool insert(enum class manager_type type);
	// };
} // namespace network


#endif