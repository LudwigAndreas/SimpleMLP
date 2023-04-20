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
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    painter.setRenderHint(QPainter::RenderHint::SmoothPixmapTransform, true);
    painter.setPen(QPen(Qt::white, 24, Qt::SolidLine));
    setPalette(pal);
    if (pixmap) {
//		qDebug() << "belive me";
		if (new_pixmap) {
			vv.clear();
			new_pixmap = false;
		}
//		TODO: pixmap.data may be not pixmap
		painter.drawPixmap(-1, -1, pixmap->scaled(this->width(), this->height()));
//		pixmap = nullptr;
    }
	for (auto & line : vv) {
		painter.drawEllipse(line.first(), 3, 3);
		for (int i = 0; i < line.size() - 1; ++i) {
			painter.drawLine(line[i], line[i + 1]);
		}
		painter.drawEllipse(line.back(), 3, 3);
	}
//    for (auto & i : vv)
//        painter.drawEllipse(i, 5, 7);
//	painter.drawPoints(vv.data(), vv.size());
//    QWidget::paintEvent(event);
    hide();
    show();
}

void PaintView::mousePressEvent(QMouseEvent *event) {
    draw = true;
	vv.push_back(QVector<QPoint>());
	vv.back().push_back(event->pos());
	QGraphicsView::mousePressEvent(event);
}

void PaintView::mouseMoveEvent(QMouseEvent *event) {
    if (draw) {
        vv.back().push_back(event->pos());
    }
    update();
    QGraphicsView::mouseMoveEvent(event);
}

void PaintView::mouseReleaseEvent(QMouseEvent *event) {
    draw = false;
    QPixmap scr = this->grab();
    scr.save("my_letter.bmp");
	emit file_saved();
	qDebug() << "file_saved emited";
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
    this->pixmap->save("my_letter.bmp");
	new_pixmap = true;
	emit file_saved();
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
