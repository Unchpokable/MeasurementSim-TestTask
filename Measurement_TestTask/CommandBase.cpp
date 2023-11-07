#include "CommandBase.h"

#include <exception>
#include "VoodoMagic.h"
#include "ContextObject.h"

void CommandBase::Execute(const std::vector<double>& args)
{
    throw std::exception("method not implemented");
}

void CommandBase::Execute(const std::vector<ContextObject*>& args)
{
    throw std::exception("Method not implemented");
}

QString CommandBase::ToString()
{
    return { "$EMPTY_COMMAND" };
}

QString CommandBase::ToPrettyString()
{
    return "Command not assigned to any 3D object";
}


void CommandBase::AddExecuteCallback(const SingleArgumentCallback<CommandBase*>& callback)
{
    m_callback_list->push_back(callback);
}

void CommandBase::RemoveExecuteCallback(const SingleArgumentCallback<CommandBase*>& callback)
{
    auto pos = std::find_if(m_callback_list->begin(), m_callback_list->end(), 
        [callback](const SingleArgumentCallback<CommandBase*>& it)
        {
            return FunctionsEquals(callback, it);
        });

    if(pos != m_callback_list->end())
        m_callback_list->erase(pos);
}

void CommandBase::ClearCallbackList()
{
    m_callback_list->clear();
}

void CommandBase::Emit(const CommandBase* who) const noexcept
{
    for(auto& func : *m_callback_list)
        if(func != nullptr)
        {
            const auto arg = const_cast<CommandBase*>(who);
            func(arg);
        }
}
