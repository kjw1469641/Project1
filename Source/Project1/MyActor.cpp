// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	TotalDistance = 0.0f;
	Count = 0;
	LastLocation = GetActorLocation();

	for (int32 i = 0; i < 10; ++i)
	{
		TriggerEvent();
	}

	FString ResultMessage = FString::Printf(TEXT("총 이동 거리: %.2f, 총 이벤트 발생 횟수: %d"), TotalDistance, Count);
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Yellow, ResultMessage);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ResultMessage);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::Move()
{
    FVector StartLocation = GetActorLocation();

    FVector Target;
    Target.X = FMath::FRandRange(-50.0, 50.0);
    Target.Y = FMath::FRandRange(-50.0, 50.0);
    Target.Z = 0;
    AddActorWorldOffset(Target);

    FVector CurrentLocation = GetActorLocation();

    TotalDistance += FVector::Dist(StartLocation, CurrentLocation);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, CurrentLocation.ToString());
    UE_LOG(LogTemp, Warning, TEXT("Move: %s"), *CurrentLocation.ToString());
}

void AMyActor::Turn()
{
    FRotator DeltaRotation;
    DeltaRotation.Yaw = FMath::FRandRange(-180.0, 180.0);
    DeltaRotation.Pitch = 0;
    DeltaRotation.Roll = 0;

    AddActorWorldRotation(DeltaRotation);

    FRotator CurrentRotation = GetActorRotation();

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, CurrentRotation.ToString());
    UE_LOG(LogTemp, Warning, TEXT("Turn: %s"), *CurrentRotation.ToString());
}

void AMyActor::TriggerEvent()
{
    if (FMath::RandRange(0, 1) == 0)
    {
        FString DebugMessage = FString::Printf(TEXT("이동 %d번째 출력: "), MoveCount);
        GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, DebugMessage);
        Move();
        MoveCount++;
        Count++;
    }

    if (FMath::RandRange(0, 1) == 0)
    {
        FString DebugMessage = FString::Printf(TEXT("회전 %d번째 출력: "), TurnCount);
        GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, DebugMessage);
        Turn();
        TurnCount++;
        Count++;
    }
}