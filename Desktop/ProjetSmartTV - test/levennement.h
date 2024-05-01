#ifndef LEVENNEMENT_H
#define LEVENNEMENT_H

#include <QDialog>

namespace Ui {
class levennement;
}

class levennement : public QDialog
{
    Q_OBJECT

public:
    explicit levennement(QWidget *parent = nullptr);
    ~levennement();

private slots:
    void on_Connecter_clicked();

    void on_Retour_clicked();

private:
    Ui::levennement *ui;
};

#endif // LEVENNEMENT_H
