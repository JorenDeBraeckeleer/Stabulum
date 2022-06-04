#pragma once
#include "BaseComponent.h"
#include "TileComponent.h"

class TransformComponent;

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

	void Dropped();

private:
	std::vector<GameObject*> m_pIngredientParts;

	TransformComponent* m_pTransformComponent;
	Ingredient m_Ingredient;
	const std::string m_SpriteSheet;

	bool m_IsUpdateNeeded;
};