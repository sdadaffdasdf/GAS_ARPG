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
* 文件名: AttackWindowNotifyState.cpp
* 功能描述：
* - 控制攻击判定窗口
* - 管理攻击能力的激活机会
* - 处理连击系统时序
*
* 核心功能：
* - 窗口开启：设置攻击判定标签
* - 窗口关闭：清理攻击相关标签
*/

#include "Animation/AttackWindowNotifyState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void UAttackWindowNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    if (!MeshComp || !MeshComp->GetOwner() || !WindowTag.IsValid())
    {
        return;
    }

    IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(MeshComp->GetOwner());
    if (!ASCInterface)
    {
        return;
    }

    UAbilitySystemComponent* AbilitySystem = ASCInterface->GetAbilitySystemComponent();
    if (AbilitySystem)
    {
        FGameplayTagContainer Tags;
        Tags.AddTag(WindowTag);
        if (AllowedAbilityTag.IsValid())
        {
            Tags.AddTag(AllowedAbilityTag);
        }
        AbilitySystem->AddLooseGameplayTags(Tags);
    }
}

void UAttackWindowNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner() || !WindowTag.IsValid())
    {
        return;
    }

    IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(MeshComp->GetOwner());
    if (!ASCInterface)
    {
        return;
    }

    UAbilitySystemComponent* AbilitySystem = ASCInterface->GetAbilitySystemComponent();
    if (AbilitySystem)
    {
        FGameplayTagContainer Tags;
        Tags.AddTag(WindowTag);
        if (AllowedAbilityTag.IsValid())
        {
            Tags.AddTag(AllowedAbilityTag);
        }
        AbilitySystem->RemoveLooseGameplayTags(Tags);
    }
}
