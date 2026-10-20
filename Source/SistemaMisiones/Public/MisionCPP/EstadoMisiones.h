#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MisionCPP/MisionTipos.h"
#include "EstadoMisiones.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(
	FEventoObjetivoReportado,
	ETipoObjetivoMision,
	FName,
	int32);

UCLASS()
class SISTEMAMISIONES_API AEstadoMisiones : public AGameStateBase
{
	GENERATED_BODY()

public:
	void ReportarEventoObjetivo(
		ETipoObjetivoMision TipoObjetivo,
		FName IDDestino,
		int32 Cantidad);

	FEventoObjetivoReportado AlReportarEventoObjetivo;
};
