// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.h"
#include "GridGenerator.generated.h"


UCLASS(Blueprintable)
class TEST_API AGridGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GenerateGrid();

	UFUNCTION(BlueprintCallable)
	void findNeighbors();

	UFUNCTION(BlueprintCallable)
	void distanceToTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	TSubclassOf<AActor> HexActorEven;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	TSubclassOf<AActor> HexActorOdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	TSubclassOf<AActor> HexActorRaised;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	float CustomXOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	float CustomXSpacing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	float CustomYSpacing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	float ActorScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	int32 q;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	int32 r;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	int32 aq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	int32 ar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	int32 bq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	int32 br;
};
