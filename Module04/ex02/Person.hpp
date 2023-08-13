#ifndef __PERSON_HPP__
#define __PERSON_HPP__

#include <string>
#include <vector>
#include <memory>
#include "Room.hpp"
#include <iostream>

class Room;
class Classroom;
class Course;

class Person
{
protected:
	std::string _name;
	/*
	 * used weak_ptr for avoid memory leaks in circular dependency
	 * changed to raw pointers
	 * Room already managed by singleton
	*/
	Room* _currentRoom;

public:
	Person(std::string p_name)
		: _name(p_name)
	{}
	const std::string& getName() const
	{
		return _name;
	}

	Room* room()
	{
		return _currentRoom;
	}
	virtual ~Person()
	{
		std::cout << "destroy Person\n";
	}
};


class Student : public Person
{
private:
	/*
	 * used weak_ptr for avoid memory leaks in circular dependency
	 * changed to raw pointers becouse course already managed by singleton
	*/
	std::vector<Course*> _subscribedCourse;

public:
	Student(std::string p_name)
		:	Person(p_name)
	{}
	void attendClass(Classroom* p_classroom)
	{
		_currentRoom = p_classroom;
	}
	void exitClass()
	{
		_currentRoom = nullptr;
	}
	void graduate(Course* p_course)
	{
		_subscribedCourse.emplace_back(p_course);
	}
};

using Person_ptr = std::shared_ptr<Person>;
using Student_ptr = std::shared_ptr<Student>;

#endif