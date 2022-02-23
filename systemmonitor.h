#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include <QThread>
#include "dbmanager.h"


class systemMonitor : public QThread
{
    Q_OBJECT
public:
    systemMonitor(DBManager *db, int frequency);
    ~systemMonitor();

protected:
    int exec();



private:
    DBManager *m_DB;
    int m_frequency;
};

#endif // SYSTEMMONITOR_H
