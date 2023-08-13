#ifndef __COURSE_HPP__
#define __COURSE_HPP__

#include <string>
#include <vector>

class Student;
class Professor;

class Course
{
private:
	std::string _name;
	Professor *_responsable;
	std::vector<Student *> _students;
	int _numberOfClassToGraduate;
	int _maximumNumberOfStudent;

public:
	Course(std::string p_name);
	void assign(Professor *p_professor)
	{
		_responsable = p_professor;
	}
	void subscribe(Student *p_student)
	{
		_students.push_back(p_student);
	}
};


#endif