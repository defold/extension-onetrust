#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/sdk.h>
#include <dmsdk/dlib/android.h>

namespace dmOneTrust {

struct OneTrust
{
    jobject        m_OneTrustJNI;

    jmethodID      m_Initialize;
};

static OneTrust       g_onetrust;

static void CallVoidMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method);
}

static bool CallBoolMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jboolean return_value = (jboolean)env->CallBooleanMethod(instance, method);
    return JNI_TRUE == return_value;
}

static void CallVoidMethodChar(jobject instance, jmethodID method, const char* cstr)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    env->CallVoidMethod(instance, method, jstr);
    env->DeleteLocalRef(jstr);
}

static void CallVoidMethodCharInt(jobject instance, jmethodID method, const char* cstr, int cint)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    env->CallVoidMethod(instance, method, jstr, cint);
    env->DeleteLocalRef(jstr);
}

static void CallVoidMethodCharBoolean(jobject instance, jmethodID method, const char* cstr, bool cbool)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    env->CallVoidMethod(instance, method, jstr, cbool);
    env->DeleteLocalRef(jstr);
}

static void CallVoidMethodInt(jobject instance, jmethodID method, int cint)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method, cint);
}

static void CallVoidMethodBool(jobject instance, jmethodID method, bool cbool)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method, cbool);
}

static void InitJNIMethods(JNIEnv* env, jclass cls)
{
    g_onetrust.m_Initialize = env->GetMethodID(cls, "initialize", "()V");
}

void Initialize_Ext(dmExtension::Params* params)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.defold.onetrust.OneTrustJNI");

    InitJNIMethods(env, cls);

    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
    g_onetrust.m_OneTrustJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
}

void Finalize_Ext()
{
}

void Initialize()
{
    CallVoidMethod(g_onetrust.m_OneTrustJNI, g_onetrust.m_Initialize);
}

} //namespace dmOneTrust

#endif
