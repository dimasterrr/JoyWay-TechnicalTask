#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryItemInterface.generated.h"

UINTERFACE()
class UInventoryItemInterface : public UInterface
{
	GENERATED_BODY()
};

class JOYWAY_TECHNICALTASK_API IInventoryItemInterface
{
	GENERATED_BODY()
	
public:

	// TODO: Replace this logic to GameplayAbilitySystem Modifiers
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Inventory)
	bool Consume(AActor* Consumer);
};
