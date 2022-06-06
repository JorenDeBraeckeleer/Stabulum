#pragma once
#include "BaseComponent.h"
#include "TileComponent.h"

class TransformComponent;
class RigidBodyComponent;
class BurgerPartComponent;

class BurgerComponent final : public BaseComponent, public Subject
{
public:
	BurgerComponent(TransformComponent* pTransformComponent, const Ingredient& ingredient, const std::string& filename = "");

	virtual ~BurgerComponent();
	BurgerComponent(const BurgerComponent& other) = delete;
	BurgerComponent(BurgerComponent&& other) = delete;
	BurgerComponent& operator=(const BurgerComponent& other) = delete;
	BurgerComponent& operator=(BurgerComponent&& other) = delete;

	virtual void Update() override;

	void Dropped(bool givePoints = true);

	void ResetParts();

	void OnTriggerEnter(ColliderComponent* pCollider);
	void OnTriggerExit(ColliderComponent* pCollider);

	bool GetIsOverlapping() { return m_IsOverlapping; }

private:
	std::vector<GameObject*> m_pIngredientParts;
	std::vector<BurgerPartComponent*> m_pBurgerParts;

	TransformComponent* m_pTransformComponent;
	RigidBodyComponent* m_pRigidBodyComponent;

	Ingredient m_Ingredient;
	const std::string m_SpriteSheet;

	int m_BurgerAmount;

	bool m_IsOverlapping;
	bool m_IsUpdateNeeded;
};