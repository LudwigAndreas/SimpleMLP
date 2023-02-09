#include "paintview.h"

PaintView::PaintView(QWidget *parent): QGraphicsView{parent}
{
    setAcceptDrops(true);
    draw = false;
    pixmap = nullptr;
    scene = new QGraphicsScene();
    this->setScene(scene);
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

void PaintView::paintEvent(QPaintEvent *event)
{
    QPainter painter(viewport());
    QPalette pal(palette());
    pal.setColor(QPalette::Window , Qt::white);
    setBackgroundRole(QPalette::Light);
    setAutoFillBackground(true);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing, true);
    painter.setPen(QPen(Qt::white, 10, Qt::SolidLine));
    setPalette(pal);
    if (pixmap) {
        painter.drawPixmap(0, 0, pixmap->scaled(this->width(), this->height()));
    }
    for (int i = 1; i < vv.size(); ++i)
        painter.drawEllipse(vv[i - 1], 7, 7);
    QWidget::paintEvent(event);
    hide();
    show();
}

void PaintView::mousePressEvent(QMouseEvent *event) {
    draw = true;
    QGraphicsView::mousePressEvent(event);
}

void PaintView::mouseMoveEvent(QMouseEvent *event) {
    if (draw) {
        vv.push_back(event->pos());
    }
    update();
    QGraphicsView::mouseMoveEvent(event);
}

void PaintView::mouseReleaseEvent(QMouseEvent *event) {
    draw = false;
    QPixmap scr = this->grab();
    scr.save("/Users/landreas/SimpleMLP/my_letter.bmp");
    QGraphicsView::mouseReleaseEvent(event);
}

void PaintView::clear() {
    vv.clear();
    if (pixmap)
    {
        delete pixmap;
        pixmap = nullptr;
    }
    hide();
    show();
}

void PaintView::dropEvent(QDropEvent *event)
{
    event->acceptProposedAction();
    const QMimeData* data = event->mimeData();
    QString file_path = data->urls()[0].path();
    qDebug() << file_path;
    if (pixmap)
        delete pixmap;
    this->pixmap = new QPixmap(file_path);
    if (pixmap->isNull())
    {
        QMessageBox::information(this,"Image Viewer","Error Displaying image");
        return;
    }
}

void PaintView::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void PaintView::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}


QPixmap *PaintView::getPixmap() {
    return pixmap;
}
