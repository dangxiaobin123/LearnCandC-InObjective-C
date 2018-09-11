//
//  ViewController.m
//  LearnOCandCandC++
//
//  Created by 林伟池 on 16/2/23.
//  Copyright © 2016年 林伟池. All rights reserved.
//

#import "ViewController.h"
#import "LearnC.h"
#import "LearnC++.hpp"
#import "LearnOCinCPP.h"
#include "jswrapper.hpp"
#include <iostream>
@interface ViewController ()

@end

@implementation ViewController
{
    cppObject* object;
    JSWrapper* jsWrapper;
    //JSWrapperData* data;
}
- (void)viewDidLoad {
    [super viewDidLoad];

    learnCplus(1, 2); //在OC中使用c
    jsWrapper = new JSWrapper();
    if ( !jsWrapper->isValid() ) {
        printf("Unable to Initialize JavaScript Wrapper.\n");
        
    }
    
    //JSWrapperData data;
    
    jsWrapper->execute( "var e=13; var a={ b : function( value ) { return value * 2; } };" );
    
    JSWrapperObject *global=jsWrapper->globalObject(); // Get the global object
    
    JSWrapperData eData, aData;
    global->get( "e", &eData );
    global->get( "a", &aData );
    
    std::cout << eData.toNumber() << std::endl;
    
    // Get the b function from the global a class
    
    if ( aData.isObject() ) {
        JSWrapperData bFuncData, rcData;
        
        aData.object()->get( "b", &bFuncData );
        
        JSWrapperArguments args; // Create the arguments to pass to b
        args.append( 23.1 );
        
        bFuncData.object()->call( &args, aData.object(), &rcData );
        std::cout << rcData.toNumber() << std::endl; // 46.2
    }
    delete global; // Cleanup
    global = nullptr;
    learnCplusplus(1, 2); //在OC中用C++编译的C
    //engine = new JsEngine();
    //在OC中使用C++的类
//    object = new cppObject();
//    NSString* str = @"GAO高级\n";
//    std::string cpp_str([str UTF8String], [str lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
//    object->exampleMethod(cpp_str);
//    delete object;
//    object = NULL; //记得删除
    //delete engine;
    //engine = nullptr;
    
    //在OC使用的C++类中 使用OC
//    LY::OCinCPP* cpp = new LY::OCinCPP();
//    cpp->lyRun();
    
    //data = nullptr;
    
}




- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
