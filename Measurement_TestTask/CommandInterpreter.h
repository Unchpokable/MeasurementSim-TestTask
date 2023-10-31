#pragma once

#include "RuntimeContext.h"
#include <thread>
#include <mutex>

#include "Callbacks.h"
#include "CommandBase.h"

class CommandInterpreter
{
public:
    CommandInterpreter() noexcept;

    ~CommandInterpreter()
    {
        delete m_exec_context;
    }

    void AddCommand(CommandBase*);
    void AddCommand(ContextObject*);

    void RunProgram() const;
    const std::thread* RunProgramAsync(SingleArgumentCallback<QString>) const;
    const RuntimeContext* GetContext() const noexcept;

private:
    void RunProgramAsyncInternal(SingleArgumentCallback<QString>);

    RuntimeContext* m_exec_context;
    std::mutex m_mutex;
};
