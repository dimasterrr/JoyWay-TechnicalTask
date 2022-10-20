#include "AmmoKitDataAsset.h"

#include "JoyWay_TechnicalTask/Pawns/PlayerCharacter.h"
#include "JoyWay_TechnicalTask/Weapons/WeaponAbstract.h"

bool UAmmoKitDataAsset::Consume_Implementation(AActor* Consumer)
{
	if (const auto Character = Cast<APlayerCharacter>(Consumer))
	{
		for (const auto& Item : Character->GetEquippedWeapons())
		{
			Item->AddAmmo(Item->MaxAmmoCount);
		}
		return true;
	}
	
	return Super::Consume_Implementation(Consumer);
}
