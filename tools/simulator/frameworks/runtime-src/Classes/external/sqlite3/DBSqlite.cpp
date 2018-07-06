#include "sqlite3/DBSqlite.h"
#include "cocos2d.h"

DBSqlite::DBSqlite()
{

}

DBSqlite::~DBSqlite()
{

}

// �������ݿ� 
void DBSqlite::initDB(const char* db)
{
	// ��һ�����ݿ⣬��������ݿⲻ���ڣ��򴴽�һ�����ݿ��ļ�  
	int result = sqlite3_open(db, &m_pDBSqlite);
	if (SQLITE_OK != result)
	{
		CCLOG("�����ݿ�ʧ�ܣ�������:%d ������ԭ��:%s\n", result, sqlite3_errstr(result));
	}
}

void DBSqlite::regsiterCallBack(std::function<int(int, std::vector<std::string>, std::vector<std::string>)> callback)
{
	m_pCallBack = callback;
}

int DBSqlite::callFunction(void* para, int count, char** column_value, char** column_name)
{
	if (nullptr == m_pCallBack)
	{
		return 0;
	}

	std::vector<std::string> value;
	value.resize(count);
	for (int i = 0; i < count; i++)
	{
		value[i] = column_value[i];
	}

	std::vector<std::string> name;
	name.resize(count);
	for (int i = 0; i < count; i++)
	{
		name[i] = column_name[i];
	}

	return m_pCallBack(count, value, name);
}

// �ص�����  
int loadRecordCB(void * para, int n_column, char ** column_value, char ** column_name)
{
	return DBSqlite::getInstance()->callFunction(para, n_column, column_value, column_name);
}

// �ص�����  
int existTableCB(void * para, int n_column, char ** column_value, char ** column_name)
{
	if (1 == n_column)
	{
		int exist = atoi(*(column_value));
		if (nullptr != para)
		{
			int* res = (int*)para;
			*res = exist;
		}
	}
	return 0;
}

// �����жϱ���Ƿ����  
// name:��ʾ����  
bool DBSqlite::existTable(std::string name)
{
	if (nullptr != m_pDBSqlite)
	{
		// �жϱ��Ƿ����  
		std::string sqlstr = "select count(*) from sqlite_master where type = 'table' and name = '" + name + "';";
		int count = 0;
		int result = sqlite3_exec(m_pDBSqlite, sqlstr.c_str(), existTableCB, &count, &m_pErrMsg);
		if (SQLITE_OK == result)
		{
			return count > 0;
		}
	}
	return false;
}

// �����ݿ����ж���Ϊname�ı�ʾ����ڣ�����������򴴽����ű�  
// @ʾ�����string sqlstr = "create table user (id integer, username text, password text)";  
void DBSqlite::createTable(std::string sql, std::string name)
{
	if (!existTable(name))
	{
		// ����������IDΪ���������Զ�����  
		int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
		if (SQLITE_OK != result)
		{
			CCLOG("������ʧ�ܣ�������:%d ������ԭ��:%s\n", result, m_pErrMsg);
		}
	}
}

// ɾ�����  
// @ʾ�����string sqlstr = "drop table name";  
void DBSqlite::deleteTable(std::string sql, std::string name)
{
	if (existTable(name))
	{
		int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
		if (SQLITE_OK != result)
		{
			CCLOG("ɾ����ʧ�ܣ�������:%d ������ԭ��:%s\n", result, m_pErrMsg);
		}
	}
}

// ��������  
// @ʾ�����string sqlstr = "insert into table_name values ('������')";  
void DBSqlite::insertData(std::string sql)
{
	int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
	if (SQLITE_OK != result)
	{
		CCLOG("�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, m_pErrMsg);
	}
}

// ɾ������  
// @ʾ�����string sqlstr = "delete from table_name where ID = 2";  
void DBSqlite::deleteData(std::string sql)
{
	int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
	if (SQLITE_OK != result)
	{
		CCLOG("ɾ����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, m_pErrMsg);
	}
}

// �޸�����  
// @ʾ�����string sqlstr = "update table_name set name = '������' where ID = 3"; 
void DBSqlite::updateData(std::string sql)
{
	int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
	if (SQLITE_OK != result)
	{
		CCLOG("�޸ļ�¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, m_pErrMsg);
	}
}

// ��ȡ��¼������  
// @ʾ�����string sqlstr = "select count(*) from user";  
// @ʾ�����  ȡ�ñ���ֶε����string sqlstr = "select * from user";  
int DBSqlite::getDataCount(std::string sql)
{
	int count = 0;
	sqlite3_exec(m_pDBSqlite, sql.c_str(), loadRecordCB, &count, &m_pErrMsg);
	return count;
}

// ��ȡһ����¼����Ϣ  
/*
*  �˷����ǲ�ѯ�������൱֮��Ҫ��pSender����Ǹ�vector 
*/
void DBSqlite::getDataInfo(std::string sql, void* sender)
{
	sqlite3_exec(m_pDBSqlite, sql.c_str(), loadRecordCB, sender, &m_pErrMsg);
}

// �رմ򿪵����ݿ�  
void DBSqlite::disposeDB()
{
	sqlite3_close(m_pDBSqlite);
}
