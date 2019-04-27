/**
 * RoboBrew
 * robobrew.h
 * Copyright Peter Buelow (goballstate@gmail.com)
 * 
 * MIT License
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
#ifndef ROBOBREW_H
#define ROBOBREW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "relaymanager.h"
#include "brewprocess.h"

#define RB_ONE_MINUTE       (1000 * 60)

class RoboBrew : public QWidget
{
    Q_OBJECT

public:
    explicit RoboBrew(QWidget *parent = nullptr);
    ~RoboBrew() override;

public slots:
    void toggleInnerCoil();
    void toggleOuterCoil();
    void togglePump();
    void elapsedTimeout();
    void elapsedSegmentTimeout();
    void relayStateChanged(int, int);
    void startBrewing();
    void updateBaseTemp(double);
    void updateFloatTemp(double);
    void newSegment(struct BrewStep);
    
protected:
    void showEvent(QShowEvent*) override;
    
private:
    void setPumpButtonBackground(int);
    void setInnerCoilButtonBackground(int);
    void setOuterCoilButtonBackground(int);
    
    QGridLayout *m_layout;
    QLCDNumber *m_temp1;
    QLCDNumber *m_temp2;
    QLabel *m_temp1Label;
    QLabel *m_temp2Label;
    QLCDNumber *m_timeElapsedLabel;
    QLCDNumber *m_timeElapsedSegmentLabel;
    QPushButton *m_innerCoil;
    QPushButton *m_outerCoil;
    QPushButton *m_pump;
    QPushButton *m_starter;
    QTimer *m_timerElapsedTime;
    QTimer *m_timerElapsedSegmentTime;
    RelayManager *m_relays;
    BrewProcess *m_process;
    
    int m_timeElapsed;
    int m_timeElapsedSegment;
};

#endif // ROBOBREW_H
