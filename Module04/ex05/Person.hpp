#ifndef __PERSON_HPP__
#define __PERSON_HPP__

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "NotifyManager.hpp"

class Room;
class Classroom;
class Course;
class NotifyManager;
class RoomEnterNotify;
class RoomExitNotify;


enum class PersonType
{
	PERSON,
	STAFF,
	STUDENT,
	PROFESSOR,
	SECRETARY,
	HEADMASTER
};

/*
 * inherit from std::enable_shared_from_this
 * because should create shared_ptr from this pointer
 * I think its not good solution
 * maybe inherit only Person types that used mediator pattern?
 * singleton managed object lifetime
 * remove inheritance for performance
*/
class Person
{
	protected:
		PersonType	_type;
		std::string _name;
		/*
		 * used weak_ptr for avoid memory leaks in circular dependency
		 * changed to raw pointers for improve performance
		 * singleton managed object lifetime 
		*/
		Room*				_currentRoom;
		NotifyManager&		_notifyManager;
		

	public:
		Person(std::string p_name, PersonType p_type = PersonType::PERSON)
			:	_name(p_name),
				_type(p_type),
				_currentRoom(nullptr),
				_notifyManager(NotifyManager::getNotifyManager())
		{}

		PersonType getType() const
		{
			return _type;
		}
		const std::string& getName() const
		{
			return _name;
		}
		/*
		 * should every person need method for exit from room?
		 * what should be if room removes person?
		*/
		Room* room()
		{
			return _currentRoom;
		}
		

		void enterRoom(Room* p_room);
		/*
		 * update person when enter or leave room
		*/
		void updateEnterRoom(Room* p_room)
		{
			_currentRoom = p_room;
		}
		void updateExitRoom()
		{
			_currentRoom = nullptr;
		}
		/*
		 * can every person exit from room?
		 * is good choice using mediator pattern?
		 * i think when person exit from room,
		 * room should exit person from self and reverse. 
		*/
		void exitRoom();
		virtual ~Person() {}
};

using Person_ptr = std::shared_ptr<Person>;

#endif