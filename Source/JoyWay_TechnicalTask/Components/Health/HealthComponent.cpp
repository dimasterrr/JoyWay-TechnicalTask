#include "HealthComponent.h"

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const auto TargetOwner = GetOwner())
	{
		TargetOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
	}
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

void UHealthComponent::SetHealth(const float NewHealth, const bool IsForce)
{
	if (IsDie()) return;

	const auto OldHealth = Health;
	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);

	if (IsForce) return;
	if (IsDie()) OnDieDelegate.Broadcast();
	else OnHealthChangedDelegate.Broadcast(OldHealth, NewHealth);
}

bool UHealthComponent::IsDie() const
{
	return FMath::IsNearlyZero(Health);
}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
									AController* InstigatedBy, AActor* DamageCauser)
{
	SetHealth(Health - Damage);
}