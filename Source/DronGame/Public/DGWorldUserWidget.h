// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DGWorldUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class DRONGAME_API UDGWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldOffset;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (ExposeOnSpawn = true))
	AActor* AttachedActor;
	
};
