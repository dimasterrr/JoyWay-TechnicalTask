#include "PickupItem.h"

#include "JoyWay_TechnicalTask/Components/Inventory/InventoryComponent.h"
#include "JoyWay_TechnicalTask/Components/Inventory/Types/InventoryComponentInterface.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickupItem::Interaction_Implementation(AActor* InInstigator)
{
	if (const auto InventoryOwner = Cast<IInventoryComponentInterface>(InInstigator))
	{
		const auto InventoryComponent = InventoryOwner->GetInventoryComponent();
		
		int32 InsertedItemIndex = INDEX_NONE;
		if (InventoryComponent->AddItem(InventoryItemId, 1, InsertedItemIndex))
		{
			Destroy();
		}
	}
}