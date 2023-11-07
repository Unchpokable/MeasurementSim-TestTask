#pragma once

#include "Callbacks.h"
#include "ContextObject.h"

class CommandBase
{
public:
    CommandBase()
    {
        m_callback_list = new std::vector<SingleArgumentCallback<CommandBase*>>;
    }
    virtual ~CommandBase()
    {
        delete m_callback_list;
    }

    virtual void Execute(const std::vector<double>& args);
    virtual void Execute(const std::vector<ContextObject*>& args);
    virtual QString ToString();
    virtual QString ToPrettyString();

    void AddExecuteCallback(const SingleArgumentCallback<CommandBase*>&);
    void RemoveExecuteCallback(const SingleArgumentCallback<CommandBase*>&);
    void ClearCallbackList();

protected:
    void Emit(const CommandBase* who = nullptr) const noexcept;
    std::vector<SingleArgumentCallback<CommandBase*>>* m_callback_list;
};

