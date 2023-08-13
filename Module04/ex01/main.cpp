#include "Course.hpp"
#include "Room.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "IObjectList.hpp"
#include "Person.hpp"
#include "Staff.hpp"
#include <thread>
#include <future>

 
int main(int argc, char const *argv[]) try
{
    auto& students = StudentList::getList();
    auto& rooms = RoomList::getList();
    auto& staffs = StaffList::getList();
    auto& courses = CourseList::getList();
    auto getItem = [&](auto& list, std::string check)
    {
        return  list.get(
                [&](auto& e) ->bool
                {
                    return e->getName() == check;
                });
    };
    std::thread t1([&](){
        students.add(std::make_shared<Student>("hello"));
        students.add(std::make_shared<Student>("dsad"));
        std::cout << "added t1\n";
    });
    std::thread t2([&](){
        students.add(std::make_shared<Student>("fdsgfd"));
        students.add(std::make_shared<Student>("vcxvx"));
        students.add(std::make_shared<Student>("dasds"));
        students.add(std::make_shared<Student>("world"));
        std::cout << "added t2\n";
    });
    auto t3 = std::packaged_task<void(void)> ([&](){
        auto& l = StudentList::getList();
        std::cout << "T1: ";
        // auto student = getItem(students, "hello");
        // std::cout << "T1 st: " << student->getName() << std::endl;
    });
    std::thread t4([&](){
        auto& l = StudentList::getList();
        // auto student = getItem(students, "world");
        std::cout << "T2: ";
        // std::cout << "T2 st: " << student->getName() << std::endl;
    });
    // t3.wait();
    t1.join();
    t2.join();
    std::thread task_td(std::move(t3));
    task_td.join();
    // t3.join();
    t4.join();
    rooms.add(std::make_shared<Classroom>());
    rooms.add(std::make_shared<StaffRestRoom>());
    rooms.add(std::make_shared<Classroom>());
    staffs.add(std::make_shared<Professor>("hhhh"));
    courses.add(std::make_shared<Course>("hhhhhh"));
    /*
     * avoid code duplication. Used generic labmdas instead
    */
   
    auto course = getItem(courses, "hhhhhh");
    auto staff = getItem(staffs, "hhhh");
    auto student = getItem(students, "hello");

    course->assign( dynamic_cast<Professor*>(staff.get()));
    course->subscribe(student.get());
    staff = getItem(staffs, "hhhh");
    std::cout << "Name: " << staff->getName() << std::endl;
    return 0;
}
catch(...) {}
