/*
 * RoboBrew
 * robobrew.h
 * Copyright Peter Buelow (goballstate@gmail.com)
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

#ifndef BREWPROCESS_H
#define BREWPROCESS_H

#include <QtCore/QtCore>

#define BP_FARENHEIT    0
#define BP_CELSIUS      1

struct BrewStep {
    int time;
    int temp;
    QString name;
};

class BrewProcess : public QObject
{
    Q_OBJECT
public:
    explicit BrewProcess(QObject *parent = nullptr);
    BrewProcess(QString, QObject *parent = nullptr);
    ~BrewProcess() override;
    
    void execute();
    bool isMetric() { return m_metric; }

protected slots:
    void timeout();
    
signals:
    void newSegment(struct BrewStep);
    
private:
    void parseRulesFile(QString);
    void parseSegment(QString, QJsonObject);
    
    QJsonDocument m_rules;
    QTimer *m_segmentTimer;
    QQueue<struct BrewStep> m_segments;
    bool m_metric;
};

#endif // BREWPROCESS_H
