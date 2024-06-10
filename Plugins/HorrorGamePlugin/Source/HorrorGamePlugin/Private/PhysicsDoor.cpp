// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsDoor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Math/Rotator.h"
#include "Math/UnrealMathUtility.h"
#include "GameUtils.h"
#include "PlayerCharacter.h"

// Sets default values
APhysicsDoor::APhysicsDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	MyPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("MyPhysicsConstraint"));

	RootComponent=DoorFrame;
	Door->SetupAttachment(DoorFrame);
	MyPhysicsConstraint->SetupAttachment(RootComponent);
	
	Door->SetSimulatePhysics(true);
	Door->SetMassOverrideInKg(NAME_None, 150.0f);
	Door->SetAngularDamping(4.0f);
	
	// Set the constrained components
	MyPhysicsConstraint->SetConstrainedComponents(DoorFrame, NAME_None, Door, NAME_None);
	MyPhysicsConstraint->SetDisableCollision(true);

	// Lock all linear motion
	MyPhysicsConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MyPhysicsConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	MyPhysicsConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

	// Lock all angular motion
	MyPhysicsConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, 90.0f);
	MyPhysicsConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	MyPhysicsConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);

	MyPhysicsConstraint->ConstraintInstance.SetProjectionParams(true, 1.0, 0.0f, 5.0, 90.0f);
}

// Called when the game starts or when spawned
void APhysicsDoor::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void APhysicsDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void APhysicsDoor::Grabbed(FVector2D Axis) {
	//GameUtils::LogMessage("PhysicsDoor.cpp: Successfully Grabbed Actor!", FColor::Green);
	float Amount = Axis.Y;
	MoveDoor(Amount);
}

void APhysicsDoor::MoveDoor(float Amount) {

	if (PlayerRef) {
		FVector PlayerLocation = PlayerRef->GetActorLocation();
		FVector DoorLocation = GetActorLocation();
		FVector DistanceVector = DoorLocation - PlayerLocation;
		DistanceVector.Normalize();

		//Check Location Door is Pointing from Player using Dot Product
		FVector DoorForward = GetActorForwardVector();

		float DotProduct = FVector::DotProduct(DistanceVector, DoorForward);

		if (DotProduct >= 0)
			Amount *= 1.0f;
		else
			Amount *= -1.0f;


		FRotator YawRotator = FRotator(0.0f, Amount, 0.0f);
		FRotator CurrentRotation = Door->GetRelativeRotation();
		FRotator NewRotation = CurrentRotation + YawRotator;

		Door->SetRelativeRotation(NewRotation);
	}
	else {
		GameUtils::LogMessage("PhysicsDoor.cpp: Failed to Get Player Reference!", FColor::Red);
	}

}