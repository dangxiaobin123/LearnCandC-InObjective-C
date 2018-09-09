//
//  JsEngine.cpp
//  ios-spidermonkey-test
//
//  Created by 党晓斌 on 2018/9/9.
//  Copyright © 2018年 党晓斌. All rights reserved.
//

#include "JsEngine.hpp"
using namespace JS;
// =============================================================================
// global_class & reportError
// =============================================================================

/* The class of the global object. */
static JSClass globalClass = {
    "global",
    JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub,
    JS_DeletePropertyStub,
    JS_PropertyStub,
    JS_StrictPropertyStub,
    JS_EnumerateStub,
    JS_ResolveStub,
    JS_ConvertStub,
    nullptr, nullptr, nullptr, nullptr,
    JS_GlobalObjectTraceHook
};


/* The error reporter callback. */
static void reportError(JSContext *cx, const char *message, JSErrorReport *report) {
    fprintf(stderr, "%s:%u:%s\n",
            report->filename ? report->filename : "<no filename="">",
            (unsigned int) report->lineno,
            message);
}
int run(JSContext *cx) {
    // Enter a request before running anything in the context.
    JSAutoRequest ar(cx);
    
    // Create the global object and a new compartment.
    RootedObject global(cx);
    global = JS_NewGlobalObject(cx, &globalClass, nullptr,
                                JS::DontFireOnNewGlobalHook);
    if (!global)
    return 1;
    
    // Enter the new global object's compartment.
    JSAutoCompartment ac(cx, global);
    
    // Populate the global object with the standard globals, like Object and
    // Array.
    if (!JS_InitStandardClasses(cx, global))
    return 1;
    
    // Your application code here. This may include JSAPI calls to create your
    // own custom JS objects and run scripts.
    
    return 0;
}

// =============================================================================
// JsEngine impl
// =============================================================================

JsEngine::JsEngine() {
    /* Create a JS runtime. */
    if (!JS_Init())
    return ;
    rt = JS_NewRuntime(8L * 1024L * 1024L);
    if (rt == NULL)
    return;
    
    /* Create a context. */
    cx = JS_NewContext(rt, 8192);
    if (cx == NULL)
    return;
    //JS_SetOptions(cx, JSOPTION_VAROBJFIX | JSOPTION_METHODJIT);
    //JS_SetVersion(cx, JSVERSION_LATEST);
    JS_SetErrorReporter(cx, reportError);
    int status = run(cx);
    /* Create the global object in a new compartment. */
    
}
JsEngine::~JsEngine() {
    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
    JS_ShutDown();
}
