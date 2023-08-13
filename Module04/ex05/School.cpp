#include "RequestToHead.hpp"
#include "School.hpp"


std::string ListManager::generateRandomID()
{
    uuid_t id;
    uuid_generate_random(id);
    char uuidStr[37];
    uuid_unparse(id, uuidStr);
    return uuidStr;
}

ListManager::ListManager()
{
    _head = std::make_shared<Headmaster>("Director");
    _secretary = std::make_shared<Secretary>("Secret");
    auto addRoom = [&](auto room)
    {
        Operation<RoomList>::add(room);
    };
    auto addStaff = [&](auto staff)
    {
        Operation<StaffList>::add(staff);
    };
    addStaff(_secretary);
    addStaff(_head);
    addRoom(std::make_shared<StaffRestRoom>());
    addRoom(std::make_shared<Courtyard>());
    auto headOffice = std::make_shared<HeadmasterOffice>();
    addRoom(headOffice);
    _head->enterRoom(std::dynamic_pointer_cast<Room> (headOffice).get());
    auto secretaryOffice = std::make_shared<SecretarialOffice>();
    addRoom(secretaryOffice);
    _secretary->enterRoom(std::dynamic_pointer_cast<Room> (secretaryOffice).get());
}

Course_ptr ListManager::getCourse(std::string p_name) const
{
    return Lambda<CourseList>::getFirst(
    [&](Course_ptr course) -> bool
    {
        return course->getName() == p_name;
    });
}

void School::runDayRoutine()
{

    for (int i = 0; i < 4; ++i)
    {
        auto a1 = std::async([&]()
        {
            launchClasses();
        });
        auto a2 = std::async([&]()
        {
            requestRingBell();
        });
    }
}



School::School() 
    :   _manager(NotifyManager::getNotifyManager())
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
        _manager.addNotify(NotifyType::AssignNotify);
        _manager.addNotify(NotifyType::SubscribeNotify);
        _manager.addNotify(NotifyType::RoomEnterNotify);
        _manager.addNotify(NotifyType::RoomExitNotify);
        _manager.addNotify(NotifyType::NoCourseNotify);
        _manager.addNotify(NotifyType::NoClassNotify);
        _manager.addNotify(NotifyType::GraduateNotify);
        _manager.addNotify(NotifyType::JoinNotify);
        _manager.addNotify(NotifyType::UnsubscribeNotify);
    _bellSystem = std::make_shared<BellSystem>();
    _listManager = std::make_unique<ListManager>();
    _listManager->getHeadmaster()->setBellSystem(_bellSystem.get());
    registerBellSystem<ProfessorList>();
    registerBellSystem<StudentList>();
}

void School::graduationCeremony()
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    /*
     * avoid dublicate code used Lambda wrapper instead
    */
    Lambda<CourseList>::apply(
    [&](Course_ptr course) -> bool
    {
        course->apply([&](Student* student) -> bool
        {
            if (student)
            {
                if (student->numberOfClasses() >= course->numberClassToGraduate())
                {
                    std::cout << "Need student to graduate" << std::endl;
                    auto *professor = course->getResponsable();
                    if (professor)
                    {
                        professor->sendRequest(FormType::CourseFinished);
                        professor->recieveRequest(student);
                    }
                }
            }
            return true;
        });
        return true;
    });
}