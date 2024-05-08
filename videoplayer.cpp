#include "videoplayer.h"
#include "ui_videoplayer.h"
#include <QMessageBox>
#include "QFileDialog"
#include <QVBoxLayout>
#include<QVideoWidget>
#include<QToolBar>
VideoPlayer::VideoPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideoPlayer),
    mediaPlayer(new QMediaPlayer(this))
{
    ui->setupUi(this);
    QString path = QFileDialog::getOpenFileName(nullptr, "Select Video", "", "*.AVI");

    // Créer un widget vidéo
    QVideoWidget *videoWidget = new QVideoWidget(this);
    this->setCentralWidget(videoWidget); // Définir le widget vidéo comme widget central

    // Créer un lecteur multimédia et associer le widget vidéo
    QMediaPlayer *mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(videoWidget);

    // Définir le fichier vidéo pour le lecteur multimédia
    mediaPlayer->setMedia(QUrl::fromLocalFile(path));

    // Créer un bouton de lecture
    //QPushButton *playButton = new QPushButton("Play", this);

    // Ajouter le bouton à une nouvelle barre d'outils
    QToolBar *toolBar = new QToolBar(this);
    //toolBar->addWidget(playButton);
    this->addToolBar(toolBar);
    mediaPlayer->play();
    // Connecter le bouton de lecture pour démarrer la lecture
    //QObject::connect(playButton, &QPushButton::clicked, mediaPlayer, &QMediaPlayer::play);
}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

void VideoPlayer::on_pushButtonStop_clicked()
{
    mediaPlayer->stop();
}

void VideoPlayer::on_pushButtonPlay_clicked()
{
    qDebug() << "here";
    qDebug() << "file path in player : " + this->path;

    if (mediaPlayer == nullptr)
    {
        qDebug() << "null media player";
        return;
    }

    qDebug() << "Player error state -> " << mediaPlayer->error(); //this says no error
    qDebug() << "Media supported state -> " << QMediaPlayer::hasSupport("video/mp4"); // this gives a "1"

    if (mediaPlayer->error() == QMediaPlayer::NoError && QMediaPlayer::hasSupport("video/mp4")) {
        mediaPlayer->play();
    } else {
        QMessageBox::critical(this, "Error", "Unable to play the video.");
    }
}
