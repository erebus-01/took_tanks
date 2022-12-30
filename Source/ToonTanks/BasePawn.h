// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurret(FVector LookAt);
	void Fire();

private:
	//Box Tank
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Component", meta=(AllowPrivateAccess="true"))
	UBoxComponent* BoxComponent;

	
	//Capsule actor for collision
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Capsule Component", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* CapsuleComponent;

	//Create element tank(Bottom)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Component", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* BaseMesh;

	//Create element tank(Top)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Component", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* TurretMesh;

	//Bullet point
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Component", meta=(AllowPrivateAccess="true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<AProjectile> ProjectileClass;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
