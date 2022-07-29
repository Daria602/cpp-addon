#include <napi.h>


namespace mathematics
{
  double mysqrt(double x);
  Napi::Number MysqrtWrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}