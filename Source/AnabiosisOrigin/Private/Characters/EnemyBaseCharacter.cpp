/*
* 文件名: EnemyBaseCharacter.cpp
* 功能描述：
* - 实现AI敌人基础功能
* - 初始化属性和能力系统
* - 处理AI行为逻辑
*/

#include "Characters/EnemyBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Attributes/EnemyAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyBaseCharacter::AEnemyBaseCharacter()
{
    // 禁用玩家控制器的旋转
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 配置移动组件
    UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
    if (MovementComponent)
    {
        MovementComponent->bOrientRotationToMovement = true;
        MovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    }

    // 初始化能力系统组件
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    // 创建属性集
    AttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("AttributeSet"));
}

void AEnemyBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

UAbilitySystemComponent* AEnemyBaseCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AEnemyBaseCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        GiveDefaultAbilities();
        ApplyDefaultEffects();
    }
}

void AEnemyBaseCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
    
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
    }
}

void AEnemyBaseCharacter::GiveDefaultAbilities()
{
    if (!HasAuthority() || !AbilitySystemComponent) return;

    for (TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
    {
        if (Ability)
        {
            AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
        }
    }
}

void AEnemyBaseCharacter::ApplyDefaultEffects()
{
    if (!HasAuthority() || !AbilitySystemComponent) return;

    FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
    EffectContext.AddSourceObject(this);

    for (const TSubclassOf<UGameplayEffect>& GameplayEffect : DefaultEffects)
    {
        if (GameplayEffect)
        {
            FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
            if (NewHandle.IsValid())
            {
                AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
            }
        }
    }
}
