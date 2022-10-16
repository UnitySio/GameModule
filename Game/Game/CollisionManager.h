#pragma once

class BoxCollider2D;

union COLLIDER_UID
{
	struct
	{
		UINT first_collider_uid;
		UINT second_collider_uid;
	};

	ULONGLONG UID;
};

class CollisionManager
{
private:
	// ΩÃ±€≈Ê
	static std::shared_ptr<CollisionManager> instance_;
	static std::once_flag flag_;

	std::map<ULONGLONG, bool> collision_info_;
	bool collision_matrix_[(size_t)LayerType::kEND][(size_t)LayerType::kEND];
public:
	CollisionManager();
	~CollisionManager() = default;

	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	static std::shared_ptr<CollisionManager> GetInstance();

	void Release();

	void LateUpdate(float delta_time);
	void SetCollisionMatrix(LayerType first_layer, LayerType second_layer);
	bool IsCollision(std::shared_ptr<BoxCollider2D> first_layer, std::shared_ptr<BoxCollider2D> second_layer);
};

