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

#include "brewprocess.h"

BrewProcess::BrewProcess(QObject *parent) : QObject(parent)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "RoboBrew", "RoboBrew");
    QString rulesFileName = settings.value("rulesfile").toString();
    parseRulesFile(rulesFileName);
}

BrewProcess::BrewProcess(QString rulesFileName, QObject *parent) : QObject(parent)
{
    parseRulesFile(rulesFileName);
}

BrewProcess::~BrewProcess() = default;

void BrewProcess::parseRulesFile(QString fn)
{
    QFile f(fn);
    
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_rules = QJsonDocument::fromJson(f.readAll());
    }
    
    if (!m_rules.isEmpty() || !m_rules.isNull()) {
        
    }
}

void BrewProcess::execute()
{
    
}

