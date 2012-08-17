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
    
};

#endif // IMAGEPROCESSOR_H
