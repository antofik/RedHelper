#ifndef BUGREPORTWINDOW_H
#define BUGREPORTWINDOW_H

#include <QWidget>

namespace Ui {
class BugReportWindow;
}

class BugReportWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BugReportWindow(QWidget *parent = 0);
    ~BugReportWindow();

private slots:
    void sendReport();

private:
    Ui::BugReportWindow *ui;
};

#endif // BUGREPORTWINDOW_H
