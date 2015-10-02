#include <cstdio>
#include <jni.h>
#include <cassert>
#include <string>

class CJava {
public:
    CJava()
    {
        JavaVMInitArgs args;
        JavaVMOption options;
        args.version = JNI_VERSION_1_6;
        args.nOptions = 1;
        options.optionString = "-Djava.class.path=java-cpp-exec-link.jar:./";
        args.options = &options;
        args.ignoreUnrecognized = false;
        if (JNI_CreateJavaVM(&m_javaVM, (void**)&m_env, &args) < 0 || m_env == nullptr)
        {
            printf("Unable to launch JVM\n");
            assert(false);
        }
        printf("Launched JVM\n");
    }

    void Compile(std::string classname, std::string code)
    {
        jclass compilerClass = m_env->FindClass("pl/krzysh/javacppexec/Compiler");
        assert(compilerClass != nullptr);
        jmethodID compileMethod = m_env->GetStaticMethodID(compilerClass, "compile", "(Ljava/lang/String;Ljava/lang/String;)V");
        assert(compileMethod != nullptr);
        m_env->CallStaticVoidMethod(compilerClass, compileMethod, m_env->NewStringUTF(classname.c_str()), m_env->NewStringUTF(code.c_str()));
        printf("Compiled!\n");
    }

    void Execute(std::string classname)
    {
        jclass userClass = m_env->FindClass(classname.c_str());
        assert(userClass != nullptr);
        jmethodID mainMethod = m_env->GetStaticMethodID(userClass, "main", "()V");
        if (mainMethod == nullptr)
        {
            printf("Main method not found!\n");
            return;
        }
        m_env->CallStaticVoidMethod(userClass, mainMethod);
    }

private:
    JavaVM* m_javaVM;
    JNIEnv* m_env;
};

int main(int argc, char* argv[])
{
    printf("Start!\n");
    CJava* java = new CJava();
    java->Compile("Test", "public class Test { public static void main() { System.out.println(\"this works\"); } }");
    java->Execute("Test");

    return 0;
}
