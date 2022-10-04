#include <QJsonObject>
#include <QDebug>

#include "kournable.h"
#include "ui_kournable.h"

Kournable::Kournable ( QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::Kournable )
{
    ui->setupUi ( this );

    connect(ui->mondayPlainTextEdit->document(), &QTextDocument::contentsChanged,
            this, &Kournable::handleDocumentChanges);
    connect(ui->tuesdayPlainTextEdit->document(), &QTextDocument::contentsChanged,
            this, &Kournable::handleDocumentChanges);
    connect(ui->wednesdayPlainTextEdit->document(), &QTextDocument::contentsChanged,
            this, &Kournable::handleDocumentChanges);
    connect(ui->thursdayPlainTextEdit->document(), &QTextDocument::contentsChanged,
            this, &Kournable::handleDocumentChanges);
    connect(ui->fridayPlainTextEdit->document(), &QTextDocument::contentsChanged,
            this, &Kournable::handleDocumentChanges);
    connect(ui->weekendPlainTextEdit->document(), &QTextDocument::contentsChanged,
            this, &Kournable::handleDocumentChanges);
    connect(ui->thisMonthPlainTextEdit->document(), &QTextDocument::contentsChanged,
            this, &Kournable::handleDocumentChanges);
    connect(ui->nextMonthPlainTextEdit->document(), &QTextDocument::contentsChanged,
            this, &Kournable::handleDocumentChanges);
}

Kournable::~Kournable()
{
    delete ui;
}

void Kournable::clear()
{
    ui->mondayPlainTextEdit->clear();
    ui->mondayPlainTextEdit->clear();
    ui->tuesdayPlainTextEdit->clear();
    ui->wednesdayPlainTextEdit->clear();
    ui->thursdayPlainTextEdit->clear();
    ui->fridayPlainTextEdit->clear();
    ui->weekendPlainTextEdit->clear();
    ui->thisMonthPlainTextEdit->clear();
    ui->nextMonthPlainTextEdit->clear();
}

void Kournable::load ( QJsonObject json )
{
    if ( json.contains ( "days" ) ) {
        QJsonObject days = json["days"].toObject();

        ui->mondayPlainTextEdit->setPlainText ( days["monday"].toString() );
        ui->tuesdayPlainTextEdit->setPlainText ( days["tuesday"].toString() );
        ui->wednesdayPlainTextEdit->setPlainText ( days["wednesday"].toString() );
        ui->thursdayPlainTextEdit->setPlainText ( days["thursday"].toString() );
        ui->fridayPlainTextEdit->setPlainText ( days["friday"].toString() );
        ui->weekendPlainTextEdit->setPlainText( days["weekend"].toString());
    }

    if ( json.contains ( "months" ) ) {
        QJsonObject months = json["months"].toObject();

        ui->thisMonthPlainTextEdit->setPlainText ( months["this_month"].toString() );
        ui->nextMonthPlainTextEdit->setPlainText ( months["next_month"].toString() );
    }
}

QJsonObject Kournable::save()
{
    QJsonObject json;

    QJsonObject days;

    days["monday"] = ui->mondayPlainTextEdit->toPlainText();
    days["tuesday"] = ui->tuesdayPlainTextEdit->toPlainText();
    days["wednesday"] = ui->wednesdayPlainTextEdit->toPlainText();
    days["thursday"] = ui->thursdayPlainTextEdit->toPlainText();
    days["friday"] = ui->fridayPlainTextEdit->toPlainText();
    days["weekend"] = ui->weekendPlainTextEdit->toPlainText();

    json["days"] = days;

    QJsonObject months;

    months["this_month"] = ui->thisMonthPlainTextEdit->toPlainText();
    months["next_month"] = ui->nextMonthPlainTextEdit->toPlainText();

    json["months"] = months;

    return json;
}

bool Kournable::isModified()
{
    return ui->mondayPlainTextEdit->document()->isModified() ||
           ui->tuesdayPlainTextEdit->document()->isModified() ||
           ui->wednesdayPlainTextEdit->document()->isModified() ||
           ui->thursdayPlainTextEdit->document()->isModified() ||
           ui->fridayPlainTextEdit->document()->isModified() ||
           ui->weekendPlainTextEdit->document()->isModified() ||
           ui->thisMonthPlainTextEdit->document()->isModified() ||
           ui->nextMonthPlainTextEdit->document()->isModified();
}

void Kournable::setModified ( bool modified )
{
    ui->mondayPlainTextEdit->document()->setModified(modified);
    ui->tuesdayPlainTextEdit->document()->setModified(modified);
    ui->wednesdayPlainTextEdit->document()->setModified(modified);
    ui->thursdayPlainTextEdit->document()->setModified(modified);
    ui->fridayPlainTextEdit->document()->setModified(modified);
    ui->weekendPlainTextEdit->document()->setModified(modified);
    ui->thisMonthPlainTextEdit->document()->setModified(modified);
    ui->nextMonthPlainTextEdit->document()->setModified(modified);
}

void Kournable::handleDocumentChanges() {
    emit contentsChanged();
}
