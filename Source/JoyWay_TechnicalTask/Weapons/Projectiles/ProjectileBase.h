#pragma once
#include "CoreMinimal.h"
#include "JoyWay_TechnicalTask/Components/ActorPollComponent/Types/ActorPoolable.h"
#include "ProjectileBase.generated.h"

UCLASS()
class JOYWAY_TECHNICALTASK_API AProjectileBase : public AActorPoolable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	UParticleSystem* BounceEmitterTemplate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	USoundBase* BounceSoundTemplate;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

	void ApplyDamage(const FHitResult& ImpactResult, bool& TargetIsDie) const;

public:
	AProjectileBase();
	UProjectileMovementComponent* GetProjectileMovementComponent() const;

protected:
	virtual void OnActivated() override;
	virtual void OnReleased() override;
};
