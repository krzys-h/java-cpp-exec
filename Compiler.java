package pl.krzysh.javacppexec;

import java.net.*;
import java.util.*;
import javax.tools.*;

public class Compiler
{
    public static class StringJavaSource extends SimpleJavaFileObject
    {
        private final String code;

        public StringJavaSource(String name, String code)
        {
            super(URI.create("string:///" + name.replace('.', '/') + Kind.SOURCE.extension), Kind.SOURCE);
            this.code = code;
        }

        public CharSequence getCharContent(boolean ignoreEncodingErrors)
        {
            return code;
        }
    }

    public static void compile(String name, String code)
    {
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        compiler.getTask(null, null, null, null, null, Arrays.asList(new StringJavaSource(name, code))).call();
    }
}
