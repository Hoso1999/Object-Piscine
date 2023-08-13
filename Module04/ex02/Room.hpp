#ifndef __ROOM_HPP__
#define __ROOM_HPP__

#include <vector>
#include <memory>
#include <iostream>

class Person;
class Course;
class Form;

class Room
{
	protected:
		long long ID;
		std::vector<Person*> _occupants;

	public:
		Room() : ID(0) {}
		bool canEnter(Person*) {
			return false;
		}
		void enter(Person* p_person)
		{
			_occupants.emplace_back(p_person);
		}
		void exit(Person* p_person)
		{

		}
		virtual ~Room()
		{
			std::cout << "destroy Room\n";
		}
		void printOccupant() {}
};

class Classroom : public Room
{
	private:
		Course* _currentRoom;

	public:
		Classroom()
			:	Room()
		{}
		void assignCourse(Course* p_course)
		{
			_currentRoom = p_course;
		}
};

class SecretarialOffice : public Room
{
	private:
		std::vector<std::shared_ptr<Form>> _archivedForms;

	public:
		SecretarialOffice()
			:	Room()
		{}
};

class HeadmasterOffice : public Room
{
	private:
	public:
		HeadmasterOffice()
			:	Room()
		{}
};

class StaffRestRoom : public Room
{
	private:
	public:
		StaffRestRoom()
			:	Room()
		{}
};

class Courtyard : public Room
{
	private:
	public:
		Courtyard()
			:	Room()
		{}
};

using Room_ptr = std::shared_ptr<Room>;
using Classroom_ptr = std::shared_ptr<Classroom>;



#endif