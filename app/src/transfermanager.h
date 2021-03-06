#ifndef TRANSFERMANAGER_H
#define TRANSFERMANAGER_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QStandardPaths>

#include "owncloudbrowser.h"
#include "transferentry.h"
#include "entryinfo.h"

class TransferManager : public QObject
{
    Q_OBJECT
public:
    TransferManager(QObject *parent = 0, OwnCloudBrowser *browser = 0);

    Q_PROPERTY(bool transfering READ isTransfering NOTIFY transferingChanged)

    Q_INVOKABLE TransferEntry* enqueueDownload(EntryInfo* entry, bool open);
    Q_INVOKABLE void enqueueUpload(QString localPath, QString remotePath);
    Q_INVOKABLE bool isNotEnqueued(EntryInfo* entry);
    Q_INVOKABLE QVariantList getTransfers();

private:
    OwnCloudBrowser *browser;
    QQueue<TransferEntry *> downloadQueue;
    QQueue<TransferEntry *> uploadQueue;
    QMutex downloadMutex;
    QMutex uploadMutex;

    QString destinationFromMIME(QString mime);

    bool isTransfering();

signals:
    void transferAdded();
    void transferingChanged();
    void downloadComplete(QString name, QString localPath);
    void downloadFailed(QString name);
    void uploadComplete(QString name, QString remotePath);
    void uploadFailed(QString name);

public slots:
    void handleDownloadCompleted();
    void handleUploadCompleted();

};

#endif // TRANSFERMANAGER_H
