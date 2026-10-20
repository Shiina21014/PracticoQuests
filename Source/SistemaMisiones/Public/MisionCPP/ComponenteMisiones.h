#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MisionCPP/MisionTipos.h"
#include "ComponenteMisiones.generated.h"

class UMisionDefinicion;

DECLARE_MULTICAST_DELEGATE_OneParam(FMisionActualizada, const FMisionEnEjecucion&);

UCLASS(ClassGroup = (Mision), meta = (BlueprintSpawnableComponent))
class SISTEMAMISIONES_API UComponenteMisiones : public UActorComponent
{
	GENERATED_BODY()

public:
	UComponenteMisiones();

	bool AgregarMision(UMisionDefinicion* DefinicionMision);

	bool EstaMisionCompletada(FName IDMision) const;

	FMisionActualizada AlIniciarMision;
	FMisionActualizada AlCambiarProgreso;
	FMisionActualizada AlCompletarMision;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void ManejarEventoObjetivo(
		ETipoObjetivoMision TipoObjetivo,
		FName IDDestino,
		int32 Cantidad);

	void ActualizarProgresoObjetivo(
		ETipoObjetivoMision TipoObjetivo,
		FName IDDestino,
		int32 Cantidad);

	FMisionEnEjecucion* BuscarMisionPorID(FName IDMision);
	void ComprobarMisionCompletada(FMisionEnEjecucion& Mision);

	UPROPERTY()
	TArray<FMisionEnEjecucion> MisionesActivas;
};
