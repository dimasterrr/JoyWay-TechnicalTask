#include "ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AProjectileBase::AProjectileBase()
{
	RootComponent = Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->OnProjectileBounce.AddDynamic(this, &AProjectileBase::OnBounce);
}

UProjectileMovementComponent* AProjectileBase::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}

void AProjectileBase::ApplyDamage(const FHitResult& ImpactResult, bool& TargetIsDie) const
{
	if (const auto TargetActor = ImpactResult.GetActor())
	{
		TargetActor->TakeDamage(Damage, FDamageEvent(DamageType), GetInstigatorController(), GetOwner());
	}
}

void AProjectileBase::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BounceEmitterTemplate, ImpactResult.Location);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BounceSoundTemplate, ImpactResult.Location);

	auto TargetIsDie = false;
	ApplyDamage(ImpactResult, TargetIsDie);

	Release();
}

void AProjectileBase::OnActivated()
{
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);

	const auto DefaultMovement = GetClass()->GetDefaultObject<AProjectileBase>()->ProjectileMovementComponent;
	const auto NewVelocity = DefaultMovement->InitialSpeed > 0.f
		                         ? DefaultMovement->Velocity.GetSafeNormal() * DefaultMovement->InitialSpeed
		                         : DefaultMovement->Velocity;
	ProjectileMovementComponent->SetVelocityInLocalSpace(NewVelocity);
}

void AProjectileBase::OnReleased()
{
}
