#pragma once

class BoxCollider2D;

union COLLIDER_UID
{
	struct
	{
		UINT group1_uid;
		UINT group2_uid;
	};
	ULONGLONG UID;
};

class CollisionManager
{
private:
	// ΩÃ±€≈Ê
	static std::unique_ptr<CollisionManager> instance_;
	static std::once_flag flag_;

	std::map<ULONGLONG, bool> info;
	bool collision_matrix_[(size_t)GroupObjectType::kEND][(size_t)GroupObjectType::kEND];
public:
	CollisionManager();
	~CollisionManager() = default;

	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	static CollisionManager* GetInstance();

	void Initiate();
	void Update(float delta_time);
	void SetCollisionMatrix(GroupObjectType group1, GroupObjectType group2);
	bool IsCollision(std::shared_ptr<BoxCollider2D> group1, std::shared_ptr<BoxCollider2D> group2);
};

