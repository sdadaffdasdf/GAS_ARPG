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
* 文件名: EnemyAttributeSet.cpp
* 功能描述：
* - 实现敌人属性系统
*/

#include "Attributes/EnemyAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Data/EnemyAttributeData.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
    // 初始化属性默认值
    Health.SetBaseValue(100.0f);
    Health.SetCurrentValue(100.0f);
    
    MaxHealth.SetBaseValue(100.0f);
    MaxHealth.SetCurrentValue(100.0f);
    
    AttackPower.SetBaseValue(10.0f);
    AttackPower.SetCurrentValue(10.0f);
    
    Defense.SetBaseValue(5.0f);
    Defense.SetCurrentValue(5.0f);
    
    DetectionRange.SetBaseValue(1000.0f);
    DetectionRange.SetCurrentValue(1000.0f);
    
    AggroValue.SetBaseValue(0.0f);
    AggroValue.SetCurrentValue(0.0f);
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    // 属性变化前的验证和调整
    if (Attribute == GetMaxHealthAttribute())
    {
        AdjustAttributeForMaxChange(Health, MaxHealth, NewValue);
    }
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    // 确保生命值不超过最大生命值
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        float NewHealth = GetHealth();
        NewHealth = FMath::Clamp(NewHealth, 0.0f, GetMaxHealth());
        SetHealth(NewHealth);
    }
}

void UEnemyAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, 
    const FGameplayAttributeData& MaxAttribute, float NewMaxValue)
{
    float CurrentValue = AffectedAttribute.GetCurrentValue();
    float CurrentMax = MaxAttribute.GetCurrentValue();
    
    if (!FMath::IsNearlyEqual(CurrentMax, NewMaxValue))
    {
        // 按比例调整当前值
        float NewValue = (CurrentValue * NewMaxValue) / CurrentMax;
        AffectedAttribute.SetCurrentValue(NewValue);
    }
}

void UEnemyAttributeSet::InitializeFromDataTable(const UDataTable* DataTable, const FName& RowName)
{
    if (!DataTable)
    {
        return;
    }

    const FEnemyAttributeData* Row = DataTable->FindRow<FEnemyAttributeData>(RowName, TEXT(""));
    if (!Row)
    {
        return;
    }

    // 设置基础属性
    Health.SetBaseValue(Row->InitialHealth);
    Health.SetCurrentValue(Row->InitialHealth);
    MaxHealth.SetBaseValue(Row->InitialMaxHealth);
    MaxHealth.SetCurrentValue(Row->InitialMaxHealth);
    
    // 设置战斗属性
    AttackPower.SetBaseValue(Row->AttackPower);
    Defense.SetBaseValue(Row->Defense);
    
    // AI相关属性设置
    DetectionRange.SetBaseValue(Row->DetectionRange);
    AggroValue.SetBaseValue(Row->AggroThreshold);
}
