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
* 文件名: AttackReadyNotifyState.cpp
* 功能描述：
* - 管理攻击就绪状态
* - 控制连击输入时机
* - 处理攻击状态转换
*
* 核心功能：
* - 就绪状态：设置攻击就绪标记
* - 状态结束：清理就绪状态标记
*/

#include "Animation/AttackReadyNotifyState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void UAttackReadyNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    if (!MeshComp || !MeshComp->GetOwner() || !ReadyTag.IsValid())
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
        AbilitySystem->AddLooseGameplayTag(ReadyTag);
    }
}

void UAttackReadyNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner() || !ReadyTag.IsValid())
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
        AbilitySystem->RemoveLooseGameplayTag(ReadyTag);
    }
}
