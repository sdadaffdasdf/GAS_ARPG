/*
* 文件名: EnemyBaseCharacter.h
* 功能描述：
* - AI敌人基类定义
* - 实现基础属性和能力系统
* - 提供AI行为接口
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"
#include "Abilities/GameplayAbility.h"
#include "EnemyBaseCharacter.generated.h"

class UAbilitySystemComponent;
class UEnemyAttributeSet;

UCLASS()
class ANABIOSISORIGIN_API AEnemyBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AEnemyBaseCharacter();

    /** 实现IAbilitySystemInterface */
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
    /** GAS系统组件 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAbilitySystemComponent* AbilitySystemComponent;

    /** 属性集 */
    UPROPERTY()
    UEnemyAttributeSet* AttributeSet;

    /** 默认能力列表 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

    /** 初始化时赋予的效果 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

    virtual void BeginPlay() override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;

    /** 初始化默认能力 */
    void GiveDefaultAbilities();
    
    /** 应用默认效果 */
    void ApplyDefaultEffects();
};
