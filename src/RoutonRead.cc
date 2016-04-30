#include "RoutonRead.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <windows.h>

using namespace v8;

Persistent<Function> RoutonRead::constructor;

RoutonRead::RoutonRead(){
}

RoutonRead::~RoutonRead() {
}

static std::string GBKToUTF8(const std::string& strGBK)
{
	static std::string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n); n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}

void RoutonRead::Init(Handle<Object> exports) {
	Isolate* isolate = Isolate::GetCurrent();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "RoutonRead"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "InitComm", DR_InitComm);
	NODE_SET_PROTOTYPE_METHOD(tpl, "CloseComm", DR_CloseComm);
	NODE_SET_PROTOTYPE_METHOD(tpl, "Authenticate", DR_Authenticate);
	NODE_SET_PROTOTYPE_METHOD(tpl, "ReadBaseInfos", DR_ReadBaseInfos);
	NODE_SET_PROTOTYPE_METHOD(tpl, "ShutDownAntenna", DR_Routon_ShutDownAntenna);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "RoutonRead"),
		tpl->GetFunction());
}

void RoutonRead::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.IsConstructCall()) {
		// Invoked as constructor: `new MyObject(...)`

		RoutonRead* obj = new RoutonRead();
		obj->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	}
	else {
		// Invoked as plain function `MyObject(...)`, turn into construct call.
		const int argc = 1;
		Local<Value> argv[argc] = { args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

void RoutonRead::DR_InitComm(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int iPort = args[0]->Int32Value();
	int result = InitComm(iPort);
	args.GetReturnValue().Set(Number::New(isolate, result));
}

void RoutonRead::DR_CloseComm(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int result = CloseComm();
	args.GetReturnValue().Set(Number::New(isolate, result));
}

void RoutonRead::DR_Routon_ShutDownAntenna(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int result = Routon_ShutDownAntenna();
	args.GetReturnValue().Set(Number::New(isolate, result));
}

void RoutonRead::DR_Authenticate(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	int result = Authenticate();
	args.GetReturnValue().Set(Number::New(isolate, result));
}

void RoutonRead::DR_ReadBaseInfos(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	char* name = new char[31];//����
	char* gender = new char[3];//�Ա�
	char* folk = new char[10];//����
	char* birthDay = new char[9];//����
	char* code = new char[19];//���֤����
	char* address = new char[71];//��ַ
	char* agency = new char[31];//ǩ֤����
	char* expireStart = new char[9];//��Ч����ʼ����
	char* expireEnd = new char[9];//��Ч�ڽ�������

	int result = ReadBaseInfos(name, gender, folk, birthDay, code, address, agency, expireStart, expireEnd);
	if (result)
	{
		Local<Object> readInfo = Object::New(isolate);
		readInfo->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, GBKToUTF8(name).c_str()));
		readInfo->Set(String::NewFromUtf8(isolate, "gender"), String::NewFromUtf8(isolate, GBKToUTF8(gender).c_str()));
		readInfo->Set(String::NewFromUtf8(isolate, "folk"), String::NewFromUtf8(isolate, GBKToUTF8(folk).c_str()));
		readInfo->Set(String::NewFromUtf8(isolate, "birthDay"), String::NewFromUtf8(isolate, birthDay));
		readInfo->Set(String::NewFromUtf8(isolate, "code"), String::NewFromUtf8(isolate, code));
		readInfo->Set(String::NewFromUtf8(isolate, "address"), String::NewFromUtf8(isolate, GBKToUTF8(address).c_str()));
		readInfo->Set(String::NewFromUtf8(isolate, "agency"), String::NewFromUtf8(isolate, GBKToUTF8(agency).c_str()));
		readInfo->Set(String::NewFromUtf8(isolate, "expireStart"), String::NewFromUtf8(isolate, expireStart));
		readInfo->Set(String::NewFromUtf8(isolate, "expireEnd"), String::NewFromUtf8(isolate, expireEnd));

		delete[]name;
		delete[]gender;
		delete[]folk;
		delete[]birthDay;
		delete[]code;
		delete[]address;
		delete[]agency;
		delete[]expireStart;
		delete[]expireEnd;
		args.GetReturnValue().Set(readInfo);
	}
	else{
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, 0));
	}
}

void InitAll(Handle<Object> exports) {
	RoutonRead::Init(exports);
}

NODE_MODULE(RoutonRead, InitAll)