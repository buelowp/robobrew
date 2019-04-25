#include "robobrew.h"
#include "ui_robobrew.h"

robobrew::robobrew(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::robobrew)
{
    m_ui->setupUi(this);
}

robobrew::~robobrew() = default;
