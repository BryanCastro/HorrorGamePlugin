// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MovementComp.h"
#include "GameUtils.h"



// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0, 0, 60.0f));
	Camera->bUsePawnControlRotation = true;


	FlashLightSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	FlashLightSpringArm->SetupAttachment(Camera);

	FlashLight = CreateDefaultSubobject<USpotLightComponent>((TEXT("Flash Light")));
	FlashLight->SetupAttachment(FlashLightSpringArm);

	MovementComp = CreateDefaultSubobject<UMovementComp>((TEXT("Movement Comp")));
	AddOwnedComponent(MovementComp);

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::Initialize() {
	if (MovementComp)
		MovementComp->Initialize(this);
	else
		GameUtils::LogMessage("PlayerCharacter.cpp: Failed to Find a MovementComp");
}

AActor* APlayerCharacter::LineTrace(float Length) {

	UWorld* World = GetWorld();
	FHitResult OutHit;
	FVector Start = Camera->GetComponentLocation();
	FVector End = Camera->GetForwardVector() * Length;
	bool bHit = World->LineTraceSingleByChannel(OutHit, Start, Start+End, ECollisionChannel::ECC_Visibility);

	if (bHit)
		return OutHit.GetActor();
	return nullptr;
}

void APlayerCharacter::DisplayDebugLine(bool success, float Length, FVector HitLocation) {
	UWorld* World = GetWorld();
	FVector Start = Camera->GetComponentLocation();
	FVector End = Camera->GetForwardVector() * Length;

	if (success) {
		DrawDebugLine(World, Start, Start + End, FColor::Green, false, 5.0f, 0, 1);
		DrawDebugPoint(World, HitLocation, 5, FColor::Yellow, false, 5.0f);
	}
	else {
		DrawDebugLine(World, Start, Start + End, FColor::Red, false, 5.0f, 0, 1);
		DrawDebugPoint(World, HitLocation, 5, FColor::Yellow, false, 5.0f);
	}
	
}

void APlayerCharacter::TurnOnFlashLight(bool bTurnOnFlashLight) {
	if (bTurnOnFlashLight)
		FlashLight->SetVisibility(true);
	else
		FlashLight->SetVisibility(false);
}

UMovementComp* APlayerCharacter::GetMovementComp() {
	return MovementComp;
}