// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	
	ArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Component"));
	ArmComponent->SetupAttachment(RootComponent);
	ArmComponent->TargetArmLength = 300.f;
	ArmComponent->bUsePawnControlRotation = true;

	FollowActor = CreateDefaultSubobject<UCameraComponent>(TEXT("CCamera Component"));
	FollowActor->SetupAttachment(ArmComponent, USpringArmComponent::SocketName);
	FollowActor->bUsePawnControlRotation = false;
	
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());

	
}

void ATank::Move(float const Value)
{
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);

	
	UE_LOG(LogTemp, Display, TEXT("Moving: %f"), Value);
}

void ATank::Turn(float const Value)
{
	FRotator DeltaRotator = FRotator::ZeroRotator;
	DeltaRotator.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotator);
	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 5, FColor::Red, false, -1.f);
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Add input moving actor
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	//Fire
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
	PlayerInputComponent->BindAction(TEXT("FireSpace"), IE_Pressed, this, &ATank::Fire);

}
