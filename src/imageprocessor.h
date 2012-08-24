#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QThread>
#include <QtCore>

class ImageProcessor : public QThread
{
    Q_OBJECT
public:
    explicit ImageProcessor(QObject *parent = 0);
    
    virtual void run();

    void run(QStringList args);

signals:
    
public slots:
    QStringList getResult();

private:
    char *get_cpath(const QString &srcfile);
    std::string get_cxxpath(const QString &srcfile);
    QString get_tpath(const QString &srcfile, const QString &prefix, const QString &subprefix = QString());
    std::string get_txxpath(const QString &srcfile, const QString &prefix, const QString &subprefix = QString());
    bool smooth_it(QString srcfile);
    bool erode_it(QString srcfile);
    bool dilate_it(QString srcfile);
    bool morph_it(QString srcfile);
    bool pyramids_it(QString srcfile);
    bool threshold_it(QString srcfile);
    bool filter2d_it(QString srcfile);
    bool border_it(QString srcfile);

private:
    QStringList margs;
    QStringList mreses;
    char mshbuf[255]; // assert no multi thread access
    QDateTime mbtime;
    QDateTime metime;
    float mdtime;
};

#endif // IMAGEPROCESSOR_H
