#ifndef PUBLICITE_H
#define PUBLICITE_H
#include "entite_pub.h"
#include <QMainWindow>
#include <QTableView>
#include <QMediaPlayer>
#include <QFileDialog>
#include "videoplayer.h"
#include "arduino.h"

namespace Ui {
class Publicite;
}

class Publicite : public QDialog
{
    Q_OBJECT

public:
    explicit Publicite(QWidget *parent = nullptr);
    ~Publicite();
private slots:

    void on_pushButton_14_clicked();

    void on_pushButton_9_clicked();

    void on_Modifier_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtontri_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_rechid_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_currentChanged(int index);

    void on_pushButton_play_clicked();

    void on_pushButton_addvideo_clicked();

    void on_tableView_publicite_clicked(const QModelIndex &index);

    void on_pushButton_on_clicked();

    void on_pushButton_off_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_clicked();
private:
    Ui::Publicite *ui;
    Entite_pub p;
    QString filePath;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};

#endif // PUBLICITE_H
