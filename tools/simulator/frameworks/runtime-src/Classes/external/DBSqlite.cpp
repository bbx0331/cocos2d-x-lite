#include "external/DBSqlite.h"
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
		value[i] = column_name[i];
	}

	return m_pCallBack(count, value, name);;
}

// �ص�����  
int loadRecordCB(void * para, int n_column, char ** column_value, char ** column_name)
{
	return DBSqlite::getInstance()->callFunction(para, n_column, column_value, column_name);
}

// �����жϱ���Ƿ����  
// name:��ʾ����  
bool DBSqlite::existTable(std::string name)
{
	if (nullptr != m_pDBSqlite)
	{
		// �жϱ��Ƿ����  
		bool isExisted;
		std::string sqlstr = "select count(type) from sqlite_master where type='table' and name ='" + name + "'";
		int result = sqlite3_exec(m_pDBSqlite, sqlstr.c_str(), loadRecordCB, &isExisted, &m_pErrMsg);
		return isExisted;
	}
	return false;
}

// �����ݿ����ж���Ϊname�ı�ʾ����ڣ�����������򴴽����ű�  
// @ʾ�����string sqlstr = "create table user(id integer,username text,password text)";  
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
// @ʾ�����string sqlstr = " insert into MyTable_1( name ) values ( '������' ) ";  
void DBSqlite::insertData(std::string sql)
{
	int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
	if (SQLITE_OK != result)
	{
		CCLOG("�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, m_pErrMsg);
	}
}

// ɾ������  
// @ʾ�����string sqlstr = "delete from MyTable_1 where ID = 2";  
void DBSqlite::deleteData(std::string sql)
{
	int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
	if (SQLITE_OK != result)
	{
		CCLOG("ɾ����¼ʧ�ܣ�������:%d ������ԭ��:%s\n", result, m_pErrMsg);
	}
}

// �޸�����  
// @ʾ�����string sqlstr = "update MyTable_1 set name='������' where ID = 3"; 
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
