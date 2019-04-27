/*
 * Copyright (c) 2019 <copyright holder> <email>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "relaymanager.h"

RelayManager::RelayManager(QObject *parent) : QObject(parent)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "RoboBrew", "RoboBrew");
    m_relays[RM_INNER_COIL] = settings.value("InnerCoil").toInt();
    m_relays[RM_OUTER_COIL] = settings.value("OuterCoil").toInt();
    m_relays[RM_PUMP] = settings.value("Pump").toInt();
    
    wiringPiSetupGpio();

    for (int i = 0; i < 3; i++) {
        pinMode(m_relays[i], OUTPUT);
        digitalWrite(m_relays[i], 0);
        m_state[i] = 0;
    }

    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
    m_timer->start();
}

RelayManager::~RelayManager()
{

}

void RelayManager::timeout()
{
    for (int i = 0; i < 3; i++) {
        if (m_state[i] == digitalRead(m_relays[i])) {
            emit relayStateChanged(i, !m_state[i]);
            m_state[i] = !m_state[i];
        }
    }
}

void RelayManager::setRelayState(int index, int value)
{
    digitalWrite(m_relays[index], value);
}

int RelayManager::getRelayState(int index)
{
    return digitalRead(m_relays[index]);
}

