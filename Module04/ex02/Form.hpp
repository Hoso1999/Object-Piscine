#ifndef __FORM_HPP__
#define __FORM_HPP__

#include <iostream>
#include "Course.hpp"


enum class FormType
{
	CourseFinished,
	NeedMoreClassRoom,
	NeedCourseCreation,
	SubscriptionToCourse
};


/*
 * Command design pattern for sign forms
*/
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
		/*
		 * How forms can know if it signed by headmaster?
		 * maybe get headmaster in execute?
		*/
		virtual void execute() = 0;
};

class CourseFinishedForm : public Form
{
	private:
		bool		_finished;
		Course*		_course;
	public:
		CourseFinishedForm()
			:	Form(FormType::CourseFinished)
		{}
		bool isFinished() const
		{
			return _finished;
		}
		void setCourse(Course* p_course)
		{
			_course = p_course;
		}
		void finish(bool p_finished)
		{
			_finished = p_finished;
		}
		void execute();
};

class NeedMoreClassRoomForm : public Form
{
	private:
		Classroom* _classroom;
	public:
		NeedMoreClassRoomForm()
			:	Form(FormType::NeedMoreClassRoom)
		{}
		Classroom* classroom() const
		{
			return _classroom;
		}
		void creation(Classroom* p_classroom)
		{
			_classroom = p_classroom;
		}
		void execute();
};

class NeedCourseCreationForm : public Form
{
	private:
		std::string		_subject;
		Professor*		_professor;
	public:
		NeedCourseCreationForm()
			:	Form(FormType::NeedCourseCreation)
		{}
		const std::string& subject() const
		{
			return _subject;
		}
		void setSubject(const std::string& p_subject)
		{
			_subject = p_subject;
		}
		void assign(Professor* p_professor)
		{
			_professor = p_professor;
		}
		void execute();
};

class SubscriptionToCourseForm : public Form
{
	private:
		Course*		_course;
		Student*	_student;
	public:
		SubscriptionToCourseForm()
			:	Form(FormType::SubscriptionToCourse)
		{}
		void subscript(Course* p_course)
		{
			_course = p_course;
		}
		void from(Student* p_student)
		{
			_student = p_student;
		}
		void execute();
};

#endif