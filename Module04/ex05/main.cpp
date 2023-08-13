#include "Course.hpp"
#include "Room.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "IObjectList.hpp"
#include "Person.hpp"
#include "Professor.hpp"
#include <thread>
#include <future>
#include <sys/wait.h>
#include "INotify.hpp"
#include "RequestToHead.hpp"
#include "Student.hpp"
#include "Headmaster.hpp"
#include "observer.hpp"
#include "School.hpp"

int main(int argc, char const *argv[]) try
{

    School sc;
    for (int i = 0; i < 20; ++i)
    {
        sc.recruteProfessor();
        sc.recruteStudent();
    }
    sc.runDayRoutine();
    sc.graduationCeremony();
    return 0;
}
catch(...) {}
