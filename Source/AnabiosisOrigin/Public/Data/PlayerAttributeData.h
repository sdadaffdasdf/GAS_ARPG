/*
* 文件名: PlayerAttributeData.h
* 功能描述：
* - 定义玩家角色属性数据结构
* - 提供数据表格式支持
* - 实现可视化编辑接口
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerAttributeData.generated.h"

/**
 * 玩家等级类型枚举
 */
UENUM(BlueprintType)
enum class EPlayerProgressionType : uint8
{
    Novice      UMETA(DisplayName = "新手"),
    Intermediate UMETA(DisplayName = "进阶"),
    Advanced    UMETA(DisplayName = "专家"),
    Master      UMETA(DisplayName = "大师")
};

/**
 * 玩家属性数据结构
 * 用于在数据表中配置角色属性
 */
USTRUCT(BlueprintType)
struct FPlayerAttributeData : public FTableRowBase
{
    GENERATED_BODY()

    /** 角色等级 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level", meta = (ClampMin = "1", ClampMax = "99"))
    int32 Level = 1;

    /** 进阶类型 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
    EPlayerProgressionType ProgressionType = EPlayerProgressionType::Novice;

    // 基础属性
    /** 力量：影响攻击力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes", meta = (ClampMin = "1"))
    float Strength = 10.0f;

    /** 敏捷：影响移动速度和闪避 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes", meta = (ClampMin = "1"))
    float Agility = 10.0f;

    /** 体质：影响生命值和防御 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes", meta = (ClampMin = "1"))
    float Constitution = 10.0f;

    /** 智力：影响技能威力和魔法值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes", meta = (ClampMin = "1"))
    float Intelligence = 10.0f;

    // 衍生属性系数
    /** 每点力量提供的攻击力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coefficients", meta = (ClampMin = "0.1"))
    float AttackPowerPerStrength = 2.0f;

    /** 每点敏捷提供的移动速度 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coefficients", meta = (ClampMin = "0.1"))
    float MovementSpeedPerAgility = 1.0f;

    /** 每点体质提供的生命值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coefficients", meta = (ClampMin = "1.0"))
    float HealthPerConstitution = 10.0f;

    /** 每点智力提供的魔法值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coefficients", meta = (ClampMin = "1.0"))
    float ManaPerIntelligence = 10.0f;

    // 成长系数
    /** 等级提升时属性成长系数 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth", meta = (ClampMin = "1.0"))
    float AttributeGrowthRate = 1.1f;

    /** 等级提升时生命值成长系数 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth", meta = (ClampMin = "1.0"))
    float HealthGrowthRate = 1.2f;
};
