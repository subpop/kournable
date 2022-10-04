#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>

class Kournable;
class KJob;

class MainWindow : public KXmlGuiWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void loadData(const QByteArray &data);

private Q_SLOTS:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();

    void downloadFinished(KJob *job);

    void documentWasModified();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();

    void saveFileToDisk(const QString &outputFileName);

    void setCurrentFile(const QString &fileName );

    Kournable *kournable;
    QString currentFile;
};

#endif // MAINWINDOW_H
