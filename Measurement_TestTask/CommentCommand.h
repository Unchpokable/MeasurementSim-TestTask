#pragma once
#include "CommandBase.h"
class CommentCommand :
    public CommandBase, public ContextObject
{
public:
    CommentCommand(const QString& object_name, const QString& message, bool show_msgbox = false)
        : ContextObject(object_name, ci_comment), m_message(message)
        , m_is_show_msg_box(show_msgbox)
    {
    }

    void Execute(const std::vector<double>& args) override;

    QString ToString() override;
    QString ToPrettyString() override;

private:
    QString m_message;
    bool m_is_show_msg_box;
};

