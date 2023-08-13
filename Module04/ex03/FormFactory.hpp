#ifndef __FORMFACTORY_HPP__
#define __FORMFACTORY_HPP__

#include <memory>
class Form;
enum class FormType;

using Form_ptr = std::shared_ptr<Form>;

class FormFactory
{
    public:
        /*
         * Forms dont have circular dependency but used many places.
        */
        static Form_ptr createForm(FormType type);
};




#endif