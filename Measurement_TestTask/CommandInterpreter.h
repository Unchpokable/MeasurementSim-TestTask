#pragma once

#include "RuntimeContext.h"
#include <thread>
#include <mutex>

#include "BindedCommand.h"
#include "Callbacks.h"
#include "CommandBase.h"

class CommandInterpreter
{
public:
    CommandInterpreter() noexcept;

    ~CommandInterpreter()
    {
        delete m_exec_context;
        for(auto it : *m_commands)
            delete it;
        delete m_commands;
    }

    void AddCommand(CommandBase*, const std::vector<double>& args);
    void AddCommand(CommandBase*, const std::vector<ContextObject*>& args);

    void RunProgram() const;
    const std::thread* RunProgramAsync(SingleArgumentCallback<QString>) const;
    const RuntimeContext* GetContext() const noexcept;

private:
    void RunProgramAsyncInternal(SingleArgumentCallback<QString>);

    RuntimeContext* m_exec_context;
    std::vector<BindedCommand*>* m_commands;
    std::mutex m_mutex;
};
