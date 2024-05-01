#ifndef LOGINPUB_H
#define LOGINPUB_H

#include <QMainWindow>

namespace Ui {
class loginpub;
}

class loginpub : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginpub(QWidget *parent = nullptr);
    ~loginpub();

private:
    Ui::loginpub *ui;
};

#endif // LOGINPUB_H
