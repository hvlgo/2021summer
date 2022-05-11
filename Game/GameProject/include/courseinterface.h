#ifndef COURSEINTERFACE_H
#define COURSEINTERFACE_H

#include <QDialog>

namespace Ui {
class CourseInterface;
}

class CourseInterface : public QWidget
{
    Q_OBJECT

public:
    explicit CourseInterface(QWidget *parent = nullptr);
    ~CourseInterface();
signals:
    void outCourse();
private slots:
    void on_pushButton_14_clicked();

private:
    Ui::CourseInterface *ui;
};

#endif // COURSEINTERFACE_H
