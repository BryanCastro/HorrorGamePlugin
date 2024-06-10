// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrabbableActorBase.h"
#include "PhysicsDoor.generated.h"

class UStaticMeshComponent;
class UPhysicsConstraintComponent;

UCLASS()
class HORRORGAMEPLUGIN_API APhysicsDoor : public AGrabbableActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsDoor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* DoorFrame;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Door;

	UPROPERTY(VisibleAnywhere)
	UPhysicsConstraintComponent* MyPhysicsConstraint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Grabbed(FVector2D Axis) override;

	void MoveDoor(float Amount);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
