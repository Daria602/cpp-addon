# C++ addon for Node.Js using N-API

## Dependencies
```bash
npm install node-gyp --save-dev
npm install node-addon-api
```

## Steps to make another C++ function (with examples from code)

1. Declare function name in *mathematics.h* and a "wrapped" version of it
```cpp
    double mysqrt(double x);
    Napi::Number MysqrtWrapped(const Napi::CallbackInfo& info);
```
2. Write the body of the function in *mathematics.cpp*
```cpp
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
```
3. Write body for the "wrapped" version of the function
```cpp
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
```

4. Add another line (like the one below) to set the exports
```cpp
exports.Set("mysqrt", Napi::Function::New(env, mathematics::MysqrtWrapped));
```
5. Done! Now run the command below and if there are no errors you can try and test your functions in index.js.
```bash
npm run build
```

## Remarks
* Run *npm run build* every time you modify the contents of C++ files, which require recompiling.
* Amazing tutorial on how to make C++ addon project from scratch can be found [here](https://morioh.com/p/e1a6f79af449)

