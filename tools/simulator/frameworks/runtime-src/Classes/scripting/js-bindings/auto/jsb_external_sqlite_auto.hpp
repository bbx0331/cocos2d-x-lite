#pragma once
#include "base/ccConfig.h"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"

extern se::Object* __jsb_DBSqlite_proto;
extern se::Class* __jsb_DBSqlite_class;

bool js_register_DBSqlite(se::Object* obj);
bool register_all_external_sqlite(se::Object* obj);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_getDataInfo);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_deleteTable);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_existTable);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_insertData);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_updateData);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_createTable);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_getDataCount);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_initDB);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_disposeDB);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_deleteData);
SE_DECLARE_FUNC(js_external_sqlite_DBSqlite_getInstance);

