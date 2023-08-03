// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "Interactable.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	MoveDir = Value.Get<FVector>();
	AddMovementInput(GetActorForwardVector(), MoveDir.Y);
	AddMovementInput(GetActorRightVector(), MoveDir.X);
}

void APlayerCharacter::StopMovement()
{
	MoveDir = FVector::Zero();
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector Dir = Value.Get<FVector>();
	AddControllerYawInput(Dir.X);
	AddControllerPitchInput(Dir.Y);
}

void APlayerCharacter::Interact()
{
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Camera->GetComponentLocation(), Camera->GetComponentLocation() + Camera->GetForwardVector() * InteractDistance, ECollisionChannel::ECC_Camera))
	{
		if (HitResult.GetActor()->Implements<UInteractable>())
		{
			IInteractable* Interactable = Cast<IInteractable>(HitResult.GetActor());
			Interactable->Execute_InteractWith(HitResult.GetActor());
		}
	}
}

void APlayerCharacter::Swing_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Swing"));
}

