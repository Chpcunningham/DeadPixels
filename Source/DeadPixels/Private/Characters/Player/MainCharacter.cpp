// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/MainCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameTags/PlayerTagManager.h"
#include "Kismet/KismetMathLibrary.h"

AMainCharacter::AMainCharacter()
{
	//Set up rotation for hit boxes
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetSprite()->SetUsingAbsoluteRotation(true);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetWorldRotation(FRotator(270.f, 270.f, 0));
	SpringArm->SetUsingAbsoluteRotation(true);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(SpringArm);
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 800.f;
	
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetAnimationComponent()->SetAnimInstanceClass(PlayerInstance);
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		PlayerController->SetShowMouseCursor(true);
		if (UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			PlayerSubsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void AMainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		FHitResult MouseHit;
		PlayerController->GetHitResultUnderCursorByChannel(TraceTypeQuery1, true,MouseHit);

		FVector MouseWorldLocation = MouseHit.Location - GetActorLocation();
		Directionality = UKismetMathLibrary::MakeVector2D(MouseWorldLocation.X, MouseWorldLocation.Y);
		UKismetMathLibrary::Normalize2D(Directionality);
	}
}

void AMainCharacter::Movement(const FInputActionValue& Value)
{
	if (PlayerTags.HasTag(Movement_State_Running) ? GetCharacterMovement()->MaxWalkSpeed = RunSpeed : GetCharacterMovement()->MaxWalkSpeed = WalkSpeed) {}
	FVector2D MovementDirection = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, MovementDirection.X);
	AddMovementInput(RightVector, MovementDirection.Y);
}
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Movement);
	}
}


