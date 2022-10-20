#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "JoyWay_TechnicalTask/Components/Health/HealthComponent.h"
#include "JoyWay_TechnicalTask/Components/Inventory/Types/InventoryItemData.h"
#include "SaveGameInfo.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API USaveGameInfo : public USaveGame
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SaveSlot)
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SaveSlot)
	TArray<FInventoryItemSlot> InventorySlots;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SaveSlot)
	TArray<FInventoryItemSlot> EquipSlots;
	
public:
	UFUNCTION(BlueprintCallable, Category=SaveSlot)
	void CollectData(const UWorld* World);

	UFUNCTION(BlueprintCallable, Category=SaveSlot)
	void ApplyData(const UWorld* World);
};
