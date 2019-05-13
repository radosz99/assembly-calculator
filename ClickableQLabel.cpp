#include "ClickableQLabel.hpp"

ClickableQLabel::ClickableQLabel(QWidget * parent) : QLabel(parent)
{

}

ClickableQLabel::~ClickableQLabel() {}

void ClickableQLabel::mousePressEvent(QMouseEvent * event)
{
    emit clicked();
}

void ClickableQLabel::setActive(bool active)
{
    this->active = active;

    if (active)
        this->setStyleSheet("QLabel { margin-left: 5px; color: #288bda; }");
    else
        this->setStyleSheet("QLabel { margin-left: 5px; color: black; }");
}

bool ClickableQLabel::isActive()
{
    return this->active;
}
