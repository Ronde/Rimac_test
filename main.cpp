#include <iostream>
#include "dbmanager.h"
#include "systemmonitor.h"
#include <QSettings>

using namespace std;

int main()
{
    DBManager m_DB("db.db");
    QSettings m_setting("setting.ini", QSettings::IniFormat);

    int frequency = m_setting.value("frequency", 10).toInt();

    systemMonitor m_sm(&m_DB, frequency);

    m_sm.start();

    return 0;
}
