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
    bool sobel_it(QString srcfile);
    bool laplace_it(QString srcfile);
    bool canny_it(QString srcfile);
    bool hough_it(QString srcfile);
    bool hough_line_it(QString srcfile);
    bool hough_circle_it(QString srcfile);
    bool remap_it(QString srcfile);
    bool affine_it (QString srcfile);
    bool hist_it (QString srcfile);
    bool hist_equal_it(QString srcfile);
    bool hist_calc_it(QString srcfile);
    bool comp_hist_it(QString src1file, QString src2file, QString src3file);
    bool back_projection_it (QString srcfile);
    bool template_match_it(QString src1file, QString src2file);
    bool find_contous_it (QString srcfile);
    bool find_convexhull_it  (QString srcfile);
    bool find_box_circle_it  (QString srcfile);
    bool find_box_ellipse_it (QString srcfile);
    bool moment_it (QString srcfile);
    bool polygon_it (QString srcfile);
    bool haar_it_cpp(QString srcfile);

    ///////////
    bool haar_it(QString srcfile);

    ///// bench
    bool bc_gm_thumb(QString srcfile);

    //
    bool surf_detect_it(QString src1file, QString src2file, QString src3file);
    bool cvextor_it(QString src1file, QString src2file, QString algo, QString hisen);

private:
    QStringList margs;
    QStringList mreses;
    char mshbuf[255]; // assert no multi thread access
    QDateTime mbtime;
    QDateTime metime;
    float mdtime;
};

#endif // IMAGEPROCESSOR_H
