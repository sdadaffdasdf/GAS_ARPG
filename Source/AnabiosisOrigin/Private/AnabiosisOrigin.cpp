/*
* 游戏模块的主要实现文件
* 功能：
* 1. 实现游戏模块的注册
* 2. 初始化全局日志系统
* 3. 提供模块级别的功能支持
*/

#include "../Public/AnabiosisOrigin.h"
#include "Modules/ModuleManager.h"
#include "AnabiosisOriginTypes.h"

// 实现主游戏模块
IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, AnabiosisOrigin, "AnabiosisOrigin");

// 定义项目的日志类别
DEFINE_LOG_CATEGORY(LogAnabiosisOrigin);
