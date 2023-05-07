#include "paintview.h"

#include "gui/utils/const.h"

PaintView::PaintView(QWidget *parent) : QGraphicsView{parent} {
  setAcceptDrops(true);
  draw = false;
  pixmap = nullptr;
  scene = new QGraphicsScene();
  this->setScene(scene);
  this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

PaintView::~PaintView() {
  delete scene;
  delete pixmap;
}

void PaintView::paintEvent(QPaintEvent *event) {
  (void)event;
  QPainter painter(viewport());
  QPalette pal(palette());
  pal.setColor(QPalette::Window, Qt::white);
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
  painter.setRenderHint(QPainter::RenderHint::SmoothPixmapTransform, true);
  painter.setPen(QPen(Qt::white, 30, Qt::SolidLine, Qt::RoundCap));
  setPalette(pal);
  if (pixmap) {
    if (new_pixmap) {
      vv.clear();
      new_pixmap = false;
    }
    painter.drawPixmap(-1, -1, pixmap->scaled(this->width(), this->height()));
  }
  for (auto &line : vv) {
    if (line.size() == 1)
      line.push_back(QPoint(line[0].x() + 1, line[0].y() + 1));
    for (int i = 0; i < line.size() - 1; ++i) {
      painter.drawLine(line[i], line[i + 1]);
    }
  }
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
  QPixmap scr = this->grab().scaled(28, 28);
  scr.save(s21::constant::letter_file.c_str());
  emit file_saved();
  QGraphicsView::mouseReleaseEvent(event);
}

void PaintView::clear() {
  vv.clear();
  if (pixmap) {
    delete pixmap;
    pixmap = nullptr;
  }
  hide();
  show();
}

void PaintView::dropEvent(QDropEvent *event) {
  event->acceptProposedAction();
  const QMimeData *data = event->mimeData();
  QString file_path = data->urls()[0].path();
  if (pixmap) delete pixmap;
  this->pixmap = new QPixmap(file_path);
  if (pixmap->isNull()) {
    QMessageBox::information(this, "Image Viewer", "Error Displaying image");
    return;
  }
  this->pixmap->save(s21::constant::letter_file.c_str());
  new_pixmap = true;
  emit file_saved();
}

void PaintView::dragEnterEvent(QDragEnterEvent *event) {
  event->acceptProposedAction();
}

void PaintView::dragMoveEvent(QDragMoveEvent *event) {
  event->acceptProposedAction();
}

QPixmap *PaintView::getPixmap() { return pixmap; }
