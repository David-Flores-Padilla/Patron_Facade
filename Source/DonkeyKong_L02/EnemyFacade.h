#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFacade.generated.h"

// Declaración anticipada de la clase Enemigo
class AEnemigo;

UCLASS()
class DONKEYKONG_L02_API AEnemyFacade : public AActor
{
    GENERATED_BODY()

public:
    AEnemyFacade();

    // Método para crear un enemigo de un tipo específico
    AEnemigo* CrearEnemigo(FString Tipo, FVector Posicion, float Velocidad);

    // Método para eliminar todos los enemigos
    void EliminarTodosLosEnemigos();

private:
    // Almacena todos los enemigos creados
    TArray<AEnemigo*> Enemigos;
};
