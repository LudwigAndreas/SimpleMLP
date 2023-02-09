#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <QFile>
#include <QWidget>
#include <QVector>
#include <QPixmap>
#include <QPainter>
#include <QPalette>
#include <QMimeData>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class PaintView : public QGraphicsView
{
    Q_OBJECT

    bool draw;
    QVector<QPoint> vv;
    QImage pic;
    QGraphicsScene *scene;

public:
    explicit PaintView(QWidget *parent = nullptr);
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
//    ~PaintView();
public slots:

signals:

};

#endif // PAINTVIEW_H
