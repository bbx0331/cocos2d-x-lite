
#include <string>
#include <functional>
#include <vector>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <sqlite3/sqlite3.h>
#else
#include <sqlite3.h>
#endif

class DBSqlite
{
public:
	static DBSqlite* getInstance()
	{
		static DBSqlite instance;
		return &instance;
	}

	DBSqlite();
	~DBSqlite();

	// 用来创建一个db数据库 db为数据库的名字  
	// 打开数据库  
	void initDB(const char* db);

	// 注册
	void regsiterCallBack(std::function<int(int, std::vector<std::string>, std::vector<std::string>)> callback);

	// 用来执行回调  
	int callFunction(void* para, int n_column, char** column_value, char** column_name);

	// 用来判断表格是否存在  
	// name:表示表名  
	bool existTable(std::string name);

	// 用来创建一个表名为name的表格，创建时会先匹配时否有该表的存在如果存在则不创建  
	// 创建表  
	void createTable(std::string sql, std::string name);

	// 用来删除一张表名为name的表格，删除时会先匹配是否有该表的存在如果不存在则不执行删除操作  
	// 删除表名  
	void deleteTable(std::string sql, std::string name);

	// 用来向表中插入一条数据  
	// 插入一条数据  
	void insertData(std::string sql);

	// 用来向表中删除一条数据  
	// 删除一条数据  
	void deleteData(std::string sql);

	// 用来向表中修改一条数据  
	// 修改一条数据  
	void updateData(std::string sql);

	// 获取一个记录的条数  
	// 获得记录的条数  
	int getDataCount(std::string sql);

	// 读取一条记录的信息  
	// 此方法是查询方法，相当之重要，sender最好是个vector  
	void getDataInfo(std::string sql, void* sender);

	// 关闭打开的数据库  
	void disposeDB();

public:
	// 数据库指针  
	sqlite3* m_pDBSqlite;
	// 错误信息  
	char* m_pErrMsg;
	// 回调函数
	std::function<int(int, std::vector<std::string>, std::vector<std::string>)> m_pCallBack;

};
