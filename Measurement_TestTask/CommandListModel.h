#pragma once

#include <QAbstractListModel>

#include "BoundCommand.h"

class CommandListModel  : public QAbstractListModel
{
    Q_OBJECT

public:
    CommandListModel(QObject *parent);
    ~CommandListModel() override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    void addObject(const BoundCommand* object);

private:
    QVector<BoundCommand*> m_commands;
};
