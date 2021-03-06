#include "systemmonitor.h"

systemMonitor::systemMonitor(DBManager *db, int frequency)
{
    m_DB = db;
    m_frequency = frequency;
}

systemMonitor::~systemMonitor()
{
    systemMonitor::quit();
}

int systemMonitor::exec()
{
    while(1)
    {
        int numberOfProcess = getNumberOfProcess(); //ToDo
        m_DB->writeNumberOfProcess(numberOfProcess);

        int numberOfThread = getNumberOfThread(); //ToDo
        m_DB->writeNumberOfThread(numberOfThread);

        int usedMemory = getUsedMemory(); //ToDo
        m_DB->writeUsedMemory(usedMemory);

        int cpuUsage = getCpuUsage(); //ToDo
        m_DB->writeCpuLoad(cpuUsage);

        wait(1000/m_frequency); //Wait to keep the frequency requested

    }
}
