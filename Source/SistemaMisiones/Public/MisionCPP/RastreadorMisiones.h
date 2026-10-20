#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MisionCPP/MisionTipos.h"
#include "RastreadorMisiones.generated.h"

class UComponenteMisiones;
class UTextBlock;

UCLASS()
class SISTEMAMISIONES_API URastreadorMisiones : public UUserWidget
{
	GENERATED_BODY()

public:
	void VincularComponente(UComponenteMisiones* ComponenteMisiones);

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeDestruct() override;

private:
	void ActualizarRastreador(const FMisionEnEjecucion& Mision);
	void MostrarMisionCompletada(const FMisionEnEjecucion& Mision);

	TWeakObjectPtr<UComponenteMisiones> ComponenteVinculado;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> TextoTitulo;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> TextoMision;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> TextoObjetivo;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> TextoEstado;
};
