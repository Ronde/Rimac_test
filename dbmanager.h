#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QPair>


class DBManager
{
public:
    DBManager(const QString &path);
    ~DBManager();
    bool writeNumberOfProcess(int numberOfProcess);
    bool writeNumberOfThread(int numberOfThread);
    bool writeUsedMemory(int usedMemory);
    bool writeCpuLoad(int cpuLoad);

    QPair<qint64, int>getMaxThread();
    QPair<qint64, int>getMinThread();
    QPair<qint64, int>getMaxCpuLoad();
    QPair<qint64, int>getMinCpuLoad();
    QPair<qint64, int>getMaxMemory();
    QPair<qint64, int>getMinMemory();
    QPair<qint64, int>getMaxCpuLoad(QPair<quint64, quint64> interval);
    QPair<qint64, int>getMinCpuLoad(QPair<quint64, quint64> interval);
    QPair<qint64, int>getMaxMemory(QPair<quint64, quint64> interval);
    QPair<qint64, int>getMinMemory(QPair<quint64, quint64> interval);


private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

