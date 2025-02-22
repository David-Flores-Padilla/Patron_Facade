// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DonkeyKong_L02GameMode.generated.h"

class AObstaculoMuro;
class AcomponentePlataforma;
class ADonkeyKong_L02Character;
class ABarril;
class AEsfera;
class AEnemyFacade;

UCLASS()
class ADonkeyKong_L02GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADonkeyKong_L02GameMode();

	AObstaculoMuro* obstaculo01;
	ADonkeyKong_L02Character* player01;
	AEnemyFacade* EnemyFacade;

	TArray<AcomponentePlataforma*> componentesPlataforma;
	TArray<ABarril*> barriles;
	TMap<int32, AEsfera*> esferasMap;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle SpawnBarrilTimerHandle;
	void SpawnBarril();

	int32 contadorBarriles;
	const int32 numeroMaximoBarriles = 3;
};



