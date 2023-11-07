#include "CommentCommand.h"

#include <QMessageBox>

void CommentCommand::Execute(const std::vector<double>& args)
{
    return;
}

QString CommentCommand::ToString()
{
    QString out {};
    out.append("$COMMENT(" + m_message + ")");
    return out;
}

QString CommentCommand::ToPrettyString()
{
    return "\nComment: " + m_message + "\n";
}
