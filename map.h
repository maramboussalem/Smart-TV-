#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include <QVariant>
#include <QtCore>
#include <QtGui>
#include <QtQuick>
namespace Ui {
class Map;
}

class Map : public QMainWindow
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();
    void setCenterPosition(double latitude, double longitude);
    void setLocationMarking(double latitude, double longitude);


private:
    Ui::Map *ui;


};

#endif // MAP_H
