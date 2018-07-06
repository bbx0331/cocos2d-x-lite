#include "sqlite3/DBSqlite.h"
#include "cocos2d.h"

DBSqlite::DBSqlite()
{

}

DBSqlite::~DBSqlite()
{

}

// 创建数据库 
void DBSqlite::initDB(const char* db)
{
	// 打开一个数据库，如果该数据库不存在，则创建一个数据库文件  
	int result = sqlite3_open(db, &m_pDBSqlite);
	if (SQLITE_OK != result)
	{
		CCLOG("打开数据库失败，错误码:%d ，错误原因:%s\n", result, sqlite3_errstr(result));
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

// 回调函数  
int loadRecordCB(void * para, int n_column, char ** column_value, char ** column_name)
{
	return DBSqlite::getInstance()->callFunction(para, n_column, column_value, column_name);
}

// 回调函数  
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

// 用来判断表格是否存在  
// name:表示表名  
bool DBSqlite::existTable(std::string name)
{
	if (nullptr != m_pDBSqlite)
	{
		// 判断表是否存在  
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

// 在数据库中判断名为name的表示否存在，如果不存在则创建这张表  
// @示例语句string sqlstr = "create table user (id integer, username text, password text)";  
void DBSqlite::createTable(std::string sql, std::string name)
{
	if (!existTable(name))
	{
		// 创建表，设置ID为主键，且自动增加  
		int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
		if (SQLITE_OK != result)
		{
			CCLOG("创建表失败，错误码:%d ，错误原因:%s\n", result, m_pErrMsg);
		}
	}
}

// 删除表格  
// @示例语句string sqlstr = "drop table name";  
void DBSqlite::deleteTable(std::string sql, std::string name)
{
	if (existTable(name))
	{
		int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
		if (SQLITE_OK != result)
		{
			CCLOG("删除表失败，错误码:%d ，错误原因:%s\n", result, m_pErrMsg);
		}
	}
}

// 插入数据  
// @示例语句string sqlstr = "insert into table_name values ('擎天柱')";  
void DBSqlite::insertData(std::string sql)
{
	int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
	if (SQLITE_OK != result)
	{
		CCLOG("插入记录失败，错误码:%d ，错误原因:%s\n", result, m_pErrMsg);
	}
}

// 删除数据  
// @示例语句string sqlstr = "delete from table_name where ID = 2";  
void DBSqlite::deleteData(std::string sql)
{
	int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
	if (SQLITE_OK != result)
	{
		CCLOG("删除记录失败，错误码:%d ，错误原因:%s\n", result, m_pErrMsg);
	}
}

// 修改数据  
// @示例语句string sqlstr = "update table_name set name = '威震天' where ID = 3"; 
void DBSqlite::updateData(std::string sql)
{
	int result = sqlite3_exec(m_pDBSqlite, sql.c_str(), NULL, NULL, &m_pErrMsg);
	if (SQLITE_OK != result)
	{
		CCLOG("修改记录失败，错误码:%d ，错误原因:%s\n", result, m_pErrMsg);
	}
}

// 获取记录的条数  
// @示例语句string sqlstr = "select count(*) from user";  
// @示例语句  取得表格字段的语句string sqlstr = "select * from user";  
int DBSqlite::getDataCount(std::string sql)
{
	int count = 0;
	sqlite3_exec(m_pDBSqlite, sql.c_str(), loadRecordCB, &count, &m_pErrMsg);
	return count;
}

// 读取一条记录的信息  
/*
*  此方法是查询方法，相当之重要，pSender最好是个vector 
*/
void DBSqlite::getDataInfo(std::string sql, void* sender)
{
	sqlite3_exec(m_pDBSqlite, sql.c_str(), loadRecordCB, sender, &m_pErrMsg);
}

// 关闭打开的数据库  
void DBSqlite::disposeDB()
{
	sqlite3_close(m_pDBSqlite);
}
