#include "bugreportwindow.h"
#include "ui_bugreportwindow.h"
#include "core.h"
#include "../Smtp/SmtpMime"

BugReportWindow::BugReportWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BugReportWindow)
{
    enter
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->cmdCancel, SIGNAL(clicked()), SLOT(close()));
    connect(ui->cmdSend, SIGNAL(clicked()), SLOT(sendReport()));
    leave
}

BugReportWindow::~BugReportWindow()
{
    enter
    delete ui;
    leave
}

void BugReportWindow::sendReport()
{
    enter

    SmtpClient smtp("smtp.mastermail.ru", 465, SmtpClient::SslConnection);
    smtp.setUser("mailbot@redhelper.ru");
    smtp.setPassword("mailbot");

    MimeMessage message;
    message.setSender(new EmailAddress("mailbot@redhelper.ru", "Qt Desktop Bug Report"));
    message.addRecipient(new EmailAddress("antofik@gmail.com", "Anton"));
    message.setSubject(QString("[QT BUGREPORT ") + __VERSION3__ + "] " + ui->txtHeader->text());

    MimeText text;
    text.setText(ui->txtDescription->toPlainText());
    message.addPart(&text);

    MimeAttachment attachment (new QFile("./redhelper.log"));
    attachment.setContentType("text/plain");
    message.addPart(&attachment);

    smtp.connectToHost();
    smtp.login();
    smtp.sendMail(message);
    smtp.quit();

    //todo send report
    close();
    leave
}
