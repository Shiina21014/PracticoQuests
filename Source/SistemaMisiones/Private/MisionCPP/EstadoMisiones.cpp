#include "MisionCPP/EstadoMisiones.h"

void AEstadoMisiones::ReportarEventoObjetivo(
	ETipoObjetivoMision TipoObjetivo,
	FName IDDestino,
	int32 Cantidad)
{
	AlReportarEventoObjetivo.Broadcast(
		TipoObjetivo,
		IDDestino,
		Cantidad);
}
