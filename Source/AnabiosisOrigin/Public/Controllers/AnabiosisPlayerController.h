/* 
 * Copyright (C) 2024 [Wang] 
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see https://www.gnu.org/licenses/. 
 */ 
 
/*
* 文件名: AnabiosisPlayerController.h
* 功能描述：
* - 处理玩家输入系统
* - 管理角色控制逻辑
* - 实现战斗控制系统
*
* 核心系统：
* - 输入系统：处理玩家操作
* - 相机系统：管理游戏视角
* - 战斗系统：控制战斗状态
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "AnabiosisPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AAnabiosisOriginCharacter;

UCLASS()
class ANABIOSISORIGIN_API AAnabiosisPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AAnabiosisPlayerController();

protected:
    // 输入映射上下文
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "输入")
    UInputMappingContext* DefaultMappingContext;

    // 基础输入动作
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "输入")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "输入")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "输入")
    UInputAction* JumpAction;

    // 战斗相关输入动作
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "输入|战斗")
    UInputAction* AttackAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "输入|战斗")
    UInputAction* AttackLookAction;

    // 相机设置
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float NormalCameraArmLength = 400.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float CombatCameraArmLength = 250.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    FVector CombatCameraOffset = FVector(0.0f, 80.0f, 30.0f);

    // 当前视角状态
    bool bIsInCombatMode;

    /** 移动相关参数 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float BaseMovementSpeed = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeedMultiplier = 1.5f;

    /** 视角相关参数 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float BaseTurnRate = 45.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float BaseLookUpRate = 45.0f;

    /** 处理移动和视角函数 */
    void ProcessPlayerMovement(const FInputActionValue& Value);
    void ProcessCharacterRotation(const FInputActionValue& Value);
    void ToggleCombatMode(const FInputActionValue& Value);

    /** 设置角色和相机状态 */
    void SetCameraParameters(float ArmLength, const FVector& Offset);
    void UpdateCharacterMovementState(bool bIsCombatMode);

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    // 输入处理函数
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Jump();
    void StopJumping();
    void OnAttackActionStarted(const FInputActionValue& Value);
    void ToggleAttackLook(const FInputActionValue& Value);

private:
    UPROPERTY()
    AAnabiosisOriginCharacter* ControlledCharacter;
};
