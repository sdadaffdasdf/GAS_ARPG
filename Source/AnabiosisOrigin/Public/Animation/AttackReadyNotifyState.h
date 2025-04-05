
/*
* 攻击就绪状态通知
* 功能职责：
* - 标记可执行连击的时机
* - 管理攻击就绪状态
* - 控制连击输入窗口
*
* 使用方式：
* - 在动画蓝图中添加该通知
* - 设置就绪状态标签
* - 在能力中检查标签状态
*/

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "AttackReadyNotifyState.generated.h"

UCLASS()
class ANABIOSISORIGIN_API UAttackReadyNotifyState : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    /** 标记攻击就绪状态的标签 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FGameplayTag ReadyTag;

public:
    /** 就绪状态开始时添加标签 */
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    
    /** 就绪状态结束时移除标签 */
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
