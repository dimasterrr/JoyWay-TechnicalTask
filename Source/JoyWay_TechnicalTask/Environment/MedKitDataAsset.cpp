#include "MedKitDataAsset.h"
#include "JoyWay_TechnicalTask/Components/Health/HealthComponent.h"

bool UMedKitDataAsset::Consume_Implementation(AActor* Consumer)
{
	if (const auto Component = Cast<UHealthComponent>(Consumer->GetComponentByClass(UHealthComponent::StaticClass())))
	{
		Component->SetHealth(Component->GetHealth() + 100);
		return true;
	}
	
	return Super::Consume_Implementation(Consumer);
}