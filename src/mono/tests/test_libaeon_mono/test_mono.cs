// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

using System;
using System.Runtime.CompilerServices;

namespace Aeon
{
    class MyObject
    {
        public MyObject()
        {
            CreateInternal();
        }

        ~MyObject()
        {
            DestroyInternal();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void CreateInternal();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void DestroyInternal();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void DoStuff(String value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern string ReturnAString(string value);
    }
}

public class ClassInstanceTest
{
    public ClassInstanceTest()
    {
        Console.WriteLine("ClassInstanceTest created.");

        Aeon.MyObject s = new Aeon.MyObject();
        s.DoStuff("Hello from C#!");

        Console.WriteLine(s.ReturnAString("Testing ReturnAString."));
    }

    ~ClassInstanceTest()
    {
        Console.WriteLine("ClassInstanceTest destroyed.");
    }

    public void Method()
    {
        Console.WriteLine("Hello Mono World from instance.");
    }

    public void MethodWithParameter(String s)
    {
        Console.WriteLine("WithParam: " + s);
    }

    public string MethodWithParameterAndReturnValue(String s)
    {
        Console.WriteLine("WithParam: " + s);
        return "Return Value: " + s;
    }

    public static int FunctionWithIntParam(int a)
    {
        Console.WriteLine("Int value: " + a);
        return a + 1337;
    }

    public static void VoidFunction(float a, int b, float c)
    {
        Console.WriteLine("VoidMethod: " + a + ", " + b + ", " + c);
    }

    public static void FunctionWithStringParam(string a)
    {
        Console.WriteLine("String value: " + a);
    }

    public static void ExceptionFunction()
    {
        throw new Exception("Hello!");
    }

    public static string StringReturnFunction(string str)
    {
        return "The string value was: " + str;
    }
}
