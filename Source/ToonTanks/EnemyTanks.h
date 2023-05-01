// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyTanks.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyTanks : public ABasePawn
{
	GENERATED_BODY()

public:


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void Move();
	UFUNCTION(BlueprintImplementableEvent)
	void StopMove();

private:

	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, Category ="Combat")
	float FireRange = 300.f;
	UPROPERTY(EditDefaultsOnly, Category ="Combat")
	float MoveRange = 500.f;
	UPROPERTY(EditDefaultsOnly, Category ="Combat")
	float StopRange = 300,f;
	

	
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();


	bool InFireRange();
	bool InMoveRange();
	bool InStopRange();
};
