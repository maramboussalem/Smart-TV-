#ifndef EMPLOYEMENT_H
#define EMPLOYEMENT_H

#include <QDialog>

namespace Ui {
class employement;
}

class employement : public QDialog
{
    Q_OBJECT

public:
    explicit employement(QWidget *parent = nullptr);
    ~employement();

private:
    Ui::employement *ui;
};

#endif // EMPLOYEMENT_H
