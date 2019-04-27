/**
 * RoboBrew
 * robobrew.cpp
 * Copyright Peter Buelow (goballstate@gmail.com)
 * 
 * MIT License
 *
 * Copyright (c) 2019 Peter Buelow
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "robobrew.h"

RoboBrew::RoboBrew(QWidget *parent) : QWidget(parent)
{
    m_timeElapsed = 0;
    m_timeElapsedSegment = 0;
    
    m_layout = new QGridLayout();
    m_temp1 = new QLCDNumber(this);
    m_temp2 = new QLCDNumber(this);
    m_temp1Label = new QLabel(this);
    m_temp2Label = new QLabel(this);
    m_timeElapsedLabel = new QLCDNumber(this);
    m_timeElapsedSegmentLabel = new QLCDNumber(this);
    m_innerCoil = new QPushButton(this);
    m_outerCoil = new QPushButton(this);
    m_pump = new QPushButton(this);
    m_starter = new QPushButton(this);
    m_timerElapsedSegmentTime = new QTimer(this);
    m_timerElapsedTime = new QTimer(this);
    
    m_temp1->setMinimumSize(((800 / 2) - 5), 100);
    m_temp2->setMinimumSize(((800 / 2) - 5), 100);
    m_timeElapsedLabel->setMinimumSize(((800 / 2) - 5), 50);
    m_timeElapsedSegmentLabel->setMinimumSize(((800 / 2) - 5), 50);
    m_temp1Label->setMinimumSize(((800 / 2) - 5), 50);
    m_temp2Label->setMinimumSize(((800 / 2) - 5), 50);
    m_innerCoil->setMinimumSize(((800 / 4) - 5), 150);
    m_outerCoil->setMinimumSize(((800 / 4) - 5), 150);
    m_pump->setMinimumSize(((800 / 4) - 5), 150);
    m_starter->setMinimumSize(((800 / 4) - 5), 150);
    
    m_layout->addWidget(m_timeElapsedLabel, 0, 0, 1, 2, Qt::AlignCenter);
    m_layout->addWidget(m_timeElapsedSegmentLabel, 0, 2, 1, 2, Qt::AlignCenter);
    m_layout->addWidget(m_temp1Label, 1, 0, 1, 2, Qt::AlignCenter);
    m_layout->addWidget(m_temp2Label, 1, 2, 1, 2, Qt::AlignCenter);
    m_layout->addWidget(m_temp1, 2, 0, 1, 2, Qt::AlignCenter);
    m_layout->addWidget(m_temp2, 2, 2, 1, 2, Qt::AlignCenter);
    m_layout->addWidget(m_starter, 3, 0, Qt::AlignCenter);
    m_layout->addWidget(m_innerCoil, 3, 1, Qt::AlignCenter);
    m_layout->addWidget(m_outerCoil, 3, 2, Qt::AlignCenter);
    m_layout->addWidget(m_pump, 3, 3, Qt::AlignCenter);
    
    setLayout(m_layout);
    
    m_innerCoil->setText("500 Watt");
    m_outerCoil->setText("1000 Watt");
    m_pump->setText("Pump");
    m_starter->setText("Begin");
    m_temp1Label->setText("Base Temperature");
    m_temp2Label->setText("Floating Temperature");
    m_timeElapsedLabel->display("0:00");
    m_timeElapsedSegmentLabel->display("0:00");

    QPalette pal = m_starter->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    m_starter->setAutoFillBackground(true);
    m_starter->setPalette(pal);

    m_relays = new RelayManager();

    connect(m_innerCoil, SIGNAL(released()), this, SLOT(toggleInnerCoil()));
    connect(m_outerCoil, SIGNAL(released()), this, SLOT(toggleOuterCoil()));
    connect(m_pump, SIGNAL(released()), this, SLOT(togglePump()));
    connect(m_starter, SIGNAL(released()), this, SLOT(startBrewing()));
    connect(m_timerElapsedTime, SIGNAL(timeout()), this, SLOT(elapsedTimeout()));
    connect(m_timerElapsedSegmentTime, SIGNAL(timeout()), this, SLOT(elapsedSegmentTimeout()));
    connect(m_relays, SIGNAL(relayStateChanged(int, int)), this, SLOT(relayStateChanged(int, int)));
}

RoboBrew::~RoboBrew() = default;

void RoboBrew::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);
}

void RoboBrew::toggleInnerCoil()
{
    m_relays->setRelayState(RM_INNER_COIL, !m_relays->getRelayState(RM_INNER_COIL));
}

void RoboBrew::toggleOuterCoil()
{
    m_relays->setRelayState(RM_OUTER_COIL, !m_relays->getRelayState(RM_OUTER_COIL));
}

void RoboBrew::togglePump()
{
    m_relays->setRelayState(RM_PUMP, !m_relays->getRelayState(RM_PUMP));
}

void RoboBrew::elapsedSegmentTimeout()
{
}

void RoboBrew::elapsedTimeout()
{
    m_timeElapsed++;
    int hour = m_timeElapsed / 60;
    int minute = m_timeElapsed % 60;
    QString displayValue = QString("%1:%2").arg(hour).arg(minute, 1, 10, QChar('0'));
    m_timeElapsedLabel->display(displayValue);
}

void RoboBrew::setInnerCoilButtonBackground(int state)
{
    QPalette pal = m_innerCoil->palette();
    if (state)
        pal.setColor(QPalette::Button, QColor(Qt::green));
    else
        pal.setColor(QPalette::Button, QColor(Qt::red));
    m_innerCoil->setAutoFillBackground(true);
    m_innerCoil->setPalette(pal);
}

void RoboBrew::setOuterCoilButtonBackground(int state)
{
    QPalette pal = m_outerCoil->palette();
    if (state)
        pal.setColor(QPalette::Button, QColor(Qt::green));
    else
        pal.setColor(QPalette::Button, QColor(Qt::red));
    m_outerCoil->setAutoFillBackground(true);
    m_outerCoil->setPalette(pal);
}

void RoboBrew::setPumpButtonBackground(int state)
{
    QPalette pal = m_pump->palette();
    if (state)
        pal.setColor(QPalette::Button, QColor(Qt::green));
    else
        pal.setColor(QPalette::Button, QColor(Qt::red));
    m_pump->setAutoFillBackground(true);
    m_pump->setPalette(pal);
}

void RoboBrew::relayStateChanged(int button, int state)
{
    switch (button) {
        case RM_INNER_COIL:
            setInnerCoilButtonBackground(state);
            break;
        case RM_OUTER_COIL:
            setOuterCoilButtonBackground(state);
            break;
        case RM_PUMP:
            setPumpButtonBackground(state);
            break;
        default:
            break;
    }
}

void RoboBrew::startBrewing()
{
    m_timerElapsedTime->setInterval(RB_ONE_MINUTE);
    m_timerElapsedTime->start();
    QPalette pal = m_starter->palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    m_starter->setAutoFillBackground(true);
    m_starter->setPalette(pal);
    m_starter->setText("End");
}

void RoboBrew::updateBaseTemp(double t)
{
    QString temp = QString("%1").arg(t, 0, 'f', 1);
    m_temp1->display(temp);
}

void RoboBrew::updateFloatTemp(double t)
{
    QString temp = QString("%1").arg(t, 0, 'f', 1);
    m_temp2->display(temp);
}

