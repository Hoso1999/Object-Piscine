#ifndef __COURSE_HPP__
#define __COURSE_HPP__

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Staff.hpp"
#include "Person.hpp"

class Student;
class Professor;

class Course
{
	private:
		std::string				_name;
		Professor*				_responsable;
		std::vector<Student*>	_students;
		int						_numberOfClassToGraduate;
		int						_maximumNumberOfStudent;

	public:
		Course(std::string p_name)
			:	_name(p_name),
				_numberOfClassToGraduate(0),
				_maximumNumberOfStudent(0)
		{}

		const std::string& getName() const
		{
			return _name;
		}
		void assign(Professor* p_professor)
		{
			_responsable = p_professor;
		}
		void subscribe(Student* p_student)
		{
			_students.emplace_back(p_student);
		}
		~Course()
		{
			std::cout << "destroy course\n";
		}
};

using Course_ptr = std::shared_ptr<Course>;

#endif