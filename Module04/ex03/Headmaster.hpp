#ifndef __HEADMASTER_HPP__
#define __HEADMASTER_HPP__

#include "Staff.hpp"

/*
 * I think there can be created only one headmaster
 * Maybe throw exception if try to create second?
 * and same i think about secretary
*/
class Headmaster : public Staff
{
	private:
		std::vector<std::shared_ptr<Form>> _formToValidate;

	public:
		Headmaster(std::string p_name)
			:	Staff(p_name, PersonType::HEADMASTER)
		{}
		std::shared_ptr<Form> recieveRequest(FormType _type);
		/*
		* how should headmaster recieve form?
		* maybe from secretary?
		*/
		bool confirm(std::shared_ptr<Form> p_form);
		void startCourses();
		void receiveForm(std::shared_ptr<Form> p_form);
};

using Headmaster_ptr = std::shared_ptr<Headmaster>;

#endif