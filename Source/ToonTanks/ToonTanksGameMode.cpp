// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include"Tower.h"
#include "EnemyTanks.h"
#include "ToonTanksPlayerController.h"

//Destroy Actor when health <= 0
void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        --NumberEnemy;
        if(NumberEnemy == 0)
            {
                 GameOver(true);
            }
    }
    else if (AEnemyTanks* DestroyedEnemyTanks = Cast<AEnemyTanks>(DeadActor))
    {
        DestroyedEnemyTanks->HandleDestruction();
        --NumberEnemy;
        if(NumberEnemy == 0)
            {
                 GameOver(true);
            }
    }
}


void AToonTanksGameMode::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart();
}
//Game Start Setting
void AToonTanksGameMode::HandleGameStart()
{
    NumberEnemy = GetNumberEnemy();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    //Blueprint
    StartGame();

//Call SetPlayerEnabledState(true) after 4 sec
    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController, 
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false
        );
    }
}
//Number of Towers in game
int32 AToonTanksGameMode::GetNumberEnemy()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    TArray<AActor*> Tanks;
    UGameplayStatics::GetAllActorsOfClass(this, AEnemyTanks::StaticClass(), Tanks);
    return Towers.Num() + Tanks.Num();
}