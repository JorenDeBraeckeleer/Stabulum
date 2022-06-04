#include "BurgerTimePCH.h"
#include "BurgerComponent.h"

#include "TransformComponent.h"
#include "TextureTransformComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"

BurgerComponent::BurgerComponent(TransformComponent* pTransformComponent, const Ingredient& ingredient, const std::string& filename)
	: m_pIngredientParts{}
	, m_pTransformComponent{ pTransformComponent }
	, m_Ingredient{ ingredient }
	, m_SpriteSheet{ filename }
	, m_IsUpdateNeeded{ true }
{
}

BurgerComponent::~BurgerComponent()
{
	for (GameObject* pObj : m_pIngredientParts)
	{
		delete pObj;
		pObj = nullptr;
	}
}

void BurgerComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		int width{ 16 };

		for (int idx{}; idx < 4; ++idx)
		{
			GameObject* pGameObject{ new GameObject{} };
			m_pIngredientParts.emplace_back(pGameObject);

			switch (m_Ingredient)
			{
			case Ingredient::BunBottom:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 16, 16, 16);
				break;
			case Ingredient::BunTop:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 0, 16, 16);
				break;
			case Ingredient::Cheese:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 32, 16, 16);
				break;
			case Ingredient::Lettuce:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 80, 16, 16);
				break;
			case Ingredient::Meat:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 48, 16, 16);
				break;
			case Ingredient::Tomato:
				pGameObject->AddComponent<TextureTransformComponent>(width * idx, 64, 16, 16);
				break;
			default:
				break;
			}

			FVec2 pos{ m_pTransformComponent->GetUnitPosition() };
			TransformComponent* pTfc = pGameObject->AddComponent<TransformComponent>(16.f * idx, 0.f);
			RigidBodyComponent* pRdb = pGameObject->AddComponent<RigidBodyComponent>(pTfc, RigidBodyComponent::BodyType::Dynamic);
			pGameObject->AddComponent<BoxColliderComponent>(pRdb, 0.5f, 0.5f, 0.25f, 0.25f)->SetSensor();
			pGameObject->AddComponent<RenderComponent>(pTfc, m_SpriteSheet);

			GetGameObject()->AddChild(pGameObject);
		}

		m_IsUpdateNeeded = false;
	}
}

void BurgerComponent::Dropped()
{
	Notify(m_pGameObject, GameEvent::BurgerDropped);
}