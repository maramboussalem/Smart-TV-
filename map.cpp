#include "map.h"
#include "ui_map.h"

Map::Map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/QmlMap.qml")));
    ui->quickWidget->show();

}
void Map::setCenterPosition(double latitude, double longitude)
{
    if (ui->quickWidget->rootObject())
    {
        QVariant returnedValue;
        QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "setCenterPosition",
                                  Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, latitude),
                                  Q_ARG(QVariant, longitude));
    }
}

void Map::setLocationMarking(double latitude, double longitude)
{
    if (ui->quickWidget->rootObject())
    {
        QVariant returnedValue;
        QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "setLocationMarking",
                                  Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, latitude),
                                  Q_ARG(QVariant, longitude));
    }
}

Map::~Map()
{
    delete ui;
}
