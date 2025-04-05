/*
* 基础攻击能力实现文件
* 实现功能：
* 1. 能力初始化
* 2. 动画播放控制
* 3. 能力生命周期管理
*/

#include "Ability/BaseAttack.h"
#include "GameFramework/AnabiosisOriginGameMode.h"

UBaseAttack::UBaseAttack()
{
    // 设置能力的实例化策略为每个角色一个实例
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UBaseAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    UE_LOG(LogTemp, Warning, TEXT("BaseAttack::ActivateAbility called"));
    
    // 首先尝试提交能力（检查消耗等）
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        // 提交失败时结束能力
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    // 检查动画资源是否有效
    if (!AttackMontage)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    // 创建动画播放任务
    MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
        this,
        NAME_None,
        AttackMontage,
        1.0f,    // 播放速率
        NAME_None,// 起始段落名称
        true     // 能力结束时停止动画
    );

    // 绑定动画完成和取消事件
    MontageTask->OnCompleted.AddDynamic(this, &UBaseAttack::OnMontageCompleted);
    MontageTask->OnCancelled.AddDynamic(this, &UBaseAttack::OnMontageCancelled);
    
    // 激活动画任务
    MontageTask->ReadyForActivation();
}

void UBaseAttack::OnMontageCompleted()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBaseAttack::OnMontageCancelled()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

