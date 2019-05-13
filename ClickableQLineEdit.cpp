#include "ClickableQLineEdit.hpp"

ClickableQLineEdit::ClickableQLineEdit(QWidget * parent) : QLineEdit(parent)
{

}

ClickableQLineEdit::~ClickableQLineEdit() {}

void ClickableQLineEdit::mousePressEvent(QMouseEvent * event)
{
    emit clicked();
}

void ClickableQLineEdit::setActive(bool active)
{
    this->active = active;

    if (active)
        this->setStyleSheet("QLineEdit { color: #288bda; }");
    else
        this->setStyleSheet("QLineEdit { color: #989898; }");
}

bool ClickableQLineEdit::isActive()
{
    return this->active;
}
