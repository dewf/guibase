#include "core/NativeImplCore.h"
#include <cstdint>

#ifdef GUIBASESERVER_EXPORTS
#define GUIBASESERVER_API __declspec(dllexport)
#else
#define GUIBASESERVER_API __declspec(dllimport)
#endif

extern "C" {
	GUIBASESERVER_API int nativeImplInit(
		niClientFuncExec clientFuncExec,
		niClientMethodExec clientMethodExec,
		niClientResourceRelease clientResourceRelease,
		niClientClearSafetyArea clientClearSafetyArea
	);
	GUIBASESERVER_API void nativeImplShutdown();

	GUIBASESERVER_API ni_ModuleRef getModule(const char* name);
	GUIBASESERVER_API ni_ModuleMethodRef getModuleMethod(ni_ModuleRef m, const char* name);
	GUIBASESERVER_API ni_InterfaceRef getInterface(ni_ModuleRef m, const char* name);
	GUIBASESERVER_API ni_InterfaceMethodRef getInterfaceMethod(ni_InterfaceRef iface, const char* name);
	GUIBASESERVER_API ni_ExceptionRef getException(ni_ModuleRef m, const char* name);
	GUIBASESERVER_API void pushModuleConstants(ni_ModuleRef m);

	GUIBASESERVER_API void invokeModuleMethod(ni_ModuleMethodRef method);
	GUIBASESERVER_API ni_ExceptionRef invokeModuleMethodWithExceptions(ni_ModuleMethodRef method);

	GUIBASESERVER_API void pushPtr(void* value);
	GUIBASESERVER_API void* popPtr();
	GUIBASESERVER_API void pushPtrArray(void** values, size_t count);
	GUIBASESERVER_API void popPtrArray(void*** values, size_t* count);

	GUIBASESERVER_API void pushSizeT(size_t value);
	GUIBASESERVER_API size_t popSizeT();
	GUIBASESERVER_API void pushSizeTArray(size_t* values, size_t count);
	GUIBASESERVER_API void popSizeTArray(size_t** values, size_t* count);

	GUIBASESERVER_API void pushBool(bool value);
	GUIBASESERVER_API bool popBool();
	GUIBASESERVER_API void pushBoolArray(bool* values, size_t count);
	GUIBASESERVER_API void popBoolArray(bool** values, size_t* count);

	GUIBASESERVER_API void pushInt8(int8_t x);
	GUIBASESERVER_API int8_t popInt8();
	GUIBASESERVER_API void pushInt8Array(int8_t* values, size_t count);
	GUIBASESERVER_API void popInt8Array(int8_t** values, size_t* count);

	GUIBASESERVER_API void pushUInt8(uint8_t x);
	GUIBASESERVER_API uint8_t popUInt8();
	GUIBASESERVER_API void pushUInt8Array(uint8_t* values, size_t count);
	GUIBASESERVER_API void popUInt8Array(uint8_t** values, size_t* count);

	GUIBASESERVER_API void pushInt16(int16_t x);
	GUIBASESERVER_API int16_t popInt16();
	GUIBASESERVER_API void pushInt16Array(int16_t* values, size_t count);
	GUIBASESERVER_API void popInt16Array(int16_t** values, size_t* count);

	GUIBASESERVER_API void pushUInt16(uint16_t x);
	GUIBASESERVER_API uint16_t popUInt16();
	GUIBASESERVER_API void pushUInt16Array(uint16_t* values, size_t count);
	GUIBASESERVER_API void popUInt16Array(uint16_t** values, size_t* count);

	GUIBASESERVER_API void pushInt32(int32_t x);
	GUIBASESERVER_API int32_t popInt32();
	GUIBASESERVER_API void pushInt32Array(int32_t* values, size_t count);
	GUIBASESERVER_API void popInt32Array(int32_t** values, size_t* count);

	GUIBASESERVER_API void pushUInt32(uint32_t x);
	GUIBASESERVER_API uint32_t popUInt32();
	GUIBASESERVER_API void pushUInt32Array(uint32_t* values, size_t count);
	GUIBASESERVER_API void popUInt32Array(uint32_t** values, size_t* count);

	GUIBASESERVER_API void pushInt64(int64_t x);
	GUIBASESERVER_API int64_t popInt64();
	GUIBASESERVER_API void pushInt64Array(int64_t* values, size_t count);
	GUIBASESERVER_API void popInt64Array(int64_t** values, size_t* count);

	GUIBASESERVER_API void pushUInt64(uint64_t x);
	GUIBASESERVER_API uint64_t popUInt64();
	GUIBASESERVER_API void pushUInt64Array(uint64_t* values, size_t count);
	GUIBASESERVER_API void popUInt64Array(uint64_t** values, size_t* count);

	GUIBASESERVER_API void pushFloat(float x);
	GUIBASESERVER_API float popFloat();
	GUIBASESERVER_API void pushFloatArray(float* values, size_t count);
	GUIBASESERVER_API void popFloatArray(float** values, size_t* count);

	GUIBASESERVER_API void pushDouble(double x);
	GUIBASESERVER_API double popDouble();
	GUIBASESERVER_API void pushDoubleArray(double* values, size_t count);
	GUIBASESERVER_API void popDoubleArray(double** values, size_t* count);

	GUIBASESERVER_API void pushString(const char* str, size_t length);
	GUIBASESERVER_API void popString(const char** strPtr, size_t* length);
	GUIBASESERVER_API void pushStringArray(const char** strs, size_t* lengths, size_t count);
	GUIBASESERVER_API void popStringArray(const char*** strs, size_t** lengths, size_t* count);

	GUIBASESERVER_API void pushBuffer(int id, bool isClientId, ni_BufferDescriptor* descriptor);
	GUIBASESERVER_API void popBuffer(int* id, bool* isClientId, ni_BufferDescriptor* descriptor);

	GUIBASESERVER_API void pushClientFunc(int id);
	GUIBASESERVER_API int popServerFunc();

	GUIBASESERVER_API void execServerFunc(int id);
	GUIBASESERVER_API ni_ExceptionRef execServerFuncWithExceptions(int id);

	GUIBASESERVER_API void invokeInterfaceMethod(ni_InterfaceMethodRef method, int serverID);
	GUIBASESERVER_API ni_ExceptionRef invokeInterfaceMethodWithExceptions(ni_InterfaceMethodRef method, int serverID);

	GUIBASESERVER_API void pushInstance(int id, bool isClientId);
	GUIBASESERVER_API int popInstance(bool* isClientId);

	GUIBASESERVER_API void pushNull();

	GUIBASESERVER_API void releaseServerResource(int id);

	GUIBASESERVER_API void clearServerSafetyArea(); // clear server resources from safety area (protects values being returned with no other shared_ptrs existing)

	GUIBASESERVER_API void dumpTables();

	GUIBASESERVER_API void setException(ni_ExceptionRef e);
}
