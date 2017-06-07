/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
    }
}

public class ClassInstanceTest
{
    public ClassInstanceTest()
    {
        Console.WriteLine("ClassInstanceTest created.");

        Aeon.MyObject s = new Aeon.MyObject();
        s.DoStuff("Hello from C#!");
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
        return "Return Value";
    }

    public static int MethodWithIntParam(int a)
    {
        Console.WriteLine("Int value: " + a);
        return a + 1337;
    }

    public static void VoidMethod(float a, int b, float c)
    {
        Console.WriteLine("VoidMethod: " + a + ", " + b + ", " + c);
    }

    public static void MethodWithStringParam(string a)
    {
        Console.WriteLine("String value: " + a);
    }

    public static void ExceptionMethod()
    {
        throw new Exception("Hello!");
    }
}
