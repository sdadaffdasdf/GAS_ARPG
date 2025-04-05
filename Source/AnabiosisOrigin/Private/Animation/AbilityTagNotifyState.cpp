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
* 文件名: AbilityTagNotifyState.cpp
* 功能描述：
* - 实现能力标签通知状态
* - 管理标签生命周期
* - 处理动画通知事件
*/

#include "Animation/AbilityTagNotifyState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void UAbilityTagNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    if (!MeshComp || !MeshComp->GetOwner())
    {
        return;
    }

    // 获取能力系统组件
    IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(MeshComp->GetOwner());
    if (!ASCInterface)
    {
        return;
    }

    UAbilitySystemComponent* AbilitySystem = ASCInterface->GetAbilitySystemComponent();
    if (!AbilitySystem)
    {
        return;
    }

    // 添加标签
    for (const FGameplayTag& Tag : TagsToAdd)
    {
        AbilitySystem->AddLooseGameplayTag(Tag);
    }
}

void UAbilityTagNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner())
    {
        return;
    }

    // 获取能力系统组件
    IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(MeshComp->GetOwner());
    if (!ASCInterface)
    {
        return;
    }

    UAbilitySystemComponent* AbilitySystem = ASCInterface->GetAbilitySystemComponent();
    if (!AbilitySystem)
    {
        return;
    }

    // 移除指定的标签
    if (TagsToRemove.Num() > 0)
    {
        for (const FGameplayTag& Tag : TagsToRemove)
        {
            AbilitySystem->RemoveLooseGameplayTag(Tag);
        }
    }
    // 如果设置了移除添加的标签，则移除开始时添加的标签
    else if (bRemoveAddedTags)
    {
        for (const FGameplayTag& Tag : TagsToAdd)
        {
            AbilitySystem->RemoveLooseGameplayTag(Tag);
        }
    }
}
