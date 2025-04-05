/*
* 文件名: AnabiosisPlayerController.cpp
* 功能描述：
* - 实现玩家输入处理系统
* - 管理角色和摄像机控制
* - 处理战斗状态切换
*
* 核心系统：
* - 输入管理：处理增强型输入系统
* - 视角控制：管理战斗/普通视角切换
* - 能力激活：处理攻击能力的触发
*/

#include "Controllers/AnabiosisPlayerController.h"
#include "Characters/AnabiosisOriginCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAnabiosisPlayerController::AAnabiosisPlayerController()
{
    // 构造函数中的初始化
}

void AAnabiosisPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 获取控制的角色
    ControlledCharacter = Cast<AAnabiosisOriginCharacter>(GetPawn());

    // 添加输入映射上下文
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
}

void AAnabiosisPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        // 绑定移动输入
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAnabiosisPlayerController::Move);
        
        // 绑定视角输入
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAnabiosisPlayerController::Look);
        
        // 绑定跳跃输入
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AAnabiosisPlayerController::StopJumping);
        
        // 绑定攻击输入
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::OnAttackActionStarted);
        
        // 绑定攻击视角切换
        EnhancedInputComponent->BindAction(AttackLookAction, ETriggerEvent::Started, this, &AAnabiosisPlayerController::ToggleAttackLook);
    }
}

void AAnabiosisPlayerController::Move(const FInputActionValue& Value)
{
    if (!ControlledCharacter)
    {
        return;
    }

    // 获取输入向量
    FVector2D MovementVector = Value.Get<FVector2D>();

    // 获取控制器旋转
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // 计算移动方向
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // 应用移动
    ControlledCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
    ControlledCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void AAnabiosisPlayerController::Look(const FInputActionValue& Value)
{
    if (!ControlledCharacter)
    {
        return;
    }

    FVector2D LookAxisVector = Value.Get<FVector2D>();
    AddYawInput(LookAxisVector.X);
    AddPitchInput(LookAxisVector.Y);
}

void AAnabiosisPlayerController::Jump()
{
    if (ControlledCharacter)
    {
        ControlledCharacter->Jump();
    }
}

void AAnabiosisPlayerController::StopJumping()
{
    if (ControlledCharacter)
    {
        ControlledCharacter->StopJumping();
    }
}

void AAnabiosisPlayerController::OnAttackActionStarted(const FInputActionValue& Value)
{
    if (!ControlledCharacter)
    {
        return;
    }

    UAbilitySystemComponent* AbilitySystem = ControlledCharacter->GetAbilitySystemComponent();
    FGameplayTag AttackTag = ControlledCharacter->GetAttackAbilityTag();

    if (!AbilitySystem)
    {
        UE_LOG(LogTemp, Error, TEXT("AbilitySystemComponent is null"));
        return;
    }

    if (!AttackTag.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("AttackAbilityTag is invalid"));
        return;
    }

    FGameplayTagContainer AbilityTags;
    AbilityTags.AddTag(AttackTag);
    
    UE_LOG(LogTemp, Warning, TEXT("Trying to activate ability with tag: %s"), *AttackTag.ToString());
    
    bool bSuccess = AbilitySystem->TryActivateAbilitiesByTag(AbilityTags);
    UE_LOG(LogTemp, Warning, TEXT("TryActivateAbilitiesByTag result: %s"), bSuccess ? TEXT("Success") : TEXT("Failed"));
}

void AAnabiosisPlayerController::ToggleAttackLook(const FInputActionValue& Value)
{
    if (!ControlledCharacter)
    {
        return;
    }

    // 切换战斗模式状态
    bIsInCombatMode = !bIsInCombatMode;

    // 获取必要组件
    ACharacter* ControlledPawn = Cast<ACharacter>(ControlledCharacter);
    UCharacterMovementComponent* MovementComp = Cast<UCharacterMovementComponent>(ControlledPawn->GetMovementComponent());
    USpringArmComponent* CameraBoom = ControlledCharacter->GetCameraBoom();

    if (!MovementComp)
    {
        return;
    }

    // 更新角色旋转设置
    ControlledPawn->bUseControllerRotationYaw = bIsInCombatMode;
    MovementComp->bOrientRotationToMovement = !bIsInCombatMode;

    // 更新相机设置
    CameraBoom->TargetArmLength = bIsInCombatMode ? CombatCameraArmLength : NormalCameraArmLength;
    CameraBoom->SocketOffset = bIsInCombatMode ? CombatCameraOffset : FVector::ZeroVector;
}

void AAnabiosisPlayerController::ProcessPlayerMovement(const FInputActionValue& Value)
{
    if (!ControlledCharacter) return;

    // 获取输入向量
    FVector2D MovementVector = Value.Get<FVector2D>();

    // 获取控制器旋转
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // 计算移动方向
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // 应用移动
    ControlledCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
    ControlledCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void AAnabiosisPlayerController::ProcessCharacterRotation(const FInputActionValue& Value)
{
    if (!ControlledCharacter) return;

    FVector2D LookAxisVector = Value.Get<FVector2D>();
    float TurnValue = LookAxisVector.X * BaseTurnRate * GetWorld()->GetDeltaSeconds();
    float LookUpValue = LookAxisVector.Y * BaseLookUpRate * GetWorld()->GetDeltaSeconds();

    AddYawInput(TurnValue);
    AddPitchInput(LookUpValue);
}

void AAnabiosisPlayerController::ToggleCombatMode(const FInputActionValue& Value)
{
    if (!ControlledCharacter) return;

    bIsInCombatMode = !bIsInCombatMode;
    UpdateCharacterMovementState(bIsInCombatMode);
}

void AAnabiosisPlayerController::SetCameraParameters(float ArmLength, const FVector& Offset)
{
    if (!ControlledCharacter) return;

    if (USpringArmComponent* CameraBoom = ControlledCharacter->GetCameraBoom())
    {
        CameraBoom->TargetArmLength = ArmLength;
        CameraBoom->SocketOffset = Offset;
    }
}

void AAnabiosisPlayerController::UpdateCharacterMovementState(bool bIsCombatMode)
{
    if (!ControlledCharacter) return;

    // 更新角色旋转设置
    ControlledCharacter->SetCharacterRotationMode(!bIsCombatMode, bIsCombatMode);

    // 更新相机设置
    float NewArmLength = bIsCombatMode ? CombatCameraArmLength : NormalCameraArmLength;
    FVector NewOffset = bIsCombatMode ? CombatCameraOffset : FVector::ZeroVector;
    SetCameraParameters(NewArmLength, NewOffset);
}
