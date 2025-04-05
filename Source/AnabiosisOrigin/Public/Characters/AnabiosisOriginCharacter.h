/*
* 文件名: AnabiosisOriginCharacter.h
* 功能描述：
* - 实现主角色的核心功能
* - 管理角色组件系统
* - 处理能力系统集成
*
* 核心组件：
* - 相机系统：控制游戏视角
* - 能力系统：处理角色技能
* - 属性系统：管理角色状态
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Data/AnabiosisAttributeData.h"
#include "AnabiosisOriginCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAttributeSet;

/**
 * 游戏主角色类
 * 实现基础移动、视角和能力系统
 */
UCLASS(config=Game)
class AAnabiosisOriginCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

private:
    /** 相机臂组件：控制相机跟随距离和位置 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    /** 跟随相机：实现第三人称视角 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

protected:
    /** GAS系统组件 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAbilitySystemComponent* AbilitySystemComponent;

    /** 属性集 */
    UPROPERTY()
    UAttributeSet* AttributeSet;

    /** 攻击能力标签 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
    FGameplayTag AttackAbilityTag;

    /** 默认能力列表 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
    TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

    /** 属性数据表引用 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Class")
    UDataTable* ClassAttributeTable;

    /** 当前角色职业 */
    UPROPERTY(ReplicatedUsing = OnRep_CurrentClass, EditAnywhere, BlueprintReadWrite, Category = "Character|Class")
    EAnabiosisPlayerClass CurrentClass;

public:
    /** 构造函数 */
    AAnabiosisOriginCharacter();

    /** 获取能力系统组件 */
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    /** 获取攻击能力标签 */
    UFUNCTION(BlueprintCallable, Category = "Abilities")
    FGameplayTag GetAttackAbilityTag() const { return AttackAbilityTag; }
    
    /** 获取相机组件 */
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    /** 设置角色旋转模式 */
    void SetCharacterRotationMode(bool bOrientToMovement, bool bUseControllerRotation);

    /** 设置角色职业 */
    UFUNCTION(BlueprintCallable, Category = "Character|Class")
    void SetPlayerClass(EAnabiosisPlayerClass NewClass);

    /** 获取当前职业 */
    UFUNCTION(BlueprintPure, Category = "Character|Class")
    EAnabiosisPlayerClass GetPlayerClass() const { return CurrentClass; }

protected:
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;
    
    /** 初始化默认能力 */
    void GiveDefaultAbilities();

    /** 处理职业变化的网络复制 */
    UFUNCTION()
    void OnRep_CurrentClass();

    /** 更新角色属性为新职业的属性 */
    void UpdateAttributesForClass();
};
