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
* 文件名: AnabiosisAttributeData.h
* 功能描述：
* - 定义所有玩家属性数据结构
* - 提供数据表格式支持
* - 实现玩家属性的可视化配置
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AnabiosisAttributeData.generated.h"

/**
 * 玩家职业类型
 */
UENUM(BlueprintType)
enum class EAnabiosisPlayerClass : uint8
{
    Warrior     UMETA(DisplayName = "战士"),
    Assassin    UMETA(DisplayName = "刺客"),
    Mage        UMETA(DisplayName = "法师")
};

/**
 * 游戏玩家的所有属性数据
 */
USTRUCT(BlueprintType)
struct FAnabiosisAttributeData : public FTableRowBase
{
    GENERATED_BODY()

    // 基本信息
    /** 职业类型 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
    EAnabiosisPlayerClass PlayerClass = EAnabiosisPlayerClass::Warrior;

    /** 角色等级 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (ClampMin = "1", ClampMax = "99"))
    int32 Level = 1;

    // 基础属性
    /** 力量：影响基础攻击力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attributes", meta = (ClampMin = "1"))
    float Strength = 10.0f;

    /** 敏捷：影响移动速度和闪避 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attributes", meta = (ClampMin = "1"))
    float Agility = 10.0f;

    /** 体质：影响生命值和防御 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attributes", meta = (ClampMin = "1"))
    float Constitution = 10.0f;

    /** 智力：影响技能伤害和魔法值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attributes", meta = (ClampMin = "1"))
    float Intelligence = 10.0f;

    // 战斗属性
    /** 生命值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
    float Health = 100.0f;

    /** 最大生命值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
    float MaxHealth = 100.0f;

    /** 魔法值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
    float Mana = 100.0f;

    /** 最大魔法值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
    float MaxMana = 100.0f;

    /** 攻击力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
    float AttackPower = 10.0f;

    /** 防御力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0"))
    float Defense = 5.0f;

    /** 暴击率 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "0", ClampMax = "1"))
    float CriticalChance = 0.05f;

    /** 暴击伤害倍率 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Attributes", meta = (ClampMin = "1"))
    float CriticalMultiplier = 1.5f;

    // 衍生属性系数
    /** 每点力量提供的攻击力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Coefficients", meta = (ClampMin = "0"))
    float AttackPowerPerStrength = 2.0f;

    /** 每点敏捷提供的移动速度 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Coefficients", meta = (ClampMin = "0"))
    float MovementSpeedPerAgility = 0.5f;

    /** 每点体质提供的生命值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Coefficients", meta = (ClampMin = "0"))
    float HealthPerConstitution = 10.0f;

    /** 每点智力提供的魔法值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Coefficients", meta = (ClampMin = "0"))
    float ManaPerIntelligence = 10.0f;

    // 成长属性
    /** 等级提升时基础属性成长率 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth", meta = (ClampMin = "1.0"))
    float AttributeGrowthRate = 1.1f;

    /** 等级提升时生命值成长率 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth", meta = (ClampMin = "1.0"))
    float HealthGrowthRate = 1.2f;

    /** 等级提升时魔法值成长率 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth", meta = (ClampMin = "1.0"))
    float ManaGrowthRate = 1.15f;

    FAnabiosisAttributeData()
    {}
};
