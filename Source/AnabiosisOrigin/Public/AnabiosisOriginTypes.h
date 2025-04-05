/*
* 文件名: AnabiosisOriginTypes.h
* 功能描述：
* - 定义游戏核心类型和枚举
* - 提供全局调试类别系统
* - 管理日志类别定义
*
* 类型系统：
* - 调试枚举：分类管理调试信息
* - 日志系统：提供全局日志支持
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnabiosisOriginTypes.generated.h"

/** 调试信息分类枚举 */
UENUM(BlueprintType)
enum class EAnabiosisDebugCategory : uint8
{
    None            UMETA(DisplayName = "无"),           // 未分类的调试信息
    Abilities       UMETA(DisplayName = "能力系统"),     // 能力系统相关调试
    Combat          UMETA(DisplayName = "战斗系统"),     // 战斗系统相关调试
    Movement        UMETA(DisplayName = "移动系统"),     // 移动系统相关调试
    Camera          UMETA(DisplayName = "相机系统"),     // 相机系统相关调试
    All            UMETA(DisplayName = "全部")          // 启用所有调试类别
};

// 声明项目的全局日志类别
ANABIOSISORIGIN_API DECLARE_LOG_CATEGORY_EXTERN(LogAnabiosisOrigin, Log, All);
