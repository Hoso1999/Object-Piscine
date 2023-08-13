#ifndef __FORM_HPP__
#define __FORM_HPP__


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
	Form(FormType p_formType) {}

	virtual void execute() = 0;
};

class CourseFinishedForm : public Form
{
private:
public:
	void execute();
};

class NeedMoreClassRoomForm : public Form
{
private:
public:
	void execute();
};

class NeedCourseCreationForm : public Form
{
private:
public:
	void execute();
};

class SubscriptionToCourseForm : public Form
{
private:
public:
	void execute();
};

#endif