#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOYWAY_TECHNICALTASK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float, OldHealth, float, NewHealth);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDieDelegate);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	float Health = 100.f;

public:
	UPROPERTY(BlueprintAssignable, Category=Hendlers)
	FOnHealthChangedDelegate OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category=Hendlers)
	FOnDieDelegate OnDieDelegate;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
	                  AActor* DamageCauser);

public:
	UFUNCTION(BlueprintPure)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(const float NewHealth, const bool IsForce = false);

	UFUNCTION(BlueprintCallable)
	bool IsDie() const;
};
