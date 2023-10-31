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

void CommandBase::AddExecuteCallback(const SingleArgumentCallback<QString>& callback)
{
    m_callback_list->push_back(callback);
}

void CommandBase::RemoveExecuteCallback(const SingleArgumentCallback<QString>& callback)
{
    auto pos = std::find_if(m_callback_list->begin(), m_callback_list->end(), 
        [callback](const SingleArgumentCallback<QString>& it)
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

void CommandBase::Emit(const QString& arg)
{
    for(auto func : *m_callback_list)
        if(func != nullptr)
            func(arg);
}


