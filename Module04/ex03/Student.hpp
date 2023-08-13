#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__

#include "Person.hpp"
#include "NotifyManager.hpp"

class Person;

class Student : public Person
{
	private:
		/*
		* used weak_ptr for avoid memory leaks in circular dependency
		*/
		std::vector<Course*> 	_subscribedCourse;
		int						_numberOfClasses;

	public:
		Student(std::string p_name);
		void attendClass(Classroom* p_classroom);
		void subcribe(Course* p_course);
		void fillForm(std::shared_ptr<Form> p_form);
		void updateSubscribe(Course* p_course)
		{
			_subscribedCourse.emplace_back(p_course);
		}
		void goClass();
		void learn()
		{
			++_numberOfClasses;
		}
		int numberOfClasses() const
		{
			return _numberOfClasses;
		}
		void exitClass()
		{
			exitRoom();
		}
		void update(bool) {}
		/*
		* is it means finish course? 
		*/
		void graduate(Course* p_course);

};

using Student_ptr = std::shared_ptr<Student>;

#endif