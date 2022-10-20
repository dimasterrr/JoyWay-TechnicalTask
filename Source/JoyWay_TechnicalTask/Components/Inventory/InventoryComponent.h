#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryItemData.h"
#include "InventoryComponent.generated.h"

// UENUM()
// enum class EInventoryChangedOperation : uint8 { Add, Remove, Update };

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOYWAY_TECHNICALTASK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryItemsChanged);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Inventory)
	int32 MaxSlots = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Inventory)
	TArray<FInventoryItemSlot> Items;

public:
	UPROPERTY(BlueprintAssignable, Category=Inventory)
	FInventoryItemsChanged InventoryItemsChanged;
	
public:
	UInventoryComponent();

	UFUNCTION(BlueprintPure, Category=Inventory)
	const TArray<FInventoryItemSlot>& GetItems() const;

	UFUNCTION(BlueprintCallable, Category=Inventory)
	virtual bool AddItem(const FPrimaryInventoryItemId& ItemId, const int32 Count, int32& OutItemIndex);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	virtual bool RemoveItem(const FPrimaryInventoryItemId& ItemId, const int32 Count);

	UFUNCTION(BlueprintPure, Category=Inventory)
	bool HasFreeSlots() const;
};
