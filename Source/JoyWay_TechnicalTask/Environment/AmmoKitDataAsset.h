#pragma once
#include "CoreMinimal.h"
#include "JoyWay_TechnicalTask/Components/Inventory/Types/InventoryItemData.h"
#include "AmmoKitDataAsset.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API UAmmoKitDataAsset : public UInventoryItemData
{
	GENERATED_BODY()

public:
	virtual bool Consume_Implementation(AActor* Consumer) override;
};
