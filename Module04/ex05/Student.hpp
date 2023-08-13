#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__

#include "Person.hpp"
#include "NotifyManager.hpp"
#include "observer.hpp"

class Person;
enum class FormType;

/*
 * inherits from Listener because should notifed on events
 * maybe inherit from Listener with private mode? 
*/
class Student : public Person, public Listener
{
	private:
		/*
		 * used weak_ptr for avoid memory leaks in circular dependency
		 * changed to raw pointer, singleton managed lifetime
		*/
		std::vector<Course*> 	_subscribedCourse;
		int						_numberOfClasses;
		Room*					_lastRoom;
		BellSystem*           	_bellSystem;

	public:
		Student(std::string p_name);
		void attendClass(Classroom* p_classroom);
		void subcribe(Course* p_course);
		void fillForm(std::shared_ptr<Form> p_form);
		void updateSubscribe(Course* p_course)
		{
			static std::mutex m;
			std::lock_guard<std::mutex> guard(m);
			_subscribedCourse.emplace_back(p_course);
		}
		void goClass();
		void learn()
		{
			static std::mutex m;
			std::lock_guard<std::mutex> guard(m);
			++_numberOfClasses;
		}

		void setBellSystem(BellSystem* p_bell);
		int numberOfClasses() const
		{
			static std::mutex m;
			std::lock_guard<std::mutex> guard(m);
			return _numberOfClasses;
		}
		void exitClass()
		{
			static std::mutex m;
			std::lock_guard<std::mutex> guard(m);
			exitRoom();
		}
		void update(Event p_event) override;
		void updateSigned(bool, FormType) {}
		/*
		* is it means finish course? 
		*/
		void graduate(Course* p_course);

};

using Student_ptr = std::shared_ptr<Student>;

#endif