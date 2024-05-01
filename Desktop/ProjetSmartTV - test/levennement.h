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

private:
    Ui::levennement *ui;
};

#endif // LEVENNEMENT_H
