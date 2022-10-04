#include <QtWidgets>

#include <KActionCollection>
#include <KStandardAction>
#include <KLocalizedString>
#include <KMessageBox>
#include <KIO/Job>

#include "mainwindow.h"
#include "kournable.h"

MainWindow::MainWindow ( QWidget *parent ) : KXmlGuiWindow ( parent )
{
    kournable = new Kournable();
    setCentralWidget ( kournable );

    createActions();
    createStatusBar();

    readSettings();

    connect ( kournable, &Kournable::contentsChanged,
              this, &MainWindow::documentWasModified );

    setCurrentFile ( QString() );

    setupGUI ( Default, "kournableui.rc" );
}

void MainWindow::closeEvent ( QCloseEvent* event )
{
    if ( maybeSave() ) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


void MainWindow::createActions()
{
    QAction *clearAction = new QAction ( this );
    clearAction->setText ( i18n ( "&Clear" ) );
    actionCollection()->setDefaultShortcut ( clearAction, Qt::CTRL + Qt::Key_W );
    actionCollection()->addAction ( "clear", clearAction );
    connect ( clearAction, &QAction::triggered, this, &MainWindow::newFile );

    KStandardAction::quit ( qApp, &QCoreApplication::quit, actionCollection() );
    KStandardAction::open ( this, &MainWindow::openFile, actionCollection() );
    KStandardAction::save ( this, &MainWindow::saveFile, actionCollection() );
    KStandardAction::saveAs ( this, &MainWindow::saveFileAs, actionCollection() );
    KStandardAction::openNew ( this, &MainWindow::newFile, actionCollection() );
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage ( i18n ( "Ready" ) );
}

void MainWindow::newFile()
{
    if ( maybeSave() ) {
        kournable->clear();
        setCurrentFile ( QString() );
    }
}

bool MainWindow::maybeSave()
{
    if ( !kournable->isModified() )
        return true;

    const QMessageBox::StandardButton ret
        = QMessageBox::warning ( this, i18n ( "Application" ),
                                 i18n ( "The document has been modified.\n"
                                        "Do you want to save your changes?" ),
                                 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel );
    switch ( ret ) {
    case QMessageBox::Save:
        saveFile();
        return true;
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}


void MainWindow::saveFileToDisk ( const QString& outputFileName )
{
    if ( !outputFileName.isNull() ) {
        QSaveFile file ( outputFileName );
        file.open ( QIODevice::WriteOnly );

        QJsonObject json = kournable->save();
        QJsonDocument document = QJsonDocument ( json );
        QByteArray outputByteArray = document.toJson();

        file.write ( outputByteArray );
        file.commit();

        currentFile = outputFileName;
    }
}

void MainWindow::saveFileAs()
{
    saveFileToDisk ( QFileDialog::getSaveFileName ( this, i18n ( "Save File As" ) ) );
}


void MainWindow::saveFile()
{
    if ( !currentFile.isEmpty() ) {
        saveFileToDisk ( currentFile );
    } else {
        saveFileAs();
    }
    setCurrentFile(currentFile);
}

void MainWindow::openFile()
{
    if ( maybeSave() ) {

        const QUrl fileNameFromDialog = QFileDialog::getOpenFileUrl ( this, i18n ( "Open File" ) );

        if ( !fileNameFromDialog.isEmpty() ) {
            KIO::Job *job = KIO::storedGet ( fileNameFromDialog );
            currentFile = fileNameFromDialog.toLocalFile();

            connect ( job, &KJob::result, this, &MainWindow::downloadFinished );

            job->exec();
        }
    }
}

void MainWindow::downloadFinished ( KJob* job )
{
    if ( job->error() ) {
        KMessageBox::error ( this, job->errorString() );
        currentFile.clear();
        return;
    }

    const KIO::StoredTransferJob *storedJob = qobject_cast<KIO::StoredTransferJob *> ( job );

    if ( storedJob ) {
        loadData ( storedJob->data() );
    }
}

void MainWindow::loadData ( const QByteArray &data )
{
    QJsonDocument document = QJsonDocument::fromJson ( data );
    QJsonObject json = document.object();

    kournable->load ( json );
    setCurrentFile ( currentFile );
}

void MainWindow::setCurrentFile ( const QString& fileName )
{
    currentFile = fileName;
    kournable->setModified ( false );
    setWindowModified ( false );

    QString shownName = currentFile;
    if ( currentFile.isEmpty() )
        shownName = "untitled.json";
    setWindowFilePath ( shownName );
}


void MainWindow::documentWasModified()
{
    setWindowModified ( kournable->isModified() );
}

void MainWindow::readSettings()
{
}

void MainWindow::writeSettings()
{
}
