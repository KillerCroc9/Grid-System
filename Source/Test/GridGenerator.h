// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.h"
#include "GridGenerator.generated.h"

USTRUCT(BlueprintType)
struct FGridActorInfoWrapper {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	AActor* Actor; // Pointer to the actor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	int32 Q; // Coordinates of the actor on the grid

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	int32 R; // Coordinates of the actor on the grid

	FGridActorInfoWrapper() : Actor(nullptr), Q(0), R(0) {}

};


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
	void GenerateGrid(int32 Height, int32 Width);

	UFUNCTION(BlueprintCallable)
	void findNeighbors(int32 Q, int32 R);

	UFUNCTION(BlueprintCallable)
	int32 distanceToTarget(int32 AQ, int32 AR, int32 BQ, int32 BR);

	UFUNCTION(BlueprintCallable)
	TArray<FGridActorInfoWrapper> GetActorInfo();


	// Blueprint variable to set in the Editor or through code
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hexagon")
	TSubclassOf<AHexagon> HexagonBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	float CustomXOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	float CustomXSpacing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	float CustomYSpacing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex")
	float ActorScale;


private:
	Grid _Grid;
};
