#include "importfileitem.h"


ImportFileItem::ImportFileItem(): QLabel()
{
    this->setAcceptDrops(true);
}

ImportFileItem::ImportFileItem(QWidget *parent): QLabel(parent)
{
    this->setAcceptDrops(true);
}

void ImportFileItem::dropEvent(QDropEvent *event) {
    event->acceptProposedAction();
    const QMimeData* data = event->mimeData();
    QString file_path = data->urls()[0].path();
    QFile file(file_path);
    qDebug() << file_path;
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    } else {
        this->file = &file;
        emit fileWasUploaded();
    }
}

QFile *ImportFileItem::getUploadedFile() {
    return this->file;
}

void ImportFileItem::dragEnterEvent(QDragEnterEvent *event)
{
//    QFont font = this->font();
//    font.setPointSize(18);
//    this->setFont(font);
//    setText(tr("drop here"));
    event->acceptProposedAction();
}

bool ImportFileItem::isFileWasUploaded() {
    if (this->file)
        return true;
    return false;
}
