#ifndef __FORM_HPP__
#define __FORM_HPP__

#include <iostream>

enum class FormType
{
	CourseFinished,
	NeedMoreClassRoom,
	NeedCourseCreation,
	SubscriptionToCourse
};

class Form
{
	protected:
		FormType _formType;

	public:
		Form(FormType p_formType)
		{}
	
		virtual ~Form()
		{
			std::cout << "destroy Form\n";
		}
		virtual void execute() = 0;
};

class CourseFinishedForm : public Form
{
	private:
	public:
		CourseFinishedForm()
			:	Form(FormType::CourseFinished)
		{}
		void execute() {}
};

class NeedMoreClassRoomForm : public Form
{
	private:
	public:
		NeedMoreClassRoomForm()
			:	Form(FormType::NeedMoreClassRoom)
		{}
		void execute() {}
};

class NeedCourseCreationForm : public Form
{
	private:
	public:
		NeedCourseCreationForm()
			:	Form(FormType::NeedCourseCreation)
		{}
		void execute() {}
};

class SubscriptionToCourseForm : public Form
{
	private:
	public:
		SubscriptionToCourseForm()
			:	Form(FormType::SubscriptionToCourse)
		{}
		void execute() {}
};

#endif