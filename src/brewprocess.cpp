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

#include "brewprocess.h"

BrewProcess::BrewProcess(QObject *parent) : QObject(parent)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "RoboBrew", "RoboBrew");
    QString rulesFileName = settings.value("rulesfile").toString();
    m_metric = settings.value("metric").toBool();
    parseRulesFile(rulesFileName);
    m_segmentTimer = new QTimer(this);
    connect(m_segmentTimer, SIGNAL(timeout()), this, SLOT(timeout()));
}

BrewProcess::BrewProcess(QString rulesFileName, QObject *parent) : QObject(parent)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "RoboBrew", "RoboBrew");
    m_metric = settings.value("metric").toBool();
    parseRulesFile(rulesFileName);
    m_segmentTimer = new QTimer(this);
    connect(m_segmentTimer, SIGNAL(timeout()), this, SLOT(timeout()));
}

BrewProcess::~BrewProcess() = default;

void BrewProcess::parseRulesFile(QString fn)
{
    QFile f(fn);
    
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_rules = QJsonDocument::fromJson(f.readAll());
    }
    
    if (m_rules.isEmpty() || m_rules.isNull()) {
        qWarning() << __PRETTY_FUNCTION__ << ": Error retrieving rules from" << fn;
    }
    if (m_rules.isObject()) {
        QJsonObject jobj = m_rules.object();
        if (jobj.contains("doughin")) {
            parseSegment("Dough In", jobj["doughin"].toObject());
        }
        if (jobj.contains("acidrest")) {
            parseSegment("Acid Rest", jobj["acidrest"].toObject());
        }
        if (jobj.contains("proteinrest")) {
            parseSegment("Protein Rest", jobj["proteinrest"].toObject());            
        }
        if (jobj.contains("mashin")) {
            parseSegment("Mash In", jobj["mashin"].toObject());          
        }
        if (jobj.contains("mash")) {
            parseSegment("Mash", jobj["mash"].toObject());          
        }
        if (jobj.contains("mashout")) {
            parseSegment("Mash Out", jobj["mashout"].toObject());          
        }
        if (jobj.contains("boil")) {
            parseSegment("Boil", jobj["boil"].toObject());          
        }
    }
}

void BrewProcess::parseSegment(QString name, QJsonObject obj)
{
    struct BrewStep bs;
    
    if (obj.contains("temperature")) {
        bs.temp = obj["temperature"].toInt();
    }
    if (obj.contains("time")) {
        int minutes = obj["time"].toInt();
        bs.time = minutes * 60 * 1000;  // Convert to millis
    }
    bs.name = name;
    m_segments.enqueue(bs);
}

void BrewProcess::execute()
{
    struct BrewStep bs;
    
    if (m_segments.size()) {
        bs = m_segments.dequeue();
        m_segmentTimer->setInterval(bs.time);
        m_segmentTimer->start();
        emit newSegment(bs);
    }
}

void BrewProcess::timeout()
{
    struct BrewStep bs;
    
    if (m_segments.size()) {
        bs = m_segments.dequeue();
        m_segmentTimer->stop();
        m_segmentTimer->setInterval(bs.time);
        m_segmentTimer->start();
        emit newSegment(bs);
    }
}

