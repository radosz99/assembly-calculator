#ifndef CLICKABLEQLABEL
#define CLICKABLEQLABEL

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableQLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableQLabel(QWidget * parent = Q_NULLPTR);
    ~ClickableQLabel();
    void setActive(bool active);
    bool isActive();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent * event);

private:
    bool active;
};

#endif // CLICKABLEQLABEL

