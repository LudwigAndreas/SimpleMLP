#ifndef IMPORTFILEITEM_H
#define IMPORTFILEITEM_H

#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QMimeData>

class ImportFileItem : public QLabel {
    Q_OBJECT
public:
    ImportFileItem();
    ImportFileItem(QWidget *);
    bool isFileWasUploaded();
    QFile *getUploadedFile();

protected:
    QFile *file;

    virtual void dropEvent(QDropEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);

signals:
    void fileWasUploaded();
};

#endif  // IMPORTFILEITEM_H
