#pragma once
#include "CoreMinimal.h"
#include "JoyWay_TechnicalTask/Components/Interaction/Types/InteractionInterface.h"
#include "JoyWay_TechnicalTask/Components/Inventory/Types/InventoryItemData.h"
#include "WeaponAbstract.generated.h"

UCLASS(Abstract)
class JOYWAY_TECHNICALTASK_API AWeaponAbstract : public AActor
{
	GENERATED_BODY()
	
private:
	// Timer handlers
	FTimerHandle DelayBetweenTimeHandle;
	FTimerHandle ReloadFireTimeHandle;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=Components)
	class USceneComponent* Root;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=Components)
	class USkeletalMeshComponent* Mesh;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=Components)
	class UArrowComponent* SpawnPoint;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Settings)
	float FireRate = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings|Effects")
	UParticleSystem* FireEmitterTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	USoundBase* FireSoundTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	UAnimMontage* OwnerFireAnimMontage;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Settings)
	int32 MaxAmmoCount = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Settings)
	int32 CurrentAmmoCount = 10;

private:
	UFUNCTION(BlueprintCallable)
	void OnFireReload();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintPure)
	bool CanReload();

	UFUNCTION(BlueprintPure)
	bool CanFire() const;

	UFUNCTION(BlueprintPure)
	bool HasAmmo() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnReloadEvent();
	virtual void OnReload();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnFireEvent();
	virtual void OnFire();

public:
	AWeaponAbstract();

	UFUNCTION(BlueprintCallable, Category=Fire)
	void FireStart();

	UFUNCTION(BlueprintCallable, Category=Fire)
	void FireStop();
	
	UFUNCTION(BlueprintCallable, Category=Fire)
	void Reload();

	UFUNCTION(BlueprintCallable, Category=Fire)
	void AddAmmo(int Value);
};
