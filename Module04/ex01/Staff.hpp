#ifndef __STAFF_HPP__
#define __STAFF_HPP__

#include "Person.hpp"
#include <memory>

enum class FormType;
class Form;

class Staff : public Person
{
private:
public:
	Staff(std::string p_name)
		:	Person(p_name)
	{}
	void sign(std::shared_ptr<Form> p_form) {}
	virtual ~Staff()
	{
		std::cout << "destroy Staff\n";
	}
};


class Headmaster : public Staff
{
private:
	std::vector<std::shared_ptr<Form>> _formToValidate;

public:
	Headmaster(std::string p_name)
		:	Staff(p_name)
	{}
	void receiveForm(std::shared_ptr<Form> p_form)
	{
		_formToValidate.emplace_back(p_form);
	}
};

class Secretary : public Staff
{
private:
public:
	Secretary(std::string p_name)
		:	Staff(p_name)
	{}

	std::shared_ptr<Form> createForm(FormType p_formType)
	{
		return nullptr;
	}

	void archiveForm() {}
};

class Professor : public Staff
{
private:
	Course* _currentCourse;

public:
	Professor(std::string p_name)
		:	Staff(p_name)
	{}
	void assignCourse(Course* p_course)
	{
		_currentCourse = p_course;
	}
	void doClass() {}
	void closeCourse() {}
};

using Staff_ptr = std::shared_ptr<Staff>;
using Secretary_ptr = std::shared_ptr<Secretary>;
using Headmaster_ptr = std::shared_ptr<Headmaster>;
using Professor_ptr = std::shared_ptr<Professor>;

#endif