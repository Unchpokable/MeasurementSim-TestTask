#include "DefaultCallbacks.h"

void OnRuntimeContextCallback(RuntimeContext* sender, QString message)
{
    QMessageBox msgBox {};
    msgBox.setText("Invalid context operation");

    QString out {};
    out.append("Runtime error: ");
    out.append("Current runtime context (");
    out.append((std::stringstream() << sender).str());
    out.append("could not execute operation cause ");
    out.append(message);

    msgBox.setInformativeText(out);

    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    msgBox.show();
}
