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

int main(int argc, char const *argv[]) try
{
    auto& students = StudentList::getList();
    auto& rooms = RoomList::getList();
    auto& staffs = StaffList::getList();
    auto& courses = CourseList::getList();
    /*
     * avoid code duplication. Used generic labmdas instead
    */
    auto getItem = [&](auto& list, std::string check)
    {
        return  list.get(
                [&](auto& e) -> bool
                {
                    return e->getName() == check;
                });
    };
    auto getRoom = [&](auto& list, int id)
    {
        return  list.get(
                [&](auto& e) -> bool
                {
                    return e->getID() == id;
                });
    };
        students.add(std::make_shared<Student>("Ishxo"));
        students.add(std::make_shared<Student>("Davo"));
        std::cout << "added t1\n";
        students.add(std::make_shared<Student>("Gev"));
        students.add(std::make_shared<Student>("Vache"));
        students.add(std::make_shared<Student>("Poxos"));
        students.add(std::make_shared<Student>("Petros"));
        students.add(std::make_shared<Student>("Grno"));
        students.add(std::make_shared<Student>("Haykaz"));
        students.add(std::make_shared<Student>("Vrdo"));
        students.add(std::make_shared<Student>("Gexam"));
        std::cout << "added t2\n";
 
    rooms.add(std::make_shared<Classroom>());
    rooms.add(std::make_shared<StaffRestRoom>());
    rooms.add(std::make_shared<Classroom>());
    staffs.add(std::make_shared<Headmaster>("Stroustroup"));
    staffs.add(std::make_shared<Secretary>("Meyers"));
    // auto assignNotify = std::make_shared<AssignNotify>();
    // auto subscribeNotify = std::make_shared<SubscribeNotify>();
    // auto enterNotify = std::make_shared<RoomEnterNotify>();
    // auto exitNotify = std::make_shared<RoomExitNotify>();
    // auto newCourse = std::make_shared<Course>("C++");
    // auto newCourse1 = std::make_shared<Course>("C++11");
    auto newProf = std::make_shared<Professor>("Einstein");
    auto pr = std::make_shared<Professor>("Valod");
    auto mm = std::make_shared<Professor>("Poxos");
    // newCourse->addNotify(assignNotify);
    // newCourse->addNotify(subscribeNotify);
    // newCourse1->addNotify(assignNotify);
    // newCourse1->addNotify(subscribeNotify);
    // newProf->addNotify(assignNotify);
    staffs.add(newProf);
    staffs.add(pr);
    staffs.add(mm);
    // courses.add(newCourse);
    
   
    auto head = std::dynamic_pointer_cast<Headmaster>( getItem(staffs, "Stroustroup") );
    auto course = getItem(courses, "C++");
    auto staff = std::dynamic_pointer_cast<Professor>(getItem(staffs, "Einstein"));
    auto student = getItem(students, "Gev");
    auto room = getRoom(rooms, 0);
    auto room1 = getRoom(rooms, 1);
    auto& manager = NotifyManager::getNotifyManager();
    manager.addNotify(std::make_shared<AssignNotify>());
    manager.addNotify(std::make_shared<SubscribeNotify>());
    manager.addNotify(std::make_shared<RoomEnterNotify>());
    manager.addNotify(std::make_shared<RoomExitNotify>());
    manager.addNotify(std::make_shared<NoCourseNotify>());
    manager.addNotify(std::make_shared<NoClassNotify>());
    manager.addNotify(std::make_shared<GraduateNotify>());
    manager.addNotify(std::make_shared<JoinCourseNotify>());
    manager.addNotify(std::make_shared<UnsubscribeNotify>());
    // student->addNotify(std::make_shared<AssignNotify>());
    head->startCourses();
    // room->addNotify(enterNotify);
    // room->addNotify(exitNotify);
    // student->addNotify(enterNotify);
    // student->addNotify(exitNotify);
    // auto secretary = std::dynamic_pointer_cast<Secretary>( getItem(staffs, "Meyers") );

    // staff->assignCourse(course);
    // newCourse1->assign(staff);
    // room1->addNotify(enterNotify);
    // room1->addNotify(exitNotify);
    // staff->addNotify(enterNotify);
    // staff->addNotify(exitNotify);
    // student->addNotify(subscribeNotify);
    // course->addNotify(subscribeNotify);
    // student->subcribe(course);
    // std::cout << room1->getID();
    // room1->enter(staff);
    // room1->enter(student);
    // room1->enter(staff);
    
    // student->enterRoom(room);
    // student->enterRoom(room1);
    // student->enterRoom(room);
    // student->exitRoom();
    // student->exitRoom();
    // room->addNotify(enterNotify);
    // room->addNotify(exitNotify);
    // student->addNotify(enterNotify);
    // student->addNotify(exitNotify);
    // student->enterRoom(room);
    // student->enterRoom(room);
    // course->subsribe(student);
    // course->assign(staff);
    // course->assign(staff);
    // course->subscribe(student);
    // room->enter(student);
    // student->exitRoom(room);
    // room->exit(student);
    // room->exit(student);
    // student->exitRoom(room);
    // auto newCourseForm = secretary->createForm(FormType::NeedCourseCreation);
    // std::dynamic_pointer_cast<NeedCourseCreationForm>(newCourseForm)->assign(staff);
    // head->sign(newCourseForm);
    // newCourseForm->execute();
    // staff = std::dynamic_pointer_cast<Professor>(getItem(staffs, "Einstein"));
    // std::cout << "Name: " << staff->getName() << std::endl;
    return 0;
}
catch(...) {}
