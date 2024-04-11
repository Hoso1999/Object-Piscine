#ifndef __UNIQUEIDGENERATOR_H__
#define __UNIQUEIDGENERATOR_H__

#include <chrono>
#include <unistd.h>

namespace generator
{
	class UniqueIDGenerator
	{
		private:
			static size_t counter;

		public:
			// Generate a unique ID based on timestamp, process ID, and a counter
			static size_t generateID()
			{
				auto now = std::chrono::system_clock::now();
				auto duration = now.time_since_epoch();
				auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
				size_t id = (millis << 16) | (getProcessID() << 8) | (counter);
				++counter;
				return id;
			}

			// Get the process ID
			static unsigned long getProcessID()
			{
				return static_cast<unsigned long>(getpid()); // Requires POSIX, might not work on all systems
			}
	};

} // namespace generator


#endif