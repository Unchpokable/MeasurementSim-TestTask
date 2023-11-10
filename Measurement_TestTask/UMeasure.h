#pragma once

#include <QtWidgets/QMainWindow>

#include "AddCommandBase.h"
#include "CommandInterpreter.h"
#include "CommandListModel.h"
#include "ui_UMeasure.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UMeasureClass; };
QT_END_NAMESPACE

class UMeasure : public QMainWindow
{
    Q_OBJECT

public:
    UMeasure(QWidget *parent = nullptr);
    ~UMeasure() override;

private:
    void ShowAddCommandForm(ContextObjectType cmd_type);
    void ExecuteCommandSequence() noexcept;

    //Если кому то интересно наглядное определение слова "Кодохульство" - то вот.

    template<typename TAddCommand,
        typename = std::enable_if_t<std::is_base_of_v<AddCommandBase, TAddCommand> &&
                                    std::is_base_of_v<QDialog, TAddCommand>>>
    void ShowFormAndAddCreatedCommand()
    {
        const auto form = new TAddCommand(this, const_cast<RuntimeContext*>(m_interpreter->GetContext()));
        int ret = form->exec();

        if (form)
        {
            const auto new_command = const_cast<BoundCommand*>(form->GetConstructedObject());

            if(new_command == nullptr)
                return;
            m_interpreter->AddCommand(new_command);
            new_command->Execute();
            m_commands_list->addObject(new_command);
        }
    }

    Ui::UMeasureClass *ui;
    CommandInterpreter* m_interpreter;
    CommandListModel* m_commands_list;

signals:
    void OutputReceived(const QString& what);

private slots:
    void OnOutputReceived(const QString& what) const noexcept;
};