#ifndef __MANAGERS_HPP__
#define __MANAGERS_HPP__

#include "Tool.hpp"

class ToolManager
{
    private:
        std::map<std::size_t, Tool*> tools;
        ToolManager();
    public:
        static ToolManager* getToolManager();
        Tool* getTool(std::size_t tool_id);
        std::set<Tool*> getToolsByWorkerID(std::size_t worker_id);
        void registerTool(Tool* tool);
        void unregisterTool(std::size_t tool_id);
        ~ToolManager();
};


#endif