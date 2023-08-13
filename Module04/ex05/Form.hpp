#ifndef __FORM_HPP__
#define __FORM_HPP__

#include <iostream>
#include <memory>

class Classroom;
class Professor;
class Student;
class Course;

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
		FormType 					_formType;

	public:
		Form(FormType p_formType)
			:	_formType(p_formType)
		{}

		FormType getType() const
		{
			return _formType;
		}

		virtual ~Form()
		{}
		/*
		 * How forms can know if it signed by headmaster?
		 * maybe get headmaster in execute?
		*/
		virtual void execute() = 0;
		virtual bool validate() = 0;
};

class CourseFinishedForm : public Form
{
	private:
		bool			_finished;
		Student*		_student;
		Professor*		_responsable;
	public:
		CourseFinishedForm()
			:	Form(FormType::CourseFinished),
				_student(nullptr),
				_responsable(nullptr)
		{}
		bool isFinished() const
		{
			return _finished;
		}
		void setResponsable(Professor* p_responsable)
		{
			_responsable = p_responsable;
		}
		void setStudent(Student* p_student)
		{
			_student = p_student;
		}
		void finish(bool p_finished)
		{
			_finished = p_finished;
		}
		bool validate();
		void execute();
};

class NeedMoreClassRoomForm : public Form
{
	private:
		Course* _course;
	public:
		NeedMoreClassRoomForm()
			:	Form(FormType::NeedMoreClassRoom),
				_course(nullptr)
		{}
		Course* course() const
		{
			return _course;
		}
		void creation(Course* p_course)
		{
			_course = p_course;
		}
		bool validate();
		void execute();
};

class NeedCourseCreationForm : public Form
{
	private:
		std::string		_subject;
		Professor*		_professor;
	public:
		NeedCourseCreationForm()
			:	Form(FormType::NeedCourseCreation),
				_professor(nullptr)
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
		bool validate();
		void execute();
};

class SubscriptionToCourseForm : public Form
{
	private:
		Course*		_course;
		Student* 	_student;
	public:
		SubscriptionToCourseForm()
			:	Form(FormType::SubscriptionToCourse),
				_course(nullptr),
				_student(nullptr)
		{}
		void subscript(Course* p_course)
		{
			_course = p_course;
		}
		void from(Student* p_student)
		{
			_student = p_student;
		}
		bool validate();
		void execute();
};

#endif