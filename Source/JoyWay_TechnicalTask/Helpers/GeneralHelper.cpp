#include "GeneralHelper.h"

#include "JoyWay_TechnicalTask/Base/PlayerHudBase.h"
#include "Kismet/GameplayStatics.h"

APlayerHudBase* UGeneralHelper::GetBasePlayerHud(const UObject* WorldContextObject)
{
	const auto PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!PlayerController) return nullptr;

	return Cast<APlayerHudBase>(PlayerController->GetHUD());
}
