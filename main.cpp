#include <Novice.h>
#include "Ball.h"
#include "Surface.h"
#include <imgui.h>

typedef struct vector2
{
	float x;
	float y;
}vector2;

const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	Ball ball(10.0f, 25.0f, 25.0f, 0.0f , 10.0f,9.8f, 300.0f , 200.0f, 0.5f, 0.3f);
	Surface concrete(0.5f, 0.3f);


	float ground = 600.0;
	float timeStep = 0.03f;
	//float restitution = 0.5;

	vector2 startLine = { 0,600.0f };
	vector2 endLine = { 1280,600.0f };
	

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///



		if (preKeys[DIK_R] == 0 && keys[DIK_R] != 0) {
			
			ball.positionX = 300.0f;
			ball.positionY = 200.0f;
			ball.velocityX = 0.0f;
			ball.velocityY = 10.0f;
			ball.radiusX = ball.initialRadiusX;
			ball.radiusY = ball.initialRadiusY;
			ball.bouncing = false;
			ball.bounceTime = 0.0f;
		}



		if (ball.positionY + ball.radiusY < ground) {
			ball.updatePosition(timeStep);
		} else {
			ball.collide(concrete);
			if (std::abs(ball.velocityY) < 0.5f) {  
				ball.radiusX = ball.initialRadiusX; 
				ball.radiusY = ball.initialRadiusY; 
				ball.bouncing = false;
			} else {
				ball.radiusX /= 1.5f; 
				ball.radiusY /= 0.8f; 
			}
		}

		if (ball.bouncing) {
			ball.bounceTime += timeStep;
			if (ball.bounceTime >= 0.1f) {
				ball.radiusX /= 0.8f;
				ball.radiusY /= 1.2f;
				ball.bouncing = false;
				if (ball.bounceTime <= 0.3f) {
					ball.radiusX = ball.initialRadiusX;
					ball.radiusY = ball.initialRadiusY;
				    ball.bounceTime = 0.0f;
				}
			} 
			
		}

		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse(int(ball.positionX), int(ball.positionY), int(ball.radiusX), int(ball.radiusY), 0.0f, 0xFFFFFFFF, kFillModeSolid);

		Novice::DrawLine(int(startLine.x), int(startLine.y), int(endLine.x), int(endLine.y), 0xFFFFFFFF);

		ImGui::Begin("Window");
		ImGui::SliderFloat("floor Restitution", &concrete.restitution, 0.0f, 1.0f, "Restitution = %.3f");
		ImGui::SliderFloat("floor Friction", &concrete.friction, 0.0f, 1.0f, "Friction = %.3f");
		ImGui::SliderFloat("ball Restitution", &ball.restitution, 0.0f, 1.0f, "Restitution = %.3f");
		ImGui::SliderFloat("ball Friction", &ball.friction, 0.0f, 1.0f, "Friction = %.3f");
		ImGui::SliderFloat("ball velocityX", &ball.restitution, 0.0f, 10.0f, "velocityX = %.3f");
		ImGui::SliderFloat("ball velocityY", &ball.friction, 0.0f, 10.0f, "velocityY = %.3f");
		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
