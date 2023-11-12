#pragma once

#include "ContextObject.h"
#include <QMessageBox>
#include <type_traits>

template<typename T, typename = std::enable_if_t<std::is_pointer_v<T> == false>>
bool AssertType(const ContextObject* source)
{
    return dynamic_cast<T*>(const_cast<ContextObject*>(source)) != nullptr;
}

template<typename T, typename = std::enable_if_t<std::is_pointer_v<T> == false>>
bool AssertTypeWithMessage(const ContextObject* source, QWidget* msgBoxParent = nullptr)
{
    if (!AssertType<T>(source))
    {
        QMessageBox::warning(msgBoxParent, "Command type check error", "Given command can not be casted to awaited type");
        return false;
    }

    return true;
}
