#ifndef LPUBLICITE_H
#define LPUBLICITE_H

#include <QDialog>

namespace Ui {
class lpublicite;
}

class lpublicite : public QDialog
{
    Q_OBJECT

public:
    explicit lpublicite(QWidget *parent = nullptr);
    ~lpublicite();



private slots:
    void on_Connecter_clicked();
    
    void on_Retour_clicked();
    
private:
    Ui::lpublicite *ui;
};

#endif // LPUBLICITE_H
