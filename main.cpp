#include <Novice.h>
#include "Ball.h"
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

	Ball ball;
	ball.Initialize();


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


		ball.Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ball.Draw();

		Novice::DrawLine(int(startLine.x), int(startLine.y), int(endLine.x), int(endLine.y), 0xFFFFFFFF);

		
		
		//Novice::ScreenPrintf(0, 0, "%d", ball.bouncing);
		//Novice::ScreenPrintf(0, 20, "%f", ball.positionY);
		//Novice::ScreenPrintf(0, 40, "%f", abs(ball.velocityY));
		//Novice::ScreenPrintf(0, 60, "%f", ball.velocityX);
		//Novice::ScreenPrintf(0, 80, "%d", ball.isFalling);
		//Novice::ScreenPrintf(0, 100, "%f", ball.angle);
		

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
