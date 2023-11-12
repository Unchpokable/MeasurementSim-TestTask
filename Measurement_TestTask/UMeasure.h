#pragma once

#include <QtWidgets/QMainWindow>

#include "AddCommandBase.h"
#include "CommandInterpreter.h"
#include "CommandListModel.h"
#include "ui_UMeasure.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UMeasureClass; };
QT_END_NAMESPACE

enum InsertionPosition {
    ip_before,
    ip_after,
    ip_replace
};

class UMeasure : public QMainWindow
{
    Q_OBJECT

public:
    UMeasure(QWidget *parent = nullptr);
    ~UMeasure() override;

private:
    void AddProgramViewContextMenu() noexcept;

    void ShowAddCommandForm(ContextObjectType cmd_type);
    void ExecuteCommandSequence() noexcept;
    void AddCommand(BoundCommand*);
    void ReplaceCommand(BoundCommand*, std::size_t);
    void RemoveCommand(std::size_t);
    void AddInsertActionToMenu(QMenu* menu, const QString& title, ContextObjectType type, InsertionPosition pos);

    void InsertNewCommandBefore(ContextObjectType type);
    void InsertNewCommandAfter(ContextObjectType type);

    BoundCommand* GetCommandByType(ContextObjectType type);

    //Если кому то интересно наглядное определение слова "Кодохульство" - то вот.

    template<typename TAddCommand,
        typename = std::enable_if_t<std::is_base_of_v<AddCommandBase, TAddCommand> &&
                                    std::is_base_of_v<QDialog, TAddCommand>>>
    BoundCommand* ShowFormCreateCommand()
    {
        const auto form = new TAddCommand(this, const_cast<RuntimeContext*>(m_interpreter->GetContext()));
        int ret = form->exec();

        if (form)
        {
            const auto new_command = const_cast<BoundCommand*>(form->GetConstructedObject());

            if(new_command == nullptr)
                return nullptr;
            return new_command;
        }

        return nullptr;
    }

    Ui::UMeasureClass *ui;
    CommandInterpreter* m_interpreter;
    CommandListModel* m_commands_list;
    QMenu* contextMenu;

signals:
    void OutputReceived(const QString& what);

private slots:
    void OnOutputReceived(const QString& what) const noexcept;

    void OnDeleteAction();
    void OnReplaceAction(ContextObjectType type);

    inline void OnCustomContextMenuRequested(const QPoint& pos) const noexcept
    {
        contextMenu->exec(ui->programView->mapToGlobal(pos));
    }
};