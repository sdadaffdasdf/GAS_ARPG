/*
* 文件名: AnabiosisOrigin.h
* 功能描述：
* - 定义游戏模块接口
* - 管理模块生命周期
* - 提供模块级功能支持
*
* 核心组件：
* - 模块接口：处理模块启动和关闭
* - 生命周期：管理模块初始化和清理
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAnabiosisOriginModule : public IModuleInterface
{
public:
    virtual void StartupModule() override {}
    virtual void ShutdownModule() override {}
};
