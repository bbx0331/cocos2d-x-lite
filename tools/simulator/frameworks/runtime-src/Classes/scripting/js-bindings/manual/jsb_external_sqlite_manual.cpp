
#include "jsb_external_sqlite_manual.hpp"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_global.h"
#include "cocos/scripting/js-bindings/manual/jsb_helper.hpp"
#include "scripting/js-bindings/auto/jsb_external_sqlite_auto.hpp"
#include "external/DBSqlite.h"

using namespace cocos2d;

static bool jsb_external_sqlite_empty_func(se::State& s)
{
    return true;
}
SE_BIND_FUNC(jsb_external_sqlite_empty_func)

static bool js_external_sqlite_DBSqlite_regsiterCallBack(se::State& s)
{
	DBSqlite* cobj = (DBSqlite*)s.nativeThisObject();
	SE_PRECONDITION2(cobj, false, "js_external_sqlite_DBSqlite_regsiterCallBack : Invalid Native Object");
	const auto& args = s.args();
	size_t argc = args.size();
	CC_UNUSED bool ok = true;
	if (argc == 1) {
		std::function<int(int, std::vector<std::string>, std::vector<std::string>)> arg0;
		do {
			if (args[0].isObject() && args[0].toObject()->isFunction())
			{
				se::Value jsThis(s.thisObject());
				se::Value jsFunc(args[0]);
				jsThis.toObject()->attachObject(jsFunc.toObject());
				auto lambda = [=](int count, std::vector<std::string> value, std::vector<std::string> name) -> int {
					se::ScriptEngine::getInstance()->clearException();
					se::AutoHandleScope hs;

					CC_UNUSED bool ok = true;
					se::ValueArray args;
					args.resize(3);
					ok &= int32_to_seval(count, &args[0]);
					ok &= std_vector_string_to_seval(value, &args[1]);
					ok &= std_vector_string_to_seval(name, &args[2]);

					se::Value rval;
					se::Object* thisObj = jsThis.isObject() ? jsThis.toObject() : nullptr;
					se::Object* funcObj = jsFunc.toObject();

					bool succeed = funcObj->call(args, thisObj, &rval);
					if (!succeed) {
						se::ScriptEngine::getInstance()->clearException();
					}
					return 0;// rval.toInt32();
				};
				arg0 = lambda;
			}
			else
			{
				arg0 = nullptr;
			}
		} while (false)
			;
		SE_PRECONDITION2(ok, false, "js_external_sqlite_DBSqlite_regsiterCallBack : Error processing arguments");
		cobj->regsiterCallBack(arg0);
		return true;
	}
	SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
	return false;
}
SE_BIND_FUNC(js_external_sqlite_DBSqlite_regsiterCallBack)

static bool register_sqlite_manual(se::Object* obj)
{
	__jsb_DBSqlite_proto->defineFunction("regsiterCallBack", _SE(js_external_sqlite_DBSqlite_regsiterCallBack));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_external_sqlite_manual(se::Object* obj)
{
	register_sqlite_manual(obj);

    return true;
}

