#include "scripting/js-bindings/auto/jsb_external_sqlite_auto.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "external/sqlite3/DBSqlite.h"

se::Object* __jsb_DBSqlite_proto = nullptr;
se::Class* __jsb_DBSqlite_class = nullptr;

static bool js_external_sqlite_DBSqlite_getDataInfo(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_getDataInfo : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        void* arg1 = nullptr;
        ok &= seval_to_std_string(args[0], &arg0);
        #pragma warning NO CONVERSION TO NATIVE FOR void*
        ok = false;
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_getDataInfo : Error processing arguments");
        cobj->getDataInfo(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_getDataInfo)

static bool js_external_sqlite_DBSqlite_deleteTable(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_deleteTable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_deleteTable : Error processing arguments");
        cobj->deleteTable(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_deleteTable)

static bool js_external_sqlite_DBSqlite_existTable(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_existTable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_existTable : Error processing arguments");
        bool result = cobj->existTable(arg0);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_existTable : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_existTable)

static bool js_external_sqlite_DBSqlite_insertData(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_insertData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_insertData : Error processing arguments");
        cobj->insertData(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_insertData)

static bool js_external_sqlite_DBSqlite_updateData(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_updateData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_updateData : Error processing arguments");
        cobj->updateData(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_updateData)

static bool js_external_sqlite_DBSqlite_createTable(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_createTable : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_createTable : Error processing arguments");
        cobj->createTable(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_createTable)

static bool js_external_sqlite_DBSqlite_getDataCount(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_getDataCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_getDataCount : Error processing arguments");
        int result = cobj->getDataCount(arg0);
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_getDataCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_getDataCount)

static bool js_external_sqlite_DBSqlite_initDB(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_initDB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= seval_to_std_string(args[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_initDB : Error processing arguments");
        cobj->initDB(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_initDB)

static bool js_external_sqlite_DBSqlite_disposeDB(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_disposeDB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->disposeDB();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_disposeDB)

static bool js_external_sqlite_DBSqlite_deleteData(se::State& s)
{
    DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_deleteData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_deleteData : Error processing arguments");
        cobj->deleteData(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_deleteData)

static bool js_external_sqlite_DBSqlite_getInstance(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        DBSqlite* result = DBSqlite::getInstance();
        ok &= native_ptr_to_seval<DBSqlite>((DBSqlite*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_getInstance : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_getInstance)




bool js_register_external_sqlite_DBSqlite(se::Object* obj)
{
    auto cls = se::Class::create("DBSqlite", obj, nullptr, nullptr);

    cls->defineFunction("getDataInfo", _SE(js_external_sqlite_DBSqlite_getDataInfo));
    cls->defineFunction("deleteTable", _SE(js_external_sqlite_DBSqlite_deleteTable));
    cls->defineFunction("existTable", _SE(js_external_sqlite_DBSqlite_existTable));
    cls->defineFunction("insertData", _SE(js_external_sqlite_DBSqlite_insertData));
    cls->defineFunction("updateData", _SE(js_external_sqlite_DBSqlite_updateData));
    cls->defineFunction("createTable", _SE(js_external_sqlite_DBSqlite_createTable));
    cls->defineFunction("getDataCount", _SE(js_external_sqlite_DBSqlite_getDataCount));
    cls->defineFunction("initDB", _SE(js_external_sqlite_DBSqlite_initDB));
    cls->defineFunction("disposeDB", _SE(js_external_sqlite_DBSqlite_disposeDB));
    cls->defineFunction("deleteData", _SE(js_external_sqlite_DBSqlite_deleteData));
    cls->defineStaticFunction("getInstance", _SE(js_external_sqlite_DBSqlite_getInstance));
    cls->install();
    JSBClassType::registerClass<DBSqlite>(cls);

    __jsb_DBSqlite_proto = cls->getProto();
    __jsb_DBSqlite_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_external_sqlite(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("db", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("db", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_external_sqlite_DBSqlite(ns);
    return true;
}

