// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



APlayerCharacter::APlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SocketOffset = FVector(0.0f, 50.0f, 75.0f);
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	AIStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AI Stimuli Source Component"));
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Camera bindings
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);

	// Jump bidings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Fire bindings
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFiring);

	// Sprint bindings
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::SprintPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::SprintReleased);
}

// Move forward input
void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

// Move right input
void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

// Sprint press input
void APlayerCharacter::SprintPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMaxSpeed;

	StopFiring();
}

// Sprint release input
void APlayerCharacter::SprintReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxSpeed;
}

void APlayerCharacter::Death_Implementation()
{
	DeathParent();

	DisableInput(GetWorld()->GetFirstPlayerController());
}