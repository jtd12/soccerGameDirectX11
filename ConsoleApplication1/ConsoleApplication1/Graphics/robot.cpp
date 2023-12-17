#include "robot.hpp"

bool Model_robot::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* texture2, ConstantBuffer<CB_VS_vertexshader>& cb_vs_vertexshader)
{
	this->device = device;
	this->deviceContext = deviceContext;
	this->texture = texture;
	this->texture2 = texture2;
	this->cb_vs_vertexshader = &cb_vs_vertexshader;
	this->cb_vs_vertexshader2 = &cb_vs_vertexshader;
	this->cb_vs_vertexshader3 = &cb_vs_vertexshader;
	this->cb_vs_vertexshader4 = &cb_vs_vertexshader;
	this->cb_vs_vertexshader5 = &cb_vs_vertexshader;
	this->cb_vs_vertexshader6 = &cb_vs_vertexshader;

	try
	{
		//Textured Square
		Vertex v[] =
		{
			Vertex(-0.5f,  -0.5f, -0.5f, 0.0f, 1.0f), //FRONT Bottom Left   - [0]
			Vertex(-0.5f,   0.5f, -0.5f, 0.0f, 0.0f), //FRONT Top Left      - [1]
			Vertex(0.5f,   0.5f, -0.5f, 1.0f, 0.0f), //FRONT Top Right     - [2]
			Vertex(0.5f,  -0.5f, -0.5f, 1.0f, 1.0f), //FRONT Bottom Right   - [3]
			Vertex(-0.5f,  -0.5f, 0.5f, 0.0f, 1.0f), //BACK Bottom Left   - [4]
			Vertex(-0.5f,   0.5f, 0.5f, 0.0f, 0.0f), //BACK Top Left      - [5]
			Vertex(0.5f,   0.5f, 0.5f, 1.0f, 0.0f), //BACK Top Right     - [6]
			Vertex(0.5f,  -0.5f, 0.5f, 1.0f, 1.0f), //BACK Bottom Right   - [7]
		};

		//Load Vertex Data
		HRESULT hr = this->vertexBuffer.Initialize(this->device, v, ARRAYSIZE(v));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize vertex buffer.");

		hr = this->vertexBuffer2.Initialize(this->device, v, ARRAYSIZE(v));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize vertex buffer.");

		hr = this->vertexBuffer3.Initialize(this->device, v, ARRAYSIZE(v));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize vertex buffer.");

		hr = this->vertexBuffer4.Initialize(this->device, v, ARRAYSIZE(v));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize vertex buffer.");

		hr = this->vertexBuffer5.Initialize(this->device, v, ARRAYSIZE(v));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize vertex buffer.");

		hr = this->vertexBuffer6.Initialize(this->device, v, ARRAYSIZE(v));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize vertex buffer.");

		DWORD indices[] =
		{
			0, 1, 2, //FRONT
			0, 2, 3, //FRONT
			4, 7, 6, //BACK 
			4, 6, 5, //BACK
			3, 2, 6, //RIGHT SIDE
			3, 6, 7, //RIGHT SIDE
			4, 5, 1, //LEFT SIDE
			4, 1, 0, //LEFT SIDE
			1, 5, 6, //TOP
			1, 6, 2, //TOP
			0, 3, 7, //BOTTOM
			0, 7, 4, //BOTTOM
		};

		//Load Index Data
		hr = this->indexBuffer.Initialize(this->device, indices, ARRAYSIZE(indices));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer.");

		hr = this->indexBuffer2.Initialize(this->device, indices, ARRAYSIZE(indices));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer.");

		hr = this->indexBuffer3.Initialize(this->device, indices, ARRAYSIZE(indices));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer.");

		hr = this->indexBuffer4.Initialize(this->device, indices, ARRAYSIZE(indices));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer.");

		hr = this->indexBuffer5.Initialize(this->device, indices, ARRAYSIZE(indices));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer.");

		hr = this->indexBuffer6.Initialize(this->device, indices, ARRAYSIZE(indices));
		COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer.");
	}
	catch (COMException& exception)
	{
		ErrorLogger::Log(exception);
		return false;
	}

	this->SetPosition(0.0f, 0.0f, 0.0f);
	this->SetRotation(0.0f, 0.0f, 0.0f);
	this->UpdateWorldMatrix();
	return true;
}

void Model_robot::SetTexture(ID3D11ShaderResourceView* texture)
{
	this->texture = texture;
}

void Model_robot::Draw(const XMMATRIX& viewProjectionMatrix)
{
	//Update Constant buffer with WVP Matrix
	this->cb_vs_vertexshader->data.mat = this->worldMatrix* this->worldMatrix_final *viewProjectionMatrix; //Calculate World-View-Projection Matrix
	this->cb_vs_vertexshader->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader->data.mat);
	this->cb_vs_vertexshader->ApplyChanges();
	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader->GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, &this->texture); //Set Texture
	this->deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
	this->deviceContext->DrawIndexed(this->indexBuffer.BufferSize(), 0, 0); //Draw


	//Update Constant buffer with WVP Matrix
	this->cb_vs_vertexshader2->data.mat = this->worldMatrix2 * this->worldMatrix_final*viewProjectionMatrix; //Calculate World-View-Projection Matrix
	this->cb_vs_vertexshader2->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader2->data.mat);
	this->cb_vs_vertexshader2->ApplyChanges();
	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader2->GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, &this->texture2); //Set Texture
	this->deviceContext->IASetIndexBuffer(this->indexBuffer2.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer2.GetAddressOf(), this->vertexBuffer2.StridePtr(), &offset);
	this->deviceContext->DrawIndexed(this->indexBuffer2.BufferSize(), 0, 0); //Draw



	//Update Constant buffer with WVP Matrix
	this->cb_vs_vertexshader3->data.mat = this->worldMatrix3 * this->worldMatrix_final * viewProjectionMatrix; //Calculate World-View-Projection Matrix
	this->cb_vs_vertexshader3->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader3->data.mat);
	this->cb_vs_vertexshader3->ApplyChanges();
	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader3->GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, &this->texture); //Set Texture
	this->deviceContext->IASetIndexBuffer(this->indexBuffer3.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer3.GetAddressOf(), this->vertexBuffer3.StridePtr(), &offset);
	this->deviceContext->DrawIndexed(this->indexBuffer3.BufferSize(), 0, 0); //Draw


	//Update Constant buffer with WVP Matrix
	this->cb_vs_vertexshader4->data.mat = this->worldMatrix4 * this->worldMatrix_final * viewProjectionMatrix; //Calculate World-View-Projection Matrix
	this->cb_vs_vertexshader4->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader4->data.mat);
	this->cb_vs_vertexshader4->ApplyChanges();
	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader4->GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, &this->texture); //Set Texture
	this->deviceContext->IASetIndexBuffer(this->indexBuffer4.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer4.GetAddressOf(), this->vertexBuffer4.StridePtr(), &offset);
	this->deviceContext->DrawIndexed(this->indexBuffer4.BufferSize(), 0, 0); //Draw


	//Update Constant buffer with WVP Matrix
	this->cb_vs_vertexshader5->data.mat = this->worldMatrix5 * this->worldMatrix_final * viewProjectionMatrix; //Calculate World-View-Projection Matrix
	this->cb_vs_vertexshader5->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader5->data.mat);
	this->cb_vs_vertexshader5->ApplyChanges();
	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader5->GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, &this->texture); //Set Texture
	this->deviceContext->IASetIndexBuffer(this->indexBuffer5.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer5.GetAddressOf(), this->vertexBuffer5.StridePtr(), &offset);
	this->deviceContext->DrawIndexed(this->indexBuffer4.BufferSize(), 0, 0); //Draw


	//Update Constant buffer with WVP Matrix
	this->cb_vs_vertexshader6->data.mat = this->worldMatrix6 * this->worldMatrix_final * viewProjectionMatrix; //Calculate World-View-Projection Matrix
	this->cb_vs_vertexshader6->data.mat = XMMatrixTranspose(this->cb_vs_vertexshader6->data.mat);
	this->cb_vs_vertexshader6->ApplyChanges();
	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader6->GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, &this->texture); //Set Texture
	this->deviceContext->IASetIndexBuffer(this->indexBuffer6.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer6.GetAddressOf(), this->vertexBuffer6.StridePtr(), &offset);
	this->deviceContext->DrawIndexed(this->indexBuffer6.BufferSize(), 0, 0); //Draw
	
}

void Model_robot::UpdateWorldMatrix()
{
	this->worldMatrix_final =  XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	this->worldMatrix =  XMMatrixRotationRollPitchYaw(0, this->rot.y, 0) * XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixTranslation(0.0f, -2.1f, 0);
	this->worldMatrix3 =   XMMatrixScaling(0.5f, 1.5f, 0.5f) * XMMatrixTranslation(0.9f, -3.0f, 0)* XMMatrixRotationRollPitchYaw(0, this->rot.y, 0);
	this->worldMatrix4 = XMMatrixScaling(0.5f, 1.5f, 0.5f) * XMMatrixTranslation(-0.9f, -3.0f, 0) * XMMatrixRotationRollPitchYaw(0, this->rot.y, 0);
	this->worldMatrix5 = XMMatrixScaling(0.5f, 2.25f, 0.5f) * XMMatrixTranslation(-0.45f, -4.9f, 0) * XMMatrixRotationRollPitchYaw(0, this->rot.y, 0);
	this->worldMatrix6 = XMMatrixScaling(0.5f, 2.25f, 0.5f) * XMMatrixTranslation(0.45f, -4.9f, 0) * XMMatrixRotationRollPitchYaw(0, this->rot.y, 0);
	this->worldMatrix2 = XMMatrixRotationRollPitchYaw(0, this->rot.y, 0) * XMMatrixScaling(1.0f, 1.0f, 1.0f)*XMMatrixTranslation(0.0f, -3.0f, 0) ;
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}

XMFLOAT3 Model_robot::normalized(XMFLOAT3 a_vector)
{
	float length = sqrt(a_vector.x * a_vector.x + a_vector.y * a_vector.y + a_vector.z * a_vector.z);
	/*
	if (length!=0)
	{
		a_vector.x /= length;
		a_vector.y /= length;
		a_vector.z /= length;
	}
	*/
	if (length != 0) return XMFLOAT3(a_vector.x /= length, a_vector.y /= length, a_vector.z /= length);
}



bool Model_robot::movement(const XMFLOAT3& playerLoc,float sp)
{

	XMFLOAT3 newpos(GetPositionFloat3());

	XMFLOAT3 direction = normalized(XMFLOAT3(playerLoc.x-GetPositionFloat3().x, playerLoc.y - GetPositionFloat3().y, playerLoc.z - GetPositionFloat3().z));
	

	newpos.y -= 0.25f;
	if (newpos.y <= 8.0f)
	{
		newpos.y = 8.0f;
	}

	newpos.x += 0.1f * direction.x;
	newpos.y += 0.1f * direction.y;
	newpos.z += 0.1f * direction.z;

	SetPosition(newpos);

	this->rot.y  = acos(direction.z*sp);
	if (direction.z >0)
	{
		this->rot.y = -this->rot.y;
	}
	return true;
}

const XMVECTOR& Model_robot::GetPositionVector() const
{
	return this->posVector;
}

const XMFLOAT3& Model_robot::GetPositionFloat3() const
{
	return this->pos;
}

const XMVECTOR& Model_robot::GetRotationVector() const
{
	return this->rotVector;
}

const XMFLOAT3& Model_robot::GetRotationFloat3() const
{
	return this->rot;
}

void Model_robot::SetPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateWorldMatrix();
}

void Model_robot::SetPosition(const XMFLOAT3& pos)
{
	this->pos = pos;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void Model_robot::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void Model_robot::AdjustPosition(const XMVECTOR& pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateWorldMatrix();
}

void Model_robot::AdjustPosition(const XMFLOAT3& pos)
{
	this->pos.x += pos.y;
	this->pos.y += pos.y;
	this->pos.z += pos.z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void Model_robot::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void Model_robot::SetRotation(const XMVECTOR& rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateWorldMatrix();
}

void Model_robot::SetRotation(const XMFLOAT3& rot)
{
	this->rot = rot;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void Model_robot::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void Model_robot::AdjustRotation(const XMVECTOR& rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateWorldMatrix();
}

void Model_robot::AdjustRotation(const XMFLOAT3& rot)
{
	this->rot.x += rot.x;
	this->rot.y += rot.y;
	this->rot.z += rot.z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void Model_robot::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void Model_robot::SetLookAtPos(XMFLOAT3 lookAtPos)
{
	//Verify that look at pos is not the same as cam pos. They cannot be the same as that wouldn't make sense and would result in undefined behavior.
	if (lookAtPos.x == this->pos.x && lookAtPos.y == this->pos.y && lookAtPos.z == this->pos.z)
		return;

	lookAtPos.x = this->pos.x - lookAtPos.x;
	lookAtPos.y = this->pos.y - lookAtPos.y;
	lookAtPos.z = this->pos.z - lookAtPos.z;

	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f)
	{
		const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch = atan(lookAtPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f)
	{
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0)
		yaw += XM_PI;

	this->SetRotation(pitch, yaw, 0.0f);
}

const XMVECTOR& Model_robot::GetForwardVector()
{
	return this->vec_forward;
}

const XMVECTOR& Model_robot::GetRightVector()
{
	return this->vec_right;
}

const XMVECTOR& Model_robot::GetBackwardVector()
{
	return this->vec_backward;
}

const XMVECTOR& Model_robot::GetLeftVector()
{
	return this->vec_left;
}