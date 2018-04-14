/*******************************************************************************
 * Copyright [2018] <青岛艾普智能仪器有限公司>
 * All rights reserved.
 *
 * version:     0.1
 * author:      zhaonanlin
 * brief:       等待提示框
*******************************************************************************/
#include "boxpop.h"

BoxPop::BoxPop(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
{
    initUI();
    initSkin();
    initAnimation();
}

void BoxPop::setText(QString text)
{
    textLabel->setText(text);
}

void BoxPop::initUI()
{
    logoLabel = new QLabel(this);
    logoLabel->setFixedSize(64, 64);
    logoLabel->setScaledContents(true);

    QHBoxLayout *ll = new QHBoxLayout;
    ll->addStretch();
    ll->addWidget(logoLabel);
    ll->addStretch();

    textLabel = new QLabel(this);

    QHBoxLayout *hh = new QHBoxLayout;
    hh->addStretch();
    hh->addWidget(textLabel);
    hh->addStretch();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(ll);
    layout->addLayout(hh);

    this->setMinimumSize(200, 100);
    this->setStyleSheet("QDialog{border:2px solid gray;}");
}

void BoxPop::initSkin()
{
    QFile file;
    QString qss;
    file.setFileName(":/qss_black.css");
    file.open(QFile::ReadOnly);
    qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
}

void BoxPop::initAnimation()
{
    animation = new QPropertyAnimation(this, "pixmap");
    animation->setDuration(1200);
    animation->setLoopCount(-1);
    for (int i = 0; i <= 8; ++i) {
        animation->setKeyValueAt(i / 8.0, i);
    }
}

int BoxPop::pixmap() const
{
    return m_index;
}

void BoxPop::setPixmap(const int index)
{
    m_index = index;
    QMatrix leftmatrix;
    leftmatrix.rotate((index/2%4)*90%360);
    QString path = (index%2 == 0) ? (":/loading1") : (":/loading2");
    QPixmap pixmap(path);
    QPixmap pix = pixmap.transformed(leftmatrix, Qt::SmoothTransformation);
    logoLabel->setPixmap(pix);
}

void BoxPop::showEvent(QShowEvent *e)
{
    animation->start();
    e->accept();
}

void BoxPop::hideEvent(QHideEvent *e)
{
    animation->stop();
    e->accept();
}

void BoxPop::mousePressEvent(QMouseEvent *e)
{
    this->accept();
    e->accept();
}
