#ifndef PUBLICITE_H
#define PUBLICITE_H

#include <QDialog>

namespace Ui {
class Publicite;
}

class Publicite : public QDialog
{
    Q_OBJECT

public:
    explicit Publicite(QWidget *parent = nullptr);
    ~Publicite();

private:
    Ui::Publicite *ui;
};

#endif // PUBLICITE_H
