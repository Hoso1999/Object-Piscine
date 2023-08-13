#ifndef __STAFF_HPP__
#define __STAFF_HPP__

#include "Person.hpp"
#include <memory>
#include "FormFactory.hpp"
#include "Course.hpp"

class FormFactory;
enum class FormType;
class Person;
class Course;
class Form;

class Staff : public Person
{
private:
public:
	Staff(std::string p_name, PersonType p_type = PersonType::STAFF)
		:	Person(p_name, p_type)
	{}
	/*
	 * maybe set to pure virtual
	*/
	void sign(std::shared_ptr<Form> p_form);
	virtual ~Staff()
	{
		// std::cout << "destroy Staff\n";
	}
};

class Secretary : public Staff
{
	private:
	public:
		Secretary(std::string p_name)
			:	Staff(p_name, PersonType::SECRETARY)
		{}
		/*
		 * used FormFactory
		*/
		std::shared_ptr<Form> createForm(FormType p_formType)
		{
			return FormFactory::createForm(p_formType);
		}
		/*
		 * I dont know what should do this function
		*/
		void archiveForm() {}
};



using Staff_ptr = std::shared_ptr<Staff>;
using Secretary_ptr = std::shared_ptr<Secretary>;

#endif