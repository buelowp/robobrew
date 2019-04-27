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
#if 0
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "RoboBrew", "RoboBrew");
    m_pins[RM_INNER_COIL] = settings.value("InnerCoil").toByteArray();
    m_pins[RM_OUTER_COIL] = settings.value("OuterCoil").toByteArray();
    m_pins[RM_PUMP] = settings.value("Pump").toByteArray();
    
    for (int i = 0; i < 3; i++) {
        QString value = QString("/sys/class/gpio%1/value").arg(m_pins[i].toInt());
        QFile gpio("/sys/class/gpio/export");
        QFile gpiodir(QString("/sys/class/gpio%1/direction").arg(m_pins[i].toInt()));
        
        if (gpio.open(QIODevice::ReadOnly | QIODevice::Text)) {
            gpio.write(m_pins[i]);
            if (gpiodir.open(QIODevice::WriteOnly | QIODevice::Text)) {
                gpiodir.write(QByteArray("out"));
                QFile *f = new QFile(value);
                if (f->open(QIODevice::ReadOnly | QIODevice::Text)) {
                    m_relays[i] = f;
                    bool state;
                    qDebug() << __PRETTY_FUNCTION__ << ": Instantiated GPIO << " << m_pins[i] << "for index" << i;
                }
            }
        }
    }
#endif
}

RelayManager::~RelayManager()
{

}

void RelayManager::setRelayState(int index, bool value)
{
#if 0
    QFile *f = m_relays[index];
    
    if (f) {
        f->write(QString("%1").arg(value).toUtf8().data());
        emit relayStateChanged(index, value);
    }
#endif
}

bool RelayManager::getRelayState(int index, bool *state)
{
#if 0
    QFile *f = m_relays[index];
    
    if (f) {
        if (f->seek(0)) {
            QByteArray ba = f->readAll();
            if (ba == "1")
                *state = true;
            else
                *state = false;
            
            return true;
        }
    }
#endif
    return false;
}

