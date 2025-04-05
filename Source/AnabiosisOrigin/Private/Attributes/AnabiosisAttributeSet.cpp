#include "Attributes/AnabiosisAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Data/AnabiosisAttributeData.h"

UAnabiosisAttributeSet::UAnabiosisAttributeSet()
{
    // 初始化属性默认值
    // ...existing code...
}

void UAnabiosisAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    // 属性变化前的验证和调整
    if (Attribute == GetMaxHealthAttribute())
    {
        AdjustAttributeForMaxChange(Health, MaxHealth, NewValue);
    }
}

void UAnabiosisAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    // 处理属性变化后的效果
    // ...existing code...
}

void UAnabiosisAttributeSet::InitFromMetaDataTable(const UDataTable* DataTable)
{
    // 从数据表初始化属性
    // ...existing code...
}

void UAnabiosisAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue)
{
    // 调整属性值确保不超过最大值
    // ...existing code...
}