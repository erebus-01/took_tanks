// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	//Returns a pointer to the player's pawn
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(TimeRate, this, &ATower::CheckFireCondition, FireRate, true);
	
}

void ATower::CheckFireCondition()
{
	if(InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange() const
{
	if(Tank)
	{
		float const Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if(Distance <= FireTurret)
		{
			return true;
		}
	}

	return false;
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}
