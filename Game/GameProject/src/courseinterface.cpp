#include "courseinterface.h"
#include "ui_courseinterface.h"

CourseInterface::CourseInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CourseInterface)
{
    ui->setupUi(this);
}

CourseInterface::~CourseInterface()
{
    delete ui;
}

void CourseInterface::on_pushButton_14_clicked()
{
    emit outCourse();
}

