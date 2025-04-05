#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "AbilityTagNotifyState.generated.h"

/*
* 能力标签通知状态
* 功能：
* 1. 在动画播放期间动态管理标签
* 2. 控制能力状态的切换
* 3. 提供灵活的标签添加和移除机制
*
* 配置选项：
* - TagsToAdd: 开始时添加的标签
* - TagsToRemove: 结束时移除的标签
* - bRemoveAddedTags: 是否自动清理添加的标签
*/

/**
 * 能力标签通知状态
 * 用于在动画播放期间动态切换角色的能力标签
 */
UCLASS()
class ANABIOSISORIGIN_API UAbilityTagNotifyState : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    // 在通知开始时添加的标签
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityTags")
    FGameplayTagContainer TagsToAdd;

    // 在通知结束时移除的标签（如果为空则移除开始时添加的标签）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityTags")
    FGameplayTagContainer TagsToRemove;

    // 是否在通知结束时移除开始时添加的标签
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityTags")
    bool bRemoveAddedTags = true;

public:
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
