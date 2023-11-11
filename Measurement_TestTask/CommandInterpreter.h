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
    command_vec_iterator& GetCurrent() const;

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
        delete m_runtime_context;
        for(auto it : *m_commands)
            delete it;
        delete m_commands;
    }

    bool AddCommand(CommandBase*, const std::vector<double>& args);
    bool AddCommand(CommandBase*, const std::vector<ContextObject*>& args);
    void AddCommand(BoundCommand*);
    bool ReplaceCommand(BoundCommand*, std::size_t);
    bool RemoveCommand(std::size_t);
    bool InsertCommand(std::size_t, BoundCommand*);
    std::shared_ptr<CommandsIterWrapper> GetCommandsIterator() const noexcept;

    void FreeIterator(const std::shared_ptr<CommandsIterWrapper>& iterator);
    void FreeIterator(CommandsIterWrapper* iterator);
    void RunProgram() const;
    const std::thread* RunProgramAsync(const SingleArgumentCallback<QString>&, 
                                       const SingleArgumentCallback<QString>&) const;
    const RuntimeContext* GetContext() const noexcept;

    std::size_t GetCommandsCount() const noexcept;
private:

    bool AddToContext(CommandBase* who);
    bool BindDependencies(ContextObject* root, const std::vector<ContextObject*>& deps);
    void InvalidateSharedIterators() const noexcept;

    RuntimeContext* m_runtime_context;
    std::vector<BoundCommand*>* m_commands;
    std::mutex m_mutex;
    std::vector<std::shared_ptr<CommandsIterWrapper>>* m_shared_iterators;
};
