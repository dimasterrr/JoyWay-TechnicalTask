#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoyWay_TechnicalTask/Components/Interaction/Types/InteractionInterface.h"
#include "JoyWay_TechnicalTask/Components/Inventory/Types/InventoryItemData.h"
#include "PickupItem.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API APickupItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory)
	FPrimaryInventoryItemId InventoryItemId;

public:
	APickupItem();

	virtual void Interaction_Implementation(AActor* Instigator) override;
};
