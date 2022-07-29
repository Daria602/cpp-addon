#include "./mathematics.h"


double mathematics::mysqrt(double x)
{
    if (x <= 0)
    {
        return 0;
    }

    double result = x;

    for (int i = 0; i < 10; i++)
    {
        if (result <= 0)
        {
            result = 0.1;
        }

        double delta;
        delta = x - (result * result);
        result = result + 0.5 * delta / result;
    }

    return result;
}


Napi::Number mathematics::MysqrtWrapped(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Number was expected").ThrowAsJavaScriptException();
    }

    Napi::Number argument = info[0].As<Napi::Number>();
    double returnValue = mathematics::mysqrt(argument.DoubleValue());

    return Napi::Number::New(env, returnValue);
}

Napi::Object mathematics::Init(Napi::Env env, Napi::Object exports) 
{
  exports.Set("mysqrt", Napi::Function::New(env, mathematics::MysqrtWrapped));
 
  return exports;
}