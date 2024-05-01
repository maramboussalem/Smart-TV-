#include "qsubtitles.h"
#include <QDebug>
#include <QDateTime>
QSubtitles::QSubtitles()
{

}
QSubtitles::QSubtitles(const QString &fileName, QObject *parent) : QObject(parent)
{
    loadSubtitles(fileName);
}

void QSubtitles::loadSubtitles(const QString &fileName)  // Fonction pour charger les sous-titres à partir d'un fichier
{
    // Ouverture du fichier en lecture
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open subtitles file";
        return;
    }

    // Lecture du fichier ligne par ligne
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;


         // Vérifie si la ligne est un numéro de séquence valide
        bool ok;
        line.toInt(&ok);
        if (!ok)
            continue;

        // Lecture des temps de début et de fin du sous-titre
        QString timeString = in.readLine().trimmed();
        QStringList timeParts = timeString.split("-->");
        if (timeParts.count() != 2)
            continue;

        qint64 startTime = QTime::fromString(timeParts[0].trimmed(), "hh:mm:ss,zzz").msecsSinceStartOfDay();
        qint64 endTime = QTime::fromString(timeParts[1].trimmed(), "hh:mm:ss,zzz").msecsSinceStartOfDay();

        // Lecture du texte du sous-titre
        QString text;
        while (true)
        {
            QString subtitleLine = in.readLine().trimmed();
            if (subtitleLine.isEmpty())
                break;

            text += subtitleLine + "\n";
        }

         // Ajout du sous-titre à la liste
        mSubtitles.insert(startTime, text);
    }

    file.close();
}

QString QSubtitles::getSubtitle(qint64 position)// Fonction pour récupérer le sous-titre correspondant à une position donnée
{
    auto it = mSubtitles.upperBound(position);
    if (it != mSubtitles.begin())
    {
        --it;
        return it.value();
    }

    return "";
}

void QSubtitles::updatePosition(qint64 position) // Fonction pour mettre à jour la position du sous-titre en fonction de la position de la vidéo
{
    QString subtitle = getSubtitle(position);
    emit subtitleChanged(subtitle);
}
