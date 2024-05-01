#ifndef LOGINEVENT_H
#define LOGINEVENT_H

#include <QMainWindow>

namespace Ui {
class loginevent;
}

class loginevent : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginevent(QWidget *parent = nullptr);
    ~loginevent();

private:
    Ui::loginevent *ui;
};

#endif // LOGINEVENT_H
