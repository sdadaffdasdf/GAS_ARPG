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
* 文件名: EnemyAttributeSet.h
* 功能描述：
* - 定义敌人属性系统
* - 管理AI角色基础属性
* - 提供属性计算接口
*
* 属性系统：
* - 战斗属性：生命值、攻击力、防御力
* - 行为属性：移动速度、警戒范围
* - 状态属性：当前状态、仇恨值
*/

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataTable.h"
#include "EnemyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ANABIOSISORIGIN_API UEnemyAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UEnemyAttributeSet();

    // 基础属性
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, AttackPower)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Combat")
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Defense)

    // AI相关属性
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|AI")
    FGameplayAttributeData DetectionRange;
    ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, DetectionRange)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|AI")
    FGameplayAttributeData AggroValue;
    ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, AggroValue)

    // 属性变化回调
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    /** 从数据表初始化属性值 */
    UFUNCTION(BlueprintCallable, Category = "属性")
    void InitializeFromDataTable(const UDataTable* DataTable, const FName& RowName);

protected:
    void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue);
};
