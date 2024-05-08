#include "videoplayeremission.h"
#include "ui_videoplayeremission.h"
#include "qsubtitles.h"
VideoPlayerEmission::VideoPlayerEmission(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideoPlayerEmission)
{
    ui->setupUi(this);

    // Initialisation du lecteur vidéo
    Player = new QMediaPlayer();

    // Initialisation des icônes des boutons de contrôle
    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Backward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    ui->horizontalSlider_Volume->setMinimum(0);
    ui->horizontalSlider_Volume->setMaximum(100);
    ui->horizontalSlider_Volume->setValue(30);

    Player->setVolume(ui->horizontalSlider_Volume->value());

    connect(Player, &QMediaPlayer::durationChanged, this, &VideoPlayerEmission::durationChanged);
    connect(Player, &QMediaPlayer::positionChanged, this, &VideoPlayerEmission::positionChanged);

    ui->horizontalSlider_Duration->setRange(0, Player->duration() / 1000);


    IS_Pause = false;
    IS_Muted = false;


   int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug()<< "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug()<< "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

}

VideoPlayerEmission::~VideoPlayerEmission()
{
    delete ui;
}
void VideoPlayerEmission::update_label()
{
    data = A.read_from_arduino();

    if (data == "*") {
        on_pushButton_Play_Pause_clicked();
    } else if (data == "LEFT") {
        on_pushButton_Seek_Backward_clicked();
    } else if (data == "RIGHT") {
        on_pushButton_Seek_Forward_clicked();
    } else if (data == "UP") {
        on_pushButton_Volume_clicked();
    } else if (data == "#") {
        on_pushButtonSousTitrage_clicked();
    } else {
        qDebug() << "Unknown button pressed. Data:" << data;
    }
}

void VideoPlayerEmission::durationChanged(qint64 duration)//
{
    mDuration = duration / 1000;
    ui->horizontalSlider_Duration->setMaximum(mDuration);
}
void VideoPlayerEmission::positionChanged(qint64 duration)//
{
        static qint64 lastPosition = 0;
        static QTime lastCallTime = QTime::currentTime();

        qint64 currentPosition = duration / 1000;
        QTime currentTime = QTime::currentTime();

        // Vérifier si un certain temps s'est écoulé depuis le dernier appel
        int elapsedMilliseconds = lastCallTime.msecsTo(currentTime);
        if (elapsedMilliseconds < 500) { // Limiter la fréquence des appels à 500 millisecondes
            return;
        }
        qDebug() << "positionChanged called";

        // Votre logique de mise à jour de l'interface utilisateur ici...
        lastPosition = currentPosition;
        lastCallTime = currentTime;

        //To Do
        /*if (!ui->horizontalSlider_Duration->isSliderDown())
          {
               ui->horizontalSlider_Duration->setValue(duration / 1000);
          }*/

        updateDuration(duration / 1000);

}

void VideoPlayerEmission::updateDuration(qint64 Duration)//
{
   if (Duration || mDuration)
    {
        QTime CurrrentTime((Duration / 3600) % 60, (Duration / 60) % 60, Duration % 60, (Duration * 1000) % 1000);
        QTime TotalTime((mDuration / 3600) % 60, (mDuration / 60) % 60, mDuration % 60, (mDuration * 1000) % 1000);
        QString Format ="";
        if(mDuration > 3600) Format ="hh:mm:ss";
        else Format ="mm:ss";

        ui->label_current_Time->setText(CurrrentTime.toString(Format));
        ui->label_Total_Time->setText(TotalTime.toString(Format));
    }

}
void VideoPlayerEmission::on_actionOpen_triggered()//
{
    QString videoFileName = QFileDialog::getOpenFileName(this, tr("Select Video File"), "", tr("Video Files (*.mp4 *.avi);;All Files (*)"));
        if (!videoFileName.isEmpty())
        {
            QString subtitleFileName = QFileDialog::getOpenFileName(this, tr("Select Subtitle File"), "", tr("Subtitle Files (*.srt);;All Files (*)"));
            if (!subtitleFileName.isEmpty())
            {
                QDir appDir = QCoreApplication::applicationDirPath();
                QString videoFilePath = appDir.absoluteFilePath(videoFileName);
                QString subtitleFilePath = appDir.absoluteFilePath(subtitleFileName);

                Video = new QVideoWidget();
                Video->setGeometry(5, 5, ui->groupBox_video->width() - 10, ui->groupBox_video->height() - 10);
                Video->setParent(ui->groupBox_video);
                Player->setVideoOutput(Video);

                // Charger le fichier vidéo
                Player->setMedia(QUrl::fromLocalFile(videoFilePath));

                // Charger les sous-titres
                QSubtitles* subtitles = new QSubtitles(subtitleFilePath);
                connect(Player, &QMediaPlayer::positionChanged, subtitles, &QSubtitles::updatePosition);

                // Afficher les sous-titres dans labelSousTitre
                connect(subtitles, &QSubtitles::subtitleChanged, ui->labelSousTitre, &QLabel::setText);

                ui->labelSousTitre->setStyleSheet("QLabel { background-color : rgba(0, 0, 0, 100); color : white; padding: 5px; }");
                ui->labelSousTitre->setAlignment(Qt::AlignCenter);

                Video->setVisible(true);
                Video->show();

                // Ajout de la fonctionnalité de sous-titrage via un bouton
                QPushButton *pushButton_Subtitle = new QPushButton("Toggle Subtitles", this);
                pushButton_Subtitle->setGeometry(10, 10, 120, 30);
                connect(pushButton_Subtitle, &QPushButton::clicked, this, &VideoPlayerEmission::on_pushButtonSousTitrage_clicked);
            }
        }
}
void VideoPlayerEmission::on_pushButton_Seek_Backward_clicked()
{
    if (ui->horizontalSlider_Duration->value() > 20) {
        ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value() - 20);
        Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
    }
}

void VideoPlayerEmission::on_pushButton_Play_Pause_clicked()
{
    if (IS_Pause == true)
    {
        IS_Pause = false;
        Player->play();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        IS_Pause = true;
        Player->pause();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }

}

void VideoPlayerEmission::on_pushButton_Stop_clicked()
{
     Player->stop();
}

void VideoPlayerEmission::on_pushButton_Seek_Forward_clicked()
{
    if (ui->horizontalSlider_Duration->value() + 20 < ui->horizontalSlider_Duration->maximum()) {
        ui->horizontalSlider_Duration->setValue(ui->horizontalSlider_Duration->value() + 20);
        Player->setPosition(ui->horizontalSlider_Duration->value() * 1000);
    }
}

void VideoPlayerEmission::on_pushButtonSousTitrage_clicked()
{
    ui->labelSousTitre->setVisible(!ui->labelSousTitre->isVisible());
}

void VideoPlayerEmission::on_pushButton_Volume_clicked()
{
    if (IS_Muted == false)
    {
        IS_Muted = true;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        Player->setMuted(true);
    }
    else
    {
        IS_Muted = false;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        Player->setMuted(false);
    }
}

void VideoPlayerEmission::on_horizontalSlider_Duration_valueChanged(int value)
{
    Player->setPosition(value * 1000);
}

void VideoPlayerEmission::on_horizontalSlider_Volume_valueChanged(int value)
{
     Player->setVolume(value);
}
