#include "syslog.h"


namespace drive {

BasicDataTable* Syslog::m_faultsTable = nullptr;
BasicDataTable* Syslog::m_warningsTable = nullptr;

///
///
///
Syslog::Syslog()
{
	m_faultsTable = new BasicDataTable(FAULTS.size(), 2, this);
	m_warningsTable = new BasicDataTable(WARNINGS.size(), 2, this);
	
	for (auto i = 0; i < 2; ++i)
	{
		m_faultsTable->setHeader(i, FAULTS_AND_WARNINGS_HEADERS[i]);
		m_warningsTable->setHeader(i, FAULTS_AND_WARNINGS_HEADERS[i]);
	}

	for (auto i = 0; i < m_faultsTable->rowCount(); ++i)
	{
		m_faultsTable->setValue(i, 0, FAULTS[i]);
	}

	for (auto i = 0; i < m_warningsTable->rowCount(); ++i)
	{
		m_warningsTable->setValue(i, 0, WARNINGS[i]);
	}
}








} // namespace drive


