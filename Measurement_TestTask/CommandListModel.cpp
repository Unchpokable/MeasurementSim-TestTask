#include "CommandListModel.h"

CommandListModel::CommandListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

CommandListModel::~CommandListModel() = default;

int CommandListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_commands.size();
}

QVariant CommandListModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || index.row() >= m_commands.size() || index.row() < 0)
        return {};

    if (role == Qt::DisplayRole)
    {
        return QVariant(m_commands.at(index.row())->ToString());
    }

    return {};
}

void CommandListModel::addObject(const BoundCommand* object)
{
    beginInsertRows(QModelIndex(), m_commands.size(), m_commands.size());
    m_commands.push_back(const_cast<BoundCommand*>(object));
    endInsertRows();
}

void CommandListModel::replaceObject(qsizetype index, BoundCommand* object)
{
    if(index < 0 || index >= m_commands.size())
        return;
    beginInsertRows(QModelIndex(), 0, m_commands.size());
    m_commands.replace(index, object);
    endInsertRows();
}

void CommandListModel::removeObject(qsizetype index)
{
    if(index < 0 || index >= m_commands.size())
        return;
    beginRemoveRows(QModelIndex(), 0, m_commands.size()-1);
    m_commands.remove(index);
    endRemoveRows();
}

void CommandListModel::insertObject(qsizetype index, BoundCommand* object)
{
    if(index < 0 || index >= m_commands.size())
        return;

    beginInsertRows(QModelIndex(), 0, m_commands.size());
    m_commands.insert(index, object);
    endInsertRows();
}
