#pragma once
#include "CoreMinimal.h"
#include "JoyWay_TechnicalTask/Components/Inventory/Types/InventoryItemData.h"
#include "MedKitDataAsset.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API UMedKitDataAsset : public UInventoryItemData
{
	GENERATED_BODY()

public:
	virtual bool Consume_Implementation(AActor* Consumer) override;
};
