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
 
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "AttackWindowNotifyState.generated.h"

/*
* 攻击窗口通知状态
* 功能职责：
* - 定义有效攻击判定时间段
* - 控制能力激活时机
* - 管理连击系统时序
* 
* 标签系统：
* - WindowTag: 当前攻击窗口标记
* - AllowedAbilityTag: 可激活能力标记
*/

UCLASS()
class ANABIOSISORIGIN_API UAttackWindowNotifyState : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    /** 标记当前攻击窗口的标签 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FGameplayTag WindowTag;

    /** 允许在此窗口激活的能力标签 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FGameplayTag AllowedAbilityTag;

    /** 窗口开始时添加标签 */
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    
    /** 窗口结束时移除标签 */
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
