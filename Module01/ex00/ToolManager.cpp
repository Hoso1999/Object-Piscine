#include "ToolManager.hpp"
#include <iostream>
#include <memory>

ToolManager::~ToolManager()
{
    for(std::map<std::size_t, Tool*>::const_iterator it = tools.begin(); it != tools.end(); ++it)
    {
        if (it->second)
        {
            std::cout << "Deleting Tool " << (it->second->getType() == ToolType::Hammer ? "Hammer" : "Shovel") << std::endl;
            delete it->second;
        }
    }
}

ToolManager::ToolManager()
{
    tools[ToolType::Hammer] = NULL;
    tools[ToolType::Shovel] = NULL;
}

ToolManager* ToolManager::getToolManager()
{
    static std::auto_ptr<ToolManager> toolManager(new ToolManager);
    return toolManager.get();
}

void ToolManager::registerTool(Tool* tool)
{
    if (!tools[tool->getType()])
        tools[tool->getType()] = tool;
    std::cout << "Register Tool " << (tool->getType() == ToolType::Hammer ? "Hammer" : "Shovel") << std::endl;
}

void ToolManager::unregisterTool(std::size_t tool_id)
{
    if (tools[tool_id])
    {
        std::cout << "Unregister Tool " << (tool_id == ToolType::Hammer ? "Hammer" : "Shovel") << std::endl;
        delete tools[tool_id];
        tools[tool_id] = NULL;

    }
}

Tool* ToolManager::getTool(std::size_t tool_id)
{
    return tools[tool_id];
}

std::set<Tool*> ToolManager::getToolsByWorkerID(std::size_t worker_id)
{
    std::set<Tool*> worker_tools;
    for(std::map<std::size_t, Tool*>::iterator it = tools.begin(); it != tools.end(); ++it)
    {
        if (it->second && it->second->getWorker(worker_id) != (std::size_t)-1)
            worker_tools.insert(it->second);
    }
    return worker_tools;
}
