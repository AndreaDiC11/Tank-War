// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTanks.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void AEnemyTanks::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(InMoveRange() && !InStopRange())
    {   
        // If in range, rotate turret toward Tank
        RotateTurret(Tank->GetActorLocation());
        Move();
    }
    else if(InStopRange())
    {
        RotateTurret(Tank->GetActorLocation());
        StopMove();
    }
    
        
    
}

void AEnemyTanks::HandleDestruction()//modifica in basepawn
{
    Super::HandleDestruction();
    Destroy();
}

void AEnemyTanks::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
  
    //Every 2 seconds(FireRate) calls the function CheckFireCondition
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTanks::CheckFireCondition, FireRate, true);
}

void AEnemyTanks::CheckFireCondition()
{
    if(Tank == nullptr)
    {
        return;
    }
    if(InFireRange() && Tank->bAlive)
    {
        Fire();
    }
}


bool AEnemyTanks::InFireRange()
{
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance <= FireRange)
        {
            return true;
        }
    }
    
    return false;
}

bool AEnemyTanks::InMoveRange()
{
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance <= MoveRange && Distance >= StopRange)
        {
            return true;
        }
    }
    
    return false;
}

bool AEnemyTanks::InStopRange()
{
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance <= StopRange || Distance >= MoveRange)
        {
            return true;
        }
    }
    
    return false;
}