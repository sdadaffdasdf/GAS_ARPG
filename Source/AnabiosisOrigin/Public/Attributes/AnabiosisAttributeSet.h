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
* 文件名: AnabiosisAttributeSet.h
* 功能描述：
* - 定义角色基础属性系统
* - 提供属性计算和修改接口
* - 管理属性同步和复制
*
* 属性系统：
* - 基础属性：力量、敏捷、体质等
* - 衍生属性：攻击力、移动速度等
* - 状态属性：生命值、魔法值等
*/

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AnabiosisAttributeSet.generated.h"

// 使用宏来定义属性的Getter和Setter
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ANABIOSISORIGIN_API UAnabiosisAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UAnabiosisAttributeSet();

    // 基础属性
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Strength)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
    FGameplayAttributeData Agility;
    ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Agility)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Base")
    FGameplayAttributeData Constitution;
    ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Constitution)

    // 衍生属性
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Derived")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, AttackPower)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Derived")
    FGameplayAttributeData MovementSpeed;
    ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, MovementSpeed)

    // 状态属性
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Status")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAnabiosisAttributeSet, MaxHealth)

    // 属性变化前的回调
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    
    // 属性基值变化时的回调
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    // 属性初始化
    virtual void InitFromMetaDataTable(const UDataTable* DataTable);

protected:
    // 属性值合法性检查
    void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue);
};
