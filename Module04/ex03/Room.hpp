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
		std::vector<Person*>				_occupants;
		std::unique_ptr<NotifyManager>		_notifyManager;
	public:
		Room(RoomType p_type)
			:	ID(_id),
				_type(p_type)
		{
			++Room::_id;
		}
		RoomType getType() const
		{
			return _type;
		}
		virtual bool canEnter(Person*)
		{
			return true;
		}
		// void addNotify(std::weak_ptr<INotifyBase> p_notify);
	
		long long getID()
		{
			return ID;
		}
		/*
		 * should person leave room first?
		*/
		void enter(Person* p_person);
		void exit(Person* p_person);
		void updateEnterPerson(Person* p_person);
		void updateExitPerson(Person* p_person);
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
			:	Room(RoomType::CLASSROOM)
		{}
		void assignCourse(Course* p_course)
		{
			_currentRoom = p_course;
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

class Courtyard : public Room
{
	private:
	public:
		Courtyard()
			:	Room(RoomType::COURTYARD)
		{}
};

using Room_ptr = std::shared_ptr<Room>;
using Classroom_ptr = std::shared_ptr<Classroom>;



#endif