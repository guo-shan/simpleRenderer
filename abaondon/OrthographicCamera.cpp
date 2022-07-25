#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) {
	m_ViewMatrix = glm::mat4(1.0f);
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
	m_ViewProjectionMatrix = m_ProjectionMatrix;
	m_ProjectionCoords = { left, right, bottom, top };
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
	m_ProjectionCoords = { left, right, bottom, top };
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix() {
	Mat4d transform = glm::translate(Mat4d(1.0f), m_Position) *
		glm::rotate(Mat4d(1.0f), glm::radians(m_Rotation), Vec3d(0, 0, 1));

	transform = glm::inverse(transform);
	transform = glm::scale(glm::mat4d(transform), Vec3d(m_Scale));

	Mat4d transform_ = glm::translate(Mat4d(1.0f), Vec3d(1.0f, 1.0f, 0.0f)) *
		glm::rotate(Mat4d(1.0f), glm::radians(m_Rotation), Vec3d(0, 0, 1));

	transform_ = glm::inverse(transform_);
	transform_ = glm::scale(Mat4d(transform_), Vec3d(m_Scale));

	m_TransformMatrix = transform_;

	m_ViewMatrix = transform;
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}