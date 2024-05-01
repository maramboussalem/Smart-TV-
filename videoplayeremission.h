#ifndef VIDEOPLAYEREMISSION_H
#define VIDEOPLAYEREMISSION_H

#include <QMainWindow>
#include <QtMultimediaWidgets>
#include <QtMultimedia>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QtWidgets>

#include "arduino.h"
namespace Ui {
class VideoPlayerEmission;
}

class VideoPlayerEmission : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayerEmission(QWidget *parent = nullptr);
    ~VideoPlayerEmission();

private slots:
    void update_label();

    void durationChanged(qint64 duration);

    void positionChanged(qint64 duration);

    void on_actionOpen_triggered();

    void on_pushButton_Seek_Backward_clicked();

    void on_pushButton_Play_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Seek_Forward_clicked();

    void on_pushButtonSousTitrage_clicked();

    void on_pushButton_Volume_clicked();

    void on_horizontalSlider_Duration_valueChanged(int value);

    void on_horizontalSlider_Volume_valueChanged(int value);
private:
    Ui::VideoPlayerEmission *ui;
    QMediaPlayer *Player;
    QVideoWidget *Video;
    qint64 mDuration;
    bool IS_Pause = true;
    bool IS_Muted = false;
    bool subtitlesEnabled = false;
    void updateDuration(qint64 Duration);


    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
};

#endif // VIDEOPLAYEREMISSION_H
