#include "MisionCPP/ComponenteMisiones.h"

#include "MisionCPP/EstadoMisiones.h"
#include "MisionCPP/MisionDefinicion.h"

UComponenteMisiones::UComponenteMisiones()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UComponenteMisiones::BeginPlay()
{
    Super::BeginPlay();

    if (AEstadoMisiones* EstadoMisiones = GetWorld()->GetGameState<AEstadoMisiones>())
    {
        EstadoMisiones->AlReportarEventoObjetivo.AddUObject(
            this,
            &UComponenteMisiones::ManejarEventoObjetivo);
    }
}

void UComponenteMisiones::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (AEstadoMisiones* EstadoMisiones = GetWorld()->GetGameState<AEstadoMisiones>())
    {
        EstadoMisiones->AlReportarEventoObjetivo.RemoveAll(this);
    }

    Super::EndPlay(EndPlayReason);
}

bool UComponenteMisiones::AgregarMision(UMisionDefinicion* DefinicionMision)
{
    if (!IsValid(DefinicionMision) || BuscarMisionPorID(DefinicionMision->IDMision) != nullptr)
    {
        return false;
    }

    FMisionEnEjecucion NuevaMision;
    NuevaMision.IDMision = DefinicionMision->IDMision;
    NuevaMision.NombreMision = DefinicionMision->NombreMision;
    NuevaMision.Objetivos = DefinicionMision->Objetivos;
    NuevaMision.bEstaActiva = true;
    NuevaMision.bEstaCompletada = false;

    for (FObjetivoMision& Objetivo : NuevaMision.Objetivos)
    {
        Objetivo.CantidadActual = 0;
    }

    MisionesActivas.Add(NuevaMision);
    AlIniciarMision.Broadcast(NuevaMision);

    return true;
}

void UComponenteMisiones::ManejarEventoObjetivo(
    ETipoObjetivoMision TipoObjetivo,
    FName IDDestino,
    int32 Cantidad)
{
    ActualizarProgresoObjetivo(TipoObjetivo, IDDestino, Cantidad);
}

void UComponenteMisiones::ActualizarProgresoObjetivo(
    ETipoObjetivoMision TipoObjetivo,
    FName IDDestino,
    int32 Cantidad)
{
    for (FMisionEnEjecucion& Mision : MisionesActivas)
    {
        if (!Mision.bEstaActiva || Mision.bEstaCompletada)
        {
            continue;
        }

        for (FObjetivoMision& Objetivo : Mision.Objetivos)
        {
            if (Objetivo.TipoObjetivo == TipoObjetivo && Objetivo.IDDestino == IDDestino)
            {
                Objetivo.CantidadActual = FMath::Clamp(
                    Objetivo.CantidadActual + Cantidad,
                    0,
                    Objetivo.CantidadRequerida);

                AlCambiarProgreso.Broadcast(Mision);
                ComprobarMisionCompletada(Mision);
                return;
            }
        }
    }
}

bool UComponenteMisiones::EstaMisionCompletada(FName IDMision) const
{
    for (const FMisionEnEjecucion& Mision : MisionesActivas)
    {
        if (Mision.IDMision == IDMision)
        {
            return Mision.bEstaCompletada;
        }
    }

    return false;
}

FMisionEnEjecucion* UComponenteMisiones::BuscarMisionPorID(FName IDMision)
{
    for (FMisionEnEjecucion& Mision : MisionesActivas)
    {
        if (Mision.IDMision == IDMision)
        {
            return &Mision;
        }
    }

    return nullptr;
}

void UComponenteMisiones::ComprobarMisionCompletada(FMisionEnEjecucion& Mision)
{
    for (const FObjetivoMision& Objetivo : Mision.Objetivos)
    {
        if (Objetivo.CantidadActual < Objetivo.CantidadRequerida)
        {
            return;
        }
    }

    Mision.bEstaActiva = false;
    Mision.bEstaCompletada = true;
    AlCompletarMision.Broadcast(Mision);
}

