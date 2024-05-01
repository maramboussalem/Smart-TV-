#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButtonEmployee_clicked();

    void on_pushButtonEmission_clicked();

    void on_pushButtonEvenement_clicked();

    void on_pushButtonPublicite_clicked();

    void on_pushButtonSponsors_clicked();

    void on_pushButtonEquipement_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
