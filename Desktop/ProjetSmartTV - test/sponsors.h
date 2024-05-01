#ifndef SPONSORS_H
#define SPONSORS_H

#include <QDialog>

namespace Ui {
class Sponsors;
}

class Sponsors : public QDialog
{
    Q_OBJECT

public:
    explicit Sponsors(QWidget *parent = nullptr);
    ~Sponsors();

private:
    Ui::Sponsors *ui;
};

#endif // SPONSORS_H
