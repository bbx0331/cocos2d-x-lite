
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

	// ��������һ��db���ݿ� dbΪ���ݿ������  
	// �����ݿ�  
	void initDB(const char* db);

	// ע��
	void regsiterCallBack(std::function<int(int, std::vector<std::string>, std::vector<std::string>)> callback);

	// ����ִ�лص�  
	int callFunction(void* para, int n_column, char** column_value, char** column_name);

	// �����жϱ���Ƿ����  
	// name:��ʾ����  
	bool existTable(std::string name);

	// ��������һ������Ϊname�ı�񣬴���ʱ����ƥ��ʱ���иñ�Ĵ�����������򲻴���  
	// ������  
	void createTable(std::string sql, std::string name);

	// ����ɾ��һ�ű���Ϊname�ı��ɾ��ʱ����ƥ���Ƿ��иñ�Ĵ��������������ִ��ɾ������  
	// ɾ������  
	void deleteTable(std::string sql, std::string name);

	// ��������в���һ������  
	// ����һ������  
	void insertData(std::string sql);

	// ���������ɾ��һ������  
	// ɾ��һ������  
	void deleteData(std::string sql);

	// ����������޸�һ������  
	// �޸�һ������  
	void updateData(std::string sql);

	// ��ȡһ����¼������  
	// ��ü�¼������  
	int getDataCount(std::string sql);

	// ��ȡһ����¼����Ϣ  
	// �˷����ǲ�ѯ�������൱֮��Ҫ��sender����Ǹ�vector  
	void getDataInfo(std::string sql, void* sender);

	// �رմ򿪵����ݿ�  
	void disposeDB();

public:
	// ���ݿ�ָ��  
	sqlite3* m_pDBSqlite;
	// ������Ϣ  
	char* m_pErrMsg;
	// �ص�����
	std::function<int(int, std::vector<std::string>, std::vector<std::string>)> m_pCallBack;

};
