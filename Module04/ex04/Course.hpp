#ifndef __COURSE_HPP__
#define __COURSE_HPP__

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>
#include "NotifyManager.hpp"
// #include "INotify.hpp"

class Student;
class Professor;
class SubscribeNotify;
class AssignNotify;
class Classroom;

/*
 * inherit from std::enable_shared_from_this
 * because should create shared_ptr from this pointer
*/
class Course
{
	private:
		std::string				_name;
		Professor*				_responsable;
		std::vector<Student*> 	_students;
		NotifyManager&			_notifyManager;
		int 					_numberOfClassToGraduate;
		int 					_maximumNumberOfStudent;

	public:
		Course(std::string p_name)
			:	_name(p_name),
				_numberOfClassToGraduate(2),
				_maximumNumberOfStudent(5),
				_notifyManager(NotifyManager::getNotifyManager())
		{}
		
		void setMaximumStudents(int p_maximum)
		{
			_maximumNumberOfStudent = p_maximum;
		}

		bool hasStudent(Student* p_student);
		bool hasResponsable() const
		{
			return _responsable;
		}
		void setRequiredClasses(int p_numberOfClasses)
		{
			_numberOfClassToGraduate = p_numberOfClasses;
		}
		int numberClassToGraduate() const
		{
			return _numberOfClassToGraduate;
		}
		int maxStudents() const
		{
			return _maximumNumberOfStudent;
		}
		int currentStudentsCount() const
		{
			return _students.size();
		}
		/*
		 * should classroom be weak_ptr?
		*/
		void assignClass(Classroom* p_class);

		bool isFull() const
		{
			return _students.size() >= _maximumNumberOfStudent;
		}

		const std::string& getName() const
		{
			return _name;
		}
		/*
		 * there can be ownership problem
		 * used weak_ptr instead
		*/
		void assign(Professor* p_professor);

		void updateResponsable(Professor* p_professor)
		{
			_responsable = p_professor;
		}
		Professor* getResponsable()
		{
			return _responsable;
		}

		void subsribe(Student* p_student);

		/*
		 * internal iterator for course
		*/
		void apply(std::function<bool(Student*)> p_callback)
		{
			for (auto st : _students)
				p_callback(st);
		}

		void updateSubscribe(Student* p_student)
		{
			_students.emplace_back(p_student);
		}
		void updateGraduate(Student* p_student);
		~Course()
		{
			// std::cout << "destroy course\n";
		}
};

using Course_ptr = std::shared_ptr<Course>;



#endif