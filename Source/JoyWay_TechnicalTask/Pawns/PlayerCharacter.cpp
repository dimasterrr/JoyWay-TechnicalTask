#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JoyWay_TechnicalTask/Base/PlayerHudBase.h"
#include "JoyWay_TechnicalTask/Components/Health/HealthComponent.h"
#include "JoyWay_TechnicalTask/Components/Interaction/InteractionComponent.h"
#include "JoyWay_TechnicalTask/Components/Inventory/InventoryComponent.h"
#include "JoyWay_TechnicalTask/Components/Inventory/InventoryEquipComponent.h"
#include "JoyWay_TechnicalTask/Components/Inventory/Helpers/InventoryHelper.h"
#include "JoyWay_TechnicalTask/Helpers/GeneralHelper.h"
#include "JoyWay_TechnicalTask/Weapons/WeaponAbstract.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;

	// Camera component
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh());
	// OR if mesh exist
	// FollowCamera->SetupAttachment(GetMesh(), TEXT("head"));
	FollowCamera->bUsePawnControlRotation = true;

	WeaponSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Weapon Point"));
	WeaponSetupPoint->SetupAttachment(FollowCamera);
	// OR if mesh exist
	// WeaponSetupPoint->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WInteractionComponent"));
	WidgetInteractionComponent->SetupAttachment(FollowCamera);

	// Health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDieDelegate.AddDynamic(this, &APlayerCharacter::OnDie);
	AddOwnedComponent(HealthComponent);

	// Interaction Component
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	AddOwnedComponent(InteractionComponent);

	// InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	AddOwnedComponent(InventoryComponent);

	InventoryEquipComponent = CreateDefaultSubobject<UInventoryEquipComponent>(TEXT("InventoryEquipComponent"));
	InventoryEquipComponent->InventorySlotEquipped.AddDynamic(this, &APlayerCharacter::OnInventorySlotEquipped);
	InventoryEquipComponent->InventorySlotUnEquipped.AddDynamic(this, &APlayerCharacter::OnInventorySlotUnEquipped);
	AddOwnedComponent(InventoryEquipComponent);
}

void APlayerCharacter::Destroyed()
{
	for (const auto& Item : EquippedWeapons) Item->Destroy();
	EquippedWeapons.Empty();

	Super::Destroyed();
}

UInventoryComponent* APlayerCharacter::GetInventoryComponent() const
{
	return InventoryComponent;
}

AWeaponAbstract* APlayerCharacter::GetEquipWeapon() const
{
	return EquippedWeapons.IsValidIndex(EquipWeaponIndex) ? EquippedWeapons[EquipWeaponIndex] : nullptr;
}

const TArray<AWeaponAbstract*>& APlayerCharacter::GetEquippedWeapons() const
{
	return EquippedWeapons;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down", this, &APlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::InteractStart);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &APlayerCharacter::InteractStop);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::FireStart);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::FireStop);
	
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);
	
	PlayerInputComponent->BindAction("Switch Weapon Up", IE_Pressed, this, &APlayerCharacter::SwitchWeaponUp);
	PlayerInputComponent->BindAction("Switch Weapon Down", IE_Pressed, this, &APlayerCharacter::SwitchWeaponDown);
	
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::Inventory);
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const auto Rotation = Controller->GetControlRotation();
		const auto YawRotation = FRotator(0, Rotation.Yaw, 0);

		const auto Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const auto Rotation = Controller->GetControlRotation();
		const auto YawRotation = FRotator(0, Rotation.Yaw, 0);

		const auto Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::InteractStart()
{
	if (WidgetInteractionComponent->IsOverInteractableWidget())
	{
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
	}
	else
	{
		InteractionComponent->Interact();
	}
}

void APlayerCharacter::InteractStop()
{
	if (WidgetInteractionComponent->IsOverInteractableWidget())
	{
		WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
	} else
	{
		// TODO: Add Interaction End for hold button logic
	}
}

void APlayerCharacter::FireStart()
{
	const auto Weapon = GetEquipWeapon();
	if (!Weapon) return;

	Weapon->FireStart();
}

void APlayerCharacter::FireStop()
{
	const auto Weapon = GetEquipWeapon();
	if (!Weapon) return;

	Weapon->FireStop();
}

void APlayerCharacter::Reload()
{
	const auto Weapon = GetEquipWeapon();
	if (!Weapon) return;

	Weapon->Reload();
}

void APlayerCharacter::SetWeapon(const TSubclassOf<AWeaponAbstract> WeaponClass)
{
	if (!WeaponClass) return;

	FActorSpawnParameters Parameters;
	Parameters.Instigator = this;
	Parameters.Owner = this;

	const auto NewWeapon = GetWorld()->SpawnActor<AWeaponAbstract>(WeaponClass, Parameters);
	NewWeapon->AttachToComponent(WeaponSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	NewWeapon->SetActorHiddenInGame(true);

	SetEquipWeapon(EquippedWeapons.Add(NewWeapon));
}

void APlayerCharacter::SetEquipWeapon(const int32 NewIndex)
{
	if (!EquippedWeapons.IsValidIndex(NewIndex)) return;

	FireStop();

	if (EquippedWeapons.IsValidIndex(EquipWeaponIndex))
	{
		const auto OldWeapon = EquippedWeapons[EquipWeaponIndex];
		OldWeapon->SetActorHiddenInGame(true);
	}

	const auto NewWeapon = EquippedWeapons[NewIndex];
	NewWeapon->SetActorHiddenInGame(false);

	EquipWeaponIndex = NewIndex;
}

void APlayerCharacter::SwitchWeaponUp()
{
	if (!EquippedWeapons.IsValidIndex(0)) return;
	SetEquipWeapon((EquipWeaponIndex + 1) % EquippedWeapons.Num());
}

void APlayerCharacter::SwitchWeaponDown()
{
	if (!EquippedWeapons.IsValidIndex(0)) return;
	SetEquipWeapon(EquipWeaponIndex - 1 < 0 ? EquippedWeapons.Num() - 1 : EquipWeaponIndex - 1);
}

void APlayerCharacter::Inventory()
{
	if (const auto Hud = UGeneralHelper::GetBasePlayerHud(GetWorld()))
	{
		const auto Inventory = Hud->ShowWidget(EScreenWidgetType::InventoryScreen);
		Hud->SetHudMode(false, true, Inventory);
	}
}

void APlayerCharacter::OnInventorySlotEquipped(EInventoryEquipSlot Slot, FPrimaryInventoryItemId Item)
{
	const auto ItemData = UInventoryHelper::GetInventoryItemData(Item, {"Data"});
	if (!ItemData) return;

	switch (Slot)
	{
	case EInventoryEquipSlot::PrimaryWeapon:
	case EInventoryEquipSlot::SpecialWeapon:
		{
			SetWeapon(ItemData->ItemClass.Get());
			break;
		}
	default: return;
	}
}

void APlayerCharacter::OnInventorySlotUnEquipped(EInventoryEquipSlot Slot, FPrimaryInventoryItemId Item)
{
	// TODO: UnEquip
}

void APlayerCharacter::OnDie()
{
	const auto PlayerHud = UGeneralHelper::GetBasePlayerHud(this);
	const auto DieScreen = PlayerHud->ShowWidget(EScreenWidgetType::PlayerDeathScreen);
	PlayerHud->SetHudMode(false, true, DieScreen);

	Destroy();
}
