#include "InventoryHelper.h"
#include "Engine/AssetManager.h"

UInventoryItemData* UInventoryHelper::GetInventoryItemData(const FPrimaryInventoryItemId& ItemId,
                                                           const TArray<FName>& InBundles)
{
	if (const auto AssetManager = UAssetManager::GetIfValid())
	{
		const auto StreamableHandler = AssetManager->LoadPrimaryAsset(ItemId, InBundles);
		if (StreamableHandler.IsValid())
		{
			// New loading asset
			StreamableHandler->WaitUntilComplete(); // Can add timeout for loading asset
			return Cast<UInventoryItemData>(StreamableHandler->GetLoadedAsset());
		}

		// Loading from memory
		return AssetManager->GetPrimaryAssetObject<UInventoryItemData>(ItemId);
	}

	return nullptr;
}
