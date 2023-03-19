#ifndef IMPORTFILEITEM_H
#define IMPORTFILEITEM_H

#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QMimeData>
#include <QDropEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QDragEnterEvent>

class ImportFileItem : public QLabel
{
    Q_OBJECT
public:
    ImportFileItem();
    ImportFileItem(QWidget *);
    bool isFileWasUploaded();
    QFile * getUploadedFile();
protected:
    QFile *file;

    virtual void dropEvent(QDropEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);

signals:
    void fileWasUploaded();
};

#endif // IMPORTFILEITEM_H
