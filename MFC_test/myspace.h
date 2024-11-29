#pragma once

#include <opencv2/opencv.hpp>

namespace my {
	CImage* MatToCImage(const cv::Mat& mat)
	{
		CImage* pImage = new CImage();

		if (mat.channels() == 3) {
			pImage->Create(mat.cols, mat.rows, 24); // 24��Ʈ �÷� �̹���
		}
		else if (mat.channels() == 1) {
			pImage->Create(mat.cols, mat.rows, 8);  // ��� �̹���
		}
		else {
			return nullptr; // �������� �ʴ� ä�� ��
		}

		BITMAPINFO bitInfo;
		bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitInfo.bmiHeader.biWidth = mat.cols;
		bitInfo.bmiHeader.biHeight = -mat.rows; // �̹����� ���� �������� �ʵ��� ���� ���� ����
		bitInfo.bmiHeader.biPlanes = 1;
		bitInfo.bmiHeader.biBitCount = mat.channels() * 8;
		bitInfo.bmiHeader.biCompression = BI_RGB;

		CDC* pDC = CDC::FromHandle(pImage->GetDC());
		StretchDIBits(
			pDC->m_hDC,
			0, 0, mat.cols, mat.rows,
			0, 0, mat.cols, mat.rows,
			mat.data,
			&bitInfo,
			DIB_RGB_COLORS,
			SRCCOPY
		);

		pImage->ReleaseDC();
		return pImage;
	}

}











