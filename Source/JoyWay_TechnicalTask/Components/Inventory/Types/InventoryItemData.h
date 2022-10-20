#pragma once
#include "CoreMinimal.h"
#include "InventoryItemInterface.h"
#include "InventoryItemData.generated.h"

static const FPrimaryAssetType InventoryItemsType = TEXT("InventoryItemData");

UENUM(BlueprintType)
enum class EInventoryItemType : uint8
{
	None,
	Consumable,
	Weapon,
	Quest
};

UENUM(BlueprintType)
enum class EInventoryEquipSlot : uint8
{
	None,

	// Weapons
	PrimaryWeapon,
	SpecialWeapon,
};

UCLASS(Blueprintable, NotPlaceable)
class JOYWAY_TECHNICALTASK_API UInventoryItemData : public UPrimaryDataAsset, public IInventoryItemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory, meta=(AssetBundles=Data))
	int32 Id;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory, meta=(AssetBundles=Data))
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory, meta=(AssetBundles=Data))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory, meta=(AssetBundles=Data))
	EInventoryItemType Type = EInventoryItemType::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory, meta=(AssetBundles=Data))
	EInventoryEquipSlot EquipSlot = EInventoryEquipSlot::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory, meta=(AssetBundles=Data))
	bool IsStackable = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory, meta=(AssetBundles=UI))
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory, meta=(AssetBundles=SoftData))
	TSubclassOf<AActor> WorldStaticItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory, meta=(AssetBundles=SoftData))
	TSubclassOf<UObject> ItemClass;

public:
	explicit UInventoryItemData(const FObjectInitializer& ObjectInitializer);
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	virtual bool Consume_Implementation(AActor* Consumer) override;
};

USTRUCT(BlueprintType)
struct FPrimaryInventoryItemId : public FPrimaryAssetId
{
	GENERATED_USTRUCT_BODY()
	FPrimaryInventoryItemId();
	explicit FPrimaryInventoryItemId(const FPrimaryAssetId& InId);
	explicit FPrimaryInventoryItemId(const FString& TypeAndName);
};

USTRUCT(BlueprintType)
struct FInventoryItemSlot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory)
	FPrimaryInventoryItemId ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	int32 Count = 1;
	
public:
	FInventoryItemSlot() = default;
	explicit FInventoryItemSlot(const FPrimaryInventoryItemId& ItemId);
	explicit FInventoryItemSlot(const FPrimaryInventoryItemId& ItemId, const int32& Count = 1);
};
