#ifndef EMISSION_H
#define EMISSION_H

#include <QDialog>

namespace Ui {
class Emission;
}

class Emission : public QDialog
{
    Q_OBJECT

public:
    explicit Emission(QWidget *parent = nullptr);
    ~Emission();

private:
    Ui::Emission *ui;
};

#endif // EMISSION_H
