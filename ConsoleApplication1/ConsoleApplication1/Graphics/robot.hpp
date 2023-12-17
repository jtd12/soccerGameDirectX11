#pragma once
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

using namespace DirectX;



class Model_robot
{
public:
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* texture2, ConstantBuffer<CB_VS_vertexshader>& cb_vs_vertexshader);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void Draw(const XMMATRIX& viewProjectionMatrix);

	bool movement(const XMFLOAT3& playerLoc,float sp);
	XMFLOAT3 normalized(XMFLOAT3 a_vector);
	const XMVECTOR& GetPositionVector() const;
	const XMFLOAT3& GetPositionFloat3() const;
	const XMVECTOR& GetRotationVector() const;
	const XMFLOAT3& GetRotationFloat3() const;

	void SetPosition(const XMVECTOR& pos);
	void SetPosition(const XMFLOAT3& pos);
	void SetPosition(float x, float y, float z);
	void AdjustPosition(const XMVECTOR& pos);
	void AdjustPosition(const XMFLOAT3& pos);
	void AdjustPosition(float x, float y, float z);
	void SetRotation(const XMVECTOR& rot);
	void SetRotation(const XMFLOAT3& rot);
	void SetRotation(float x, float y, float z);
	void AdjustRotation(const XMVECTOR& rot);
	void AdjustRotation(const XMFLOAT3& rot);
	void AdjustRotation(float x, float y, float z);
	void SetLookAtPos(XMFLOAT3 lookAtPos);
	const XMVECTOR& GetForwardVector();
	const XMVECTOR& GetRightVector();
	const XMVECTOR& GetBackwardVector();
	const XMVECTOR& GetLeftVector();
private:
	void UpdateWorldMatrix();

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	ConstantBuffer<CB_VS_vertexshader>* cb_vs_vertexshader = nullptr;
	ConstantBuffer<CB_VS_vertexshader>* cb_vs_vertexshader2 = nullptr;
	ConstantBuffer<CB_VS_vertexshader>* cb_vs_vertexshader3 = nullptr;
	ConstantBuffer<CB_VS_vertexshader>* cb_vs_vertexshader4 = nullptr;
	ConstantBuffer<CB_VS_vertexshader>* cb_vs_vertexshader5 = nullptr;
	ConstantBuffer<CB_VS_vertexshader>* cb_vs_vertexshader6 = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;
	ID3D11ShaderResourceView* texture2 = nullptr;

	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;

	VertexBuffer<Vertex> vertexBuffer2;
	IndexBuffer indexBuffer2;

	VertexBuffer<Vertex> vertexBuffer3;
	IndexBuffer indexBuffer3;

	VertexBuffer<Vertex> vertexBuffer4;
	IndexBuffer indexBuffer4;


	VertexBuffer<Vertex> vertexBuffer5;
	IndexBuffer indexBuffer5;

	VertexBuffer<Vertex> vertexBuffer6;
	IndexBuffer indexBuffer6;

	XMMATRIX worldMatrix_final = XMMatrixIdentity();
	XMMATRIX worldMatrix = XMMatrixIdentity();
	XMMATRIX worldMatrix2 = XMMatrixIdentity();
	XMMATRIX worldMatrix3 = XMMatrixIdentity();
	XMMATRIX worldMatrix4 = XMMatrixIdentity();
	XMMATRIX worldMatrix5 = XMMatrixIdentity();
	XMMATRIX worldMatrix6 = XMMatrixIdentity();

	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_BACKWARD_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR vec_forward;
	XMVECTOR vec_left;
	XMVECTOR vec_right;
	XMVECTOR vec_backward;
};