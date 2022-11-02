#pragma once
class CollisionManager
{
private:
	// �̱���
	static std::shared_ptr<CollisionManager> instance_;
	static std::once_flag flag_;

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
};

