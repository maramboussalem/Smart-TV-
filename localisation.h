#ifndef LOCALISATION_H
#define LOCALISATION_H

#include <QDialog>
#include <QWidget>
#include <QtQuickWidgets/QQuickWidget>
namespace Ui {
class localisation;
}

class localisation : public QDialog
{
    Q_OBJECT

public:
    explicit localisation(QWidget *parent = nullptr);
    ~localisation();

private:
    Ui::localisation *ui;
};

#endif // LOCALISATION_H
