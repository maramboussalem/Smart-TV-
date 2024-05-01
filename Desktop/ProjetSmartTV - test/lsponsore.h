#ifndef LSPONSORE_H
#define LSPONSORE_H

#include <QDialog>

namespace Ui {
class lsponsore;
}

class lsponsore : public QDialog
{
    Q_OBJECT

public:
    explicit lsponsore(QWidget *parent = nullptr);
    ~lsponsore();

private slots:
    void on_Connecter_2_clicked();
    
    void on_Connecter_clicked();

    void on_Retour_clicked();

private:
    Ui::lsponsore *ui;
};

#endif // LSPONSORE_H
