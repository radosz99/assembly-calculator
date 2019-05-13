#ifndef CLICKABLEQLINEEDIT
#define CLICKABLEQLINEEDIT


#include <QLineEdit>
#include <QWidget>
#include <Qt>

class ClickableQLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit ClickableQLineEdit(QWidget * parent = Q_NULLPTR);
    ~ClickableQLineEdit();
    void setActive(bool active);
    bool isActive();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent * event);

private:
    bool active;
};

#endif // CLICKABLEQLINEEDIT

