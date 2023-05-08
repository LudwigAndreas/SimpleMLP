#include "importfileitem.h"

ImportFileItem::ImportFileItem() : QLabel() {
    this->setAcceptDrops(true);
}

ImportFileItem::ImportFileItem(QWidget *parent) : QLabel(parent) {
    this->setAcceptDrops(true);
}

void ImportFileItem::dropEvent(QDropEvent *event) {
    event->acceptProposedAction();
    const QMimeData *data = event->mimeData();
    if (!data->urls().empty()) {
        QString file_path = data->urls()[0].path();
        auto *file_try = new QFile(file_path);
        if (file_try->open(QIODevice::ReadOnly)) {
            this->file = file_try;
            emit fileWasUploaded();
        } else {
            delete file_try;
        }
    } else {
        QMessageBox::information(this, tr("Unable to open file"),
                                 "File open error.");
        return;
    }
}

QFile *ImportFileItem::getUploadedFile() {
    return this->file;
}

void ImportFileItem::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

bool ImportFileItem::isFileWasUploaded() {
    if (this->file) return true;
    return false;
}
