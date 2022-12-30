// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	
	
protected:
	virtual void BeginPlay() override;

private:
	ATank* Tank;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float FireTurret = 1200.f;

	FTimerHandle TimeRate;
	float FireRate = 2.f;

	void CheckFireCondition();

	bool InFireRange() const;
	
};
