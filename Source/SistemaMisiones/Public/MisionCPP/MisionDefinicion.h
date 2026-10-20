#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MisionCPP/MisionTipos.h"
#include "MisionDefinicion.generated.h"

UCLASS()
class SISTEMAMISIONES_API UMisionDefinicion : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Mision")
	FName IDMision = NAME_None;

	UPROPERTY(EditAnywhere, Category = "Mision")
	FText NombreMision;

	UPROPERTY(EditAnywhere, Category = "Mision")
	FText Descripcion;

	UPROPERTY(EditAnywhere, Category = "Mision")
	TArray<FObjetivoMision> Objetivos;
};
