#include "ChakraCore.h"

#include <iostream>

constexpr auto kScript = R"(
var module = {}
module.foo = function() {
  var junk = Math.cos(0.5) * 0;
}
module;
)";

int main()
{
  JsRuntimeHandle runtime;
  JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime);

  JsContextRef context;
  JsCreateContext(runtime, &context);

  JsValueRef module;
  {
    JsSetCurrentContext(context);

    JsValueRef script, url;
    JsCreateExternalArrayBuffer((void *)kScript, strlen(kScript), nullptr, nullptr, &script);
    JsCreateString("foo.js", 6, &url);

    JsRun(script, 0, url, JsParseScriptAttributeNone, &module);
    JsAddRef(module, nullptr);

    JsSetCurrentContext(JS_INVALID_REFERENCE);
  }

  for (int i = 0; i < 100000; i += 1)
  {
    std::cout << "iteration=" << i << std::endl;
    JsSetCurrentContext(context);

    JsValueRef fn;
    JsPropertyIdRef prop_id;
    JsCreatePropertyId("foo", 3, &prop_id);
    JsGetProperty(module, prop_id, &fn);

    JsValueRef undefined;
    JsGetUndefinedValue(&undefined);
    JsValueRef args[] = {undefined};

    JsValueRef ret;
    JsCallFunction(fn, args, 1, &ret);

    JsSetCurrentContext(JS_INVALID_REFERENCE);
  }
}