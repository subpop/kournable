#include "kournable.h"
#include "ui_kournable.h"

kournable::kournable(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::kournable)
{
    m_ui->setupUi(this);
}

kournable::~kournable() = default;
