#pragma once

#include "RuntimeContext.h"
#include <thread>
#include <mutex>

#include "BoundCommand.h"
#include "Callbacks.h"
#include "CommandBase.h"

using command_vec_iterator = std::vector<BoundCommand*>::iterator;

class CommandsIterWrapper
{
    friend class CommandInterpreter;

public:
    const command_vec_iterator& GetBegin() const;
    const command_vec_iterator& GetEnd() const;
    const command_vec_iterator& GetCurrent() const;

    void Free();
    bool IsValid() const noexcept;

private:
    void Invalidate();

    command_vec_iterator m_commandsBegin;
    command_vec_iterator m_commandsEnd;
    command_vec_iterator m_commandsCurrent;

    bool m_iter_wrapper_valid = true;
    const CommandInterpreter* m_owner;
};

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
    void AddCommand(BoundCommand*);

    std::shared_ptr<CommandsIterWrapper> GetCommandsIterator() const noexcept;

    void FreeIterator(const std::shared_ptr<CommandsIterWrapper>& iterator);
    void FreeIterator(CommandsIterWrapper* iterator);
    void RunProgram() const;
    const std::thread* RunProgramAsync(SingleArgumentCallback<QString>) const;
    const RuntimeContext* GetContext() const noexcept;

private:

    void AddToContext(CommandBase* who);
    void InvalidateSharedIterators();

    RuntimeContext* m_exec_context;
    std::vector<BoundCommand*>* m_commands;
    std::mutex m_mutex;
    std::vector<std::shared_ptr<CommandsIterWrapper>>* m_shared_iterators;
};
