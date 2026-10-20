#pragma once

#include "CoreMinimal.h"
#include "MisionTipos.generated.h"

UENUM()
enum class ETipoObjetivoMision : uint8
{
	Recolectar,
	Interactuar
};

USTRUCT()
struct FObjetivoMision
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Mision")
	FName IDObjetivo = NAME_None;

	UPROPERTY(EditAnywhere, Category = "Mision")
	FText Nombre;

	UPROPERTY(EditAnywhere, Category = "Mision")
	ETipoObjetivoMision TipoObjetivo = ETipoObjetivoMision::Recolectar;

	UPROPERTY(EditAnywhere, Category = "Mision")
	FName IDDestino = NAME_None;

	UPROPERTY(EditAnywhere, Category = "Mision")
	int32 CantidadRequerida = 1;

	UPROPERTY()
	int32 CantidadActual = 0;
};

USTRUCT()
struct FMisionEnEjecucion
{
	GENERATED_BODY()

	UPROPERTY()
	FName IDMision = NAME_None;

	UPROPERTY()
	FText NombreMision;

	UPROPERTY()
	TArray<FObjetivoMision> Objetivos;

	UPROPERTY()
	bool bEstaActiva = true;

	UPROPERTY()
	bool bEstaCompletada = false;
};
