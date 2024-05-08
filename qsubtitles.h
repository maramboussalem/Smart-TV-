#ifndef QSUBTITLES_H
#define QSUBTITLES_H

#include <QObject>

#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QTimer>

class QSubtitles : public QObject
{
    Q_OBJECT
public:
    QSubtitles();
    explicit QSubtitles(const QString &fileName, QObject *parent = nullptr);
    explicit QSubtitles(QObject *parent = nullptr);
        void loadSubtitles(const QString &fileName);
        QString getSubtitle(qint64 position);

    signals:
        void subtitleChanged(const QString &text);

    public slots:
        void updatePosition(qint64 position);

    private:
        QMap<qint64, QString> mSubtitles;
};

#endif // QSUBTITLES_H
