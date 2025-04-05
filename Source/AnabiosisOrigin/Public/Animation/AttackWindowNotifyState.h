#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "AttackWindowNotifyState.generated.h"

/*
* 攻击窗口通知状态
* 功能职责：
* - 定义有效攻击判定时间段
* - 控制能力激活时机
* - 管理连击系统时序
* 
* 标签系统：
* - WindowTag: 当前攻击窗口标记
* - AllowedAbilityTag: 可激活能力标记
*/

UCLASS()
class ANABIOSISORIGIN_API UAttackWindowNotifyState : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    /** 标记当前攻击窗口的标签 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FGameplayTag WindowTag;

    /** 允许在此窗口激活的能力标签 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FGameplayTag AllowedAbilityTag;

    /** 窗口开始时添加标签 */
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    
    /** 窗口结束时移除标签 */
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
