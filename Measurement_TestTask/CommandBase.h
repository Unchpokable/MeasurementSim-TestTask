#pragma once
#include <QString>
#include "Callbacks.h"
#include "ContextObject.h"

class CommandBase
{
public:
    CommandBase()
    {
        m_callback_list = new std::vector<SingleArgumentCallback<QString>>;
    }
    virtual ~CommandBase()
    {
        delete m_callback_list;
    }

    virtual void Execute(const std::vector<double>& args);
    virtual void Execute(const std::vector<ContextObject*>& args);
    virtual QString ToString();

    void AddExecuteCallback(const SingleArgumentCallback<QString>&);
    void RemoveExecuteCallback(const SingleArgumentCallback<QString>&);
    void ClearCallbackList();

protected:
    void Emit(const QString& arg);
    std::vector<SingleArgumentCallback<QString>>* m_callback_list;
};

