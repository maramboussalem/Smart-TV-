#ifndef LEMPLOYES_H
#define LEMPLOYES_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMap>
namespace Ui {
class lemployes;
}

class lemployes : public QDialog
{
    Q_OBJECT

public:
    explicit lemployes(QWidget *parent = nullptr);
    ~lemployes();

private slots:
    void on_Connecter_clicked();

    void on_Retour_clicked();

private:
    Ui::lemployes *ui;
};

#endif // LEMPLOYES_H
