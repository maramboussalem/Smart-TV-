#ifndef GESTIONEMPLOYEE_H
#define GESTIONEMPLOYEE_H

#include <QDialog>

namespace Ui {
class Gestionemployee;
}

class Gestionemployee : public QDialog
{
    Q_OBJECT

public:
    explicit Gestionemployee(QWidget *parent = nullptr);
    ~Gestionemployee();

private slots:
    void on_label_2_linkActivated(const QString &link);

    void on_pushButtonEmployee_I_clicked();

private:
    Ui::Gestionemployee *ui;
};

#endif // GESTIONEMPLOYEE_H
