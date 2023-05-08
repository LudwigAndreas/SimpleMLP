#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <QDebug>
#include <QFile>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMessageBox>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QVector>
#include <QWidget>

class PaintView : public QGraphicsView {
    Q_OBJECT

    bool draw;
    bool new_pixmap = false;
    //	QVector<QPoint> vv;
    QVector<QVector<QPoint> > vv;
    QImage pic;
    QGraphicsScene *scene;

public:
    explicit PaintView(QWidget *parent = nullptr);
    ~PaintView();
    void clear();
    QPixmap *getPixmap();

protected:
    QPixmap *pixmap;

    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
public slots:

signals:
    void file_saved();
};

#endif  // PAINTVIEW_H
