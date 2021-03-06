
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "stdlib.h"
#include "contextquickie_windows_Registry.h"

LSTATUS ReadRegistry(JNIEnv* env, jint hKey, jstring location, jstring key, PVOID buffer, LPDWORD bufferLength)
{
  DWORD pdwType;
  const char *nativeKey = env->GetStringUTFChars(key, FALSE);
  const char *nativeLocation = env->GetStringUTFChars(location, FALSE);

  LSTATUS status = RegGetValueA(((HKEY)(ULONG_PTR)((LONG)hKey)), nativeLocation, nativeKey, RRF_RT_ANY, &pdwType, buffer, bufferLength);

  env->ReleaseStringUTFChars(key, nativeKey);
  env->ReleaseStringUTFChars(location, nativeLocation);

  return status;
}

JNIEXPORT jlong JNICALL Java_contextquickie_windows_Registry_readLongValue(JNIEnv* env, jobject, jint hKey, jstring location, jstring key, jlong defaultValue)
{
	long buffer;
	DWORD bufferLength = sizeof(buffer);
	
  if (ReadRegistry(env, hKey, location, key, &buffer, &bufferLength) == ERROR_SUCCESS)
  {
    return buffer;
  }
  else
  {
    return defaultValue;
  }
}

JNIEXPORT jstring JNICALL Java_contextquickie_windows_Registry_readStringValue(JNIEnv* env, jobject, jint hKey, jstring location, jstring key, jstring defaultValue)
{
	char buffer[1024];
	DWORD bufferLength = sizeof(buffer);

  if (ReadRegistry(env, hKey, location, key, &buffer, &bufferLength) == ERROR_SUCCESS)
	{
		return env->NewStringUTF(buffer);
	}
	else
	{
		return defaultValue;
	}
}

JNIEXPORT void JNICALL Java_contextquickie_windows_Registry_writeStringValue(JNIEnv* env, jobject, jint hKey, jstring location, jstring key, jstring value)
{
  const char* nativeKey = env->GetStringUTFChars(key, FALSE);
  const char* nativeLocation = env->GetStringUTFChars(location, FALSE);
  const char* nativeValue = env->GetStringUTFChars(value, FALSE);

  HKEY localKey;

  size_t size = strlen(nativeLocation) + 1;
  wchar_t* nativeLocation_wc = new wchar_t[size];
  size_t outSize;
  mbstowcs_s(&outSize, nativeLocation_wc, size, nativeLocation, size - 1);
  RegOpenKeyEx(((HKEY)(ULONG_PTR)((LONG)hKey)), nativeLocation_wc, 0, KEY_SET_VALUE, &localKey);
  LSTATUS status = RegSetValueExA(localKey, nativeKey, NULL, REG_SZ, (const BYTE *)nativeValue, (DWORD)(strlen(nativeValue) + 1));
  RegCloseKey(localKey);

  env->ReleaseStringUTFChars(key, nativeKey);
  env->ReleaseStringUTFChars(location, nativeLocation);
  env->ReleaseStringUTFChars(value, nativeValue);
}

