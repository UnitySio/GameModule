#pragma once

class BoxCollider2D;

union ColliderUID
{
	struct
	{
		UINT first_collider_uid;
		UINT second_collider_uid;
	};

	ULONGLONG uid;
};

class CollisionManager
{
private:
	// ΩÃ±€≈Ê
	static std::shared_ptr<CollisionManager> instance_;
	static std::once_flag flag_;

	std::map<ULONGLONG, bool> collision_info_;
	bool collision_matrix_[(size_t)LayerType::kEnd][(size_t)LayerType::kEnd];
public:
	CollisionManager();
	~CollisionManager() = default;

	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	static std::shared_ptr<CollisionManager> GetInstance();

	void Release();

	void PhysicsUpdate();
	void SetCollisionMatrix(LayerType first, LayerType second);

	bool IsCollision(std::shared_ptr<BoxCollider2D> first, std::shared_ptr<BoxCollider2D> second);
};
