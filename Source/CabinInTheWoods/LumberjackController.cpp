// Fill out your copyright notice in the Description page of Project Settings.


#include "LumberjackController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ALumberjackController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		UE_LOG(LogTemp, Warning, TEXT("Mapping context added"));
	}

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	SetupInputComponent();
}

void ALumberjackController::SetupInputComponent()
{
	if (!PlayerCharacter)
	{
		return;
	}
	
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, PlayerCharacter, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, PlayerCharacter, &APlayerCharacter::StopMovement);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, PlayerCharacter, &APlayerCharacter::StopMovement);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, PlayerCharacter, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, PlayerCharacter, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(SwingAction, ETriggerEvent::Started, PlayerCharacter, &APlayerCharacter::Swing);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, PlayerCharacter, &APlayerCharacter::Interact);
	}
}
