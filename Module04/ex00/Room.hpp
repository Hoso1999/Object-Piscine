#ifndef __ROOM_HPP__
#define __ROOM_HPP__

#include <vector>

class Person;
class Course;
class Form;

class Room
{
protected:
	long long ID;
	std::vector<Person *> _occupants;

public:
	Room();
	bool canEnter(Person *);
	void enter(Person *);
	void exit(Person *);

	void printOccupant();
};

class Classroom : public Room
{
private:
	Course *_currentRoom;

public:
	Classroom();
	void assignCourse(Course *p_course)
	{
		_currentRoom = p_course;
	}
};

class SecretarialOffice : public Room
{
private:
	std::vector<Form *> _archivedForms;

public:
};

class HeadmasterOffice : public Room
{
private:
public:
};

class StaffRestRoom : public Room
{
private:
public:
};

class Courtyard : public Room
{
private:
public:
};





#endif