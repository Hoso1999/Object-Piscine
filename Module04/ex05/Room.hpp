#ifndef __ROOM_HPP__
#define __ROOM_HPP__

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "Person.hpp"
#include "NotifyManager.hpp"

class Person;
class Course;
class Form;
class RoomEnterNotify;
class RoomExitNotify;

enum class RoomType
{
	CLASSROOM,
	SECRETARIALOFFICE,
	STAFFRESTROOM,
	HEADMASTEROFFICE,
	COURTYARD
};

class Room
{
	protected:
		static long long _id;
		long long ID;
		RoomType							_type;
		NotifyManager						_notifyManager;
		std::vector<Person*>				_occupants;
	public:
		Room(RoomType p_type);
		RoomType getType() const
		{
			return _type;
		}
		/*
		 * maybe change to pure virtual?
		*/
		virtual bool canEnter(Person*)
		{
			return true;
		}
	
		long long getID()
		{
			return ID;
		}
		/*
		 * should person leave room first?
		*/
		void enter(Person* p_person);
		void exit(Person* p_person);
		/*
		 * update room when person enter or leave room
		*/
		void updateEnterPerson(Person* p_person);
		void updateExitPerson(Person* p_person);
		virtual ~Room()
		{
			// std::cout << "destroy Room\n";
		}
		void printOccupant() {}
};


class Classroom : public Room
{
	private:
		Course* _currentRoom;

	public:
		Classroom()
			:	Room(RoomType::CLASSROOM),
				_currentRoom(nullptr)
		{}
		void assignCourse(Course* p_course)
		{
			_currentRoom = p_course;
		}
		void removeCourse()
		{
			_currentRoom = nullptr;
		}
		bool hasOccupied() const
		{
			return _currentRoom != nullptr;
		}
		bool canEnter(Person* p_person) override
		{
			if (!p_person)
				return false;
			auto p = p_person;
			return !hasOccupied() && (p && (p->getType() == PersonType::STUDENT || p->getType() == PersonType::PROFESSOR));
		}
};
/*
 * does SecretarialOffice can be only one?
 * maybe throw an exception when trying create second?
 * i dont want do it with singleton
*/
class SecretarialOffice : public Room
{
	private:
		std::vector<std::shared_ptr<Form>> _archivedForms;

	public:
		SecretarialOffice()
			:	Room(RoomType::SECRETARIALOFFICE)
		{}
		bool canEnter(Person* p_person) override
		{
			if (!p_person)
				return false;
			auto p = p_person;
			return (p && (p->getType() == PersonType::SECRETARY || p->getType() == PersonType::HEADMASTER));
		}
};
/*
 * does HeadmasterOffice can be only one?
 * maybe throw an exception when trying create second?
 * i dont want do it with singleton
*/
class HeadmasterOffice : public Room
{
	private:
	public:
		HeadmasterOffice()
			:	Room(RoomType::HEADMASTEROFFICE)
		{}
		bool canEnter(Person* p_person) override
		{
			if (!p_person)
				return false;
			auto p = p_person;
			return (p && (p->getType() == PersonType::HEADMASTER));
		}
};
/*
 * does StaffRestRoom can be only one?
 * maybe throw an exception when trying create second?
 * i dont want do it with singleton
*/
class StaffRestRoom : public Room
{
	private:
	public:
		StaffRestRoom()
			:	Room(RoomType::STAFFRESTROOM)
		{}
		bool canEnter(Person* p_person) override
		{
			if (!p_person)
				return false;
			auto p = p_person;
			return (p && (p->getType() != PersonType::STUDENT));
		}
};
/*
 * does Courtyard can be only one?
 * maybe throw an exception when trying create second?
 * i dont want do it with singleton
*/
class Courtyard : public Room
{
	private:
	public:
		Courtyard()
			:	Room(RoomType::COURTYARD)
		{}
		/*
		 * no need override canEnter
		 * every person can enter to Courtyard
		*/
};

using Room_ptr = std::shared_ptr<Room>;
using Classroom_ptr = std::shared_ptr<Classroom>;



#endif