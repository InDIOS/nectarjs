__NJS_VAR __NJS_Boolean_Result(__NJS_VAR _v)
{
	if (_v.type == NJS::Enum::Type::NUMBER)
		return _v.get().i;
	else if (_v.type == NJS::Enum::Type::BOOLEAN)
		return _v.get().b;
	else if (_v.type == NJS::Enum::Type::STRING)
	{
		if (strlen(_v.get().s->__NJS_VALUE.c_str()) > 0)
			return true;
		else
			return false;
	}
	else if (_v.type == NJS::Enum::Type::ARRAY)
		return true;
	else
		return false;
}

ostream &operator<<(ostream &os, const __NJS_VAR &_v)
{
	switch (_v.type)
	{
	case NJS::Enum::Type::BOOLEAN:
		if (_v.get().b)
			os << "true";
		else
			os << "false";
		break;
	case NJS::Enum::Type::NUMBER:
		os << _v.get().i;
		break;
	case NJS::Enum::Type::DOUBLE:
		os << _v.get().d;
		break;
	case NJS::Enum::Type::STRING:
		os << _v.get().s->__NJS_VALUE;
		break;
	case NJS::Enum::Type::OBJECT:
		os << __NJS_Object_Stringify(_v);
		break;
	case NJS::Enum::Type::ARRAY:
		os << __NJS_Object_Stringify(_v);
		break;
	case NJS::Enum::Type::NATIVE:
		os << "[Native]";
		break;
	case NJS::Enum::Type::ISNAN:
		os << "NaN";
		break;
	case NJS::Enum::Type::FUNCTION:
		os << "[Function]";
		break;
	case NJS::Enum::Type::ISINFINITY:
		os << "Infinity";
		break;
	case NJS::Enum::Type::ISNULL:
		os << "null";
		break;
	default:
		os << "undefined";
		break;
	}
	return os;
}

__NJS_VAR parseInt(__NJS_VAR _str)
{
	if (_str.type == NJS::Enum::Type::STRING)
	{
#ifdef __NJS_ARDUINO
		return __NJS_VAR();
#else
		return __NJS_Create_Number(stoi(_str.get().s->__NJS_VALUE));
#endif
	}
	else
		return __NJS_Create_Undefined();
}

__NJS_VAR __NJS_Log_Console(__NJS_VAR _var)
{
#ifdef __NJS_ARDUINO

#else
	cout << _var;
	cout << endl;
#endif

	return __NJS_VAR();
}

__NJS_VAR __NJS_Object_Keys(__NJS_VAR _var)
{
	if (_var.type != NJS::Enum::Type::OBJECT)
		return 0;
	var _res = __NJS_Create_Array();

	vector<pair<const char *, __NJS_VAR>> *_obj = &_var.get().o->__OBJECT;
	int _j = (*_obj).size();
	for (int _i = 0; _i < _j; _i++)
	{
		__NJS_Object_Set(_i, (*_obj)[_i].first, _res);
	}
	return _res;
}

__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var)
{
	return __NJS_Object_Stringify(_var, true);
}
__NJS_VAR __NJS_Object_Stringify(__NJS_VAR _var, bool _bracket)
{

	NJS::Enum::Type _t = _var.type;

	if (_t == NJS::Enum::Type::UNDEFINED)
		return "undefined";
	else if (_t == NJS::Enum::Type::ISNAN)
		return "NaN";
	else if (_t == NJS::Enum::Type::NUMBER)
		return var("") + _var;
	else if (_t == NJS::Enum::Type::DOUBLE)
		return var("") + _var;
	else if (_t == NJS::Enum::Type::STRING)
		return var("\"") + _var + "\"";
	else if (_t == NJS::Enum::Type::FUNCTION)
		return var("\"") + "[Function]" + "\"";
	else if (_t == NJS::Enum::Type::ARRAY)
	{
		var _res = "";
		vector<__NJS_VAR> *_arr = &_var.get().a->__NJS_VALUE;
		if(_bracket) _res += "[";
		int j = (*_arr).size();
		for (int i = 0; i < j; i++)
		{
			if (i > 0)
				_res += ",";
			_res += __NJS_Object_Stringify((*_arr)[i], _bracket);
		}
		if(_bracket) _res += "]";

		return _res;
	}
	else if (_t == NJS::Enum::Type::OBJECT)
	{
		var _res = "";
		vector<pair<const char *, __NJS_VAR>> *_obj = &_var.get().o->__OBJECT;
		_res = "{";
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			if (_i > 0)
				_res += ", ";
			_res += var("\"") + (*_obj)[_i].first + "\"";
			_res += ":";
			_res += __NJS_Object_Stringify((*_obj)[_i].second);
		}
		_res += "}";
		return _res;
	}
	else
		return "";
}

__NJS_VAR __NJS_Object_Clone(__NJS_VAR _var)
{
	NJS::Enum::Type _t = _var.type;
	switch(_t)
	{
		case NJS::Enum::Type::UNDEFINED:
		case NJS::Enum::Type::ISNAN:
		case NJS::Enum::Type::NUMBER:
		case NJS::Enum::Type::DOUBLE:
		case NJS::Enum::Type::STRING:
		case NJS::Enum::Type::FUNCTION:
			return _var;
		case NJS::Enum::Type::ARRAY:
		{
			var _res = __NJS_Create_Array();
			vector<__NJS_VAR> *_arr = &_var.get().a->__NJS_VALUE;

			int j = (*_arr).size();
			for (int i = 0; i < j; i++)
			{
				__NJS_Object_Set(i, __NJS_Object_Clone((*_arr)[i]), _res);
			}
			return _res;
		}
		case NJS::Enum::Type::OBJECT:
		{
			var _res = __NJS_Create_Object();
			vector<pair<const char *, __NJS_VAR>> *_obj = &_var.get().o->__OBJECT;
			int j = (*_obj).size();
			for (int _i = 0; _i < j; _i++)
			{
				__NJS_Object_Set((*_obj)[_i].first, __NJS_Object_Clone((*_obj)[_i].second), _res);
			}
			return _res;
		}
		default:
			return __NJS_VAR();
	}
}

void __NJS_Object_Construct(__NJS_VAR _this, __NJS_VAR _prototype)
{
	if(_this.type == NJS::Enum::Type::OBJECT && _prototype.type == NJS::Enum::Type::OBJECT)
	{
		vector<pair<const char *, __NJS_VAR>> *_obj = &_prototype.get().o->__OBJECT;
		int j = (*_obj).size();
		for (int _i = 0; _i < j; _i++)
		{
			__NJS_VAR _tmp =  __NJS_Object_Get((*_obj)[_i].first, _this);
			if(_tmp.type == NJS::Enum::Type::UNDEFINED)
			{
				__NJS_Object_Set((*_obj)[_i].first, (*_obj)[_i].second, _this);
			}
		}
	}
	
}


__NJS_VAR __NJS_Create_Object()
{
	__NJS_Class_Object *_obj = new __NJS_Class_Object();
	return __NJS_VAR(_obj);
}

__NJS_VAR __NJS_CREATE_FUNCTION(void *_fn)
{
	return __NJS_VAR(NJS::Enum::Type::FUNCTION, _fn);
}

__NJS_VAR __NJS_Create_Native(void *_native)
{
	return __NJS_VAR(NJS::Enum::Type::UNDEFINED, _native);
}

/*
void* __NJS_Get_Function(__NJS_VAR _fn)
{
  return _fn.get().f;
}
*/

function<var(vector<var>)> *__NJS_Get_Function(__NJS_VAR _v)
{
	return (function<var(vector<var>)> *)_v.get().f->__NJS_VALUE;
}

void *__NJS_Get_Native(__NJS_VAR _native)
{
	return _native.get().f;
}

/*** REDIFINING STD OPERATORS ***/

template <typename t>
t operator+(t _left, const __NJS_VAR &_right)
{
	return _left + (t)_right;
}

template <typename t>
t operator-(t _left, const __NJS_VAR &_right)
{
	return _left - (t)_right;
}

template <typename t>
t operator*(t _left, const __NJS_VAR &_right)
{
	return _left * (t)_right;
}

template <typename t>
t operator/(t _left, const __NJS_VAR &_right)
{
	return _left / (t)_right;
}

template <typename t>
t operator<(t _left, const __NJS_VAR &_right)
{
	return _left / (t)_right;
}

template <typename t>
t operator>(t _left, const __NJS_VAR &_right)
{
	return _left / (t)_right;
}


/*** END REDIFINING STD OPERATORS ***/

__NJS_Create_Lambda(__IMPL_EVAL)
{
	__NJS_Log_Console("eval not implemented, return undefined");
	return var();
});
var eval = __NJS_Create_Function(__IMPL_EVAL);

function<__NJS_VAR(vector<var>)> *__NJS_IS_NAN = new function<__NJS_VAR(vector<var>)>([](vector<var> __NJS_VARARGS) {
	var _test;
	if (__NJS_VARARGS.size() > 0)
		_test = __NJS_VARARGS[0];
	else
		return __NJS_Create_Boolean(0);

	if (_test.type == NJS::Enum::Type::NUMBER || _test.type == NJS::Enum::Type::DOUBLE)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
});

__NJS_VAR isNaN = __NJS_VAR(NJS::Enum::Type::FUNCTION, __NJS_IS_NAN);

__NJS_VAR __NJS_EQUAL_VALUE_AND_TYPE(__NJS_VAR _left, __NJS_VAR _right)
{
	if (_left.type == _right.type && _left == _right)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
}

__NJS_VAR __NJS_NOT_EQUAL_VALUE_AND_TYPE(__NJS_VAR _left, __NJS_VAR _right)
{
	if (_left.type != _right.type || _left != _right)
	{
		return __NJS_Create_Boolean(1);
	}

	return __NJS_Create_Boolean(0);
}