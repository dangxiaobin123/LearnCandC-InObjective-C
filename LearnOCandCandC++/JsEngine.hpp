//
//  JsEngine.hpp
//  ios-spidermonkey-test
//
//  Created by 党晓斌 on 2018/9/9.
//  Copyright © 2018年 党晓斌. All rights reserved.
//

#ifndef JsEngine_hpp
#define JsEngine_hpp

#include <stdio.h>
#include <string>
#include "jsapi.h"

class JsEngine {
    public:
    JsEngine();
    virtual ~JsEngine();
    
    void execJS(const std::string& script);
    protected:
    /* JS variables. */
    JSRuntime *rt;
    JSContext *cx;
    JSObject *global;
};

#endif /* JsEngine_hpp */
