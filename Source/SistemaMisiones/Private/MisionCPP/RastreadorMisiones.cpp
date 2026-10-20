#include "MisionCPP/RastreadorMisiones.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "MisionCPP/ComponenteMisiones.h"
#include "Styling/CoreStyle.h"

TSharedRef<SWidget> URastreadorMisiones::RebuildWidget()
{
    UCanvasPanel* PanelRaiz = WidgetTree->ConstructWidget<UCanvasPanel>(
        UCanvasPanel::StaticClass(),
        TEXT("PanelRaiz"));

    WidgetTree->RootWidget = PanelRaiz;

    UVerticalBox* CajaMisiones = WidgetTree->ConstructWidget<UVerticalBox>(
        UVerticalBox::StaticClass(),
        TEXT("CajaMisiones"));

    UCanvasPanelSlot* SlotCaja = PanelRaiz->AddChildToCanvas(CajaMisiones);
    SlotCaja->SetAnchors(FAnchors(1.0f, 0.0f));
    SlotCaja->SetAlignment(FVector2D(1.0f, 0.0f));
    SlotCaja->SetPosition(FVector2D(-40.0f, 40.0f));
    SlotCaja->SetSize(FVector2D(430.0f, 220.0f));

    TextoTitulo = WidgetTree->ConstructWidget<UTextBlock>(
        UTextBlock::StaticClass(),
        TEXT("TextoTitulo"));
    TextoTitulo->SetText(FText::FromString(TEXT("MISIONES")));
    TextoTitulo->SetFont(FCoreStyle::GetDefaultFontStyle("Bold", 26));
    TextoTitulo->SetColorAndOpacity(FSlateColor(FLinearColor::White));

    UVerticalBoxSlot* SlotTitulo = CajaMisiones->AddChildToVerticalBox(TextoTitulo);
    SlotTitulo->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 12.0f));

    TextoMision = WidgetTree->ConstructWidget<UTextBlock>(
        UTextBlock::StaticClass(),
        TEXT("TextoMision"));
    TextoMision->SetText(FText::FromString(TEXT("Misión: sin misión activa")));
    TextoMision->SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 20));

    UVerticalBoxSlot* SlotMision = CajaMisiones->AddChildToVerticalBox(TextoMision);
    SlotMision->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 6.0f));

    TextoObjetivo = WidgetTree->ConstructWidget<UTextBlock>(
        UTextBlock::StaticClass(),
        TEXT("TextoObjetivo"));
    TextoObjetivo->SetText(FText::FromString(TEXT("Objetivo: —")));
    TextoObjetivo->SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 18));

    UVerticalBoxSlot* SlotObjetivo = CajaMisiones->AddChildToVerticalBox(TextoObjetivo);
    SlotObjetivo->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 6.0f));

    TextoEstado = WidgetTree->ConstructWidget<UTextBlock>(
        UTextBlock::StaticClass(),
        TEXT("TextoEstado"));
    TextoEstado->SetText(FText::GetEmpty());
    TextoEstado->SetFont(FCoreStyle::GetDefaultFontStyle("Bold", 18));
    TextoEstado->SetColorAndOpacity(FSlateColor(FLinearColor::Green));

    CajaMisiones->AddChildToVerticalBox(TextoEstado);

    return Super::RebuildWidget();
}

void URastreadorMisiones::VincularComponente(
    UComponenteMisiones* ComponenteMisiones)
{
    if (!IsValid(ComponenteMisiones))
    {
        return;
    }

    if (ComponenteVinculado.IsValid())
    {
        ComponenteVinculado->AlIniciarMision.RemoveAll(this);
        ComponenteVinculado->AlCambiarProgreso.RemoveAll(this);
        ComponenteVinculado->AlCompletarMision.RemoveAll(this);
    }

    ComponenteVinculado = ComponenteMisiones;

    ComponenteMisiones->AlIniciarMision.AddUObject(
        this,
        &URastreadorMisiones::ActualizarRastreador);

    ComponenteMisiones->AlCambiarProgreso.AddUObject(
        this,
        &URastreadorMisiones::ActualizarRastreador);

    ComponenteMisiones->AlCompletarMision.AddUObject(
        this,
        &URastreadorMisiones::MostrarMisionCompletada);
}

void URastreadorMisiones::NativeDestruct()
{
    if (ComponenteVinculado.IsValid())
    {
        ComponenteVinculado->AlIniciarMision.RemoveAll(this);
        ComponenteVinculado->AlCambiarProgreso.RemoveAll(this);
        ComponenteVinculado->AlCompletarMision.RemoveAll(this);
    }

    Super::NativeDestruct();
}

void URastreadorMisiones::ActualizarRastreador(
    const FMisionEnEjecucion& Mision)
{
    if (!IsValid(TextoMision) || !IsValid(TextoObjetivo) || Mision.Objetivos.IsEmpty())
    {
        return;
    }

    const FObjetivoMision& Objetivo = Mision.Objetivos[0];

    TextoMision->SetText(FText::Format(
        FText::FromString(TEXT("Misión: {0}")),
        Mision.NombreMision));

    TextoObjetivo->SetText(FText::Format(
        FText::FromString(TEXT("{0}: {1}/{2}")),
        Objetivo.Nombre,
        FText::AsNumber(Objetivo.CantidadActual),
        FText::AsNumber(Objetivo.CantidadRequerida)));

    if (IsValid(TextoEstado))
    {
        TextoEstado->SetText(FText::GetEmpty());
    }
}

void URastreadorMisiones::MostrarMisionCompletada(
    const FMisionEnEjecucion& Mision)
{
    ActualizarRastreador(Mision);

    if (IsValid(TextoEstado))
    {
        TextoEstado->SetText(FText::FromString(TEXT("MISIÓN COMPLETADA")));
    }
}
