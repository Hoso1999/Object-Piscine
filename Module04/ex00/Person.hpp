#ifndef __PERSON_HPP__
#define __PERSON_HPP__

#include <string>
#include <vector>
class Room;
class Classroom;
class Course;

class Person
{
	protected:
		std::string _name;
		Room *_currentRoom;

	public:
		Person(std::string p_name)
			:	_name(p_name),
				_currentRoom(nullptr)
		{}
		Room *room() { return (_currentRoom); }
};


class Student : public Person
{
private:
	std::vector<Course *> _subscribedCourse;

public:
	void attendClass(Classroom *p_classroom);
	void exitClass();
	void graduate(Course *p_course);
};



#endif