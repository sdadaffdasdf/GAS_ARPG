/* 
 * Copyright (C) 2024 [Wang] 
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see https://www.gnu.org/licenses/. 
 */ 
 
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
