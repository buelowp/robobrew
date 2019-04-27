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

#ifndef RELAYMANAGER_H
#define RELAYMANAGER_H

#include <QtCore/QtCore>
#include <wiringPi.h>

/**
 * We cheat, but the SB components relay I use has pins
 * 15->1
 * 13->2
 * 11->3
 * 7->4
 * 
 * It may be different for you, so define them in the settings file
 * 
 * Note that you must specify the GPIO in the settings, not the pin #
 * So, 15 == 22
 * 13 == 27
 * 11 == 17
 * 7 == 4
 */

#define RM_INNER_COIL       0
#define RM_OUTER_COIL       1
#define RM_PUMP             2

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

class RelayManager : public QObject
{
    Q_OBJECT
public:
    RelayManager(QObject *parent = nullptr);
    ~RelayManager();

    int getRelayState(int);
    
public slots:
    void setRelayState(int, int);
    void timeout();
    
signals:
    void relayStateChanged(int, int);
    
private:
    QMap<int, int> m_relays;
    QMap<int, int> m_state;
    QTimer  *m_timer;
};

#endif // RELAYMANAGER_H
