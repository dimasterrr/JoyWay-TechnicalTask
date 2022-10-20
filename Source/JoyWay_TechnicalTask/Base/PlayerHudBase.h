#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHudBase.generated.h"

UENUM(BlueprintType)
enum class EScreenWidgetType : uint8
{
	None,
	PlayerScreen,
	PlayerDeathScreen,
	InventoryScreen,
	MapSelectorScreen,
};

UCLASS()
class JOYWAY_TECHNICALTASK_API APlayerHudBase : public AHUD
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_OneParam(FWidgetChanged, EScreenWidgetType /* To */);

protected:
	UPROPERTY(BlueprintReadOnly)
	UUserWidget* CurrentWidgetReference;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EScreenWidgetType, TSubclassOf<UUserWidget>> WidgetsMap;

	FWidgetChanged WidgetChanged;

private:
	UUserWidget* CreateWidgetByClass(const TSubclassOf<UUserWidget> Class, const int ZOrder = 0) const;

public:
	UFUNCTION(BlueprintCallable)
	UUserWidget* ShowWidget(const EScreenWidgetType Type, const int ZOrder = 0);

	UFUNCTION(BlueprintCallable)
	void HideWidget();

	UFUNCTION(BlueprintPure)
	UUserWidget* GetCurrentWidget() const;

	UFUNCTION(BlueprintPure)
	EScreenWidgetType GetCurrentWidgetType() const;

	UFUNCTION(BlueprintCallable)
	void SetHudMode(const bool IsPaused, const bool IsUiOnly, UUserWidget* FocusWidget = nullptr) const;

	// Helpers
	template <class T>
	T* GetCurrentWidget() const;
};
