#pragma once

#include "CoreMinimal.h"
#include "JoyWay_TechnicalTask/Components/Inventory/Types/InventoryItemData.h"
#include "InventoryHelper.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API UInventoryHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category=Inventory)
	static UInventoryItemData* GetInventoryItemData(const FPrimaryInventoryItemId& ItemId,
	                                                const TArray<FName>& InBundles);
};
