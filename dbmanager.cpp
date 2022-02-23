#include "dbmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QString>

DBManager::DBManager(const QString &path)
{
     m_db = QSqlDatabase::addDatabase("QSQLITE");
     m_db.setDatabaseName(path);
     if (!m_db.open())
     {
        qDebug() << "Error: connection with database failed";
     }
     else
     {
        qDebug() << "Database: connection ok";
     }

     QSqlQuery query;
}

DBManager::~DBManager()
{
    m_db.close();
}

bool DBManager::writeNumberOfProcess(int numberOfProcess)
{
    bool success = false;

    QSqlQuery query;

    qint64 timestamp = QDateTime::currentSecsSinceEpoch();

    query.prepare("INSERT INTO process (timestamp, numberOfProcess) VALUES (:timestamp, :numberOfProcess)");
    query.bindValue(":timestamp", QString::number(timestamp));
    query.bindValue(":name", numberOfProcess);

    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "addPerson error:"
                  << query.lastError();
    }

    return success;
}

bool DBManager::writeNumberOfThread(int numberOfThread)
{
    bool success = false;

    QSqlQuery query;

    qint64 timestamp = QDateTime::currentSecsSinceEpoch();

    query.prepare("INSERT INTO thread (timestamp, numberOfThread) VALUES (:timestamp, :numberOfThread)");
    query.bindValue(":timestamp", QString::number(timestamp));
    query.bindValue(":name", numberOfThread);

    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "addPerson error:"
                  << query.lastError();
    }

    return success;
}

bool DBManager::writeUsedMemory(int usedMemory)
{
    bool success = false;

    QSqlQuery query;

    qint64 timestamp = QDateTime::currentSecsSinceEpoch();

    query.prepare("INSERT INTO memory (timestamp, usedMemory) VALUES (:timestamp, :usedMemory)");
    query.bindValue(":timestamp", QString::number(timestamp));
    query.bindValue(":name", usedMemory);

    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "addPerson error:"
                  << query.lastError();
    }

    return success;
}

bool DBManager::writeCpuLoad(int cpuLoad)
{
    bool success = false;

    if(cpuLoad > 100)
    {
        return success;
    }

    QSqlQuery query;

    qint64 timestamp = QDateTime::currentSecsSinceEpoch();

    query.prepare("INSERT INTO cpu (timestamp, cpuLoad) VALUES (:timestamp, :cpuLoad)");
    query.bindValue(":timestamp", QString::number(timestamp));
    query.bindValue(":name", cpuLoad);

    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "addPerson error:"
                  << query.lastError();
    }

    return success;
}

QPair<qint64, int> DBManager::getMaxThread()
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MAX(numberOfThread) FROM thread");

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("numberOfThread").toInt();
    }
    return retval;
}

QPair<qint64, int> DBManager::getMinThread()
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MIN(numberOfThread) FROM thread");

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("numberOfThread").toInt();
    }
    return retval;
}

QPair<qint64, int> DBManager::getMaxCpuLoad()
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MAX(cpuLoad) FROM cpu");

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("cpuLoad").toInt();
    }
    return retval;
}

QPair<qint64, int> DBManager::getMinCpuLoad()
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MIN(cpuLoad) FROM cpu");

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("cpuLoad").toInt();
    }
    return retval;
}

QPair<qint64, int> DBManager::getMaxMemory()
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MAX(usedMemory) FROM memory");

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("usedMemory").toInt();
    }
    return retval;
}

QPair<qint64, int> DBManager::getMinMemory()
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MIN(usedMemory) FROM memory");

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("usedMemory").toInt();
    }
    return retval;
}

QPair<qint64, int> DBManager::getMaxCpuLoad(QPair<quint64, quint64> interval)
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MAX(cpuLoad) FROM cpu WHERE timestamp < :timestampMax AND timestamp > :timestampMin");
    query.bindValue(":timestampMax", interval.second);
    query.bindValue(":timestampMin", interval.first);

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("cpuLoad").toInt();
    }
    return retval;
}

QPair<qint64, int> DBManager::getMinCpuLoad(QPair<quint64, quint64> interval)
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MIN(cpuLoad) FROM cpu WHERE timestamp < :timestampMax AND timestamp > :timestampMin");
    query.bindValue(":timestampMax", interval.second);
    query.bindValue(":timestampMin", interval.first);

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("cpuLoad").toInt();
    }
    return retval;
}

QPair<qint64, int> DBManager::getMaxMemory(QPair<quint64, quint64> interval)
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MAX(usedMemory) FROM memory WHERE timestamp < :timestampMax AND timestamp > :timestampMin");
    query.bindValue(":timestampMax", interval.second);
    query.bindValue(":timestampMin", interval.first);

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("usedMemory").toInt();
    }
    return retval;
}

QPair<qint64, int> DBManager::getMinMemory(QPair<quint64, quint64> interval)
{
    QSqlQuery query;
    QPair<qint64, int>retval(0,0);

    query.prepare("SELECT MIN(usedMemory) FROM memory WHERE timestamp < :timestampMax AND timestamp > :timestampMin");
    query.bindValue(":timestampMax", interval.second);
    query.bindValue(":timestampMin", interval.first);

    if(query.next())
    {
        retval.first = query.value("timestamp").toLongLong();
        retval.second = query.value("usedMemory").toInt();
    }
    return retval;
}
