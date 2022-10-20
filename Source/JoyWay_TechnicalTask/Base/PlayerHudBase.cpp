#include "PlayerHudBase.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

UUserWidget* APlayerHudBase::CreateWidgetByClass(const TSubclassOf<UUserWidget> Class, const int ZOrder) const
{
	const auto NewWidget = CreateWidget<UUserWidget>(GetWorld(), Class);
	NewWidget->AddToViewport(ZOrder);

	return NewWidget;
}

UUserWidget* APlayerHudBase::ShowWidget(const EScreenWidgetType Type, const int ZOrder)
{
	HideWidget();

	const auto WidgetClass = WidgetsMap.Find(Type);
	if (WidgetClass && *WidgetClass)
	{
		CurrentWidgetReference = CreateWidgetByClass(*WidgetClass, ZOrder);
		WidgetChanged.Broadcast(Type);
	}

	return CurrentWidgetReference;
}

void APlayerHudBase::HideWidget()
{
	if (!CurrentWidgetReference) return;

	CurrentWidgetReference->RemoveFromParent();
	CurrentWidgetReference = nullptr;
}

UUserWidget* APlayerHudBase::GetCurrentWidget() const
{
	return CurrentWidgetReference;
}

EScreenWidgetType APlayerHudBase::GetCurrentWidgetType() const
{
	const auto CurrentWidget = GetCurrentWidget();
	if (!CurrentWidget) return EScreenWidgetType::None;

	return *WidgetsMap.FindKey(CurrentWidget->GetClass());
}

void APlayerHudBase::SetHudMode(const bool IsPaused, const bool IsUiOnly, UUserWidget* FocusWidget) const
{
	const auto PlayerController = GetOwningPlayerController();

	// Set Game Paused
	UGameplayStatics::SetGamePaused(PlayerController->GetWorld(), IsPaused);

	// Set Ui Mode
	PlayerController->SetShowMouseCursor(IsUiOnly);

	if (IsUiOnly) UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, FocusWidget);
	else UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
}

// Helpers
template <class T>
T* APlayerHudBase::GetCurrentWidget() const
{
	return Cast<T>(CurrentWidgetReference);
}
