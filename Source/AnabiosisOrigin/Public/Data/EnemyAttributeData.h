/*
* 文件名: EnemyAttributeData.h
* 功能描述：
* - 定义敌人属性数据结构
* - 提供数据表格式支持
* - 实现AI参数配置
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyAttributeData.generated.h"

/**
 * 敌人类型枚举
 */
UENUM(BlueprintType)
enum class EEnemyType : uint8
{
    Normal      UMETA(DisplayName = "普通怪物"),
    Elite       UMETA(DisplayName = "精英怪物"),
    Boss        UMETA(DisplayName = "Boss"),
    MiniBoss    UMETA(DisplayName = "小Boss")
};

/**
 * 行为模式枚举
 */
UENUM(BlueprintType)
enum class EEnemyBehaviorType : uint8
{
    Passive     UMETA(DisplayName = "被动"),
    Aggressive  UMETA(DisplayName = "主动"),
    Territorial UMETA(DisplayName = "领地"),
    Patrol      UMETA(DisplayName = "巡逻")
};

/**
 * 敌人属性数据结构
 */
USTRUCT(BlueprintType)
struct FEnemyAttributeData : public FTableRowBase
{
    GENERATED_BODY()

    /** 基本信息 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
    EEnemyType EnemyType = EEnemyType::Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
    EEnemyBehaviorType BehaviorType = EEnemyBehaviorType::Passive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
    int32 Level = 1;

    /** 战斗属性 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ClampMin = "1.0"))
    float InitialHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ClampMin = "1.0"))
    float InitialMaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ClampMin = "0.0"))
    float AttackPower = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ClampMin = "0.0"))
    float Defense = 5.0f;

    /** AI行为参数 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0"))
    float DetectionRange = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0"))
    float PatrolRadius = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0"))
    float ChaseRange = 1500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0"))
    float AggroThreshold = 50.0f;

    /** 战斗行为参数 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Behavior")
    float AttackRange = 150.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Behavior")
    float AttackInterval = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Behavior")
    bool bCanUseSpecialAttack = false;

    /** 奖励系统 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
    float ExperienceValue = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
    float LootChance = 0.5f;

    FEnemyAttributeData()
    {}
};
