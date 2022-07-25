#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Math/Matrix.h"
#include "Math/Vec.h"

class OrthographicCamera {
public:
	OrthographicCamera(double left, double right, double bottom, double top);

	void SetProjection(double left, double right, double bottom, double top);

	void SetPosition(const Vec3d& position) {
		m_Position = position;
		RecalculateViewMatrix();
	}

	void SetRotation(double rotation) {
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void SetScale(const Vec3d& scale_factor) {
		m_Scale = scale_factor;
		RecalculateViewMatrix();
	}

	float GetRotation() const { return m_Rotation; }
	const Vec4d& GetProjectionCoords() { return m_ProjectionCoords; }
	const Vec3d& GetPosition() { return m_Position; }
	const Mat4d& GetProjectionMatrix() { return m_ProjectionMatrix; }
	const Mat4d& GetViewMatrix() { return m_ViewMatrix; }
	const Mat4d& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
	const Vec3d& GetScale() { return m_Scale; }
	const Mat4d& GetTransformMatrix() { return m_TransformMatrix; }

private:

	void RecalculateViewMatrix();

private:
	Mat4d m_ProjectionMatrix;
	Mat4d m_ViewMatrix;
	Mat4d m_ViewProjectionMatrix;
	Mat4d m_TransformMatrix;

	Vec3d m_Position = { 0.0, 0.0, 0.0 };
	Vec4d m_ProjectionCoords = { 0.0, 0.0, 0.0, 0.0 };
	Vec3d m_Scale = { 1.0, 1.0, 0.0 };

	double m_Rotation = 0.0;
};