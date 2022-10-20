#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JoyWay_TechnicalTask/Components/Inventory/Types/InventoryComponentInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API APlayerCharacter : public ACharacter, public IInventoryComponentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	class UWidgetInteractionComponent* WidgetInteractionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	class UInventoryEquipComponent* InventoryEquipComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	class UArrowComponent* WeaponSetupPoint;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Settings)
	float TurnRateGamepad = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	TArray<class AWeaponAbstract*> EquippedWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	int32 EquipWeaponIndex = INDEX_NONE;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void InteractStart();
	void InteractStop();
	
	void FireStart();
	void FireStop();
	void Reload();

	void SwitchWeaponUp();
	void SwitchWeaponDown();

	void Inventory();

	void SetWeapon(TSubclassOf<AWeaponAbstract> WeaponClass);
	void SetEquipWeapon(int32 NewIndex);

protected:
	UFUNCTION()
	void OnInventorySlotEquipped(EInventoryEquipSlot Slot, FPrimaryInventoryItemId Item);

	UFUNCTION()
	void OnInventorySlotUnEquipped(EInventoryEquipSlot Slot, FPrimaryInventoryItemId Item);

	UFUNCTION()
	void OnDie();

public:
	APlayerCharacter();
	virtual void Destroyed() override;

	UFUNCTION(BlueprintPure, Category=Components)
	virtual UInventoryComponent* GetInventoryComponent() const override;

	UFUNCTION(BlueprintPure, Category=Weapons)
	class AWeaponAbstract* GetEquipWeapon() const;

	UFUNCTION(BlueprintPure, Category=Weapons)
	const TArray<AWeaponAbstract*>& GetEquippedWeapons() const;
};