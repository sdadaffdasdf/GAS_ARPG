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
* 文件名: AnabiosisOriginGameMode.cpp
* 功能描述：
* - 实现游戏模式核心逻辑
* - 处理调试系统功能
* - 管理游戏规则和状态
*
* 核心功能：
* - 调试管理：控制调试类别和信息显示
* - 游戏配置：设置默认玩家类和控制器
*/

#include "GameFramework/AnabiosisOriginGameMode.h"
#include "Characters/AnabiosisOriginCharacter.h"
#include "Controllers/AnabiosisPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AAnabiosisOriginGameMode::AAnabiosisOriginGameMode()
{
    // 设置默认类
    // 设置默认Pawn类
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    // 设置默认控制器类
    PlayerControllerClass = AAnabiosisPlayerController::StaticClass();
}

void AAnabiosisOriginGameMode::SetDebugCategoryEnabled(EAnabiosisDebugCategory Category, bool bEnabled)
{
    if (bEnabled)
    {
        EnabledDebugCategories.Add(Category);
        if (Category == EAnabiosisDebugCategory::All)
        {
            for (uint8 i = 0; i < static_cast<uint8>(EAnabiosisDebugCategory::All); ++i)
            {
                EnabledDebugCategories.Add(static_cast<EAnabiosisDebugCategory>(i));
            }
        }
    }
    else
    {
        EnabledDebugCategories.Remove(Category);
        if (Category == EAnabiosisDebugCategory::All)
        {
            EnabledDebugCategories.Empty();
        }
    }
}

bool AAnabiosisOriginGameMode::IsDebugCategoryEnabled(EAnabiosisDebugCategory Category) const
{
    return EnabledDebugCategories.Contains(Category) || EnabledDebugCategories.Contains(EAnabiosisDebugCategory::All);
}

void AAnabiosisOriginGameMode::DebugMessage(const FString& Message, EAnabiosisDebugCategory Category)
{
    if (AAnabiosisOriginGameMode* GameMode = Cast<AAnabiosisOriginGameMode>(GWorld->GetAuthGameMode()))
    {
        if (GameMode->IsDebugCategoryEnabled(Category))
        {
            const FString CategoryName = StaticEnum<EAnabiosisDebugCategory>()->GetNameStringByValue(static_cast<int64>(Category));
            UE_LOG(LogAnabiosisOrigin, Log, TEXT("[%s] %s"), *CategoryName, *Message);
            
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("[%s] %s"), *CategoryName, *Message));
            }
        }
    }
}