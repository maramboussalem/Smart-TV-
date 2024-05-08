#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include<QMainWindow>

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void setPath(QString path)
    {
        this->path = path  ;
    }

private slots:
    void on_pushButtonStop_clicked();

    void on_pushButtonPlay_clicked();


private:
    Ui::VideoPlayer *ui;
    QString path ;
    QMediaPlayer * mediaPlayer = new QMediaPlayer();
};

#endif // VIDEOPLAYER_H
