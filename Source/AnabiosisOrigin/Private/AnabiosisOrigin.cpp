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
