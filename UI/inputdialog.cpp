#include "inputdialog.h"
#include <QPlainTextEdit>
#include <QLabel>
#include <QGridLayout>
#include "Common/notifier.h"

InputDialog::InputDialog(const QString &title, const QString &tip, const QString &text, bool canEmpty, QWidget *parent)
    : CFramelessDialog (title,parent,true)
{
   QLabel *tipLabel=new QLabel(tip,this);
   edit=new QPlainTextEdit(text,this);
   edit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
   QGridLayout *inputGLayout=new QGridLayout(this);
   inputGLayout->addWidget(tipLabel, 0, 0);
   inputGLayout->addWidget(edit, 1, 0);
   inputGLayout->setRowStretch(1, 1);
   inputGLayout->setColumnStretch(0, 1);
   inputGLayout->setContentsMargins(0, 0, 0, 0);
   this->canEmpty=canEmpty;
}

InputDialog::InputDialog(const QString &title, const QString &tip, QWidget *parent): CFramelessDialog (title,parent,true), edit(nullptr)
{
    QLabel *tipLabel=new QLabel(tip,this);
    QVBoxLayout *inputVLayout=new QVBoxLayout(this);
    inputVLayout->addWidget(tipLabel);
}

InputDialog::InputDialog(const QByteArray &imgData, const QString &title, const QString &tip, const QString &text, QWidget *parent): CFramelessDialog (title,parent,true)
{
    QLabel *imgLabel = new QLabel(this);
    QPixmap pixmap;
    pixmap.loadFromData(imgData);
    imgLabel->setPixmap(pixmap);
    imgLabel->setScaledContents(true);
    imgLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    int w = pixmap.width(), h =pixmap.height();
    if(w > 0 && h > 0)
    {
        int nw = 260*logicalDpiX()/96;
        int nh = nw*h/w;
        imgLabel->setMinimumSize(nw, nh);
    }

    QLabel *tipLabel=new QLabel(tip,this);
    edit=new QPlainTextEdit(text,this);
    QGridLayout *inputGLayout=new QGridLayout(this);
    inputGLayout->addWidget(imgLabel, 0, 0);
    inputGLayout->addWidget(tipLabel, 1, 0);
    inputGLayout->addWidget(edit, 2, 0);
    inputGLayout->setRowStretch(0, 1);
    inputGLayout->setColumnStretch(0, 1);
    inputGLayout->setContentsMargins(0, 0, 0, 0);
}

InputDialog::InputDialog(const QByteArray &imgData, const QString &title, const QString &tip, QWidget *parent): CFramelessDialog (title,parent, true), edit(nullptr)
{
    QLabel *imgLabel = new QLabel(this);
    QPixmap pixmap;
    pixmap.loadFromData(imgData);
    imgLabel->setPixmap(pixmap);
    imgLabel->setScaledContents(true);
    imgLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    int w = pixmap.width(), h =pixmap.height();
    if(w > 0 && h > 0)
    {
        int nw = 260*logicalDpiX()/96;
        int nh = nw*h/w;
        imgLabel->setMinimumSize(nw, nh);
    }


    QLabel *tipLabel=new QLabel(tip,this);

    QGridLayout *inputGLayout=new QGridLayout(this);
    inputGLayout->addWidget(imgLabel, 0, 0);
    inputGLayout->addWidget(tipLabel, 1, 0);
    inputGLayout->setRowStretch(1, 1);
    inputGLayout->setColumnStretch(0, 1);
    inputGLayout->setContentsMargins(0, 0, 0, 0);
}

void InputDialog::onAccept()
{
    if(edit)
    {
        text=edit->toPlainText().trimmed();
        if(!canEmpty && text.isEmpty())
        {
            showMessage(tr("Can't be empty"), NM_ERROR | NM_HIDE);
            return;
        }
    }
    CFramelessDialog::onAccept();
}
